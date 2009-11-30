/*****************************************************************************/
/**
 *  @file   Screen.h
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
#ifndef KVS__QT__SCREEN_H_INCLUDE
#define KVS__QT__SCREEN_H_INCLUDE

#include <kvs/ScreenBase>
#include <kvs/InitializeEventListener>
#include <kvs/PaintEventListener>
#include <kvs/ResizeEventListener>
#include <kvs/MousePressEventListener>
#include <kvs/MouseMoveEventListener>
#include <kvs/MouseReleaseEventListener>
#include <kvs/MouseDoubleClickEventListener>
#include <kvs/WheelEventListener>
#include <kvs/KeyPressEventListener>
#include <kvs/TimerEventListener>
#include <kvs/EventHandler>
#include <kvs/MouseEvent>
#include <kvs/KeyEvent>
#include <kvs/qt/Window>
#include <kvs/qt/Timer>
#include <kvs/qt/Application>


namespace kvs
{

namespace qt
{

/*===========================================================================*/
/**
 *  @brief  Qt screen class.
 */
/*===========================================================================*/
class Screen : public kvs::qt::Window, public kvs::ScreenBase
{
    Q_OBJECT

    typedef void (Screen::*PaintEventFunction)( void );
    typedef void (Screen::*ResizeEventFunction)( int, int );
    typedef void (Screen::*MousePressEventFunction)( kvs::MouseEvent* );
    typedef void (Screen::*MouseMoveEventFunction)( kvs::MouseEvent* );
    typedef void (Screen::*MouseReleaseEventFunction)( kvs::MouseEvent* );
    typedef void (Screen::*WheelEventFunction)( kvs::WheelEvent* );
    typedef void (Screen::*KeyPressEventFunction)( kvs::KeyEvent* );

protected:

    PaintEventFunction         m_paint_event_func;
    ResizeEventFunction        m_resize_event_func;
    MousePressEventFunction    m_mouse_press_event_func;
    MouseMoveEventFunction     m_mouse_move_event_func;
    MouseReleaseEventFunction  m_mouse_release_event_func;
    WheelEventFunction         m_wheel_event_func;
    KeyPressEventFunction      m_key_press_event_func;

    QTimer*                    m_idle_mouse_timer;
    std::list<kvs::qt::Timer*> m_timer_event_handler;
    kvs::EventHandler*         m_initialize_event_handler;
    kvs::EventHandler*         m_event_handler;

public:

    Screen( kvs::qt::Application* application = 0, QWidget* parent = 0 );

    virtual ~Screen( void );

public:

    void setPosition( const int x, const int y );

    void setSize( const int width, const int height );

    void setGeometry( const int x, const int y, const int width, const int height );

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

public:

    kvs::EventHandler* eventHandler( void ) const;

    void setPaintEvent( kvs::PaintEventListener* event );

    void setResizeEvent( kvs::ResizeEventListener* event );

    void setMousePressEvent( kvs::MousePressEventListener* event );

    void setMouseMoveEvent( kvs::MouseMoveEventListener* event );

    void setMouseReleaseEvent( kvs::MouseReleaseEventListener* event );

    void setMouseDoubleClickEvent( kvs::MouseDoubleClickEventListener* event );

    void setWheelEvent( kvs::WheelEventListener* event );

    void setKeyPressEvent( kvs::KeyPressEventListener* event );

public:

    void addInitializeEvent( kvs::InitializeEventListener* event );

    void addPaintEvent( kvs::PaintEventListener* event );

    void addResizeEvent( kvs::ResizeEventListener* event );

    void addMousePressEvent( kvs::MousePressEventListener* event );

    void addMouseMoveEvent( kvs::MouseMoveEventListener* event );

    void addMouseReleaseEvent( kvs::MouseReleaseEventListener* event );

    void addMouseDoubleClickEvent( kvs::MouseDoubleClickEventListener* event );

    void addWheelEvent( kvs::WheelEventListener* event );

    void addKeyPressEvent( kvs::KeyPressEventListener* event );

    void addTimerEvent( kvs::TimerEventListener* event, int msec );

public:

    int show( void );

protected:

    void default_paint_event( void );

    void default_resize_event( int width, int height );

    void default_mouse_press_event( kvs::MouseEvent* event );

    void default_mouse_move_event( kvs::MouseEvent* event );

    void default_mouse_release_event( kvs::MouseEvent* event );

    void default_wheel_event( kvs::WheelEvent* event );

    void default_key_press_event( kvs::KeyEvent* event );

public slots:

    void idleMouseEvent( void );
};

} // end of namespace qt

} // end of namespace kvs

#endif // KVS__QT__SCREEN_H_INCLUDE
