/*****************************************************************************/
/**
 *  @file   zooming.frag
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
#include "../Shader/shading.h"

varying vec3 position;
varying vec3 normal;

varying vec2 centerCoord;
varying float radius;

uniform Shading shading;

/*===========================================================================*/
/**
 *  @brief  Calculates a shaded color of the particle with Lambert shading.
 */
/*===========================================================================*/
void main( void )
{
    // Discard a pixel outside circle.
    if ( radius > 0.0 )
    {
        if( distance( gl_FragCoord.xy, centerCoord ) > radius ) discard;
    }

    // Light position.
    vec3 light_position = gl_LightSource[0].position.xyz;

    // Light vector (L) and Normal vector (N)
    vec3 L = normalize( light_position - position );
    vec3 N = normalize( gl_NormalMatrix * normal );

#if   defined( ENABLE_LAMBERT_SHADING )
    vec3 shaded_color = ShadingLambert( shading, gl_Color.xyz, L, N );

#elif defined( ENABLE_PHONG_SHADING )
    vec3 shaded_color = ShadingPhong( shading, gl_Color.xyz, L, N );

#elif defined( ENABLE_BLINN_PHONG_SHADING )
    vec3 C = normalize( -position );
    vec3 shaded_color = ShadingBlinnPhong( shading, gl_Color.xyz, L, N, C );

#else // DISABLE SHADING
    vec3 shaded_color = ShadingNone( shading, gl_Color.xyz );
#endif

    gl_FragColor.xyz = shaded_color;
    gl_FragColor.w = 1.0;
}