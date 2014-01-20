/*****************************************************************************/
/**
 *  @file   ObjectBase.cpp
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
#include "ObjectBase.h"
#include <iomanip>
#include <kvs/Camera>
#include <kvs/Math>
#include <kvs/OpenGL>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ObjectBase class.
 *  @param  collision [in] collision detection flag
 */
/*===========================================================================*/
ObjectBase::ObjectBase( const bool collision ):
    kvs::XformControl(),
    m_can_collision( collision ),
    m_name("unknown"),
    m_min_object_coord( kvs::Vec3( -3.0, -3.0, -3.0 ) ),
    m_max_object_coord( kvs::Vec3(  3.0,  3.0,  3.0 ) ),
    m_min_external_coord( kvs::Vec3( -3.0, -3.0, -3.0 ) ),
    m_max_external_coord( kvs::Vec3(  3.0,  3.0,  3.0 ) ),
    m_has_min_max_object_coords( false ),
    m_has_min_max_external_coords( false ),
    m_show_flag( true )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the ObjectBase class.
 */
/*===========================================================================*/
ObjectBase::~ObjectBase()
{
}

/*===========================================================================*/
/**
 *  @brief  '=' operator.
 */
/*===========================================================================*/
ObjectBase& ObjectBase::operator = ( const ObjectBase& object )
{
    kvs::XformControl::operator =( object );
    m_name = object.m_name;
    m_min_object_coord = object.m_min_object_coord;
    m_max_object_coord = object.m_max_object_coord;
    m_min_external_coord = object.m_min_external_coord;
    m_max_external_coord = object.m_max_external_coord;
    m_has_min_max_object_coords = object.m_has_min_max_object_coords;
    m_has_min_max_external_coords = object.m_has_min_max_external_coords;
    m_object_center = object.m_object_center;
    m_external_position = object.m_external_position;
    m_normalize = object.m_normalize;
    m_show_flag = object.m_show_flag;

    return *this;
}

/*===========================================================================*/
/**
 *  @breif  Sets the min/max object coordinates.
 *  @param  min_coord [in] min. object coordinate value
 *  @param  max_coord [in] max. object coordinate value
 */
/*===========================================================================*/
void ObjectBase::setMinMaxObjectCoords(
    const kvs::Vec3& min_coord,
    const kvs::Vec3& max_coord )
{
    m_min_object_coord = min_coord;
    m_max_object_coord = max_coord;
    m_has_min_max_object_coords = true;
    this->updateNormalizeParameters();
}

/*===========================================================================*/
/**
 *  @breif  Sets the min/max external coordinates.
 *  @param  min_coord [in] min. external coordinate value
 *  @param  max_coord [in] max. external coordinate value
 */
/*===========================================================================*/
void ObjectBase::setMinMaxExternalCoords(
    const kvs::Vec3& min_coord,
    const kvs::Vec3& max_coord )
{
    m_min_external_coord = min_coord;
    m_max_external_coord = max_coord;
    m_has_min_max_external_coords = true;
    this->updateNormalizeParameters();
}

/*===========================================================================*/
/**
 *  @brief  Prints information of the object base.
 *  @param  os [in] output stream
 *  @param  indent [in] indent
 */
/*===========================================================================*/
void ObjectBase::print( std::ostream& os, const kvs::Indent& indent ) const
{
    const std::ios_base::fmtflags flags( os.flags() );
    os << indent << "Name : " << this->name() << std::endl;
    os.setf( std::ios::boolalpha );
    os << indent << "Set of min/max object coord : " << this->hasMinMaxObjectCoords() << std::endl;
    os << indent << "Set of min/max external coord : " << this->hasMinMaxObjectCoords() << std::endl;
    os.unsetf( std::ios::boolalpha );
    os << indent << "Min object coord : " << this->minObjectCoord() << std::endl;
    os << indent << "Max object coord : " << this->maxObjectCoord() << std::endl;
    os << indent << "Min external coord : " << this->minExternalCoord() << std::endl;
    os << indent << "Max external coord : " << this->maxExternalCoord() << std::endl;
    os << indent << "Object center : " << this->objectCenter() << std::endl;
    os << indent << "External position : " << this->externalPosition() << std::endl;
    os << indent << "Normalize parameter : " << this->normalize() << std::endl;
    os.flags( flags );
}

