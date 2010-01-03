/*****************************************************************************/
/**
 *  @file   ParticleVolumeRenderer.cpp
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
#include "ParticleVolumeRenderer.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/IgnoreUnusedVariable>
#include <kvs/File>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/CellByCellMetropolisSampling>
#include <kvs/ParticleVolumeRenderer>
#include <kvs/Bounds>
#include <kvs/PaintEventListener>
#include <kvs/MousePressEventListener>
#include <kvs/MouseReleaseEventListener>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#if defined( KVS_SUPPORT_GLEW )
#include <kvs/glew/ParticleVolumeRenderer>
#endif


namespace
{

bool EnableLODControl = true;
bool EnableGPURendering = true;
bool HasBounds = false;

} // end of namespace

namespace
{

inline const size_t GetRevisedSubpixelLevel(
    const size_t subpixel_level,
    const size_t repetition_level )
{
    return( static_cast<size_t>( subpixel_level * sqrtf( static_cast<float>(repetition_level) ) + 0.5f ) );
}

template <typename Renderer>
const void InitializeParticleVolumeRenderer(
    const kvsview::ParticleVolumeRenderer::Argument& arg,
    kvs::PipelineModule& renderer )
{
    // Transfer function.
    const kvs::TransferFunction& function = arg.transferFunction();
    renderer.get<Renderer>()->setTransferFunction( function );

    // Shading on/off.
    const bool noshading = arg.noShading();
    if ( noshading ) renderer.get<Renderer>()->disableShading();
    else renderer.get<Renderer>()->enableShading();

    // Shader type.
    const float ka = arg.ambient();
    const float kd = arg.diffuse();
    const float ks = arg.specular();
    const float n = arg.shininess();
    const int shader = arg.shader();
    switch ( shader )
    {
    case 0:
    {
        renderer.get<Renderer>()->setShader( kvs::Shader::Lambert( ka, kd ) );
        break;
    }
    case 1:
    {
        renderer.get<Renderer>()->setShader( kvs::Shader::Phong( ka, kd, ks, n ) );
        break;
    }
    case 2:
    {
        renderer.get<Renderer>()->setShader( kvs::Shader::BlinnPhong( ka, kd, ks, n ) );
        break;
    }
    default: break;
    }
}

} // end of namespace


namespace kvsview
{

namespace ParticleVolumeRenderer
{

class PaintEvent : public kvs::PaintEventListener
{
    void update( void )
    {
#if defined( KVS_SUPPORT_GLEW )
        if ( ::EnableLODControl )
        {
            if ( ::EnableGPURendering )
            {
                const int id = ::HasBounds ? 2 : 1;
                const kvs::RendererBase* base = screen()->rendererManager()->renderer( id );
                kvs::glew::ParticleVolumeRenderer* renderer = (kvs::glew::ParticleVolumeRenderer*)base;
                if ( screen()->mouse()->isAuto() ) renderer->enableCoarseRendering();
            }
        }
#endif
    }
};

class MousePressEvent : public kvs::MousePressEventListener
{
    void update( kvs::MouseEvent* ev )
    {
        kvs::IgnoreUnusedVariable( ev );
#if defined( KVS_SUPPORT_GLEW )
        if ( ::EnableLODControl )
        {
            if ( ::EnableGPURendering )
            {
                const int id = ::HasBounds ? 2 : 1;
                const kvs::RendererBase* base = screen()->rendererManager()->renderer( id );
                kvs::glew::ParticleVolumeRenderer* renderer = (kvs::glew::ParticleVolumeRenderer*)base;
                renderer->enableCoarseRendering();
            }
        }
#endif
    }
};

class MouseReleaseEvent : public kvs::MouseReleaseEventListener
{
    void update( kvs::MouseEvent* ev )
    {
        kvs::IgnoreUnusedVariable( ev );
#if defined( KVS_SUPPORT_GLEW )
        if ( ::EnableLODControl )
        {
            if ( ::EnableGPURendering )
            {
                const int id = ::HasBounds ? 2 : 1;
                const kvs::RendererBase* base = screen()->rendererManager()->renderer( id );
                kvs::glew::ParticleVolumeRenderer* renderer = (kvs::glew::ParticleVolumeRenderer*)base;
                renderer->disableCoarseRendering();
                screen()->redraw();
            }
        }
#endif
    }
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a point renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "ParticleVolumeRenderer")
{
    // Parameters for the ParticleVolumeRenderer class.
    add_option( kvsview::ParticleVolumeRenderer::CommandName, kvsview::ParticleVolumeRenderer::Description, 0 );
    add_option( "s", "Subpixel level. (default: 1)", 1, false );
    add_option( "r", "Repetition level. (default: 1)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
    add_option( "noshading", "Disable shading. (optional)", 0, false );
    add_option( "nolod", "Disable Level-of-Detail control. (optional)", 0, false );
    add_option( "nogpu", "Disable GPU rendering. (optional)", 0, false );
    add_option( "ka", "Coefficient of the ambient color. (default: 0.5)", 1, false );
    add_option( "kd", "Coefficient of the diffuse color. (default: 0.5)", 1, false );
    add_option( "ks", "Coefficient of the specular color. (default: 0.3)", 1, false );
    add_option( "n", "Shininess. (default: 20.0)", 1, false );
    add_option( "shader", "Shader type. (default: 0)\n"
                "\t      0 = Lambert shading\n"
                "\t      1 = Phong shading\n"
                "\t      2 = Blinn-Phong shading", 1, false );
}

const int Argument::shader( void ) const
{
    const int default_value = 0;

    if ( this->hasOption("shader") ) return( this->optionValue<int>("shader") );
    else return( default_value );
}

const bool Argument::noShading( void ) const
{
    return( this->hasOption("noshading") );
}

const bool Argument::noLOD( void ) const
{
    return( this->hasOption("nolod") );
}

const bool Argument::noGPU( void ) const
{
#if defined( KVS_SUPPORT_GLEW )
    return( this->hasOption("nogpu") );
#else
    return( true );
#endif
}

const float Argument::ambient( void ) const
{
    const float default_value = 0.5f;

    if ( this->hasOption("ka") ) return( this->optionValue<float>("ka") );
    else return( default_value );
}

const float Argument::diffuse( void ) const
{
    const float default_value = 0.5f;

    if ( this->hasOption("kd") ) return( this->optionValue<float>("kd") );
    else return( default_value );
}

const float Argument::specular( void ) const
{
    const float default_value = 0.3f;

    if ( this->hasOption("ks") ) return( this->optionValue<float>("ks") );
    else return( default_value );
}

const float Argument::shininess( void ) const
{
    const float default_value = 20.0f;

    if ( this->hasOption("n") ) return( this->optionValue<float>("n") );
    else return( default_value );
}

const size_t Argument::subpixelLevel( void ) const
{
    const size_t default_value = 1;

    if ( this->hasOption("s") ) return( this->optionValue<size_t>("s") );
    else return( default_value );
}

const size_t Argument::repetitionLevel( void ) const
{
    const size_t default_value = 1;

    if ( this->hasOption("r") ) return( this->optionValue<size_t>("r") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a transfer function.
 *  @return transfer function
 */
