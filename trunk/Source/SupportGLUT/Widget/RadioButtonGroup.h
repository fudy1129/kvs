/*****************************************************************************/
/**
 *  @file   RadioButtonGroup.h
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
#ifndef KVS__GLUT__RADIO_BUTTON_GROUP_H_INCLUDE
#define KVS__GLUT__RADIO_BUTTON_GROUP_H_INCLUDE

#include <list>
#include <kvs/ClassName>
#include <kvs/glut/WidgetBase>
#include "RadioButton.h"


namespace kvs
{

namespace glut
{

class RadioButton;

/*===========================================================================*/
/**
 *  @brief  Radio button group class.
 */
/*===========================================================================*/
class RadioButtonGroup : public kvs::glut::WidgetBase
{
    // Class name.
    kvsClassName( RadioButtonGroup );

public:

    typedef kvs::glut::WidgetBase BaseClass;

protected:

    std::list<kvs::glut::RadioButton*> m_buttons; ///< radio button list

public:

    RadioButtonGroup( kvs::glut::Screen* screen = 0 );

public:

    virtual void pressed( kvs::glut::RadioButton* button ) {};

    virtual void pressed( int id ) {};

    virtual void released( kvs::glut::RadioButton* button ) {};

    virtual void released( int id ) {};

    virtual void screenUpdated( void ) {};

    virtual void screenResized( void ) {};

public:

    const std::list<kvs::glut::RadioButton*>& radioButtons( void ) const;

    void add( kvs::glut::RadioButton* button );

    void remove( kvs::glut::RadioButton* button );

    void show( void );

    void hide( void );

private:

    void paintEvent( void );

    void resizeEvent( int width, int height );

    void mousePressEvent( kvs::MouseEvent* event );

    void mouseReleaseEvent( kvs::MouseEvent* event );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__RADIO_BUTTON_GROUP_H_INCLUDE