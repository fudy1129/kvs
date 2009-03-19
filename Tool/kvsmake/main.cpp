/****************************************************************************/
/**
 *  @file main.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include <string>

#include <kvs/Compiler>
#include <kvs/Message>
#include <kvs/Directory>
#include <kvs/File>

#include "Argument.h"
#include "Constant.h"

#include "WriteMakefile.h"

#if defined ( KVS_COMPILER_VC )
#include "WriteVCProject.h"
#include "WriteVCProjectCUDA.h"
#endif

#include "WriteQtProject.h"


/*==========================================================================*/
/**
 *  @param argc [in] TODO.
 *  @param argv [in] TODO.
 *
 *  @return TODO.
 */
/*==========================================================================*/
int main( int argc, char** argv )
{
    kvsmake::Argument argument( argc, argv );
    if ( !argument.parse() )
    {
        exit( EXIT_FAILURE );
    }

    if ( argument.hasOption( "g" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "g" ) );

        kvsmake::WriteMakefile( project_name );

        return( 0 );
    }
    if ( argument.hasOption( "G" ) )
    {
        const kvs::Directory dir( "." );
        const std::string project_name( dir.directoryName() );

        kvsmake::WriteMakefile( project_name );

        return( 0 );
    }

    if ( argument.hasOption( "q" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "q" ) );

        kvsmake::WriteQtProject( project_name );

        return( 0 );
    }
    if ( argument.hasOption( "qt" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "qt" ) );

        kvsmake::WriteQtProject( project_name );

        return( 0 );
    }
    if ( argument.hasOption( "qtproj" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "qtproj" ) );

        kvsmake::WriteQtProject( project_name );

        return( 0 );
    }

#if defined ( KVS_COMPILER_VC )
    if ( argument.hasOption( "v" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "v" ) );

        kvsmake::WriteVCProject( project_name );

        return( 0 );
    }
    if ( argument.hasOption( "vc" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "vc" ) );

        kvsmake::WriteVCProject( project_name );

        return( 0 );
    }
    if ( argument.hasOption( "vcproj" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "vcproj" ) );

        kvsmake::WriteVCProject( project_name );

        return( 0 );
    }
    if ( argument.hasOption( "cuda" ) )
    {
        const std::string project_name( argument.optionValue<std::string>( "cuda" ) );

        kvsmake::WriteVCProjectCUDA( project_name );

        return( 0 );
    }
#endif

    if ( !kvs::File( kvsmake::Makefile ).isExisted() )
    {
        kvsMessageError( "Cannot find %s.", kvsmake::Makefile.c_str() );
        exit( EXIT_FAILURE );
    }

    std::string make_argument;
    for ( int i = 1; i < argc; ++i )
    {
        make_argument += std::string( " " ) + std::string( argv[i] );
    }

    const std::string command =
        kvsmake::MakeCommand + std::string( " -f " ) + kvsmake::Makefile + make_argument;

    system( command.c_str() );

    return( 0 );
}
