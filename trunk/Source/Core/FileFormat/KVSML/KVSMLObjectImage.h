/****************************************************************************/
/**
 *  @file KVSMLObjectImage.h
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
#ifndef KVS__KVSML_OBJECT_IMAGE_H_INCLUDE
#define KVS__KVSML_OBJECT_IMAGE_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML image object format.
 */
/*===========================================================================*/
class KVSMLObjectImage : public kvs::FileFormatBase
{
    kvsClassName( kvs::KVSMLObjectImage );

public:

    typedef kvs::FileFormatBase BaseClass;

    enum WritingDataType
    {
        Ascii = 0,     ///< ascii data type
        ExternalAscii, ///< external ascii data type
        ExternalBinary ///< external binary data type
    };

protected:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< KVSML tag information
    kvs::kvsml::ObjectTag m_object_tag; ///< Object tag information
    size_t m_width; ///< image width
    size_t m_height; ///< image height
    std::string m_pixel_type; ///< pixel type
    WritingDataType m_writing_type; ///< writing data type
    kvs::ValueArray<kvs::UInt8> m_data; ///< color(r,g,b) array

public:

    KVSMLObjectImage();
    KVSMLObjectImage( const std::string& filename );
    virtual ~KVSMLObjectImage();

public:

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    const kvs::kvsml::ObjectTag& objectTag() const;

public:

    size_t width() const;
    size_t height() const;
    const std::string& pixelType() const;
    const kvs::ValueArray<kvs::UInt8>& data() const;

public:

    void setWidth( const size_t width );
    void setHeight( const size_t height );
    void setPixelType( const std::string& pixel_type );
    void setWritingDataType( const WritingDataType writing_type );
    void setData( const kvs::ValueArray<kvs::UInt8>& data );

public:

    bool read( const std::string& filename );
    bool write( const std::string& filename );

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );

    friend std::ostream& operator <<( std::ostream& os, const KVSMLObjectImage& rhs );
};

} // end of namespace kvs

#endif // KVS__KVSML_OBJECT_IMAGE_H_INCLUDE
