/****************************************************************************/
/**
 *  @file ReadLocker.cpp
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
#include "ReadLocker.h"
#include "ReadWriteLock.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param rwlock [in] pointer to read/write lock
 */
/*==========================================================================*/
ReadLocker::ReadLocker( kvs::ReadWriteLock* rwlock )
    : m_rwlock( rwlock )
{
    this->relock();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
ReadLocker::~ReadLocker()
{
    this->unlock();
}

/*==========================================================================*/
/**
 *  Relock.
 */
/*==========================================================================*/
void ReadLocker::relock()
{
    if ( m_rwlock ) { m_rwlock->lockRead(); }
}

/*==========================================================================*/
/**
 *  Unlock.
 */
/*==========================================================================*/
void ReadLocker::unlock()
{
    if ( m_rwlock ) { m_rwlock->unlock(); }
}

/*==========================================================================*/
/**
 *  Get pointer to the read/write lock.
 *  @return pointer to the read/write lock
 */
/*==========================================================================*/
kvs::ReadWriteLock* ReadLocker::readWriteLock()
{
    return( m_rwlock );
}

} // end of namespace kvs
