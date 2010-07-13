/****************************************************************************/
/**
 *  @file XMLDeclaration.h
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
#ifndef KVS_CORE_XML_DECLARATION_H_INCLUDE
#define KVS_CORE_XML_DECLARATION_H_INCLUDE

#include <string>
#include "TinyXML.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  XML declaration class.
 */
/*==========================================================================*/
class XMLDeclaration : public TiXmlDeclaration
{
public:

    typedef TiXmlDeclaration SuperClass;

public:

    XMLDeclaration( void );

    XMLDeclaration(
        const std::string& version,
        const std::string& encoding = "",
        const std::string& standalone = "" );

    virtual ~XMLDeclaration( void );
};

} // end of namespace kvs

#endif // KVS_CORE_XML_DECLARATION_H_INCLUDE