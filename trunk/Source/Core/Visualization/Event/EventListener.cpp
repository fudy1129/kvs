/*****************************************************************************/
/**
 *  @file   EventListener.cpp
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
#include "EventListener.h"
#include <kvs/ResizeEvent>
#include <kvs/MouseButton>
#include <kvs/IgnoreUnusedVariable>
#include <typeinfo>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new EventListener class.
 */
/*===========================================================================*/
EventListener::EventListener( void ):
    m_screen( NULL ),
    m_window( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the EventListener class.
 */
/*===========================================================================*/
EventListener::~EventListener( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Executes the event function.
 *  @param  event [in] pointer to the event
 */
/*===========================================================================*/
void EventListener::onEvent( kvs::EventBase* event )
{
    if ( !event )
    {
        this->paintEvent();
    }
    else
    {
        if ( typeid( *event ) == typeid( kvs::MouseEvent ) )
        {
            kvs::MouseEvent* e = static_cast<kvs::MouseEvent*>( event );
            switch ( e->action() )
            {
            case kvs::MouseButton::Pressed:
                this->mousePressEvent( e ); break;
            case kvs::MouseButton::Moved:
                this->mouseMoveEvent( e ); break;
            case kvs::MouseButton::Released:
                this->mouseReleaseEvent( e ); break;
            case kvs::MouseButton::DoubleClicked:
                this->mouseDoubleClickEvent( e ); break;
            default: break;
            }
        }
        else if ( typeid( *event ) == typeid( kvs::ResizeEvent ) )
        {
            kvs::ResizeEvent* e = static_cast<kvs::ResizeEvent*>( event );
            this->resizeEvent( e->width(), e->height() );
        }
        else if ( typeid( *event ) == typeid( kvs::WheelEvent ) )
        {
            kvs::WheelEvent* e = static_cast<kvs::WheelEvent*>( event );
            this->wheelEvent( e );
        }
        else if ( typeid( *event ) == typeid( kvs::KeyEvent ) )
        {
            kvs::KeyEvent* e = static_cast<kvs::KeyEvent*>( event );
            this->keyPressEvent( e );
        }
        else if ( typeid( *event ) == typeid( kvs::TimeEvent ) )
        {
            kvs::TimeEvent* e = static_cast<kvs::TimeEvent*>( event );
            this->timerEvent( e );
        }
    }
}

/*===========================================================================*/
/**
 *  @brief  Returns the event type.
 *  @return event type
 */
/*===========================================================================*/
const int EventListener::eventType( void ) const
{
    return( m_event_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the screen.
 *  @return pointer to the screen
 */
/*===========================================================================*/
kvs::ScreenBase* EventListener::screen( void )
{
    return( m_screen );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the window.
 *  @return pointer to the window
 */
/*===========================================================================*/
kvs::WindowBase* EventListener::window( void )
{
    return( m_window );
}

/*===========================================================================*/
/**
 *  @brief  Sets an event type.
 *  @param  event_type [in] event type
 */
/*===========================================================================*/
void EventListener::setEventType( int event_type )
{
    m_event_type = event_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the screen.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
void EventListener::setScreen( kvs::ScreenBase* screen )
{
    m_screen = screen;
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the window.
 *  @param  window [in] pointer to the window
 */
/*===========================================================================*/
void EventListener::setWindow( kvs::WindowBase* window )
{
    m_window = window;
}

/*===========================================================================*/
/**
 *  @brief  Paint event function.
 */
/*===========================================================================*/
void EventListener::paintEvent( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Resize event function.
 *  @param  width [in] window width
 *  @param  height [in] window height
 */
/*===========================================================================*/
void EventListener::resizeEvent( int width, int height )
{
    kvs::IgnoreUnusedVariable( width );
    kvs::IgnoreUnusedVariable( height );
}

/*===========================================================================*/
/**
 *  @brief  Mouse press event function.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void EventListener::mousePressEvent( kvs::MouseEvent* event )
{
    kvs::IgnoreUnusedVariable( event );
}

/*===========================================================================*/
/**
 *  @brief  Mouse move event function.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void EventListener::mouseMoveEvent( kvs::MouseEvent* event )
{
    kvs::IgnoreUnusedVariable( event );
}

/*===========================================================================*/
/**
 *  @brief  Mouse relase event function.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void EventListener::mouseReleaseEvent( kvs::MouseEvent* event )
{
    kvs::IgnoreUnusedVariable( event );
}

/*===========================================================================*/
/**
 *  @brief  Mouse double-clicke event function.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void EventListener::mouseDoubleClickEvent( kvs::MouseEvent* event )
{
    kvs::IgnoreUnusedVariable( event );
}

/*===========================================================================*/
/**
 *  @brief  Wheel event function.
 *  @param  event [in] pointer to the wheel event
 */
/*===========================================================================*/
void EventListener::wheelEvent( kvs::WheelEvent* event )
{
    kvs::IgnoreUnusedVariable( event );
}

/*===========================================================================*/
/**
 *  @brief  Key press event function.
 *  @param  event [in] pointer to the key event
 */
/*===========================================================================*/
void EventListener::keyPressEvent( kvs::KeyEvent* event )
{
    kvs::IgnoreUnusedVariable( event );
}

/*===========================================================================*/
/**
 *  @brief  Timer event function.
 *  @param  event [in] pointer to the timer event
 */
/*===========================================================================*/
void EventListener::timerEvent( kvs::TimeEvent* event )
{
    kvs::IgnoreUnusedVariable( event );
}

} // end of namespace kvs