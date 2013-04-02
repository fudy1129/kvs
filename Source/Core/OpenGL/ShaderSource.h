/*****************************************************************************/
/**
 *  @file   ShaderSource.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: ShaderSource.h 634 2010-10-13 07:04:05Z naohisa.sakamoto $
 */
/*****************************************************************************/
#ifndef KVS__SHADER_SOURCE_H_INCLUDE
#define KVS__SHADER_SOURCE_H_INCLUDE

#include <string>


namespace kvs
{

/*===========================================================================*/
/**
 *  Shader source class.
 */
/*===========================================================================*/
class ShaderSource
{
protected:

    std::string m_code; ///< shader source code

public:

    ShaderSource( const std::string& source );

    const std::string& code() const;
    void setCode( const std::string& code );
    void clearCode();
    void define( const std::string& name );
    bool read( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__SHADER_SOURCE_H_INCLUDE