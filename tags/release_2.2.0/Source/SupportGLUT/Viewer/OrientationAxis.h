/****************************************************************************/
/**
 *  @file OrientationAxis.h
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
#ifndef KVS__GLUT__ORIENTATION_AXIS_H_INCLUDE
#define KVS__GLUT__ORIENTATION_AXIS_H_INCLUDE

#include <kvs/Camera>
#include <kvs/RGBColor>
#if KVS_ENABLE_DEPRECATED
#include <kvs/ObjectBase>
#include <kvs/glut/Screen>
#endif
#include <kvs/glut/WidgetBase>


namespace kvs
{

class ScreenBase;
class ObjectBase;

namespace glut
{

class Screen;

/*===========================================================================*/
/**
 *  @brief  Orientation axis class.
 */
/*===========================================================================*/
class OrientationAxis : public kvs::glut::WidgetBase
{
public:

    typedef kvs::glut::WidgetBase BaseClass;
    typedef kvs::Camera::ProjectionType ProjectionType;

    enum AxisType
    {
        CorneredAxis = 0,
        CenteredAxis,
        NoneAxis
    };

    enum BoxType
    {
        WiredBox = 0,
        SolidBox,
        NoneBox
    };

protected:

    const kvs::ObjectBase* m_object; ///< pointer to the object
    std::string m_x_tag; ///< x axis tag
    std::string m_y_tag; ///< y axis tag
    std::string m_z_tag; ///< z axis tag
    kvs::RGBColor m_x_axis_color; ///< x axis color
    kvs::RGBColor m_y_axis_color; ///< y axis color
    kvs::RGBColor m_z_axis_color; ///< z axis color
    float m_axis_line_width; ///< axis line width
    kvs::RGBColor m_box_color; ///< box color
    kvs::RGBColor m_box_line_color; ///< box line color
    float m_box_line_width; ///< box line width
    bool m_enable_anti_aliasing; ///< check flag for anti-aliasing
    AxisType m_axis_type; ///< axis type
    BoxType m_box_type; ///< box type
    ProjectionType m_projection_type; ///< projection type

public:

    OrientationAxis( kvs::glut::Screen* screen );
    OrientationAxis( kvs::ScreenBase* screen, const kvs::ObjectBase* object );
    virtual ~OrientationAxis( void );

public:

    virtual void screenUpdated( void ){};
    virtual void screenResized( void ){};

    const std::string& xTag( void ) const;
    const std::string& yTag( void ) const;
    const std::string& zTag( void ) const;
    const kvs::RGBColor& xAxisColor( void ) const;
    const kvs::RGBColor& yAxisColor( void ) const;
    const kvs::RGBColor& zAxisColor( void ) const;
    const float axisLineWidth( void ) const;
    const kvs::RGBColor& boxColor( void ) const;
    const kvs::RGBColor& boxLineColor( void ) const;
    const float boxLineWidth( void ) const;
    const AxisType axisType( void ) const;
    const BoxType boxType( void ) const;
    const ProjectionType projectionType( void ) const;

    void setObject( const kvs::ObjectBase* object );
    void setSize( const size_t size );
    void setXTag( const std::string& tag );
    void setYTag( const std::string& tag );
    void setZTag( const std::string& tag );
    void setXAxisColor( const kvs::RGBColor& color );
    void setYAxisColor( const kvs::RGBColor& color );
    void setZAxisColor( const kvs::RGBColor& color );
    void setAxisLineWidth( const float width );
    void setBoxColor( const kvs::RGBColor& color );
    void setBoxLineColor( const kvs::RGBColor& color );
    void setBoxLineWidth( const float width );
    void setAxisType( const AxisType type );
    void setBoxType( const BoxType type );
    void setProjectionType( const ProjectionType type );
    void enableAntiAliasing( void );
    void disableAntiAliasing( void );

    void paintEvent( void );
    void resizeEvent( int width, int height );

private:

    int get_fitted_width( void );
    int get_fitted_height( void );
    void draw_centered_axis( const float length );
    void draw_cornered_axis( const float length );
    void draw_wired_box( const float length );
    void draw_solid_box( const float length );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__ORIENTATION_AXIS_H_INCLUDE
