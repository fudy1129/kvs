/****************************************************************************/
/**
 *  @file ScreenBase.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_SUPPORT_GLUT_SCREEN_BASE_H_INCLUDE
#define KVS_SUPPORT_GLUT_SCREEN_BASE_H_INCLUDE

#include <vector>
#include <string>
#include <kvs/ScreenCore>
#include <kvs/RGBColor>


namespace kvs
{

namespace glut
{

typedef void (*InitializeFuncBase)( void );
typedef void (*PaintEventBase)( void );
typedef void (*ResizeEventBase)( int, int );
typedef void (*MousePressEventBase)( int, int, int, int );
typedef void (*MouseMoveEventBase)( int, int );
typedef void (*MouseReleaseEventBase)( int, int, int, int );
typedef void (*KeyPressEventBase)( unsigned char, int, int );
typedef void (*SpkeyPressEventBase)( int, int, int );
typedef void (*TimerMouseEventBase)( int );
typedef void (*TimerEventBase)( int );

typedef void (*TimerMouseEvent)( int );
typedef void (*TimerEvent)( int );

/*==========================================================================*/
/**
 *  Screen base class for GLUT.
 */
/*==========================================================================*/
class ScreenBase : public kvs::ScreenCore
{
protected:

    static PaintEventBase         m_pfunc_paint_event;
    static ResizeEventBase        m_pfunc_resize_event;
    static MousePressEventBase    m_pfunc_mouse_press_event;
    static MouseMoveEventBase     m_pfunc_mouse_move_event;
    static KeyPressEventBase      m_pfunc_key_press_event;
    static SpkeyPressEventBase    m_pfunc_spkey_press_event;
    static TimerMouseEventBase    m_pfunc_timer_mouse_event;
    static std::vector<TimerEventBase> m_pfunc_timer_event;

    static std::vector<int>        m_timer_event_time;

protected:

    static void default_paint_event( void );
    static void default_resize_event( int width, int height );
    static void default_mouse_press_event( int button, int state, int x, int y );
    static void default_mouse_move_event( int x, int y );
    static void default_timer_mouse_event( int value );
    static void default_key_press_event( unsigned char key, int x, int y );
    static void default_spkey_press_event( int key, int x, int y );

    static void replaced_mouse_press_event( int button, int state, int x, int y );
    static void replaced_mouse_move_event( int x, int y );
    static void replaced_key_press_event( unsigned char key, int x, int y );
    static void replaced_spkey_press_event( int key, int x, int y );

public:

    ScreenBase( void );

    virtual ~ScreenBase( void );

public:

    void addTimerEvent( TimerEvent event, int time );

    void setPaintEvent( PaintEvent event );

    void setResizeEvent( ResizeEvent event );

    void setMousePressEvent( MousePressEvent event );

    void setMouseMoveEvent( MouseMoveEvent event );

    void setKeyPressEvent( KeyPressEvent event );

    void setTimerMouseEvent( TimerMouseEvent event );

public:

    int show( bool last = true );

    static void showFullScreen( void );

    static void showNormal( void );

    static bool isFullScreen( void );

    static void popUp( void );

    static void pushDown( void );

    static void hide( void );

    static void showWindow( void );

    static void redraw( void );

    static void resize( int width, int height );

    static void disableAllMove( void );

protected:

    static void mouse_wheel_up( int x, int y );

    static void mouse_wheel_down( int x, int y );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS_SUPPORT_GLUT_SCREEN_BASE_H_INCLUDE