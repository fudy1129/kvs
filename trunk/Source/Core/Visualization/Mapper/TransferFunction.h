/****************************************************************************/
/**
 *  @file TransferFunction.h
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
#ifndef KVS_CORE_TRANSFER_FUNCTION_H_INCLUDE
#define KVS_CORE_TRANSFER_FUNCTION_H_INCLUDE

#include <kvs/ClassName>

#include <kvs/ColorMap>
#include <kvs/OpacityMap>


namespace kvs
{

/*==========================================================================*/
/**
 *  TransferFunction.
 */
/*==========================================================================*/
class TransferFunction
{
    kvsClassName( TransferFunction );

private:

    kvs::ColorMap   m_color_map;   ///< Color map.
    kvs::OpacityMap m_opacity_map; ///< Opacity map.

public:

    explicit TransferFunction( const size_t resolution = 256 );

    TransferFunction( const std::string& filename );

    // 'explicit' is not specified by design.
    TransferFunction( const kvs::ColorMap& color_map );

    // 'explicit' is not specified by design.
    TransferFunction( const kvs::OpacityMap& opacity_map );

    TransferFunction(
        const kvs::ColorMap&   color_map,
        const kvs::OpacityMap& opacity_map );

    TransferFunction( const TransferFunction& other );

    virtual ~TransferFunction( void );

public:

    void setColorMap( const kvs::ColorMap& color_map );

    void setOpacityMap( const kvs::OpacityMap& opacity_map );

public:

    const kvs::ColorMap& colorMap( void ) const;

    const kvs::OpacityMap& opacityMap( void ) const;

public:

    const size_t resolution( void ) const;

public:

    void create( const size_t resolution );

    const bool read( const std::string& filename );

    const bool write( const std::string& filename );

public:

    TransferFunction& operator =( const TransferFunction& rhs );
};

} // end of namespace kvs

#endif // KVS_CORE_TRANSFER_FUNCTION_H_INCLUDE