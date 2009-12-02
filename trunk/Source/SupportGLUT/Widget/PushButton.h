/*****************************************************************************/
/**
 *  @file   PushButton.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__GLUT__PUSH_BUTTON_H_INCLUDE
#define KVS__GLUT__PUSH_BUTTON_H_INCLUDE

#include "WidgetBase.h"
#include <kvs/ClassName>


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  PushButton widget class.
 */
/*===========================================================================*/
class PushButton : public kvs::glut::WidgetBase
{
    // Class name.
    kvsClassName( PushButton );

public:

    typedef kvs::glut::WidgetBase BaseClass;

protected:

    std::string   m_caption; ///< caption
    int           m_text_margin; ///< text margin
    kvs::RGBColor m_button_color; ///< button color
    kvs::RGBColor m_clicked_button_color; ///< clicked button color
    kvs::RGBColor m_upper_edge_color; ///< upper edge color
    kvs::RGBColor m_lower_edge_color; ///< lower edge color

public:

    PushButton( kvs::glut::Screen* screen = 0 );

public:

    virtual void pressed( void ){};

    virtual void released( void ){};

public:

    const std::string& caption( void ) const;

    void setCaption( const std::string caption );

    void setTextMargin( const int margin );

    void setButtonColor( const kvs::RGBColor& color );

private:

    void draw_button( void );

    int get_fitted_width( void );

    int get_fitted_height( void );

    int get_aligned_x( void );

    int get_aligned_y( void );

private:

    void paintEvent( void );

    void mousePressEvent( kvs::MouseEvent* event );

    void mouseReleaseEvent( kvs::MouseEvent* event );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__PUSH_BUTTON_H_INCLUDE