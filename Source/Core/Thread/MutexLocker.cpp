/****************************************************************************/
/**
 *  @file MutexLocker.cpp
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
#include "MutexLocker.h"

#include "Mutex.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param mutex [in] pointer to the mutex
 */
/*==========================================================================*/
MutexLocker::MutexLocker( kvs::Mutex* mutex )
    : m_mutex( mutex )
{
    this->relock();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
MutexLocker::~MutexLocker( void )
{
    this->unlock();
}

/*==========================================================================*/
/**
 *  Relock.
 */
/*==========================================================================*/
void MutexLocker::relock( void )
{
    if ( m_mutex ) { m_mutex->lock(); }
}

/*==========================================================================*/
/**
 *  Unlock.
 */
/*==========================================================================*/
void MutexLocker::unlock( void )
{
    if ( m_mutex ) { m_mutex->unlock(); }
}

/*==========================================================================*/
/**
 *  Get pointer to the mutex.
 *  @return pointer to the mutex
 */
/*==========================================================================*/
Mutex* MutexLocker::mutex( void )
{
    return( m_mutex );
}

} // end of namespace kvs