/*===========================================================================*/
const kvs::TransferFunction Argument::transferFunction( void ) const
{
    if ( this->hasOption("t") )
    {
        const std::string filename = this->optionValue<std::string>("t");
        return( kvs::TransferFunction( filename ) );
    }
    else
    {
        const size_t resolution = 256;
        return( kvs::TransferFunction( resolution ) );
    }
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class for a point renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Main::Main( int argc, char** argv )
{
    m_argc = argc;
    m_argv = argv;
}

/*===========================================================================*/
/**
 *  @brief  Executes main process.
 */
/*===========================================================================*/
const bool Main::exec( void )
{
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    kvsview::ParticleVolumeRenderer::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    kvsview::ParticleVolumeRenderer::PaintEvent paint_event;
    kvsview::ParticleVolumeRenderer::MousePressEvent mouse_press_event;
    kvsview::ParticleVolumeRenderer::MouseReleaseEvent mouse_release_event;

    // Create a global and screen class.
    kvs::glut::Screen screen( &app );
    screen.addPaintEvent( &paint_event );
    screen.addMousePressEvent( &mouse_press_event );
    screen.addMouseReleaseEvent( &mouse_release_event );
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::ParticleVolumeRenderer::CommandName );

    // Check the input point or volume data.
    bool is_volume = false; // check flag whether the input data is volume data
    m_input_name = arg.value<std::string>();
    if ( !kvsview::FileChecker::ImportablePoint( m_input_name ) )
    {
        if ( !( kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) ||
                kvsview::FileChecker::ImportableUnstructuredVolume( m_input_name ) ) )
        {
            kvsMessageError("%s is not volume data.", m_input_name.c_str());
            return( false );
        }

        is_volume = true;
    }

    // Visualization pipeline.
    kvs::VisualizationPipeline pipe( m_input_name );
    pipe.import();

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "IMPORTED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
    }

    // For bounding box.
    if ( arg.hasOption("bounds") )
    {
        ::HasBounds = true;

        kvs::LineObject* bounds = new kvs::Bounds( pipe.object() );

        bounds->setColor( kvs::RGBColor( 0, 0, 0 ) );
        if ( arg.hasOption("bounds_color") )
        {
            const kvs::UInt8 r( static_cast<kvs::UInt8>(arg.optionValue<int>("bounds_color",0)) );
            const kvs::UInt8 g( static_cast<kvs::UInt8>(arg.optionValue<int>("bounds_color",1)) );
            const kvs::UInt8 b( static_cast<kvs::UInt8>(arg.optionValue<int>("bounds_color",2)) );
            bounds->setColor( kvs::RGBColor( r, g, b ) );
        }

        kvs::VisualizationPipeline p( bounds );
        p.exec();
        p.renderer()->disableShading();

        screen.registerObject( &p );
    }

    // Set a mapper (CellByCellMetropolisSampling)
    kvs::PipelineModule mapper( new kvs::CellByCellMetropolisSampling );
    {
        const kvs::TransferFunction& function = arg.transferFunction();
        const size_t subpixel_level = arg.subpixelLevel();
        const size_t repetition_level = arg.repetitionLevel();
        const size_t level = ::GetRevisedSubpixelLevel( subpixel_level, repetition_level );
        const float step = 0.5f;
        const float depth = 0.0f;

        mapper.get<kvs::CellByCellMetropolisSampling>()->attachCamera( screen.camera() );
        mapper.get<kvs::CellByCellMetropolisSampling>()->setTransferFunction( function );
        mapper.get<kvs::CellByCellMetropolisSampling>()->setSubpixelLevel( level );
        mapper.get<kvs::CellByCellMetropolisSampling>()->setSamplingStep( step );
        mapper.get<kvs::CellByCellMetropolisSampling>()->setObjectDepth( depth );
    }

    // Set a renderer (ParticleVolumeRenderer).
    if ( arg.noGPU() )
    {
        kvs::PipelineModule renderer( new kvs::ParticleVolumeRenderer );
        ::InitializeParticleVolumeRenderer<kvs::ParticleVolumeRenderer>( arg, renderer );

        // Subpixel level.
        const size_t subpixel_level = arg.subpixelLevel();
        const size_t repetition_level = arg.repetitionLevel();
        const size_t level = ::GetRevisedSubpixelLevel( subpixel_level, repetition_level );
        renderer.get<kvs::ParticleVolumeRenderer>()->setSubpixelLevel( level );

        if ( is_volume ) pipe.connect( mapper ).connect( renderer );
        else pipe.connect( renderer );
    }
