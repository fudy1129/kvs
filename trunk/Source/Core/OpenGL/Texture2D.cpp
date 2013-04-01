/****************************************************************************/
/**
 *  @file   Texture2D.cpp
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
#include "Texture2D.h"
#include <kvs/Math>
#include <kvs/OpenGL>
#include <kvs/Assert>
#include <iostream>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Texture2D::Texture2D():
    Texture( GL_TEXTURE_2D ),
    m_is_downloaded( false )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Texture2D::~Texture2D()
{
    this->release();
}

bool Texture2D::isDownloaded() const
{
    return m_is_downloaded;
}

/*==========================================================================*/
/**
 *  Create the texture.
 */
/*==========================================================================*/
void Texture2D::create( const size_t width, const size_t height )
{
    KVS_ASSERT( width > 0 );
    KVS_ASSERT( width <= kvs::OpenGL::MaxTextureSize() );
    KVS_ASSERT( height > 0 );
    KVS_ASSERT( height <= kvs::OpenGL::MaxTextureSize() );

    BaseClass::generateTexture();
    BaseClass::bind();
    BaseClass::setParameter( GL_TEXTURE_MAG_FILTER, BaseClass::magFilter() );
    BaseClass::setParameter( GL_TEXTURE_MIN_FILTER, BaseClass::minFilter() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_S, BaseClass::wrapS() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_T, BaseClass::wrapT() );
    this->download( width, height, NULL );
}

/*==========================================================================*/
/**
 *  Release the texture.
 */
/*==========================================================================*/
void Texture2D::release()
{
    BaseClass::deleteTexture();
    m_is_downloaded = false;
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
    const void* pixels,
    const size_t xoffset,
    const size_t yoffset )
{
    BaseClass::setSize( width, height );

    const GLint swap = kvs::OpenGL::Integer( GL_UNPACK_SWAP_BYTES );
    const GLint alignment = kvs::OpenGL::Integer( GL_UNPACK_ALIGNMENT );
    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap ? GL_TRUE : GL_FALSE );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, 1 );

    if ( !m_is_downloaded )
    {
        BaseClass::setImage2D( width, height, pixels );
        m_is_downloaded = true;
    }
    else
    {
        BaseClass::setSubImage2D( width, height, pixels, xoffset, yoffset );
    }

    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, alignment );
}

} // end of namespace kvs