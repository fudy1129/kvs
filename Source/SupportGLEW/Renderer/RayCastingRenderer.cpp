/*****************************************************************************/
/**
 *  @file   RayCastingRenderer.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "RayCastingRenderer.h"
#include <kvs/Shader>
#include <kvs/Vector3>

#if defined ( KVS_GLEW_RAY_CASTING_RENDERER__EMBEDDED_SHADER )
#include "RayCastingRenderer/Shader.h"
#endif


namespace
{

/*===========================================================================*/
/**
 *  @brief  Check the OpenGL error.
 *  @param  message [in] error message
 */
/*===========================================================================*/
void CheckOpenGLError( const char* message )
{
    const GLenum error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        kvsMessageError( "OPENGL ERROR: %s (%s)", message, gluErrorString( error ) );
        exit( EXIT_FAILURE );
    }
}

template <typename T>
kvs::AnyValueArray NormalizeValues( const kvs::StructuredVolumeObject* volume )
{
    kvs::AnyValueArray data;

    const kvs::Real32 min = static_cast<kvs::Real32>( volume->minValue() );
    const kvs::Real32 max = static_cast<kvs::Real32>( volume->maxValue() );

    const kvs::Real32 scale = 1.0f / ( max - min );
    const size_t nnodes = volume->nnodes();
    const T* src = static_cast<const T*>( volume->values().pointer() );
    kvs::Real32* dst = static_cast<kvs::Real32*>( data.allocate<kvs::Real32>( nnodes ) );
    for ( size_t i = 0; i < nnodes; i++ )
    {
        *(dst++) = ( *(src++) - min ) * scale;
    }

    return( data );
}

template <typename DstType, typename SrcType>
kvs::AnyValueArray SignedToUnsigned( const kvs::StructuredVolumeObject* volume )
{
    kvs::AnyValueArray data;

    const SrcType min = kvs::Value<SrcType>::Min();
    const size_t nvalues = volume->values().size();
    const SrcType* src = static_cast<const SrcType*>( volume->values().pointer() );
    DstType* dst = static_cast<DstType*>( data.allocate<DstType>( nvalues ) );
    for ( size_t i = 0; i < nvalues; i++ )
    {
        *(dst++) = static_cast<DstType>( *(src++) - min );
    }

    return( data );
}

} // end of namespace


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Construct a new RayCastingRenderer class.
 */
/*===========================================================================*/
RayCastingRenderer::RayCastingRenderer( void )
{
    BaseClass::setShader( kvs::Shader::Lambert() );
    this->initialize();
}

/*===========================================================================*/
/**
 *  @brief  Destroys the RayCastingRenderer class.
 */