#if defined( KVS_SUPPORT_GLEW )
    else
    {
        kvs::PipelineModule renderer( new kvs::glew::ParticleVolumeRenderer );
        ::InitializeParticleVolumeRenderer<kvs::glew::ParticleVolumeRenderer>( arg, renderer );
        ::EnableGPURendering = true;

        // Subpixel level and repetition level.
        const size_t subpixel_level = arg.subpixelLevel();
        const size_t repetition_level = arg.repetitionLevel();
        renderer.get<kvs::glew::ParticleVolumeRenderer>()->setSubpixelLevel( subpixel_level );
        renderer.get<kvs::glew::ParticleVolumeRenderer>()->setRepetitionLevel( repetition_level );

        if ( is_volume ) pipe.connect( mapper ).connect( renderer );
        else pipe.connect( renderer );
    }
#endif

    // LOD control.
    ::EnableLODControl = !arg.noLOD();

    // Construct the visualization pipeline.
    if ( !pipe.exec() )
    {
        kvsMessageError("Cannot execute the visulization pipeline.");
        return( false );
    }
    screen.registerObject( &pipe );

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "RENDERERED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
        std::cout << "VISUALIZATION PIPELINE" << std::endl;
        std::cout << pipe << std::endl;
    }

    // Apply the specified parameters to the global and the visualization pipeline.
    arg.applyTo( screen, pipe );
    arg.applyTo( screen );

    // Show the screen.
    screen.show();

    return( app.run() );
}

} // end of namespace ParticleVolumeRenderer

} // end of namespace kvsview