/*===========================================================================*/
/**
 *  @brief  Returns the object position in the device coordinate.
 *  @param  camera [in] camera
 *  @param  global_trans [in] translation vector in the global
 *  @param  global_scale [in] scaling vector in the global
 *  @return object position in the device coordinate
 */
/*===========================================================================*/
const kvs::Vec2 ObjectBase::positionInDevice(
    kvs::Camera* camera,
    const kvs::Vec3& global_trans,
    const kvs::Vec3& global_scale ) const
{
    kvs::Vec2 ret;
    kvs::OpenGL::PushMatrix();
    {
        camera->update();

        ObjectBase::transform( global_trans, global_scale );

        ret = camera->projectObjectToWindow( m_object_center );
        ret.y() = camera->windowHeight() - ret.y();
    }
    kvs::OpenGL::PopMatrix();

    return ret;
}

/*===========================================================================*/
/**
 *  @brief  Returns the object position in the world coordinate.
 *  @param  global_trans [in] translation vector in the global
 *  @param  global_scale [in] scaling vector in the global
 *  @return object position in the world coordinate
 */
/*===========================================================================*/
const kvs::Vec3 ObjectBase::positionInWorld(
    const kvs::Vec3& global_trans,
    const kvs::Vec3& global_scale ) const
{
    kvs::Vec3 init_pos = m_external_position - global_trans;

    init_pos.x() *= global_scale.x();
    init_pos.y() *= global_scale.y();
    init_pos.z() *= global_scale.z();

    return this->xform().transform( init_pos );
}

/*===========================================================================*/
/**
 *  @brief  Updates the normalize parameters.
 */
/*===========================================================================*/
void ObjectBase::updateNormalizeParameters()
{
    kvs::Vec3 diff_obj = m_max_object_coord - m_min_object_coord;
    kvs::Vec3 diff_ext = m_max_external_coord - m_min_external_coord;

    m_object_center = ( m_max_object_coord + m_min_object_coord ) * 0.5;
    m_external_position = ( m_max_external_coord + m_min_external_coord ) * 0.5;

    if ( kvs::Math::Equal( diff_obj.x(), 0.0f ) &&
         kvs::Math::Equal( diff_obj.y(), 0.0f ) &&
         kvs::Math::Equal( diff_obj.z(), 0.0f ) )
    {
        // In the case of 'diff_obj == (0,0,0)', such as a point object composed of
        // a single vertex point, the normalization parameters is set to '(1,1,1)'.
        m_normalize = kvs::Vec3( 1.0f, 1.0f, 1.0f );
    }
    else
    {
        m_normalize.x() =
            ( !kvs::Math::Equal( diff_obj.x(), 0.0f ) ) ? diff_ext.x() / diff_obj.x() :
            ( kvs::Math::Equal( diff_obj.y(), 0.0f ) ) ? diff_ext.z() / diff_obj.z() :
            ( kvs::Math::Equal( diff_obj.z(), 0.0f ) ) ? diff_ext.y() / diff_obj.y() :
            kvs::Math::Max( diff_ext.y() / diff_obj.y(), diff_ext.z() / diff_obj.z() );

        m_normalize.y() =
            ( !kvs::Math::Equal( diff_obj.y(), 0.0f ) ) ? diff_ext.y() / diff_obj.y() :
            ( kvs::Math::Equal( diff_obj.x(), 0.0f ) ) ? diff_ext.z() / diff_obj.z() :
            ( kvs::Math::Equal( diff_obj.z(), 0.0f ) ) ? diff_ext.x() / diff_obj.x() :
            kvs::Math::Max( diff_ext.x() / diff_obj.x(), diff_ext.z() / diff_obj.z() );

        m_normalize.z() =
            ( !kvs::Math::Equal( diff_obj.z(), 0.0f ) ) ? diff_ext.z() / diff_obj.z() :
            ( kvs::Math::Equal( diff_obj.x(), 0.0f ) ) ? diff_ext.y() / diff_obj.y() :
            ( kvs::Math::Equal( diff_obj.y(), 0.0f ) ) ? diff_ext.x() / diff_obj.x() :
            kvs::Math::Max( diff_ext.x() / diff_obj.x(), diff_ext.y() / diff_obj.y() );
    }
}

/*===========================================================================*/
/**
 *  @brief  Transform the object.
 *  @param  Tg [in] translation vector in the global
 *  @param  Sg [in] scaling vector in the global
 */
