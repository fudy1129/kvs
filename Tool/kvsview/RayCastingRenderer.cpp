/*****************************************************************************/
/**
 *  @file   RayCastingRenderer.cpp
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
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/IgnoreUnusedVariable>
#include <kvs/File>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/AVSField>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/RayCastingRenderer>
#include <kvs/Bounds>
#include <kvs/PaintEventListener>
#include <kvs/MousePressEventListener>
#include <kvs/MouseReleaseEventListener>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>


namespace
{

bool EnableLODControl = true;
bool HasBounds = false;

} // end of namespace


namespace kvsview
{

namespace RayCastingRenderer
{

class PaintEvent : public kvs::PaintEventListener
{
    void update( void )
    {
        if ( ::EnableLODControl )
        {
            const int id = ::HasBounds ? 2 : 1;
            const kvs::RendererBase* base = screen()->rendererManager()->renderer( id );
            kvs::RayCastingRenderer* renderer = (kvs::RayCastingRenderer*)base;
            if ( screen()->mouse()->isAuto() ) renderer->enableCoarseRendering();
        }
    }
};

class MousePressEvent : public kvs::MousePressEventListener
{
    void update( kvs::MouseEvent* ev )
    {
        kvs::IgnoreUnusedVariable( ev );

        if ( ::EnableLODControl )
        {
            const int id = ::HasBounds ? 2 : 1;
            const kvs::RendererBase* base = screen()->rendererManager()->renderer( id );
            kvs::RayCastingRenderer* renderer = (kvs::RayCastingRenderer*)base;
            renderer->enableCoarseRendering();
        }
    }
};

class MouseReleaseEvent : public kvs::MouseReleaseEventListener
{
    void update( kvs::MouseEvent* ev )
    {
        kvs::IgnoreUnusedVariable( ev );

        if ( ::EnableLODControl )
        {
            const int id = ::HasBounds ? 2 : 1;
            const kvs::RendererBase* base = screen()->rendererManager()->renderer( id );
            kvs::RayCastingRenderer* renderer = (kvs::RayCastingRenderer*)base;
            renderer->disableCoarseRendering();
            screen()->redraw();
        }
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
    kvsview::Argument::Common( argc, argv, "RayCastingRenderer")
{
    // Parameters for the RayCastingRenderer class.
    add_option( kvsview::RayCastingRenderer::CommandName, kvsview::RayCastingRenderer::Description, 0 );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
    add_option( "noshading", "Disable shading. (optional)", 0, false );
    add_option( "nolod", "Disable Level-of-Detail control. (optional)", 0, false );
    add_option( "ka", "Coefficient of the ambient color. (default: lambert=0.5, phong=0.3)", 1, false );
    add_option( "kd", "Coefficient of the diffuse color. (default: 0.5)", 1, false );
    add_option( "ks", "Coefficient of the specular color. (default: 0.8)", 1, false );
    add_option( "n", "Shininess. (default: 20.0)", 1, false );
    add_option( "shader", "Shader type. (default: 0)\n"
                "\t      0 = Lambert shading\n"
                "\t      1 = Phong shading\n"
                "\t      2 = Blinn-Phong shading", 1, false );
}

const int Argument::shader( void )
{
    const int default_value = 0;

    if ( this->hasOption("shader") ) return( this->optionValue<int>("shader") );
    else return( default_value );
}

const bool Argument::noShading( void )
{
    return( this->hasOption("noshading") );
}

const bool Argument::noLOD( void )
{
    return( this->hasOption("nolod") );
}

const float Argument::ambient( void )
{
    const float default_value = this->shader() == 0 ? 0.5f : 0.3f;

    if ( this->hasOption("ka") ) return( this->optionValue<float>("ka") );
    else return( default_value );
}

const float Argument::diffuse( void )
{
    const float default_value = 0.5f;

    if ( this->hasOption("kd") ) return( this->optionValue<float>("kd") );
    else return( default_value );
}

const float Argument::specular( void )
{
    const float default_value = 0.8f;

    if ( this->hasOption("ks") ) return( this->optionValue<float>("ks") );
    else return( default_value );
}

const float Argument::shininess( void )
{
    const float default_value = 20.0f;

    if ( this->hasOption("n") ) return( this->optionValue<float>("n") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a transfer function.
 *  @return transfer function
 */
/*===========================================================================*/
const kvs::TransferFunction Argument::transferFunction( void )
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
    RayCastingRenderer::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    RayCastingRenderer::PaintEvent paint_event;
    RayCastingRenderer::MousePressEvent mouse_press_event;
    RayCastingRenderer::MouseReleaseEvent mouse_release_event;

    // Create a global and screen class.
    kvs::glut::Screen screen( &app );
    screen.setSize( 512, 512 );
    screen.addPaintEvent( &paint_event );
    screen.addMousePressEvent( &mouse_press_event );
    screen.addMouseReleaseEvent( &mouse_release_event );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::RayCastingRenderer::CommandName );

    // Check the input point data.
    m_input_name = arg.value<std::string>();
    if ( !( kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) ||
            kvsview::FileChecker::ImportableUnstructuredVolume( m_input_name ) ) )
    {
        kvsMessageError("%s is not volume data.", m_input_name.c_str());
        return( false );
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

    // Set up a RayCastingRenderer class.
    kvs::PipelineModule renderer( new kvs::RayCastingRenderer );

    // Transfer function.
    const kvs::TransferFunction function = arg.transferFunction();
    {
        renderer.get<kvs::RayCastingRenderer>()->setTransferFunction( function );
    }

    // Shading on/off.
    const bool noshading = arg.noShading();
    {
        if ( noshading ) renderer.get<kvs::RayCastingRenderer>()->disableShading();
        else renderer.get<kvs::RayCastingRenderer>()->enableShading();
    }

    // Shader type.
    const int shader = arg.shader();
    {
        const float ka = arg.ambient();
        const float kd = arg.diffuse();
        const float ks = arg.specular();
        const float n  = arg.shininess();
        switch ( shader )
        {
        case 0:
        {
            renderer.get<kvs::RayCastingRenderer>()->setShader( kvs::Shader::Lambert( ka, kd ) );
            break;
        }
        case 1:
        {
            renderer.get<kvs::RayCastingRenderer>()->setShader( kvs::Shader::Phong( ka, kd, ks, n ) );
            break;
        }
        case 2:
        {
            renderer.get<kvs::RayCastingRenderer>()->setShader( kvs::Shader::BlinnPhong( ka, kd, ks, n ) );
            break;
        }
        default: break;
        }
    }

    // LOD control.
    ::EnableLODControl = !arg.noLOD();

    // Construct the visualization pipeline.
    pipe.connect( renderer );
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

} // end of namespace Default

} // end of namespace kvsview
