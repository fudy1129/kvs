/* DONT'T EDIT THIS FILE.
 * THIS IS GENERATED BY "Configure/configure_shader.py".
 */
#ifndef KVS__GLEW__GLSL__StochasticRenderingEngine_H_INCLUDE
#define KVS__GLEW__GLSL__StochasticRenderingEngine_H_INCLUDE

#include <string>

namespace kvs { namespace glew { namespace glsl {

namespace StochasticRenderingEngine
{

namespace Vertex
{

const std::string line =
    "varying vec3 position;\n"
    "varying vec2 id;\n"
    "\n"
    "attribute vec2 identifier;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_Position = ftransform();\n"
    "    gl_FrontColor = gl_Color;\n"
    "\n"
    "    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;\n"
    "    id = identifier;\n"
    "}\n"
;

const std::string point =
    "uniform float densityFactor;\n"
    "uniform int circle_threshold;\n"
    "uniform vec2 screen_scale;\n"
    "uniform sampler2D random_texture;\n"
    "uniform float random_texture_size_inv;\n"
    "uniform vec2 random_offset;\n"
    "attribute vec2 identifier;\n"
    "\n"
    "const float CIRCLE_SCALE = 0.564189583547756; // 1.0 / sqrt(PI)\n"
    "\n"
    "varying vec3  position;\n"
    "varying vec3  normal;\n"
    "varying vec2  center;\n"
    "varying float radius;\n"
    "\n"
    "\n"
    "float zooming( in vec4 p )\n"
    "{\n"
    "    // Depth value.\n"
    "    float D = p.z;\n"
    "    if ( D < 1.0 ) D = 1.0; // to avoid front-clip\n"
    "\n"
    "    // Calculate the footprint size of the particle.\n"
    "    float s = densityFactor / D; // footprint size of the particle in pixel\n"
    "    float sf = floor( s );       // round-down value of s\n"
    "    float sc = ceil( s );        // round-up value of s\n"
    "\n"
    "    // Calculate a probability 'pc' that the footprint size is 'sc'.\n"
    "    float fraction = fract( s );\n"
    "    float pc = fraction * ( 2.0 * sf + fraction ) / ( 2.0 * sf + 1.0 );\n"
    "\n"
    "    // Random number from the random number texture.\n"
    "    vec2 random_texture_index = identifier * random_texture_size_inv;\n"
    "    float R = texture2D( random_texture, random_texture_index ).x;\n"
    "\n"
    "    if ( circle_threshold <= 0 || s <= float( circle_threshold ) )\n"
    "    {\n"
    "        // Draw the particle as square.\n"
    "        s = ( ( R < pc ) ? sc : sf );\n"
    "        radius = 0.0;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        // Draw the particle as circle.\n"
    "        // Convert position to screen coordinates.\n"
    "        center = screen_scale + ( ( p.xy / p.w ) * screen_scale );\n"
    "        radius = ( ( R < pc ) ? sc : sf ) * CIRCLE_SCALE;\n"
    "        s = ceil( s * CIRCLE_SCALE * 2.0 ) + 1.0;\n"
    "    }\n"
    "\n"
    "    return( s );\n"
    "}\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
    "    gl_FrontColor = gl_Color;\n"
    "\n"
    "    position = vec3( gl_ModelViewMatrix * gl_Vertex );\n"
    "    normal = ( gl_NormalMatrix * gl_Normal ).xyz;\n"
    "\n"
    "    gl_PointSize = zooming( gl_Position );\n"
    "}\n"
;

const std::string polygon =
    "varying vec3 position;\n"
    "varying vec3 normal;\n"
    "varying vec2 id;\n"
    "\n"
    "attribute vec2 identifier;\n"
    "\n"
    "uniform float polygon_offset;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_Position = ftransform();\n"
    "    gl_Position.z -= polygon_offset;\n"
    "    gl_FrontColor = gl_Color;\n"
    "\n"
    "    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;\n"
    "    normal = ( gl_NormalMatrix * gl_Normal ).xyz;\n"
    "    id = identifier;\n"
    "}\n"
;

const std::string unstructured_volume =
    "varying vec4 position_in;\n"
    "varying vec2 id_in;\n"
    "varying float value_in;\n"
    "varying vec3 normal_in;\n"
    "\n"
    "attribute vec2 identifier;\n"
    "attribute float value;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_Position = ftransform();\n"
    "\n"
    "    position_in = gl_ModelViewMatrix * gl_Vertex;\n"
    "    id_in = identifier;\n"
    "    value_in = value;\n"
    "    normal_in = gl_NormalMatrix * gl_Normal;\n"
    "}\n"
;

} // end of namespace Vertex

namespace Geometry
{

const std::string unstructured_volume =
    "#version 120\n"
    "#extension GL_EXT_geometry_shader4 : enable\n"
    "#extension GL_EXT_gpu_shader4 : enable\n"
    "\n"
    "varying in vec4 position_in[4];\n"
    "varying in float value_in[4];\n"
    "varying in vec2 id_in[4];\n"
    "varying in vec3 normal_in[4];\n"
    "\n"
    "varying out vec3 position;\n"
    "varying out vec3 normal;\n"
    "varying out vec2 id;\n"
    "\n"
    "varying out float scalar_front;\n"
    "varying out float scalar_back;\n"
    "varying out float distance;\n"
    "\n"
    "uniform vec2 preintegration_scale_offset;\n"
    "uniform sampler2D decomposion_texture;\n"
    "\n"
    "vec3 screen_position[4];\n"
    "\n"
    "int direction( in int p0, in int p1, in int p2 )\n"
    "{\n"
    "    vec2 v1 = screen_position[p1].xy - screen_position[p0].xy;\n"
    "    vec2 v2 = screen_position[p2].xy - screen_position[p0].xy;\n"
    "    float cross_product = v1.x * v2.y - v1.y * v2.x;\n"
    "    return( int( sign( cross_product ) + 1.0 ) );\n"
    "}\n"
    "\n"
    "void emitExistPoint( const in int index, const in float dist )\n"
    "{\n"
    "    gl_Position = gl_PositionIn[index]; \n"
    "    position    = position_in[index].xyz;\n"
    "\n"
    "    normal = normal_in[index].xyz;\n"
    "\n"
    "    scalar_front = value_in[index];\n"
    "    scalar_back  = value_in[index];\n"
    "    distance     = dist;\n"
    "    EmitVertex();\n"
    "}\n"
    "\n"
    "void emitNewPoint(\n"
    "    const in vec4 center_position,\n"
    "    const in vec3 center_position_3D,\n"
    "    const in vec3 center_normal_3D,\n"
    "    const in float center_scalar_front,\n"
    "    const in float center_scalar_back,\n"
    "    const in float center_distance )\n"
    "{\n"
    "    gl_Position = center_position;\n"
    "    position    = center_position_3D;\n"
    "\n"
    "    normal = center_normal_3D;\n"
    "\n"
    "    scalar_front = center_scalar_front;\n"
    "    scalar_back  = center_scalar_back;\n"
    "    distance     = center_distance;\n"
    "    EmitVertex();\n"
    "}\n"
    "\n"
    "mat3 inverse( in mat3 m )\n"
    "{\n"
    "    float det22[9];\n"
    "    det22[0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];\n"
    "    det22[1] = m[1][0] * m[2][2] - m[1][2] * m[2][0];\n"
    "    det22[2] = m[1][0] * m[2][1] - m[1][1] * m[2][0];\n"
    "    det22[3] = m[0][1] * m[2][2] - m[0][2] * m[2][1];\n"
    "    det22[4] = m[0][0] * m[2][2] - m[0][2] * m[2][0];\n"
    "    det22[5] = m[0][0] * m[2][1] - m[0][1] * m[2][0];\n"
    "    det22[6] = m[0][1] * m[1][2] - m[0][2] * m[1][1];\n"
    "    det22[7] = m[0][0] * m[1][2] - m[0][2] * m[1][0];\n"
    "    det22[8] = m[0][0] * m[1][1] - m[0][1] * m[1][0];\n"
    "\n"
    "    float det33 =\n"
    "        m[0][0] * det22[0] - m[0][1] * det22[1] + m[0][2] * det22[2];\n"
    "\n"
    "    float dat33_inv = 1.0 / det33;\n"
    "\n"
    "    return( dat33_inv * mat3(\n"
    "        +det22[0], -det22[3], +det22[6],\n"
    "        -det22[1], +det22[4], -det22[7],\n"
    "        +det22[2], -det22[5], +det22[8] ) );\n"
    "}\n"
    "\n"
    "mat4 inverse( in mat4 m )\n"
    "{\n"
    "    float det22upper[6];\n"
    "    det22upper[0] = m[0][2] * m[1][3] - m[0][3] * m[1][2];\n"
    "    det22upper[1] = m[0][1] * m[1][3] - m[0][3] * m[1][1];\n"
    "    det22upper[2] = m[0][0] * m[1][3] - m[0][3] * m[1][0];\n"
    "    det22upper[3] = m[0][1] * m[1][2] - m[0][2] * m[1][1];\n"
    "    det22upper[4] = m[0][0] * m[1][2] - m[0][2] * m[1][0];\n"
    "    det22upper[5] = m[0][0] * m[1][1] - m[0][1] * m[1][0];\n"
    "\n"
    "    float det22lower[6];\n"
    "    det22lower[0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];\n"
    "    det22lower[1] = m[2][1] * m[3][3] - m[2][3] * m[3][1];\n"
    "    det22lower[2] = m[2][0] * m[3][3] - m[2][3] * m[3][0];\n"
    "    det22lower[3] = m[2][1] * m[3][2] - m[2][2] * m[3][1];\n"
    "    det22lower[4] = m[2][0] * m[3][2] - m[2][2] * m[3][0];\n"
    "    det22lower[5] = m[2][0] * m[3][1] - m[2][1] * m[3][0];\n"
    "\n"
    "    float det33[16];\n"
    "    det33[0]  = m[1][1] * det22lower[0] - m[1][2] * det22lower[1] + m[1][3] * det22lower[3];\n"
    "    det33[1]  = m[1][0] * det22lower[0] - m[1][2] * det22lower[2] + m[1][3] * det22lower[4];\n"
    "    det33[2]  = m[1][0] * det22lower[1] - m[1][1] * det22lower[2] + m[1][3] * det22lower[5];\n"
    "    det33[3]  = m[1][0] * det22lower[3] - m[1][1] * det22lower[4] + m[1][2] * det22lower[5];\n"
    "    det33[4]  = m[0][1] * det22lower[0] - m[0][2] * det22lower[1] + m[0][3] * det22lower[3];\n"
    "    det33[5]  = m[0][0] * det22lower[0] - m[0][2] * det22lower[2] + m[0][3] * det22lower[4];\n"
    "    det33[6]  = m[0][0] * det22lower[1] - m[0][1] * det22lower[2] + m[0][3] * det22lower[5];\n"
    "    det33[7]  = m[0][0] * det22lower[3] - m[0][1] * det22lower[4] + m[0][2] * det22lower[5];\n"
    "    det33[8]  = m[3][1] * det22upper[0] - m[3][2] * det22upper[1] + m[3][3] * det22upper[3];\n"
    "    det33[9]  = m[3][0] * det22upper[0] - m[3][2] * det22upper[2] + m[3][3] * det22upper[4];\n"
    "    det33[10] = m[3][0] * det22upper[1] - m[3][1] * det22upper[2] + m[3][3] * det22upper[5];\n"
    "    det33[11] = m[3][0] * det22upper[3] - m[3][1] * det22upper[4] + m[3][2] * det22upper[5];\n"
    "    det33[12] = m[2][1] * det22upper[0] - m[2][2] * det22upper[1] + m[2][3] * det22upper[3];\n"
    "    det33[13] = m[2][0] * det22upper[0] - m[2][2] * det22upper[2] + m[2][3] * det22upper[4];\n"
    "    det33[14] = m[2][0] * det22upper[1] - m[2][1] * det22upper[2] + m[2][3] * det22upper[5];\n"
    "    det33[15] = m[2][0] * det22upper[3] - m[2][1] * det22upper[4] + m[2][2] * det22upper[5];\n"
    "\n"
    "    float det44 = m[0][0] * det33[0] - m[0][1] * det33[1] + m[0][2] * det33[2] - m[0][3] * det33[3];\n"
    "    float det44_inv = 1.0 / det44;\n"
    "\n"
    "    return( det44_inv * mat4(\n"
    "                +det33[0], -det33[4], +det33[ 8], -det33[12],\n"
    "                -det33[1], +det33[5], -det33[ 9], +det33[13],\n"
    "                +det33[2], -det33[6], +det33[10], -det33[14],\n"
    "                -det33[3], +det33[7], -det33[11], +det33[15] ) );\n"
    "}\n"
    "\n"
    "vec3 gradientOfCell( void )\n"
    "{\n"
    "    mat4 a = mat4( position_in[0], position_in[1], position_in[2], position_in[3] );\n"
    "    vec4 b = vec4( value_in[0], value_in[1], value_in[2], value_in[3] );\n"
    "    vec4 x = inverse( a ) * b;\n"
    "\n"
    "    return x.xyz;\n"
    "}\n"
    "\n"
    "float distance_to_texture_coord( const in float distance )\n"
    "{\n"
    "    return( distance * preintegration_scale_offset.x + preintegration_scale_offset.y );\n"
    "}\n"
    "\n"
    "void calculate_across_triangle_to_line_2D( out float r2, out float r3, in int p0, in int p1, in int p2, in int p3 )\n"
    "{\n"
    "    vec2 v01 = screen_position[p0].xy - screen_position[p1].xy;\n"
    "    vec2 v21 = screen_position[p2].xy - screen_position[p1].xy;\n"
    "    vec2 v31 = screen_position[p3].xy - screen_position[p1].xy;\n"
    "    float delta = v21.x * v31.y - v31.x * v21.y;\n"
    "    if ( delta == 0 )\n"
    "    {\n"
    "        r2 = r3 = 1.0 / 3.0;\n"
    "        return;\n"
    "    }\n"
    "\n"
    "    float delta_inv = 1.0 / delta;\n"
    "    r2 = delta_inv * (  v31.y * v01.x - v31.x * v01.y );\n"
    "    r3 = delta_inv * ( -v21.y * v01.x + v21.x * v01.y );\n"
    "}\n"
    "\n"
    "float perspective_correct( const in float r, const in float p0z, const in float p1z )\n"
    "{\n"
    "    if ( p0z == p1z ) return r;\n"
    "\n"
    "    float p0z_inv = 1.0 / p0z;\n"
    "    float p1z_inv = 1.0 / p1z;\n"
    "    float pz_inv  = p0z_inv + ( p1z_inv - p0z_inv ) * r;\n"
    "    float pz = 1.0 / pz_inv;\n"
    "\n"
    "    float result = ( pz - p0z ) / ( p1z - p0z );\n"
    "    if ( result < 0.0 ) result = 0.0;\n"
    "    if ( result > 1.0 ) result = 1.0;\n"
    "    return( result );\n"
    "}\n"
    "\n"
    "void perspective_correct_triangle( inout float r2, inout float r3, in int p0, in int p1, in int p2, in int p3 )\n"
    "{\n"
    "    if ( r2 + r3 <= 0 ) return;\n"
    "    float p1z    = gl_PositionIn[p1].w;\n"
    "    float p2z    = gl_PositionIn[p2].w;\n"
    "    float p3z    = gl_PositionIn[p3].w;\n"
    "    float k_2D   = r2 + r3;\n"
    "    float r23_2D = r3 / k_2D;\n"
    "\n"
    "    float r23_3D = perspective_correct( r23_2D, p2z, p3z );\n"
    "\n"
    "    float p23z = p2z + ( p3z - p2z ) * r23_3D;\n"
    "    float k_3D = perspective_correct( k_2D, p1z, p23z );\n"
    "\n"
    "    r3 = r23_3D * k_3D;\n"
    "    r2 = k_3D - r3;\n"
    "}\n"
    "\n"
    "void perspective_correct_line( inout float r, const in int p0, const in int p1 )\n"
    "{\n"
    "    float p0z  = gl_PositionIn[p0].w;\n"
    "    float p1z  = gl_PositionIn[p1].w;\n"
    "    float r_3D = perspective_correct( r, p0z, p1z );\n"
    "\n"
    "    r = r_3D;\n"
    "}\n"
    "\n"
    "void calculate_across_line_to_line_2D( out float r1, out float r3, in int p0, in int p1, in int p2, in int p3 )\n"
    "{\n"
    "    vec2 v02 = screen_position[p0].xy - screen_position[p2].xy;\n"
    "    vec2 v01 = screen_position[p0].xy - screen_position[p1].xy;\n"
    "    vec2 v32 = screen_position[p3].xy - screen_position[p2].xy;\n"
    "    float delta = v01.x * v32.y - v32.x * v01.y;\n"
    "    if ( delta == 0 )\n"
    "    {\n"
    "        r1 = r3 = 1.0 / 2.0;\n"
    "        return;\n"
    "    }\n"
    "    float delta_inv = 1.0 / delta;\n"
    "    r1 = delta_inv * (  v32.y * v02.x - v32.x * v02.y );\n"
    "    r3 = delta_inv * ( -v01.y * v02.x + v01.x * v02.y );\n"
    "}\n"
    "\n"
    "/*\n"
    "void create_type_1( in int p0, in int p1, in int p2, in int p3 )\n"
    "{\n"
    "   float r2, r3;\n"
    "   calculate_across_triangle_to_line_2D( r2, r3, p0, p1, p2, p3 );\n"
    "   perspective_correct_triangle( r2, r3, p0, p1, p2, p3 );\n"
    "\n"
    "   vec4  p123 = position_in[p1] + ( position_in[p2]  - position_in[p1] ) * r2 + ( position_in[p3] - position_in[p1] ) * r3;\n"
    "   float s123 = value_in[p1] + ( value_in[p2] - value_in[p1] ) * r2 + ( value_in[p3] - value_in[p1] ) * r3;\n"
    "\n"
    "   vec4 center_position;\n"
    "   vec3 center_position_3D;\n"
    "   float center_scalar_front, center_scalar_back; \n"
    "\n"
    "   vec3 n123 = normal_in[p1] + ( normal_in[p2] - normal_in[p1] ) * r2 + ( normal_in[p3] - normal_in[p1] ) * p3;\n"
    "   vec3 center_normal_3D;\n"
    "\n"
    "   if ( length( p123.z ) < length( position_in[p0].z ) )\n"
    "   {\n"
    "       center_position = gl_ProjectionMatrix * p123;\n"
    "       center_position_3D = p123.xyz;\n"
    "\n"
    "       center_normal_3D = n123.xyz;\n"
    "\n"
    "       center_scalar_front = s123;\n"
    "       center_scalar_back = value_in[p0];\n"
    "   }\n"
    "   else\n"
    "   {\n"
    "       center_position = gl_PositionIn[p0];\n"
    "       center_position_3D = position_in[p0].xyz;\n"
    "\n"
    "       center_normal_3D = normal_in[p0].xyz;\n"
    "\n"
    "       center_scalar_front = value_in[p0];\n"
    "       center_scalar_back = s123;\n"
    "   }\n"
    "\n"
    "   float center_distance = distance_to_texture_coord( length( position_in[p0] - p123 ) );\n"
    "\n"
    "    // p1-p2-C p2-C-p3 C-p3-p1\n"
    "    emitExistPoint( p1, 0.0 );\n"
    "    emitExistPoint( p2, 0.0 );\n"
    "    emitNewPoint( center_position, center_position_3D, center_normal_3D, center_scalar_front, center_scalar_back, center_distance );\n"
    "    emitExistPoint( p3, 0.0 );\n"
    "    emitExistPoint( p1, 0.0 );\n"
    "    EndPrimitive();\n"
    "}\n"
    "\n"
    "/*\n"
    "void create_type_2( in int p0, in int p1, in int p2, in int p3 )\n"
    "{\n"
    "\n"
    "   float r1, r3;\n"
    "   calculate_across_line_to_line_2D( r1, r3, p0, p1, p2, p3 );\n"
    "   perspective_correct_line( r1, p0, p1 );\n"
    "   perspective_correct_line( r3, p2, p3 );\n"
    "\n"
    "   vec4  p01 = position_in[p0] + ( position_in[p1] - position_in[p0] ) * r1;\n"
    "   float s01 = value_in[p0] + ( value_in[p1] - value_in[p0] ) * r1;\n"
    "\n"
    "   vec4  p23 = position_in[p2] + ( position_in[p3]  - position_in[p2] ) * r3;\n"
    "   float s23 = value_in[p2] + ( value_in[p3] - value_in[p2] ) * r3;\n"
    "\n"
    "   vec4 center_position;\n"
    "   vec3 center_position_3D;\n"
    "   float center_scalar_front, center_scalar_back; \n"
    "\n"
    "   vec3 n01 = normal_in[p0] + ( normal_in[p1] - normal_in[p0] ) * r1;\n"
    "   vec3 n23 = normal_in[p2] + ( normal_in[p3] - normal_in[p2] ) * r3;\n"
    "   vec3 center_normal_3D;\n"
    "\n"
    "   if ( length( p01.xyz ) < length( p23.xyz ) )\n"
    "   {\n"
    "       center_position = gl_ProjectionMatrix * p01;\n"
    "       center_position_3D = p01.xyz;\n"
    "\n"
    "       center_normal_3D = n01.xyz;\n"
    "\n"
    "       center_scalar_front = s01;\n"
    "       center_scalar_back = s23;\n"
    "   }\n"
    "   else\n"
    "   {\n"
    "       center_position = gl_ProjectionMatrix * p23;\n"
    "       center_position_3D = p23.xyz;\n"
    "\n"
    "       center_normal_3D = n23.xyz;\n"
    "\n"
    "       center_scalar_front = s23;\n"
    "       center_scalar_back = s01;\n"
    "   }\n"
    "\n"
    "   float center_distance = distance_to_texture_coord( length( p01.z - p23.z ) );\n"
    "\n"
    "    // right half: p0-p2-C, p2-C-p1\n"
    "    emitExistPoint( p0, 0.0 );\n"
    "    emitExistPoint( p2, 0.0 );\n"
    "    emitNewPoint( center_position, center_position_3D, center_normal_3D, center_scalar_front, center_scalar_back, center_distance );\n"
    "    emitExistPoint( p1, 0.0 );\n"
    "    EndPrimitive();\n"
    "\n"
    "    // left half: p0-p3-C, p3-C-p1\n"
    "    emitExistPoint( p0, 0.0 );\n"
    "    emitExistPoint( p3, 0.0 );\n"
    "    emitNewPoint( center_position, center_position_3D, center_normal_3D, center_scalar_front, center_scalar_back, center_distance );\n"
    "    emitExistPoint( p1, 0.0 );\n"
    "    EndPrimitive();\n"
    "}\n"
    "\n"
    "/*\n"
    "void create_type_3( in int p0, in int p1, in int p2, in int p3 )\n"
    "{\n"
    "    create_type_2( p0, p1, p2, p3 );\n"
    "}\n"
    "\n"
    "/*\n"
    "void create_type_4( in int p0, in int p1, in int p2, in int p3 )\n"
    "{\n"
    "\n"
    "    int pFront, pBack;\n"
    "    if ( position_in[p2].z < position_in[p3].z )\n"
    "    {\n"
    "        pFront = p2;\n"
    "        pBack = p3;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        pFront = p3;\n"
    "        pBack = p2;\n"
    "    }\n"
    "    float center_distance = distance_to_texture_coord( length( position_in[pBack] - position_in[pFront] ) );\n"
    "    emitExistPoint( p0, 0.0 );\n"
    "    emitExistPoint( p1, 0.0 );\n"
    "    emitExistPoint( pFront, center_distance );\n"
    "    EndPrimitive();\n"
    "}\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    if ( gl_PositionIn[0].w <= 0 ||\n"
    "         gl_PositionIn[1].w <= 0 ||\n"
    "         gl_PositionIn[2].w <= 0 ||\n"
    "         gl_PositionIn[3].w <= 0 ) return;\n"
    "\n"
    "    screen_position[0] = gl_PositionIn[0].xyz / gl_PositionIn[0].w;\n"
    "    screen_position[1] = gl_PositionIn[1].xyz / gl_PositionIn[1].w;\n"
    "    screen_position[2] = gl_PositionIn[2].xyz / gl_PositionIn[2].w;\n"
    "    screen_position[3] = gl_PositionIn[3].xyz / gl_PositionIn[3].w;\n"
    "\n"
    "    if ( ( screen_position[0].x < -1.0 && screen_position[1].x < -1.0 && screen_position[2].x < -1.0 && screen_position[3].x < -1.0 ) ||\n"
    "         ( screen_position[0].x >  1.0 && screen_position[1].x >  1.0 && screen_position[2].x >  1.0 && screen_position[3].x >  1.0 ) ||\n"
    "         ( screen_position[0].y < -1.0 && screen_position[1].y < -1.0 && screen_position[2].y < -1.0 && screen_position[3].y < -1.0 ) ||\n"
    "         ( screen_position[0].y >  1.0 && screen_position[1].y >  1.0 && screen_position[2].y >  1.0 && screen_position[3].y >  1.0 ) ) return;\n"
    "\n"
    "    id = id_in[0] * 3.0 + id_in[1] * 5.0 + id_in[2] * 7.0 + id_in[3] * 11.0;\n"
    "\n"
    "    int d321 = direction( 3, 2, 1 );\n"
    "    int d230 = direction( 2, 3, 0 );\n"
    "    int d103 = direction( 1, 0, 3 );\n"
    "    int d012 = direction( 0, 1, 2 );\n"
    "\n"
    "    int pos = d321 * 27 + d230 * 9 + d103 * 3 + d012;\n"
    "    vec2 t_pos = vec2( ( float(pos) + 0.5 ) / 81.0, 0.5 );\n"
    "    vec4 info = texture2D( decomposion_texture, t_pos );\n"
    "    int type = int( ( info.a * 255.0 + 16.0 ) / 32.0 );\n"
    "    int p0   = int( ( info.x * 255.0 + 16.0 ) / 32.0 );\n"
    "    int p1   = int( ( info.y * 255.0 + 16.0 ) / 32.0 );\n"
    "    int p2   = int( ( info.z * 255.0 + 16.0 ) / 32.0 );\n"
    "    int p3   = 6 - ( p0 + p1 + p2 );\n"
    "\n"
    "    if ( type == 1 )\n"
    "    {\n"
    "        create_type_1( p0, p1, p2, p3 );\n"
    "    }\n"
    "    else if ( type == 2 )\n"
    "    {\n"
    "        create_type_2( p0, p1, p2, p3 );\n"
    "    }\n"
    "    else if ( type == 3 )\n"
    "    {\n"
    "        create_type_3( p0, p1, p2, p3 );\n"
    "    }\n"
    "    else if ( type == 4 )\n"
    "    {\n"
    "        create_type_4( p0, p1, p2, p3 );\n"
    "    }\n"
    "\n"
    "}\n"
;

} // end of namespace Geometry

namespace Fragment
{

const std::string line =
    "varying vec3 position;\n"
    "varying vec2 id;\n"
    "\n"
    "uniform sampler2D random_texture;\n"
    "\n"
    "uniform vec2 screen_scale;\n"
    "uniform vec2 screen_scale_inv;\n"
    "\n"
    "uniform float random_texture_size_inv;\n"
    "uniform vec2 random_offset;\n"
    "\n"
    "uniform float opacity;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    if ( opacity == 0.0 ) { discard; return; }\n"
    "\n"
    "    if ( opacity < 0.99999 )\n"
    "    {\n"
    "        vec2 random_position = ( vec2( float( int( id.x ) * 73 ), float( int( id.y ) * 31 ) ) \n"
    "                    + random_offset + gl_FragCoord.xy ) * random_texture_size_inv;\n"
    "\n"
    "        float randf = texture2D( random_texture, random_position ).a;\n"
    "        if ( randf > opacity ) { discard; return; }\n"
    "    }\n"
    "\n"
    "    gl_FragColor = vec4( gl_Color.rgb, 1.0 );\n"
    "}\n"
;

const std::string point =
    "struct Shading\n"
    "{\n"
    "    float Ka; // ambient\n"
    "    float Kd; // diffuse\n"
    "    float Ks; // specular\n"
    "    float S;  // shininess\n"
    "};\n"
    "\n"
    "vec3 ShadingNone( in Shading shading, in vec3 color )\n"
    "{\n"
    "    return( color );\n"
    "}\n"
    "\n"
    "vec3 ShadingLambert( in Shading shading, in vec3 color, in vec3 L, in vec3 N )\n"
    "{\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "#endif\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "\n"
    "    return( color * ( Ia + Id ) );\n"
    "}\n"
    "\n"
    "vec3 ShadingPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 R = reflect( -L, N );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( R, V ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( R, V ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "vec3 ShadingBlinnPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 H = normalize( L + V );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( H, N ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( H, N ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "varying vec3  position;\n"
    "varying vec3  normal;\n"
    "varying vec2  center;\n"
    "varying float radius;\n"
    "\n"
    "uniform Shading shading;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    // Discard a pixel outside circle.\n"
    "    if ( radius > 0.0 )\n"
    "    {\n"
    "        if( distance( gl_FragCoord.xy, center ) > radius ) discard;\n"
    "    }\n"
    "\n"
    "    // Light position.\n"
    "    vec3 light_position = gl_LightSource[0].position.xyz;\n"
    "\n"
    "    // Light vector (L) and Normal vector (N)\n"
    "    vec3 L = normalize( light_position - position );\n"
    "    vec3 N = normalize( normal );\n"
    "\n"
    "#if   defined( ENABLE_LAMBERT_SHADING )\n"
    "    vec3 shaded_color = ShadingLambert( shading, gl_Color.xyz, L, N );\n"
    "\n"
    "#elif defined( ENABLE_PHONG_SHADING )\n"
    "    vec3 V = normalize( -position );\n"
    "    vec3 shaded_color = ShadingPhong( shading, gl_Color.xyz, L, N, V );\n"
    "\n"
    "#elif defined( ENABLE_BLINN_PHONG_SHADING )\n"
    "    vec3 V = normalize( -position );\n"
    "    vec3 shaded_color = ShadingBlinnPhong( shading, gl_Color.xyz, L, N, V );\n"
    "\n"
    "#else // DISABLE SHADING\n"
    "    vec3 shaded_color = ShadingNone( shading, gl_Color.xyz );\n"
    "#endif\n"
    "\n"
    "    gl_FragColor.xyz = shaded_color;\n"
    "    gl_FragColor.w = 1.0;\n"
    "}\n"
;

const std::string polygon =
    "struct Shading\n"
    "{\n"
    "    float Ka; // ambient\n"
    "    float Kd; // diffuse\n"
    "    float Ks; // specular\n"
    "    float S;  // shininess\n"
    "};\n"
    "\n"
    "vec3 ShadingNone( in Shading shading, in vec3 color )\n"
    "{\n"
    "    return( color );\n"
    "}\n"
    "\n"
    "vec3 ShadingLambert( in Shading shading, in vec3 color, in vec3 L, in vec3 N )\n"
    "{\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "#endif\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "\n"
    "    return( color * ( Ia + Id ) );\n"
    "}\n"
    "\n"
    "vec3 ShadingPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 R = reflect( -L, N );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( R, V ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( R, V ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "vec3 ShadingBlinnPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 H = normalize( L + V );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( H, N ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( H, N ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "varying vec3 position;\n"
    "varying vec3 normal;\n"
    "varying vec2 id;\n"
    "\n"
    "uniform sampler2D random_texture;\n"
    "\n"
    "uniform vec2 screen_scale;\n"
    "uniform vec2 screen_scale_inv;\n"
    "\n"
    "uniform float random_texture_size_inv;\n"
    "uniform vec2 random_offset;\n"
    "\n"
    "uniform Shading shading;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    if ( gl_Color.a == 0.0 ) { discard; return; }\n"
    "\n"
    "    if ( gl_Color.a < 0.99999 )\n"
    "    {\n"
    "        vec2 random_position = ( vec2( float( int( id.x ) * 73 ), float( int( id.y ) * 31 ) ) \n"
    "                    + random_offset + gl_FragCoord.xy ) * random_texture_size_inv;\n"
    "\n"
    "        float randf = texture2D( random_texture, random_position ).a;\n"
    "        if ( randf > gl_Color.a ) { discard; return; }\n"
    "    }\n"
    "\n"
    "    vec3 frag_color = gl_Color.rgb;\n"
    "\n"
    "    // Light position.\n"
    "    vec3 light_position = gl_LightSource[0].position.xyz;\n"
    "\n"
    "    // Light vector (L) and Normal vector (N)\n"
    "    vec3 L = normalize( light_position - position );\n"
    "    vec3 N = normalize( normal );\n"
    "\n"
    "#if   defined( ENABLE_LAMBERT_SHADING )\n"
    "    vec3 shaded_color = ShadingLambert( shading, frag_color, L, N );\n"
    "\n"
    "#elif defined( ENABLE_PHONG_SHADING )\n"
    "    vec3 V = normalize( -position );\n"
    "    vec3 shaded_color = ShadingPhong( shading, frag_color, L, N, V );\n"
    "\n"
    "#elif defined( ENABLE_BLINN_PHONG_SHADING )\n"
    "    vec3 V = normalize( -position );\n"
    "    vec3 shaded_color = ShadingBlinnPhong( shading, frag_color, L, N, V );\n"
    "\n"
    "#else // DISABLE SHADING\n"
    "    vec3 shaded_color = ShadingNone( shading, frag_color );\n"
    "#endif\n"
    "\n"
    "    gl_FragColor = vec4( shaded_color, 1.0 );\n"
    "}\n"
;

const std::string unstructured_volume =
    "struct Shading\n"
    "{\n"
    "    float Ka; // ambient\n"
    "    float Kd; // diffuse\n"
    "    float Ks; // specular\n"
    "    float S;  // shininess\n"
    "};\n"
    "\n"
    "vec3 ShadingNone( in Shading shading, in vec3 color )\n"
    "{\n"
    "    return( color );\n"
    "}\n"
    "\n"
    "vec3 ShadingLambert( in Shading shading, in vec3 color, in vec3 L, in vec3 N )\n"
    "{\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "#endif\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "\n"
    "    return( color * ( Ia + Id ) );\n"
    "}\n"
    "\n"
    "vec3 ShadingPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 R = reflect( -L, N );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( R, V ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( R, V ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "vec3 ShadingBlinnPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 H = normalize( L + V );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( H, N ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( H, N ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "varying vec3 position;\n"
    "varying vec3 normal;\n"
    "varying vec2 id;\n"
    "\n"
    "varying float scalar_front;\n"
    "varying float scalar_back;\n"
    "varying float distance;\n"
    "\n"
    "uniform sampler3D preintegration_texture;\n"
    "uniform sampler2D random_texture;\n"
    "\n"
    "uniform vec2 screen_scale;\n"
    "uniform vec2 screen_scale_inv;\n"
    "uniform vec2 preintegration_scale_offset;\n"
    "\n"
    "uniform float random_texture_size_inv;\n"
    "uniform vec2 random_offset;\n"
    "\n"
    "uniform Shading shading;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    vec3 lutcoord = vec3( scalar_front, scalar_back, distance );\n"
    "    vec4 lutdata = texture3D( preintegration_texture, lutcoord );\n"
    "    if ( lutdata.a == 0.0 ) { discard; return; }\n"
    "\n"
    "    vec2 random_position = ( vec2( float( int( id.x ) * 73 ), float( int( id.y ) * 31 ) ) \n"
    "                + random_offset + gl_FragCoord.xy ) * random_texture_size_inv;\n"
    "\n"
    "    float randf = texture2D( random_texture, random_position ).x;\n"
    "    if ( randf > lutdata.a ) { discard; return; }\n"
    "\n"
    "    vec3 frag_color = lutdata.xyz / lutdata.a;\n"
    "\n"
    "    // Light position.\n"
    "    vec3 light_position = gl_LightSource[0].position.xyz;\n"
    "\n"
    "    // Light vector (L) and Normal vector (N)\n"
    "    vec3 L = normalize( light_position - position );\n"
    "    vec3 N = normalize( normal );\n"
    "\n"
    "#if   defined( ENABLE_LAMBERT_SHADING )\n"
    "    vec3 shaded_color = ShadingLambert( shading, frag_color, L, N );\n"
    "\n"
    "#elif defined( ENABLE_PHONG_SHADING )\n"
    "    vec3 V = normalize( - position );\n"
    "    vec3 shaded_color = ShadingPhong( shading, frag_color, L, N, V );\n"
    "\n"
    "#elif defined( ENABLE_BLINN_PHONG_SHADING )\n"
    "    vec3 V = normalize( - position );\n"
    "    vec3 shaded_color = ShadingBlinnPhong( shading, frag_color, L, N, V );\n"
    "\n"
    "#else // DISABLE SHADING\n"
    "    vec3 shaded_color = ShadingNone( shading, frag_color );\n"
    "#endif\n"
    "\n"
    "    gl_FragColor = vec4( shaded_color, 1.0 );\n"
    "}\n"
;

} // end of namespace Fragment

} // end of namespace StochasticRenderingEngine

} } } // end of namespace kvs, glew, glsl

#endif // KVS__GLEW__GLSL__StochasticRenderingEngine_H_INCLUDE