/*===========================================================================*/
void ObjectBase::transform( const kvs::Vec3& Tg, const kvs::Vec3& Sg ) const
{
    float X[16]; this->xform().toArray( X );
    const kvs::Vec3& Te = m_external_position;
    const kvs::Vec3& Sl = m_normalize;
    const kvs::Vec3& Tl = m_object_center;

    kvs::OpenGL::MultMatrix( X );
    kvs::OpenGL::Scale( Sg.x(), Sg.y(), Sg.z() );
    kvs::OpenGL::Translate( -Tg.x(), -Tg.y(), -Tg.z() );
    kvs::OpenGL::Translate( Te.x(), Te.y(), Te.z() );
    kvs::OpenGL::Scale( Sl.x(), Sl.y(), Sl.z() );
    kvs::OpenGL::Translate( -Tl.x(), -Tl.y(), -Tl.z() );
}

/*===========================================================================*/
/**
 *  @brief  Executes collision detection.
 *  @param  p_win [in] point in the window coordinate system
 *  @param  camera [in] pointer to the camera
 *  @param  global_trans [in] translation vector in the global
 *  @param  global_scale [in] scaling vector in the global
 *  @return true, if the collision is detected.
 *
 *  This method in current version is not accurate. In this version,
 *  we don't take account of depth from camera position to the object.
 */
/*===========================================================================*/
bool ObjectBase::collision(
    const kvs::Vec2& p_win,
    kvs::Camera* camera,
    const kvs::Vec3& global_trans,
    const kvs::Vec3& global_scale )
{
    float max_distance = -1.0f;

    // Center of this object in the window coordinate system.
    kvs::Vec2 center;

    kvs::OpenGL::PushMatrix();
    {
        camera->update();

        ObjectBase::transform( global_trans, global_scale );

        center = camera->projectObjectToWindow( m_object_center );

        // Object's corner points in the object coordinate system.
        const kvs::Vec3 corners[8] = {
            kvs::Vec3( m_min_object_coord.x(), m_min_object_coord.y(), m_min_object_coord.z() ),
            kvs::Vec3( m_max_object_coord.x(), m_min_object_coord.y(), m_min_object_coord.z() ),
            kvs::Vec3( m_min_object_coord.x(), m_min_object_coord.y(), m_max_object_coord.z() ),
            kvs::Vec3( m_max_object_coord.x(), m_min_object_coord.y(), m_max_object_coord.z() ),
            kvs::Vec3( m_min_object_coord.x(), m_max_object_coord.y(), m_min_object_coord.z() ),
            kvs::Vec3( m_max_object_coord.x(), m_max_object_coord.y(), m_min_object_coord.z() ),
            kvs::Vec3( m_min_object_coord.x(), m_max_object_coord.y(), m_max_object_coord.z() ),
            kvs::Vec3( m_max_object_coord.x(), m_max_object_coord.y(), m_max_object_coord.z() ) };

        // Calculate max distance between the center and the corner in
        // the window coordinate system.
        for( int i = 0; i < 8; i++ )
        {
            const kvs::Vec2 corner = camera->projectObjectToWindow( corners[i] );
            const float distance = static_cast<float>( ( corner - center ).length() );
            max_distance = kvs::Math::Max( max_distance, distance );
        }
    }
    kvs::OpenGL::PopMatrix();

    kvs::Vec2 pos_window( p_win.x(), camera->windowHeight() - p_win.y() );

    return ( pos_window - center ).length() < max_distance;
}

/*===========================================================================*/
/**
 *  @brief  Executes collision detection.
 *  @param  p_world [in] point in the world coordinate system
 *  @param  global_trans [in] translation vector in the global
 *  @param  global_scale [in] scaling vector in the global
 *  @return true, if the collision is detected.
 */
