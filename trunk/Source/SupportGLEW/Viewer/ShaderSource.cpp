/*****************************************************************************/
/**
 *  @file   ShaderSource.cpp
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
#include "ShaderSource.h"
#include <kvs/File>
#include <kvs/Message>
#include <sstream>
#include <fstream>


namespace kvs
{

namespace glew
{

ShaderSource::ShaderSource( void )
{
}

ShaderSource::ShaderSource( const std::string& source )
{
    const kvs::File file( source );
    if ( file.isExisted() )
    {
        const std::string filename( source );
        this->read( filename );
    }
    else
    {
        const std::string code( source );
        this->setCode( code );
    }
}

ShaderSource::~ShaderSource( void )
{
}

const std::string& ShaderSource::code( void ) const
{
    return( m_code );
}

void ShaderSource::setCode( const std::string& code )
{
    m_code = code;
}

const bool ShaderSource::read( const std::string& filename )
{
    std::ifstream ifs( filename.c_str() );
    if ( ifs.fail() )
    {
        kvsMessageError( "Cannot open '%s'.", filename.c_str() );
        return( false );
    }

    std::ostringstream buffer;
    buffer << ifs.rdbuf();

    std::string code( buffer.str() );
    ifs.close();

    this->setCode( code );

    return( true );
}

} // end of namespace glew

} // end of namespace kvs