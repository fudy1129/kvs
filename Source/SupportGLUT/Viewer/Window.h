/*****************************************************************************/
/**
 *  @file   Window.h
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
#ifndef KVS__GLUT__WINDOW_H_INCLUDE
#define KVS__GLUT__WINDOW_H_INCLUDE

#include <kvs/WindowBase>
#include <kvs/Timer>
#include <kvs/MouseEvent>
#include <kvs/KeyEvent>
#include <kvs/KeyEvent>
#include <kvs/WheelEvent>
#include <kvs/EventHandler>
#include <kvs/DisplayFormat>
#include <string>


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  GLUT window class.
 */
/*===========================================================================*/
class Window : public kvs::WindowBase
{
public:

    Window( void );

    virtual ~Window( void );

public:

    virtual void create( void );

    virtual void showFullScreen( void );

    virtual void showNormal( void );

    virtual void popUp( void );

    virtual void pushDown( void );

    virtual void hide( void );

    virtual void showWindow( void );

    virtual void redraw( void );

    virtual void resize( int width, int height );

public:

    virtual void initializeEvent( void );

    virtual void paintEvent( void );

    virtual void resizeEvent( int width, int height );

    virtual void mousePressEvent( kvs::MouseEvent* event );

    virtual void mouseMoveEvent( kvs::MouseEvent* event );

    virtual void mouseReleaseEvent( kvs::MouseEvent* event );

    virtual void mouseDoubleClickEvent( kvs::MouseEvent* event );

    virtual void wheelEvent( kvs::WheelEvent* event );

    virtual void keyPressEvent( kvs::KeyEvent* event );

private:

    // Callback functions for GLUT.

    friend void DisplayFunction( void );

    friend void ResizeFunction( int width, int height );

    friend void MouseFunction( int button, int state, int x, int y );

    friend void MouseMoveFunction( int x, int y );

    friend void KeyPressFunction( unsigned char key, int x, int y );

    friend void SpecialKeyPressFunction( int key, int x, int y );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__WINDOW_H_INCLUDE