/****************************************************************************/
/**
 *  @file SystemInformation.h
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
#ifndef KVS_CORE_SYSTEM_INFORMATION_H_INCLUDE
#define KVS_CORE_SYSTEM_INFORMATION_H_INCLUDE

#include <cstdio>


namespace kvs
{

/*==========================================================================*/
/**
 *  System information class.
 */
/*==========================================================================*/
class SystemInformation
{
public:

    static const size_t nprocessors( void );

    static const size_t totalMemorySize( void );

    static const size_t freeMemorySize( void );
};

} // end of namespace kvs

#endif // KVS_CORE_SYSTEM_INFORMATION_H_INCLUDE