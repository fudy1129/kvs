/****************************************************************************/
/**
 *  @file Trackball.cpp
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
#include "Trackball.h"
#include <kvs/Camera>
#include <kvs/Matrix33>
#include <kvs/Quaternion>


namespace
{

const float ScalingFactor = 100.0f;
const float Sqrt2 = 1.4142135623730950488f;
const float HalfOfSqrt2 = 0.7071067811865475244f;

} // end of namespace


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Trackball::Trackball()
{
    this->reset();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Trackball::~Trackball()
{
    this->reset();
}

/*==========================================================================*/
/**
 *  Attach the camera.
 *  @param camera [in] pointer to the camera
 */
/*==========================================================================*/
void Trackball::attachCamera( kvs::Camera* camera )
{
    m_ref_camera = camera;
}

/*==========================================================================*/
/**
 *  Reset the center of rotation.
 */
/*==========================================================================*/
void Trackball::resetRotationCenter()
{
    m_rotation_center = kvs::Vector2f( 0.0, 0.0 );
}

/*==========================================================================*/
/**
 *  Set virtual trackball size
 *  @param size [in] trackball size
 */
/*==========================================================================*/
void Trackball::setTrackballSize( const float size )
{
    m_size = size;
}

/*==========================================================================*/
/**
 *  Set depth value.
 *  @param depth [in] depth
 */
/*==========================================================================*/
void Trackball::setDepthValue( const float depth )
{
    m_depth = depth;
}

/*==========================================================================*/
/**
 *  Set the center of rotation.
 *  @param center [in] center of rotation
 */
/*==========================================================================*/
void Trackball::setRotationCenter( const kvs::Vector2f& center )
{
    m_rotation_center = center;
}

void Trackball::setScaling( const kvs::Vector3f& scaling )
{
    m_scaling = scaling;
}

void Trackball::setTranslation( const kvs::Vector3f& translation )
{
    m_translation = translation;
}

void Trackball::setRotation( const kvs::Quaternion& rotation )
{
    m_rotation = rotation;
}

/*==========================================================================*/
/**
 *  Set window size.
 *  @param width [in] window width
 *  @param height [in] window height
 */
/*==========================================================================*/
void Trackball::setWindowSize( const int width, const int height )
{
    m_window_width  = width;
    m_window_height = height;
}

/*==========================================================================*/
/**
 *  Get virtual trackball size.
 */
/*==========================================================================*/
float Trackball::size() const
{
    return m_size;
}

/*==========================================================================*/
/**
 *  Get depth value.
 */
/*==========================================================================*/
float Trackball::depthValue() const
{
    return m_depth;
}

/*==========================================================================*/
/**
 *  Get center of rotation.
 */
/*==========================================================================*/
const kvs::Vector2f& Trackball::rotationCenter() const
{
    return m_rotation_center;
}

/*==========================================================================*/
/**
 *  Get scaling value.
 */
/*==========================================================================*/
const kvs::Vector3f& Trackball::scaling() const
{
    return m_scaling;
}

/*==========================================================================*/
/**
 *  Get translation vector.
 */
/*==========================================================================*/
const kvs::Vector3f& Trackball::translation() const
{
    return m_translation;
}

/*==========================================================================*/
/**
 *  Get roation matrix.
 */
/*==========================================================================*/
const kvs::Quaternion& Trackball::rotation() const
{
    return m_rotation;
}

/*==========================================================================*/
/**
 *  Get window width.
 */
/*==========================================================================*/
int Trackball::windowWidth() const
{
    return m_window_width;
}

/*==========================================================================*/
/**
 *  Get window height.
 */
/*==========================================================================*/
int Trackball::windowHeight() const
{
    return m_window_height;
}

/*==========================================================================*/
/**
 *  Scaling.
 *  @param start [in] start dragging point
 *  @param end [in] end dragging point
 */
