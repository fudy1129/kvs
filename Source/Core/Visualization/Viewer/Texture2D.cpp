/****************************************************************************/
/**
 *  @file Texture2D.cpp
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
#include "Texture2D.h"
#include <kvs/Math>
#include <iostream>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Texture2D::Texture2D( void ):
    m_is_downloaded( false ),
    m_wrap_s( GL_CLAMP ),
    m_wrap_t( GL_CLAMP ),
    m_width( 0 ),
    m_height( 0 ),
    m_pixels( 0 )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param wrap_s [in] wrap method for s-axis
 *  @param wrap_t [in] wrap method for t-axis
 */
/*==========================================================================*/
Texture2D::Texture2D( const GLenum wrap_s, const GLenum wrap_t ):
    m_is_downloaded( false ),
    m_wrap_s( wrap_s ),
    m_wrap_t( wrap_t ),
    m_width( 0 ),
    m_height( 0 ),
    m_pixels( 0 )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Texture2D::~Texture2D( void )
{
    this->release();
}

/*==========================================================================*/
/**
 *  Returns the wrap method for s-axis.
 */
/*==========================================================================*/
const GLenum Texture2D::wrapS( void ) const
{
    return( m_wrap_s );
}

/*==========================================================================*/
/**
 *  Returns the wrap method for t-axis.
 */
/*==========================================================================*/
const GLenum Texture2D::wrapT( void ) const
{
    return( m_wrap_t );
}

/*==========================================================================*/
/**
 *  Returns the texture width.
 */
/*==========================================================================*/
const size_t Texture2D::width( void ) const
{
    return( m_width );
}

/*==========================================================================*/
/**
 *  Returns the texture height.
 */
/*==========================================================================*/
const size_t Texture2D::height( void ) const
{
    return( m_height );
}

const bool Texture2D::isDownloaded( void ) const
{
    return( m_is_downloaded );
}

/*==========================================================================*/
/**
 *  Set the wrap method for s-axis.
 *  @param wrap_s [in] wrap method for s-axis
 */
/*==========================================================================*/
void Texture2D::setWrapS( const GLenum wrap_s )
{
    m_wrap_s = wrap_s;
}

/*==========================================================================*/
/**
 *  Set the wrap method for t-axis.
 *  @param wrap_t [in] wrap method for t-axis
 */
/*==========================================================================*/
void Texture2D::setWrapT( const GLenum wrap_t )
{
    m_wrap_t = wrap_t;
}

/*==========================================================================*/
/**
 *  Create the texture.
 */
/*==========================================================================*/
void Texture2D::create( const size_t width, const size_t height )
{
    m_width  = width;
    m_height = height;

    if( !glIsTexture( m_id ) ) glGenTextures( 1, &m_id );

    // Bind the texture.
    glBindTexture( GL_TEXTURE_2D, m_id );

    // Set the filter methods.
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_mag_filter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_min_filter );

    // Set the wrap methods.
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t );

    this->download( width, height, NULL );
}

/*==========================================================================*/
/**
 *  Download the texture data to the GPU.
 *  @param width [in] texture width
 *  @param height [in] texture height
 *  @param pixels [in] pointer to the pixel data
 *  @param xoffset [in] texel offset in the x direction within the pixel data
 *  @param yoffset [in] texel offset in the y direction within the pixel data
 */
/*==========================================================================*/
void Texture2D::download(
    const size_t width,
    const size_t height,
    const void*  pixels,
    const size_t xoffset,
    const size_t yoffset )
{
    GLint swap;
    GLint alignment;

    glGetIntegerv( GL_UNPACK_SWAP_BYTES, &swap );
    glGetIntegerv( GL_UNPACK_ALIGNMENT, &alignment );

    glPixelStorei( GL_UNPACK_SWAP_BYTES, swap ? GL_TRUE : GL_FALSE );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    if ( !m_is_downloaded )
    {
//        const size_t ext_width  = 1 << ( kvs::Math::Log2Smallest( width ) );
//        const size_t ext_height = 1 << ( kvs::Math::Log2Smallest( height ) );

        const GLint level = 0;  // level-of-detail number
        const GLint border = 0; // border width (0 or 1)
        glTexImage2D(
            GL_TEXTURE_2D,
            level,
            BaseClass::internalFormat(),
            width,
            height,
            border,
            BaseClass::externalFormat(),
            BaseClass::externalType(),
            pixels );

        m_is_downloaded = true;
    }
    else
    {
        const GLint level = 0; // level-of-detail number
        glTexSubImage2D(
            GL_TEXTURE_2D,
            level,
            xoffset,
            yoffset,
            width,
            height,
            BaseClass::externalFormat(),
            BaseClass::externalType(),
            pixels );
    }

    glPixelStorei( GL_UNPACK_ALIGNMENT, alignment );
    glPixelStorei( GL_UNPACK_SWAP_BYTES, swap );
}

