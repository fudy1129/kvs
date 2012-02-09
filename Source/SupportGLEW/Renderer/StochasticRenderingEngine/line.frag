/*****************************************************************************/
/**
 *  @file   line.frag
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
varying vec3 position;
varying vec2 id;

uniform sampler2D random_texture;

uniform vec2 screen_scale;
uniform vec2 screen_scale_inv;

uniform float random_texture_size_inv;
uniform vec2 random_offset;

uniform float opacity;

void main( void )
{
    if ( opacity == 0.0 ) { discard; return; }

    if ( opacity < 0.99999 )
    {
        vec2 random_position = ( vec2( float( int( id.x ) * 73 ), float( int( id.y ) * 31 ) ) 
                    + random_offset + gl_FragCoord.xy ) * random_texture_size_inv;

        float randf = texture2D( random_texture, random_position ).a;
        if ( randf > opacity ) { discard; return; }
    }

    gl_FragColor = vec4( gl_Color.rgb, 1.0 );
}
