/*****************************************************************************/
/**
 *  @file   multivariate_tetrahedra.vert
 *  @author Jun Nishimura
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
varying vec4 position_in;
varying vec2 id_in;
varying vec2 value_in;
varying vec3 normal_in;

attribute vec2 identifier;
attribute vec2 value;

void main( void )
{
    gl_Position = ftransform();

    position_in = gl_ModelViewMatrix * gl_Vertex;
    id_in = identifier;
    value_in = value;
    normal_in = gl_NormalMatrix * gl_Normal;
}