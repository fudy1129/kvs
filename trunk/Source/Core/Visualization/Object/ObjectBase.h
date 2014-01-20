/*****************************************************************************/
/**
 *  @file   ObjectBase.h
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
#ifndef KVS__OBJECT_BASE_H_INCLUDE
#define KVS__OBJECT_BASE_H_INCLUDE

#include <iostream>
#include <kvs/XformControl>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Module>
#include <kvs/Indent>
#include <kvs/Deprecated>


namespace kvs
{

class Camera;

/*==========================================================================*/
/**
 *  Object base class.
 */
/*==========================================================================*/
class ObjectBase : public kvs::XformControl
{
    kvsModuleBase;
    kvsModuleName( kvs::ObjectBase );

public:

    enum ObjectType
    {
        Geometry = 0, ///< Geometric object.
        Volume, ///< Volumetric object.
        Image, ///< Image object
        Table, ///< table object
        ObjectManager, ///< Object manager
        UnknownObject ///< unknown object (for user defined object data)
    };

private:

    bool m_can_collision; ///< flag for collision detection
    std::string m_name; ///< object name
    kvs::Vec3 m_min_object_coord; ///< min coord in the object coordinate system
    kvs::Vec3 m_max_object_coord; ///< max coord in the object coordinate system
    kvs::Vec3 m_min_external_coord; ///< min coord in the external coordinate system
    kvs::Vec3 m_max_external_coord; ///< max coord in the external coordinate system
    bool m_has_min_max_object_coords; ///< has min-max coorinate values ?
    bool m_has_min_max_external_coords; ///< has min-max coorinate values ?
    kvs::Vec3 m_object_center; ///< center of gravity in object coordinate system
    kvs::Vec3 m_external_position; ///< position in external coordinate system
    kvs::Vec3 m_normalize; ///< normalize parameter
    bool m_show_flag; ///< flag for showing object

public:

    ObjectBase( const bool collision = true );
    virtual ~ObjectBase();

    ObjectBase& operator = ( const ObjectBase& object );

    void setName( const std::string& name ) { m_name = name; }
    void setMinMaxObjectCoords( const kvs::Vec3& min_coord, const kvs::Vec3& max_coord );
    void setMinMaxExternalCoords( const kvs::Vec3& min_coord, const kvs::Vec3& max_coord );
    void show() { m_show_flag = true; }
    void hide() { m_show_flag = false; }
    virtual void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    virtual ObjectType objectType() const = 0;
    const std::string& name() const { return m_name; }
    const kvs::Vec3& minObjectCoord() const { return m_min_object_coord; }
    const kvs::Vec3& maxObjectCoord() const { return m_max_object_coord; }
    const kvs::Vec3& minExternalCoord() const { return m_min_external_coord; }
    const kvs::Vec3& maxExternalCoord() const { return m_max_external_coord; }
    bool hasMinMaxObjectCoords() const { return m_has_min_max_object_coords; }
    bool hasMinMaxExternalCoords() const { return m_has_min_max_external_coords; }
    const kvs::Vec3& objectCenter() const { return m_object_center; }
    const kvs::Vec3& externalPosition() const { return m_external_position; }
    const kvs::Vec3& normalize() const { return m_normalize; }
    bool isShown() const { return m_show_flag; }
    const kvs::Vec2 positionInDevice( kvs::Camera* camera, const kvs::Vec3& global_trans, const kvs::Vec3& global_scale ) const;
    const kvs::Vec3 positionInWorld( const kvs::Vec3& global_trans, const kvs::Vec3& global_scale ) const;
    const kvs::Vec3& positionInExternal() const { return m_external_position; }

    virtual void updateMinMaxCoords(){};
    void updateNormalizeParameters();
    void transform( const kvs::Vec3& Tg, const kvs::Vec3& Sg ) const;
    bool collision( const kvs::Vec2& p_win, kvs::Camera* camera, const kvs::Vec3& global_trans, const kvs::Vec3& global_scale );
    bool collision( const kvs::Vec3& p_world, const kvs::Vec3& global_trans, const kvs::Vec3& global_scale );

    void enableCollision();
    void disableCollision();
    bool canCollision() const;

protected:

    void setObjectCenter( const kvs::Vec3& object_center );
    void setNormalize( const kvs::Vec3& normalize );

private:

    const kvs::Vec3 object_to_world_coordinate(
        const kvs::Vec3& p_obj,
        const kvs::Vec3& global_trans,
        const kvs::Vec3& global_scale ) const;

public:

    KVS_DEPRECATED( ObjectBase( const kvs::Vec3& translation, const kvs::Vec3& scaling, const kvs::Mat3& rotation, const bool collision = true ) )
    {
        m_can_collision = collision;
        m_name = std::string("unknown");
        m_min_object_coord = kvs::Vec3( -3.0, -3.0, -3.0 );
        m_max_object_coord = kvs::Vec3(  3.0,  3.0,  3.0 );
        m_min_external_coord = kvs::Vec3( -3.0, -3.0, -3.0 );
        m_max_external_coord = kvs::Vec3(  3.0,  3.0,  3.0 );
        m_has_min_max_object_coords = false;
        m_has_min_max_external_coords = false;
        m_show_flag = true;

        this->setXform( kvs::Xform( translation, scaling, rotation ) );
        this->saveXform();
    }

    KVS_DEPRECATED( void rotate( const kvs::Mat3& rotation, const kvs::Vec3& center ) )
    {
        const kvs::Xform x = kvs::Xform::Translation( center )
                           * kvs::Xform::Rotation( rotation )
                           * kvs::Xform::Translation( -center );
        this->multiplyXform( x );
    }

    KVS_DEPRECATED( void scale( const kvs::Vec3& scaling, const kvs::Vec3& center ) )
    {
        const kvs::Xform x = kvs::Xform::Translation( center )
                           * kvs::Xform::Scaling( scaling )
                           * kvs::Xform::Translation( -center );
        this->multiplyXform( x );
    }

    KVS_DEPRECATED( friend std::ostream& operator << ( std::ostream& os, const ObjectBase& object ) );
};

} // end of namespace kvs

#endif // KVS__OBJECT_BASE_H_INCLUDE
