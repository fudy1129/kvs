/****************************************************************************/
/**
 *  @file   ParticleBasedRenderer.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "ParticleBasedRenderer.h"
#include <kvs/ParticleBuffer>
#include <kvs/PointObject>
#include <kvs/Camera>
#include <kvs/Assert>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
ParticleBasedRenderer::ParticleBasedRenderer():
    m_ref_point( NULL )
{
    BaseClass::setShader( kvs::Shader::Lambert() );

    this->initialize();
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param point [in] pointer to the point object
 *  @param subpixel_level [in] subpixel level
 */
/*==========================================================================*/
ParticleBasedRenderer::ParticleBasedRenderer(
    const kvs::PointObject* point,
    const size_t            subpixel_level ):
    m_ref_point( NULL )
{
    BaseClass::setShader( kvs::Shader::Lambert() );

    this->initialize();
    this->setSubpixelLevel( subpixel_level );
    this->attachPointObject( point );
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
ParticleBasedRenderer::~ParticleBasedRenderer()
{
    this->delete_particle_buffer();
}

/*==========================================================================*/
/**
 *  Rendering.
 *  @param object [in] pointer to the object (PointObject)
 *  @param camera [in] pointet to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void ParticleBasedRenderer::exec(
    kvs::ObjectBase* object,
    kvs::Camera*     camera,
    kvs::Light*      light )
{
    if( !m_enable_rendering ) return;

    kvs::PointObject* point = kvs::PointObject::DownCast( object );
    if ( !m_ref_point ) this->attachPointObject( point );
    if ( point->normals().size() == 0 ) BaseClass::disableShading();

    BaseClass::startTimer();
    this->create_image( point, camera, light );
    BaseClass::drawImage();
    this->clean_particle_buffer();
    BaseClass::stopTimer();
}

/*==========================================================================*/
/**
 *  Attach the point object.
 *  @param point [in] pointer to the point object
 */
/*==========================================================================*/
void ParticleBasedRenderer::attachPointObject( const kvs::PointObject* point )
{
    m_ref_point = point;
}

/*==========================================================================*/
/**
 *  Set the subpixel level.
 *  @param subpixel_level [in] subpixel level
 */
/*==========================================================================*/
void ParticleBasedRenderer::setSubpixelLevel( const size_t subpixel_level )
{
    m_subpixel_level = subpixel_level;
}

/*==========================================================================*/
/**
 *  Initialize.
 */
/*==========================================================================*/
void ParticleBasedRenderer::initialize()
{
    m_enable_rendering = true;
    m_subpixel_level = 1;
    m_buffer = NULL;
}

/*==========================================================================*/
/**
 *  Get the pointer to the point buffer.
 */
/*==========================================================================*/
const kvs::ParticleBuffer* ParticleBasedRenderer::particleBuffer() const
{
    return m_buffer;
}

/*==========================================================================*/
/**
 *  Get the subpixel level.
 */
/*==========================================================================*/
size_t ParticleBasedRenderer::subpixelLevel() const
{
    return m_subpixel_level;
}

/*==========================================================================*/
/**
 *  Be enable rendering.
 */
/*==========================================================================*/
void ParticleBasedRenderer::enableRendering()
{
    m_enable_rendering = true;
}

/*==========================================================================*/
/**
 *  Be disable rendering.
 */
/*==========================================================================*/
void ParticleBasedRenderer::disableRendering()
{
    m_enable_rendering = false;
}

/*==========================================================================*/
/**
 *  Create the point buffer.
 */
/*==========================================================================*/
bool ParticleBasedRenderer::create_particle_buffer(
    const size_t width,
    const size_t height,
    const size_t subpixel_level )
{
    m_buffer = new kvs::ParticleBuffer( width, height, subpixel_level );
    if( !m_buffer ) return( false );

    return( true );
}

/*==========================================================================*/
/**
 *  Clean the particle buffer.
 */
/*==========================================================================*/
void ParticleBasedRenderer::clean_particle_buffer()
{
    m_buffer->clean();
}

/*==========================================================================*/
/**
 *  Delete the particle buffer.
 */
/*==========================================================================*/
void ParticleBasedRenderer::delete_particle_buffer()
{
    if( m_buffer ){ delete m_buffer; m_buffer = NULL; }
}

/*==========================================================================*/
/**
 *  Create the rendering image.
 *  @param point [in] pointer to the point object
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void ParticleBasedRenderer::create_image(
    const kvs::PointObject* point,
    const kvs::Camera*      camera,
    const kvs::Light*       light )
{
    // Create memory region for the buffers, if the screen size is changed.
    if( ( BaseClass::m_width  != camera->windowWidth() ) ||
        ( BaseClass::m_height != camera->windowHeight() ) )
    {
        BaseClass::m_width  = camera->windowWidth();
        BaseClass::m_height = camera->windowHeight();

        BaseClass::m_color_data.allocate( m_width * m_height * 4 );
        BaseClass::m_depth_data.allocate( m_width * m_height );

        this->delete_particle_buffer();
        this->create_particle_buffer(
            BaseClass::m_width,
            BaseClass::m_height,
            m_subpixel_level );
    }

    // Initialize the frame buffers.
    BaseClass::m_color_data.fill( 0 );
    BaseClass::m_depth_data.fill( 0 );

    this->project_particle( point, camera, light );
}

/*==========================================================================*/
/**
 *  Project the particles.
 *  @param point [in] pointer to the point object
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void ParticleBasedRenderer::project_particle(
    const kvs::PointObject* point,
    const kvs::Camera*      camera,
    const kvs::Light*       light )
{
    float t[16]; camera->getCombinedMatrix( &t );
    const size_t w = camera->windowWidth() / 2;
    const size_t h = camera->windowHeight() / 2;

    // Set shader initial parameters.
    BaseClass::m_shader->set( camera, light );

    // Attach the shader and the point object to the point buffer.
    m_buffer->attachShader( BaseClass::m_shader );
    m_buffer->attachPointObject( point );

    // Aliases.
    const size_t       nv = point->numberOfVertices();
    const kvs::Real32* v  = point->coords().data();

    size_t index3 = 0;
    const size_t bounds_width  = m_width  - 1;
    const size_t bounds_height = m_height - 1;
    for( size_t index = 0; index < nv; index++, index3 += 3 )
    {
        /* Calculate the projected point position in the window coordinate system.
         * Ex.) Camera::projectObjectToWindow().
         */
        float p_tmp[4] = {
            v[index3]*t[0] + v[index3+1]*t[4] + v[index3+2]*t[ 8] + t[12],
            v[index3]*t[1] + v[index3+1]*t[5] + v[index3+2]*t[ 9] + t[13],
            v[index3]*t[2] + v[index3+1]*t[6] + v[index3+2]*t[10] + t[14],
            v[index3]*t[3] + v[index3+1]*t[7] + v[index3+2]*t[11] + t[15] };
        p_tmp[3] = 1.0f / p_tmp[3];
        p_tmp[0] *= p_tmp[3];
        p_tmp[1] *= p_tmp[3];
        p_tmp[2] *= p_tmp[3];

        const float p_win_x = ( 1.0f + p_tmp[0] ) * w;
        const float p_win_y = ( 1.0f + p_tmp[1] ) * h;
        const float depth   = ( 1.0f + p_tmp[2] ) * 0.5f;

        // Store the projected point in the point buffer.
        if( ( 0 < p_win_x ) & ( 0 < p_win_y ) )
        {
            if( ( p_win_x < bounds_width ) & ( p_win_y < bounds_height ) )
            {
                m_buffer->add( p_win_x, p_win_y, depth, index );
            }
        }
    }

    // Shading calculation.
    if( m_enable_shading ) m_buffer->enableShading();
    else                   m_buffer->disableShading();

    m_buffer->createImage( &m_color_data, &m_depth_data );
}

} // end of namespace kvs