/*===========================================================================*/
bool ObjectBase::collision(
    const kvs::Vec3& p_world,
    const kvs::Vec3& global_trans,
    const kvs::Vec3& global_scale )
{
    float max_distance = -1.0f;
    kvs::Vec3 center;

    center = object_to_world_coordinate( m_object_center, global_trans, global_scale );

    // Object's corner points in the object coordinate system.
    const kvs::Vec3 corners[8] = {
        kvs::Vec3( m_min_object_coord.x(), m_min_object_coord.y(), m_min_object_coord.z() ),
        kvs::Vec3( m_max_object_coord.x(), m_min_object_coord.y(), m_min_object_coord.z() ),
        kvs::Vec3( m_min_object_coord.x(), m_min_object_coord.y(), m_max_object_coord.z() ),
        kvs::Vec3( m_max_object_coord.x(), m_min_object_coord.y(), m_max_object_coord.z() ),
        kvs::Vec3( m_min_object_coord.x(), m_max_object_coord.y(), m_min_object_coord.z() ),
        kvs::Vec3( m_max_object_coord.x(), m_max_object_coord.y(), m_min_object_coord.z() ),
        kvs::Vec3( m_min_object_coord.x(), m_max_object_coord.y(), m_max_object_coord.z() ),
        kvs::Vec3( m_max_object_coord.x(), m_max_object_coord.y(), m_max_object_coord.z() ) };

    // Calculate max distance between the center and the corner in
    // the world coordinate system.
    for( int i = 0; i < 8; i++ )
    {
        const kvs::Vec3 corner =
            this->object_to_world_coordinate( corners[i], global_trans, global_scale );
        const float distance = static_cast<float>( ( corner - center ).length() );
        max_distance = kvs::Math::Max( max_distance, distance );
    }

    return ( p_world - center ).length() < max_distance;
}

/*===========================================================================*/
/**
 *  @brief  Projects the point from the object coord. to world coord.
 *  @param  p_obj [in] point in the object coordinate
 *  @param  global_trans [in] translation vector in the global
 *  @param  global_scale [in] scaling vector in the global
 *  @return projected point in the world coodinate.
 */
/*===========================================================================*/
const kvs::Vec3 ObjectBase::object_to_world_coordinate(
    const kvs::Vec3& p_obj,
    const kvs::Vec3& global_trans,
    const kvs::Vec3& global_scale ) const
{
    kvs::Vec3 p_external = p_obj - m_object_center;

    p_external.x() *= m_normalize.x();
    p_external.y() *= m_normalize.y();
    p_external.z() *= m_normalize.z();

    p_external += m_external_position;

    kvs::Vec3 p_world = p_external - global_trans;

    p_world.x() *= global_scale.x();
    p_world.y() *= global_scale.y();
    p_world.z() *= global_scale.z();

    return this->xform().transform( p_world );
}

/*==========================================================================*/
/**
 *  Enable collision detection.
 */
/*==========================================================================*/
void ObjectBase::enableCollision()
{
    m_can_collision = true;
}

/*==========================================================================*/
/**
 *  Disable collision detection.
 */
/*==========================================================================*/
void ObjectBase::disableCollision()
{
    m_can_collision = false;
}

/*==========================================================================*/
/**
 *  Test whether the collision is detected.
 */
/*==========================================================================*/
bool ObjectBase::canCollision() const
{
    return m_can_collision;
}

/*===========================================================================*/
/**
 *  @brief  Sets a object center in the object coordinate system.
 *  @param  object_center [in] object center
 */
/*===========================================================================*/
void ObjectBase::setObjectCenter( const kvs::Vec3& object_center )
{
    m_object_center = object_center;
}

/*===========================================================================*/
/**
 *  @brief  Sets a normalize parameter.
 *  @param  normalize [in] normalize parameter
 */
/*===========================================================================*/
void ObjectBase::setNormalize( const kvs::Vec3& normalize )
{
    m_normalize = normalize;
}

/*===========================================================================*/
/**
 *  @brief  '<<' operator.
 */
/*===========================================================================*/
std::ostream& operator << ( std::ostream& os, const ObjectBase& object )
{
    const std::ios_base::fmtflags flags( os.flags() );
    os << "Name: " << object.name() << std::endl;
    os.setf( std::ios::boolalpha );
    os << "Set of min/max object coord:  " << object.hasMinMaxObjectCoords() << std::endl;
    os << "Set of min/max external coord:  " << object.hasMinMaxObjectCoords() << std::endl;
    os.unsetf( std::ios::boolalpha );
    os << "Min object coord:  " << object.minObjectCoord() << std::endl;
    os << "Max object coord:  " << object.maxObjectCoord() << std::endl;
    os << "Min external coord:  " << object.minExternalCoord() << std::endl;
    os << "Max external coord:  " << object.maxExternalCoord() << std::endl;
    os << "Object center:  " << object.objectCenter() << std::endl;
    os << "External position:  " << object.externalPosition() << std::endl;
    os << "Normalize parameter:  " << object.normalize();
    os.flags( flags );

    return os;
}

} // end of namespace kvs