/*==========================================================================*/
void Trackball::scale(
    const kvs::Vector2i& start,
    const kvs::Vector2i& end,
    ScalingType          type )
{
    m_scaling = kvs::Vector3f( 1.0, 1.0, 1.0 );

    const kvs::Vector2f n_old = this->get_norm_position( start );
    const kvs::Vector2f n_new = this->get_norm_position( end );

    const float h = static_cast<float>( m_window_height );
    const float s = 1.0f + ::ScalingFactor * ( n_old.y() - n_new.y() ) / h;
    switch ( type )
    {
    case ScalingXYZ: m_scaling.set( s, s, s ); break;
    case ScalingX:   m_scaling.set( s, 1, 1 ); break;
    case ScalingY:   m_scaling.set( 1, s, 1 ); break;
    case ScalingZ:   m_scaling.set( 1, 1, s ); break;
    case ScalingXY:  m_scaling.set( s, s, 1 ); break;
    case ScalingYZ:  m_scaling.set( 1, s, s ); break;
    case ScalingZX:  m_scaling.set( s, 1, s ); break;
    default:         m_scaling.set( 1, 1, 1 ); break;
    }
}

/*==========================================================================*/
/**
 *  Translation function
 *  @param start [in] start dragging point in the window coordinate system
 *  @param end [in] end dragging point in the widnow coordinate system
 */
/*==========================================================================*/
void Trackball::translate( const kvs::Vector2i& start, const kvs::Vector2i& end )
{
    kvs::Vector2i diff = end - start;
    kvs::Vector3f trans;
    trans.x() = (float)diff.x() * 10.0f / m_window_width;
    trans.y() = -(float)diff.y() * 10.0f / m_window_height;
    trans.z() = 0;

    // Transform camera to world.
    m_translation = m_ref_camera->xform().transformNormal( trans );
}

/*==========================================================================*/
/**
 *  Rotation function
 *  @param start [in] start dragging point in the window coordinate system
 *  @param end [in] end dragging point in the window coordinate system
 */
/*==========================================================================*/
void Trackball::rotate( const kvs::Vector2i& start, const kvs::Vector2i& end )
{
    if( start == end )
    {
        m_rotation.set( 0.0, 0.0, 0.0, 1.0 );
        return;
    }

    kvs::Vector2f n_old( this->get_norm_position( start ) );
    kvs::Vector2f n_new( this->get_norm_position( end   ) );

    kvs::Vector3f p1( n_old, this->depth_on_sphere( n_old ) );
    kvs::Vector3f p2( n_new, this->depth_on_sphere( n_new ) );

    // Transform to world coordinate.
    kvs::Vector3f p1w = m_ref_camera->xform().transformNormal( p1 );
    kvs::Vector3f p2w = m_ref_camera->xform().transformNormal( p2 );

    m_rotation = kvs::Quaternion::rotationQuaternion( p1w, p2w );
}

/*==========================================================================*/
/**
 *  Reset.
 */
/*==========================================================================*/
void Trackball::reset()
{
    m_size            = 0.6f;
    m_depth           = 1.0f;
    m_rotation_center = kvs::Vector2f( 0.0f, 0.0f );
    m_scaling         = kvs::Vector3f( 1.0f, 1.0f, 1.0f );
    m_translation     = kvs::Vector3f( 0.0f, 0.0f, 0.0f );
    m_rotation        = kvs::Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
}

/*==========================================================================*/
/**
 *  Calculate a distance between 'dir' and the virtual sphere.
 *  @param dir [in] position
 *  @return distance
 */
/*==========================================================================*/
float Trackball::depth_on_sphere( const kvs::Vector2f& dir ) const
{
    const double r = m_size;
    const double d = dir.length();
    float z;

    // inside sphere
    if( d < r * ::HalfOfSqrt2 )
    {
        z = static_cast<float>( std::sqrt( r * r - d * d ) );
    }

    // on hyperbola
    else
    {
        const double t = r / ::Sqrt2;
        z = static_cast<float>( t * t / d );
    }

    return z;
}

/*==========================================================================*/
/**
 *  Get the mouse position.
 *  @return mouse position (on the normal device coordinate system)
 *
 *  Get the mouse position on the normal device coordinate system.
 *  A center of the normal device coordinate system is a center of the image
 *  and the rage is [-1,-1].
 */
/*==========================================================================*/
kvs::Vector2f Trackball::get_norm_position( const kvs::Vector2i& pos ) const
{
    const float x =  2.0f * ( pos.x() - m_rotation_center.x() ) / m_window_width;
    const float y = -2.0f * ( pos.y() - m_rotation_center.y() ) / m_window_height;

    return kvs::Vector2f( x, y );
}

} // end of namespace kvs