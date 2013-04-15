/*****************************************************************************/
/**
 *  @file   WorldCoordinate.h
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
/*****************************************************************************/
#ifndef KVS__WORLD_COORDINATE_H_INCLUDE
#define KVS__WORLD_COORDINATE_H_INCLUDE

#include <kvs/Vector3>


namespace kvs
{

class Camera;
class ObjectBase;
class CameraCoordinate;
class ObjectCoordinate;

/*===========================================================================*/
/**
 *  @brief  World coordinate class.
 */
/*===========================================================================*/
class WorldCoordinate
{
private:

    kvs::Vector3f m_position; ///< position in world coordinates

public:

    WorldCoordinate( const kvs::Vector3f& position );

    const kvs::Vector3f& position() const;

    const CameraCoordinate toCameraCoordinate( const kvs::Camera* camera ) const;
    const ObjectCoordinate toObjectCoordinate( const kvs::ObjectBase* object ) const;
};

} // end of namespace kvs

#endif // KVS__WORLD_COORDINATE_H_INCLUDE
