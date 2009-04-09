/*****************************************************************************/
/**
 *  @file   LineObjectTag.h
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
#ifndef KVS__KVSML__LINE_OBJECT_TAG_H_INCLUDE
#define KVS__KVSML__LINE_OBJECT_TAG_H_INCLUDE

#include <string>
#include <kvs/XMLNode>
#include <kvs/Vector3>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <LineObject>
 */
/*===========================================================================*/
class LineObjectTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree
    bool m_has_line_type; ///< flag to check whether 'line_type' is specified or not
    std::string m_line_type; ///< line type
    bool m_has_color_type; ///< flag to check whether 'color_type' is specified or not
    std::string m_color_type; ///< color type

public:

    LineObjectTag( void );

    virtual ~LineObjectTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool hasLineType( void ) const;

    const std::string& lineType( void ) const;

    const bool hasColorType( void ) const;

    const std::string& colorType( void ) const;

public:

    void setLineType( const std::string& line_type );

    void setColorType( const std::string& color_type );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__LINE_OBJECT_TAG_H_INCLUDE