/*===========================================================================*/
RayCastingRenderer::~RayCastingRenderer( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Main rendering routine.
 *  @param  object [i] pointer to the object
 *  @param  camera [i] pointer to the camera
 *  @param  light [i] pointer to the light
 */
/*===========================================================================*/
void RayCastingRenderer::exec(
    kvs::ObjectBase* object,
    kvs::Camera*     camera,
    kvs::Light*      light )
{
    kvs::StructuredVolumeObject* volume = kvs::StructuredVolumeObject::DownCast( object );

    BaseClass::m_timer.start();
    this->create_image( volume, camera, light );
    BaseClass::m_timer.stop();
}

/*===========================================================================*/
/**
 *  @brief  Initialize the member parameters.
 */
/*===========================================================================*/
void RayCastingRenderer::initialize( void )
{
    BaseClass::m_width = 0;
    BaseClass::m_height = 0;

    m_draw_front_face = true;
    m_draw_back_face = true;
    m_draw_volume = true;

    m_step = 0.5f;
    m_opaque = 1.0f;
}

void RayCastingRenderer::setSamplingStep( const float step )
{
    m_step = step;
}

void RayCastingRenderer::setOpaqueValue( const float opaque )
{
    m_opaque = opaque;
}

void RayCastingRenderer::setDrawingBuffer( const RayCastingRenderer::DrawingBuffer drawing_buffer )
{
    m_draw_front_face = false;
    m_draw_back_face = false;
    m_draw_volume = false;

    switch ( drawing_buffer )
    {
    case RayCastingRenderer::FrontFace: m_draw_front_face = true; break;
    case RayCastingRenderer::BackFace: m_draw_back_face = true; break;
    case RayCastingRenderer::Volume:
    {
        m_draw_front_face = true;
        m_draw_back_face = true;
        m_draw_volume = true;
        break;
    }
    default: break;
    }
}

/*===========================================================================*/
/**
 *  @brief  Creates a rendering image.
 *  @param  volume [in] pointer to the structured volume object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void RayCastingRenderer::create_image(
    const kvs::StructuredVolumeObject* volume,
    const kvs::Camera* camera,
    const kvs::Light* light )
{
    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT );

    RendererBase::initialize();

    // Following processes are executed once.
    if ( BaseClass::m_width == 0 && BaseClass::m_height == 0 )
    {
        this->initialize_shaders( volume );
        this->create_bounding_cube( volume );
    }

    // Following processes are executed when the window size is changed.
    if ( ( BaseClass::m_width  != camera->windowWidth() ) ||
         ( BaseClass::m_height != camera->windowHeight() ) )
    {
        BaseClass::m_width = camera->windowWidth();
        BaseClass::m_height = camera->windowHeight();
        this->create_entry_points();
        this->create_exit_points();
    }

    // Download the transfer function data to the 1D texture on the GPU.
    if ( !glIsTexture( m_transfer_function_texture.id() ) )
    {
        this->create_transfer_function( volume );
    }

    // Download the volume data to the 3D texture on the GPU.
    if ( !glIsTexture( m_volume_data.id() ) )
    {
        this->create_volume_data( volume );
    }

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glDisable( GL_LIGHTING );

    m_bounding_cube_shader.bind();
    {
        // Draw the back face of the bounding cube for the entry points.
        if ( m_draw_back_face )
        {
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glCullFace( GL_FRONT );
            this->draw_bounding_cube();
            glActiveTexture( GL_TEXTURE2 ); m_exit_points.bind(); glEnable( GL_TEXTURE_2D );
            glCopyTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 0, 0, BaseClass::m_width, BaseClass::m_height );
        }

        // Draw the front face of the bounding cube for the entry points.
        if ( m_draw_front_face )
        {
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glCullFace( GL_BACK );
            this->draw_bounding_cube();
            glActiveTexture( GL_TEXTURE3 ); m_entry_points.bind(); glEnable( GL_TEXTURE_2D );
            glCopyTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 0, 0, BaseClass::m_width, BaseClass::m_height );
        }
    }
    m_bounding_cube_shader.unbind();

    if ( m_draw_volume )
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glDisable( GL_CULL_FACE );
        glEnable( GL_BLEND );
        glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );

        // Enable or disable OpenGL capabilities.
        if ( BaseClass::isEnabledShading() ) glEnable( GL_LIGHTING );
        else glDisable( GL_LIGHTING );

        // Ray casting.
        m_ray_caster.bind();
        glActiveTexture( GL_TEXTURE4 ); m_transfer_function_texture.bind(); glEnable( GL_TEXTURE_1D );
        glActiveTexture( GL_TEXTURE1 ); m_volume_data.bind(); glEnable( GL_TEXTURE_3D );
        {
            const kvs::Vector3ui ngrids = volume->resolution() - kvs::Vector3ui(1);
            const kvs::Real32 max_ngrids = kvs::Math::Max( ngrids.x(), ngrids.y(), ngrids.z() );
            const kvs::Vector3f light_position = camera->projectWorldToObject( light->position() * max_ngrids );
            const kvs::Vector3f camera_position = camera->projectWorldToObject( camera->position() * max_ngrids );
            m_ray_caster.setUniformValuef( "light_position", light_position );
            m_ray_caster.setUniformValuef( "camera_position", camera_position );
            m_ray_caster.setUniformValuei( "volume.data", 1 );
            m_ray_caster.setUniformValuei( "exit_points", 2 );
            m_ray_caster.setUniformValuei( "entry_points", 3 );
            m_ray_caster.setUniformValuei( "transfer_function.data", 4 );
            this->draw_quad( 1.0f );
        }
        glActiveTexture( GL_TEXTURE4 ); m_transfer_function_texture.unbind(); glDisable( GL_TEXTURE_1D );
        glActiveTexture( GL_TEXTURE1 ); m_volume_data.unbind(); glDisable( GL_TEXTURE_3D );
        m_ray_caster.unbind();
    }

    glActiveTexture( GL_TEXTURE0 );

    glPopAttrib();
    glFinish();
}

/*==========================================================================*/
/**
 *  @brief  Initialize OpenGL.
 */
/*==========================================================================*/
void RayCastingRenderer::initialize_shaders( const kvs::StructuredVolumeObject* volume )
{
    const kvs::Vector3ui ngrids = volume->resolution();
    const kvs::Real32 max_ngrids = kvs::Math::Max( ngrids.x()-1, ngrids.y()-1, ngrids.z()-1 );
    const kvs::Real32 n = 1.0f / max_ngrids;
    const kvs::Vector3f offset( 1.0f * n, 1.0f * n, 1.0f * n );
    const kvs::Vector3f ratio( ngrids.x() * n, ngrids.y() * n, ngrids.z() * n );

    // Bounding cube shader.
    {
#if defined( KVS_GLEW_RAY_CASTING_RENDERER__EMBEDDED_SHADER )
        const std::string vert_code = kvs::glew::glsl::RayCastingRenderer::Vertex::bounding_cube;
        const std::string frag_code = kvs::glew::glsl::RayCastingRenderer::Fragment::bounding_cube;
#else
        const std::string vert_code = "RayCastingRenderer/bounding_cube.vert";
        const std::string frag_code = "RayCastingRenderer/bounding_cube.frag";
#endif

        kvs::glew::ShaderSource vert( vert_code );
        kvs::glew::ShaderSource frag( frag_code );
        this->create_shaders( m_bounding_cube_shader, vert, frag );

        ::CheckOpenGLError( "Cannot initialize bounding cube shader." );
    }

    // Ray caster.
    {
#if defined( KVS_GLEW_RAY_CASTING_RENDERER__EMBEDDED_SHADER )
        const std::string vert_code = kvs::glew::glsl::RayCastingRenderer::Vertex::ray_caster;
        const std::string frag_code = kvs::glew::glsl::RayCastingRenderer::Fragment::ray_caster;
#else
        const std::string vert_code = "RayCastingRenderer/ray_caster.vert";
        const std::string frag_code = "RayCastingRenderer/ray_caster.frag";
#endif

        kvs::glew::ShaderSource vert( vert_code );
        kvs::glew::ShaderSource frag( frag_code );

        switch ( BaseClass::m_shader->type() )
        {
        case kvs::Shader::LambertShading: frag.define("ENABLE_LAMBERT_SHADING"); break;
        case kvs::Shader::PhongShading: frag.define("ENABLE_PHONG_SHADING"); break;
        case kvs::Shader::BlinnPhongShading: frag.define("ENABLE_BLINN_PHONG_SHADING"); break;
        default: /* NO SHADING */ break;
        }

        kvs::Real32 min_range = 0.0f;
        kvs::Real32 max_range = 0.0f;
        kvs::Real32 min_value = 0.0f;
        kvs::Real32 max_value = 0.0f;
        const std::type_info& type = volume->values().typeInfo()->type();
        if ( type == typeid( kvs::UInt8 ) )
        {
            min_range = 0.0f;
            max_range = 255.0f;
            min_value = 0.0f;
            max_value = 255.0f;
        }
        else if ( type == typeid( kvs::Int8 ) )
        {
            min_range = static_cast<kvs::Real32>( kvs::Value<kvs::UInt8>::Min() );
            max_range = static_cast<kvs::Real32>( kvs::Value<kvs::UInt8>::Max() );
            min_value = -128.0f;
            max_value = 127.0f;
        }
        else if ( type == typeid( kvs::UInt16 ) )
        {
            min_range = static_cast<kvs::Real32>( kvs::Value<kvs::UInt16>::Min() );
            max_range = static_cast<kvs::Real32>( kvs::Value<kvs::UInt16>::Max() );
            min_value = static_cast<kvs::Real32>( volume->minValue() );
            max_value = static_cast<kvs::Real32>( volume->maxValue() );
        }
        else if ( type == typeid( kvs::Int16 ) )
        {
            min_range = static_cast<kvs::Real32>( kvs::Value<kvs::Int16>::Min() );
            max_range = static_cast<kvs::Real32>( kvs::Value<kvs::Int16>::Max() );
            min_value = static_cast<kvs::Real32>( volume->minValue() );
            max_value = static_cast<kvs::Real32>( volume->maxValue() );
        }
        else if ( type == typeid( kvs::UInt32 ) ||
                  type == typeid( kvs::Int32  ) ||
                  type == typeid( kvs::Real32 ) )
        {
            min_range = 0.0f;
            max_range = 1.0f;
            min_value = 0.0f;
            max_value = 1.0f;
        }
        else
        {
            kvsMessageError( "Not supported data type '%s'.",
                             volume->values().typeInfo()->typeName() );
        }

        this->create_shaders( m_ray_caster, vert, frag );

        m_ray_caster.bind();
        m_ray_caster.setUniformValuef( "volume.ratio", ratio );
        m_ray_caster.setUniformValuef( "volume.min_range", min_range );
        m_ray_caster.setUniformValuef( "volume.max_range", max_range );
        m_ray_caster.setUniformValuef( "volume.min_value", min_value );
        m_ray_caster.setUniformValuef( "volume.max_value", max_value );
        m_ray_caster.setUniformValuef( "offset", offset );
        m_ray_caster.setUniformValuef( "dt", m_step * n );
        m_ray_caster.setUniformValuef( "opaque", m_opaque );
        switch ( BaseClass::m_shader->type() )
        {
        case kvs::Shader::LambertShading:
        {
            const GLfloat Ka = ((kvs::Shader::Lambert*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::Lambert*)(BaseClass::m_shader))->Kd;
            m_ray_caster.setUniformValuef( "shading.Ka", Ka );
            m_ray_caster.setUniformValuef( "shading.Kd", Kd );
            break;
        }
        case kvs::Shader::PhongShading:
        {
            const GLfloat Ka = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Kd;
            const GLfloat Ks = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Ks;
            const GLfloat S  = ((kvs::Shader::Phong*)(BaseClass::m_shader))->S;
            m_ray_caster.setUniformValuef( "shading.Ka", Ka );
            m_ray_caster.setUniformValuef( "shading.Kd", Kd );
            m_ray_caster.setUniformValuef( "shading.Ks", Ks );
            m_ray_caster.setUniformValuef( "shading.S",  S );
            break;
        }
        case kvs::Shader::BlinnPhongShading:
        {
            const GLfloat Ka = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Kd;
            const GLfloat Ks = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Ks;
            const GLfloat S  = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->S;
            m_ray_caster.setUniformValuef( "shading.Ka", Ka );
            m_ray_caster.setUniformValuef( "shading.Kd", Kd );
            m_ray_caster.setUniformValuef( "shading.Ks", Ks );
            m_ray_caster.setUniformValuef( "shading.S",  S );
            break;
        }
        default: /* NO SHADING */ break;
        }
        m_ray_caster.unbind();

        ::CheckOpenGLError( "Cannot initialize ray caster." );
    }
}

/*==========================================================================*/
/**
 *  @brief  Creates GLSL shader programs.
 */
/*==========================================================================*/
void RayCastingRenderer::create_shaders(
    kvs::glew::ProgramObject& program_object,
    const kvs::glew::ShaderSource& vertex_source,
    const kvs::glew::ShaderSource& fragment_source )
{
    // Vertex shader.
    kvs::glew::VertexShader vertex_shader;
    if ( !vertex_shader.create( vertex_source ) )
    {
        kvsMessageError( "Cannot compile vertex shader." );
        std::cout << "error log:" << std::endl;
        std::cout << vertex_shader.log() << std::endl;
    }

    // Fragment shader.
    kvs::glew::FragmentShader fragment_shader;
    if ( !fragment_shader.create( fragment_source ) )
    {
        kvsMessageError( "Cannot compile fragment shader." );
        std::cout << "error log:" << std::endl;
        std::cout << fragment_shader.log() << std::endl;
    }

    // Link the shaders.
    if ( !program_object.link( vertex_shader, fragment_shader ) )
    {
        kvsMessageError( "Cannot link shaders." );
        std::cout << "error log:" << std::endl;
        std::cout << program_object.log() << std::endl;
        exit(1);
    }
}

/*===========================================================================*/
/**
 *  @brief  Create the entry points texture.
 */
/*===========================================================================*/
void RayCastingRenderer::create_entry_points( void )
{
    const size_t width = BaseClass::m_width;
    const size_t height = BaseClass::m_height;

    m_entry_points.release();
    m_entry_points.setWrapS( GL_CLAMP_TO_EDGE );
    m_entry_points.setWrapT( GL_CLAMP_TO_EDGE );
    m_entry_points.setMagFilter( GL_LINEAR );
    m_entry_points.setMinFilter( GL_LINEAR );
//    m_entry_points.setPixelFormat( GL_RGB16F_ARB, GL_RGB, GL_FLOAT  );
    m_entry_points.setPixelFormat( GL_RGB, GL_RGB, GL_FLOAT  );
    m_entry_points.create( width, height );

    ::CheckOpenGLError( "Entry point texture allocation failed." );
}

/*===========================================================================*/
/**
 *  @brief  Create the exit points texture.
 */
/*===========================================================================*/
void RayCastingRenderer::create_exit_points( void )
{
    const size_t width = BaseClass::m_width;
    const size_t height = BaseClass::m_height;

    m_exit_points.release();
    m_exit_points.setWrapS( GL_CLAMP_TO_EDGE );
    m_exit_points.setWrapT( GL_CLAMP_TO_EDGE );
    m_exit_points.setMagFilter( GL_LINEAR );
    m_exit_points.setMinFilter( GL_LINEAR );
//    m_exit_points.setPixelFormat( GL_RGB16F_ARB, GL_RGB, GL_FLOAT  );
    m_exit_points.setPixelFormat( GL_RGB, GL_RGB, GL_FLOAT  );
    m_exit_points.create( width, height );

    ::CheckOpenGLError( "Exit point texture allocation failed." );
}

/*===========================================================================*/
/**
 *  @brief  Creates a bounding cube in the VBO on GPU.
 *  @param  volume [in] pointer to the structured volume object
 */
/*===========================================================================*/
void RayCastingRenderer::create_bounding_cube( const kvs::StructuredVolumeObject* volume )
{
    /* Index number of the bounding cube.
     *
     *       4 ------------ 5
     *     / |            / |
     *    /  |           /  |
     *   7--------------6   |
     *   |   |          |   |
     *   |   0 ---------|-- 1
     *   |  /           |  /
     *   | /            | /
     *   3 ------------ 2
     *
     */
    const kvs::Vector3ui min( 0, 0, 0 );
//    const kvs::Vector3ui max( volume->resolution() - kvs::Vector3ui( 1, 1, 1 ) );
    const kvs::Vector3ui max( volume->resolution() );
    const size_t nelements = 72; // = 4 vertices x 3 dimensions x 6 faces

    const float coords[ nelements ] = {
        min.x(), min.y(), min.z(), // 0
        max.x(), min.y(), min.z(), // 1
        max.x(), min.y(), max.z(), // 2
        min.x(), min.y(), max.z(), // 3

        min.x(), max.y(), max.z(), // 7
        max.x(), max.y(), max.z(), // 6
        max.x(), max.y(), min.z(), // 5
        min.x(), max.y(), min.z(), // 4

        min.x(), max.y(), min.z(), // 4
        max.x(), max.y(), min.z(), // 5
        max.x(), min.y(), min.z(), // 1
        min.x(), min.y(), min.z(), // 0

        max.x(), max.y(), min.z(), // 5
        max.x(), max.y(), max.z(), // 6
        max.x(), min.y(), max.z(), // 2
        max.x(), min.y(), min.z(), // 1

        max.x(), max.y(), max.z(), // 6
        min.x(), max.y(), max.z(), // 7
        min.x(), min.y(), max.z(), // 3
        max.x(), min.y(), max.z(), // 2

        min.x(), min.y(), min.z(), // 0
        min.x(), min.y(), max.z(), // 3
        min.x(), max.y(), max.z(), // 7
        min.x(), max.y(), min.z()  // 4
    };

    const size_t byte_size = sizeof(float) * nelements;
    m_bounding_cube.create( byte_size );
    m_bounding_cube.download( byte_size, coords );

    ::CheckOpenGLError( "Cannot download bounding cube (VBO)." );
}

/*===========================================================================*/
/**
 *  @brief  Crates a transfer function texture.
 *  @param  volume [in] pointer to the structured volume object
 */
/*===========================================================================*/
void RayCastingRenderer::create_transfer_function( const kvs::StructuredVolumeObject* volume )
{
    const size_t width = BaseClass::m_tfunc.resolution();
    kvs::ValueArray<float> colors( width * 4 );
    float* data = colors.pointer();

    const kvs::ColorMap& cmap = BaseClass::m_tfunc.colorMap();
    const kvs::OpacityMap& omap = BaseClass::m_tfunc.opacityMap();
    for ( size_t i = 0; i < width; i++ )
    {
        *(data++) = static_cast<float>( cmap[i].r() ) / 255.0f;
        *(data++) = static_cast<float>( cmap[i].g() ) / 255.0f;
        *(data++) = static_cast<float>( cmap[i].b() ) / 255.0f;
        *(data++) = omap[i];
    }

    m_transfer_function_texture.release();
    m_transfer_function_texture.setWrapS( GL_CLAMP_TO_EDGE );
    m_transfer_function_texture.setMagFilter( GL_LINEAR );
    m_transfer_function_texture.setMinFilter( GL_LINEAR );
    m_transfer_function_texture.setPixelFormat( GL_RGBA, GL_RGBA, GL_FLOAT  );
    m_transfer_function_texture.create( width );
    m_transfer_function_texture.download( width, colors.pointer() );

    ::CheckOpenGLError( "Cannot create transfer function texture." );
}

/*===========================================================================*/
/**
 *  @brief  Create a volume data in the 3D texture on GPU.
 *  @param  volume [in] pointer to the structured volume object
 */
/*===========================================================================*/
void RayCastingRenderer::create_volume_data( const kvs::StructuredVolumeObject* volume )
{
    const size_t width = volume->resolution().x();
    const size_t height = volume->resolution().y();
    const size_t depth = volume->resolution().z();

    m_volume_data.release();
    m_volume_data.setWrapS( GL_CLAMP_TO_EDGE );
    m_volume_data.setWrapT( GL_CLAMP_TO_EDGE );
    m_volume_data.setWrapR( GL_CLAMP_TO_EDGE );
    m_volume_data.setMagFilter( GL_LINEAR );
    m_volume_data.setMinFilter( GL_LINEAR );

    GLenum data_format = 0;
    GLenum data_type = 0;
    kvs::AnyValueArray data_value;
    const std::type_info& type = volume->values().typeInfo()->type();
    if ( type == typeid( kvs::UInt8 ) )
    {
        data_format = GL_ALPHA8;
        data_type = GL_UNSIGNED_BYTE;
        data_value = volume->values();
    }
    else if ( type == typeid( kvs::UInt16 ) )
    {
        data_format = GL_ALPHA16;
        data_type = GL_UNSIGNED_SHORT;
        data_value = volume->values();
    }
    else if ( type == typeid( kvs::Int8 ) )
    {
        data_format = GL_ALPHA8;
        data_type = GL_UNSIGNED_BYTE;
        data_value = ::SignedToUnsigned<kvs::UInt8,kvs::Int8>( volume );
    }
    else if ( type == typeid( kvs::Int16 ) )
    {
        data_format = GL_ALPHA16;
        data_type = GL_UNSIGNED_SHORT;
        data_value = ::SignedToUnsigned<kvs::UInt16,kvs::Int16>( volume );
    }
    else if ( type == typeid( kvs::UInt32 ) )
    {
        data_format = GL_ALPHA;
        data_type = GL_FLOAT;
        data_value = ::NormalizeValues<kvs::UInt32>( volume );
    }
    else if ( type == typeid( kvs::Int32 ) )
    {
        data_format = GL_ALPHA;
        data_type = GL_FLOAT;
        data_value = ::NormalizeValues<kvs::Int32>( volume );
    }
    else if ( type == typeid( kvs::Real32 ) )
    {
        data_format = GL_ALPHA;
        data_type = GL_FLOAT;
        data_value = ::NormalizeValues<kvs::Real32>( volume );
    }
    else
    {
        kvsMessageError( "Not supported data type '%s'.",
                         volume->values().typeInfo()->typeName() );
    }

    m_volume_data.setPixelFormat( data_format, GL_ALPHA, data_type );
    m_volume_data.create( width, height, depth );
    m_volume_data.download( width, height, depth, data_value.pointer() );

    ::CheckOpenGLError( "Cannot create volume data texture." );
}

/*===========================================================================*/
/**
 *  @brief  Draws the bounding cube.
 */
/*===========================================================================*/
void RayCastingRenderer::draw_bounding_cube( void )
{
    m_bounding_cube.bind();
    {
        glEnableClientState( GL_VERTEX_ARRAY );
        {
            glVertexPointer( 3, GL_FLOAT, 0, 0 );
            glDrawArrays( GL_QUADS, 0, 72 );
        }
        glDisableClientState( GL_VERTEX_ARRAY );
    }
    m_bounding_cube.unbind();
}

/*===========================================================================*/
/**
 *  @brief  Draws the quad for texture mapping.
 *  @param  opacity [in] opacity
 */
/*===========================================================================*/
void RayCastingRenderer::draw_quad( const float opacity )
{
    glViewport( 0, 0, BaseClass::m_width, BaseClass::m_height );

    glMatrixMode( GL_MODELVIEW );  glPushMatrix(); glLoadIdentity();
    glMatrixMode( GL_PROJECTION ); glPushMatrix(); glLoadIdentity();
    {
        glOrtho( 0, 1, 0, 1, -1, 1 );
        glDisable( GL_DEPTH_TEST );
        glDisable( GL_LIGHTING );
        glBegin( GL_QUADS );
        {
            glColor4f( 1.0, 1.0, 1.0, opacity );
            glTexCoord2f( 1, 1 ); glVertex2f( 1, 1 );
            glTexCoord2f( 0, 1 ); glVertex2f( 0, 1 );
            glTexCoord2f( 0, 0 ); glVertex2f( 0, 0 );
            glTexCoord2f( 1, 0 ); glVertex2f( 1, 0 );
        }
        glEnd();
    }
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
}

} // end of namespace glew

} // end of namespace kvs