/*==========================================================================*/
/**
 *  Bind the texture.
 */
/*==========================================================================*/
void Texture2D::bind( void )
{
    glBindTexture( GL_TEXTURE_2D, m_id );
}

/*==========================================================================*/
/**
 *  Unbind the texture.
 */
/*==========================================================================*/
void Texture2D::unbind( void )
{
    glBindTexture( GL_TEXTURE_2D, 0 );
}

/*==========================================================================*/
/**
 *  Release the texture.
 */
/*==========================================================================*/
void Texture2D::release( void )
{
    if ( glIsTexture( m_id ) == GL_TRUE ) glDeleteTextures( 1, &m_id );

    m_id = 0;
    m_is_downloaded = false;
}

/*==========================================================================*/
/**
 *  Returns the used texture memory size.
 *  @return Used texture memory size [byte]
 */
/*==========================================================================*/
unsigned int Texture2D::UsedTextureMemorySize( void )
{
    return( Texture2D::get_texture_memory_size_on_gpu( GL_PROXY_TEXTURE_2D ) );
}

/*==========================================================================*/
/**
 *  Returns the used texture memory size for given proxy.
 *  @param proxy [in] proxy
 *  @return Used texture memory size [byte]
 */
/*==========================================================================*/
unsigned int Texture2D::get_texture_memory_size_on_gpu( const GLenum proxy )
{
    // Get the texture size.
    GLint texture_size[2] = { 0, 0 };
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_WIDTH,          &(texture_size[0]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_HEIGHT,         &(texture_size[1]) );

    // Get the each channel size.
    GLint channel_size[7] = { 0, 0, 0, 0, 0, 0, 0 };
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_RED_SIZE,       &(channel_size[0]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_GREEN_SIZE,     &(channel_size[1]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_BLUE_SIZE,      &(channel_size[2]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_ALPHA_SIZE,     &(channel_size[3]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_LUMINANCE_SIZE, &(channel_size[4]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_INTENSITY_SIZE, &(channel_size[5]) );
#if GL_EXT_paletted_texture
    //glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_INDEX_SIZE_EXT, &(channel_size[6]) );
#endif

#if GL_ARB_texture_compression
    // Get compressed texture size.
    GLint compressed[1] = { 0 };
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_COMPRESSED_ARB, &(compressed[0]) );
    if( compressed[0] )
    {
        GLint  size[1] = { 0 };
#if   GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB
        GLenum pname = GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB;
        glGetTexLevelParameteriv( proxy, 0, pname, &(size[0]) );
#elif GL_TEXTURE_IMAGE_SIZE_ARB
        GLenum pname = GL_TEXTURE_IMAGE_SIZE_ARB;
        glGetTexLevelParameteriv( proxy, 0, pname, &(size[0]) );
#endif
        return( size[0] );
    }
#endif

    // Compute the number of bytes per voxel.
    GLint total_bits =
        channel_size[0] +
        channel_size[1] +
        channel_size[2] +
        channel_size[3] +
        channel_size[4] +
        channel_size[5] +
        channel_size[6];

    // Convert unit from 'bit' to 'byte'.
    GLfloat bytes = (GLfloat)total_bits / 8.0f;

    // Round up to the next whole byte.
    if( !kvs::Math::Equal( bytes, (GLfloat)( (GLint)bytes) ) )
    {
        bytes = (GLfloat)((GLint)bytes) + 1.0f;
    }

    // compute the amount of texture memory used.
    return( texture_size[0] * texture_size[1] * (GLint)bytes );
}

} // end of namespace kvs
