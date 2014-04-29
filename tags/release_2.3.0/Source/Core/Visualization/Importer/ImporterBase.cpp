/****************************************************************************/
/**
 *  @file   ImporterBase.cpp
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
#include "ImporterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ImporterBase class.
 */
/*===========================================================================*/
ImporterBase::ImporterBase():
    m_is_success( true )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the ImageBase class.
 */
/*===========================================================================*/
ImporterBase::~ImporterBase()
{
}

/*===========================================================================*/
/**
 *  @brief  Check whether the object is imported or not.
 *  @return true if the import process is done successfully
 */
/*===========================================================================*/
bool ImporterBase::isSuccess() const
{
    return m_is_success;
}

/*===========================================================================*/
/**
 *  @brief  Check whether the object is imported or not.
 *  @return true if the object is not imported
 */
/*===========================================================================*/
bool ImporterBase::isFailure() const
{
    return !m_is_success;
}

/*===========================================================================*/
/**
 *  @brief  Sets a status of the importing process.
 *  @param  success [in] status of importing process
 */
/*===========================================================================*/
void ImporterBase::setSuccess( const bool success )
{
    m_is_success = success;
}

} // end of namespace kvs
