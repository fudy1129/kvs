/*****************************************************************************/
/**
 *  @file   GL.h
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
#ifndef KVS__GL_H_INCLUDE
#define KVS__GL_H_INCLUDE

#include <kvs/Macro>
#include <kvs/Breakpoint>
#include <kvs/Platform>

#if !defined( KVS_PLATFORM_WINDOWS )
#define GL_GLEXT_PROTOTYPES
#endif

#if defined( KVS_PLATFORM_WINDOWS )
#include <cstdlib>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#endif

// GLEW header file 'glew.h' must be included before the OpenGL header files.
#include <GL/glew.h>

#if defined( KVS_PLATFORM_MACOSX )
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


namespace kvs
{

namespace GL
{

namespace detail
{

bool HasError( const char* file, const int line, const char* func, const char* command );

} // end of namespace detail

} // end of namespace GL

} // end of namespace kvs


#if defined KVS_ENABLE_DEBUG
#define KVS_GL_CALL( command )                                          \
    KVS_MACRO_MULTI_STATEMENT_BEGIN                                     \
    if ( kvs::GL::detail::HasError( KVS_MACRO_FILE, KVS_MACRO_LINE, KVS_MACRO_FUNC, "Unknown" ) ) { KVS_BREAKPOINT; } \
    command;                                                            \
    if ( kvs::GL::detail::HasError( KVS_MACRO_FILE, KVS_MACRO_LINE, KVS_MACRO_FUNC, #command ) ) { KVS_BREAKPOINT; } \
    KVS_MACRO_MULTI_STATEMENT_END
#else
#define KVS_GL_CALL( command ) ( command )
#endif

#endif // KVS__GL_H_INCLUDE