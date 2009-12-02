/*****************************************************************************/
/**
 *  @file   Label.h
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
#ifndef KVS__GLUT__LABEL_H_INCLUDE
#define KVS__GLUT__LABEL_H_INCLUDE

#include <string>
#include <vector>
#include <kvs/ClassName>
#include "WidgetBase.h"


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  Label class.
 */
/*===========================================================================*/
class Label : public kvs::glut::WidgetBase
{
    // Class name.
    kvsClassName( Label );

public:

    typedef kvs::glut::WidgetBase BaseClass;

protected:

    std::vector<std::string> m_text; ///< text list

public:

    Label( kvs::glut::Screen* screen = 0 );

public:

    void setText( const char* text, ... );

    void addText( const char* text, ... );

private:

    int get_fitted_width( void );

    int get_fitted_height( void );

public:

    void paintEvent( void );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__LABEL_H_INCLUDE