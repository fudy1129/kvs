/****************************************************************************/
/**
 *  @file XMLComment.cpp
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
#include "XMLComment.h"

namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
XMLComment::XMLComment( void )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param comment [in] comments
 */
/*==========================================================================*/
XMLComment::XMLComment( const char* comment ):
    TiXmlComment()
{
    this->SetValue( comment );
}

/*==========================================================================*/
/**
 *  Desturctor.
 */
/*==========================================================================*/
XMLComment::~XMLComment( void )
{
}

} // end of namespace kvs
