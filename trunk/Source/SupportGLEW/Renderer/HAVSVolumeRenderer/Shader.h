/* DONT'T EDIT THIS FILE.
 * THIS IS GENERATED BY "Configure/configure_shader.py".
 */
#ifndef KVS__GLEW__GLSL__HAVSVolumeRenderer_H_INCLUDE
#define KVS__GLEW__GLSL__HAVSVolumeRenderer_H_INCLUDE

#include <string>

namespace kvs { namespace glew { namespace glsl {

namespace HAVSVolumeRenderer
{

namespace Vertex
{

const std::string begin =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_Position = ftransform();\n"
    "}\n"
;

const std::string kbuffer =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    vec3 eyePos = vec3( gl_ModelViewMatrix * gl_Vertex );\n"
    "    vec3 distvec = -eyePos;\n"
    "    float dist = length( distvec );\n"
    "\n"
    "    // scalar value\n"
    "    gl_TexCoord[0] = gl_MultiTexCoord0;\n"
    "\n"
    "    // eye coordinate\n"
    "    gl_TexCoord[1].xyz = eyePos.xyz;\n"
    "\n"
    "    gl_Position = ftransform();\n"
    "}\n"
;

} // end of namespace Vertex

namespace Fragment
{

const std::string k2 =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "//-----------------------------------------------------------------------------\n"
    "// \n"
    "// The program consists of the following steps:\n"
    "//\n"
    "// 1. Find the first and second entries in the fixed size k-buffer list sorted \n"
    "//    by d (2+1 entries)\n"
    "// 2. Perform a 3D pre-integrated transfer function lookup using front and back\n"
    "//    scalar data values + the segment length computed from the distance values\n"
    "//    of the first and second entries from the k-buffer.\n"
    "// 3. Composite the color and opacity from the transfer function with the\n"
    "//    color and opacity from the framebuffer. Discard winning k-buffer entry,\n"
    "//    write the remaining k-buffer entries.\n"
    "//\n"
    "// The following textures are used:\n"
    "// \n"
    "//   Tex framebuffer: off-screen framebuffer (2D RGBA 16/32 bpp float)\n"
    "//   Tex kbuffer1: k-buffer entries 1 and 2 (same)\n"
    "//   Tex lut: transfer function lookup table (3D RGBA 8/16 bpp int)\n"
    "//\n"
    "\n"
    "uniform vec4 scale;        // scale and bias parameters (1/pw, 1/ph, \n"
    "                           // (1-1/z_size)/max_length, 1/(2*z_size)\n"
    "uniform sampler2D framebuffer;\n"
    "uniform sampler2D kbuffer1;\n"
    "uniform sampler3D lut;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    // Compute texture coords from window position so that it is not\n"
    "    // interpolated perspective-correct.\n"
    "    vec2 position = gl_FragCoord.xy * scale.xy;\n"
    "    vec4 fbcolor = vec4(texture2D(framebuffer, position));\n"
    "\n"
    "    // Early discard test\n"
    "    if (fbcolor.a > 0.99) discard;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Fragment Ordering via Selection Sort\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Compute fragment-to-eye distance\n"
    "    float dist = length(gl_TexCoord[1]);\n"
    "    // Setup k-buffer entry k0 using the incoming fragment\n"
    "    vec2 k0 = vec2(gl_TexCoord[0].x, dist);\n"
    "\n"
    "    // Read the k-buffer entries k1 and k2 from texture.\n"
    "    // Each k-buffer entry contains the scalar data value in x or z\n"
    "    // and the distance value in y or w.\n"
    "    vec4 tmp = vec4(texture2D(kbuffer1, position));\n"
    "    vec2 k1 = tmp.xy;\n"
    "    vec2 k2 = tmp.zw;\n"
    "\n"
    "    // Find fragment with minimum distance (first) and save the rest (rest[1-2])\n"
    "    // first = min_distance(k0, k1); rest1 = max_distance(k0, k1);\n"
    "    vec2 first = (k0.y < k1.y) ? k0 : k1;\n"
    "    vec2 rest1 = (k0.y <= k1.y) ? k1 : k0;\n"
    "\n"
    "    // first = min_distance(first, k2); rest2 = max_distance(first, k2);\n"
    "    vec2 rest2 = (first.y <= k2.y) ? k2 : first;\n"
    "    first = (first.y < k2.y) ? first : k2;\n"
    "\n"
    "    // Find fragment with minimum distance (second) from the rest.\n"
    "    // second = min_distance(rest1, rest2);\n"
    "    vec2 second = (rest1.y < rest2.y) ? rest1 : rest2;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Transfer Function\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Set up texcoords for lookup\n"
    "    vec3 texcoords = vec3(second.x, first.x, second.y - first.y);\n"
    "    texcoords.z = texcoords.z * scale.z + scale.w;\n"
    "\n"
    "    // Transfer function lookup\n"
    "    vec4 col = vec4(texture3D(lut, texcoords));\n"
    "\n"
    "    // Invalidate initialization fragments and fragments with a distance\n"
    "    // greater than unit scale (non-convexity)\n"
    "    vec4 zero = vec4(0.0);\n"
    "    if (first.x <= 0.0) col = zero;\n"
    "    if (texcoords.z > 1.0) col = zero;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Compositing\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Composite color with the framebuffer: FRONT TO BACK\n"
    "    float transp = 1.0 - fbcolor.a;\n"
    "    vec4 final = col * transp + fbcolor;\n"
    "\n"
    "    // Write the k-buffer entries back into textures.\n"
    "    gl_FragData[1] = vec4(rest1.x, rest1.y, rest2.x, rest2.y);\n"
    "    gl_FragData[0] = final;\n"
    "}\n"
;

const std::string k2_begin =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "//\n"
    "// ---------------------------------------------------------------------------\n"
    "// The program consists of the following steps:\n"
    "//\n"
    "// 1. Clear the off-screen framebuffer to 0.0\n"
    "// 2. Clear the k-buffers entries 1-2 to -1.0\n"
    "// \n"
    "// The following textures are used:\n"
    "//\n"
    "//  Tex 0: off-screen framebuffer\n"
    "//  Tex 1: k-buffer entries 1 and 2 (2D RGBA 16/32 bpp float)\n"
    "//\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_FragData[0] = vec4( 0.0 );\n"
    "    gl_FragData[1] = vec4( -1.0 );\n"
    "}\n"
;

const std::string k2_end =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "//-----------------------------------------------------------------------------\n"
    "// \n"
    "// The program consists of the following steps:\n"
    "//\n"
    "// 1. Find the first and second entries in the fixed size k-buffer list sorted \n"
    "//    by d (2 entries)\n"
    "// 2. Perform a 3D pre-integrated transfer function lookup using front and back\n"
    "//    scalar data values + the segment length computed from the distance values\n"
    "//    of the first and second entries from the k-buffer.\n"
    "// 3. Composite the color and opacity from the transfer function with the\n"
    "//    color and opacity from the framebuffer. Discard winning k-buffer entry,\n"
    "//    write the remaining k-buffer entries.\n"
    "//\n"
    "// The following textures are used:\n"
    "// \n"
    "//   Tex framebuffer: off-screen framebuffer (2D RGBA 16/32 bpp float)\n"
    "//   Tex kbuffer1: k-buffer entries 1 and 2 (same)\n"
    "//   Tex lut: transfer function lookup table (3D RGBA 8/16 bpp int)\n"
    "//\n"
    "uniform vec4 scale;        // scale and bias parameters (1/pw, 1/ph, \n"
    "                           // (1-1/z_size)/max_length, 1/(2*z_size)\n"
    "uniform sampler2D framebuffer;\n"
    "uniform sampler2D kbuffer1;\n"
    "uniform sampler3D lut;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    // Computer Texture coords from window position so that it is not\n"
    "    // interpolated perspective-correct.\n"
    "    vec2 position = gl_FragCoord.xy * scale.xy;\n"
    "    vec4 fbcolor = vec4 (texture2D(framebuffer, position));\n"
    "\n"
    "    // Early discard test\n"
    "    if(fbcolor.a >= 0.99) discard;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Fragment Ordering via Selection Sort\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Read the k-buffer entries k1 and k2 from texture.\n"
    "    // Each k-buffer entry contains the scalar data value in x or z\n"
    "    // And the distance value in y or w.\n"
    "    vec4 tmp = vec4(texture2D(kbuffer1, position));\n"
    "    vec2 k1 = tmp.xy;\n"
    "    vec2 k2 = tmp.zw;\n"
    "\n"
    "    // first = min_distance(k1,k2); second = max_distance(k1,k2);\n"
    "    vec2 first = (k1.y < k2.y) ? k1 : k2;\n"
    "    vec2 second = (k1.y <= k2.y) ? k2 : k1;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Transfer Function\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Set up the texcoords for lookup\n"
    "    vec3 texcoords = vec3 (first.x, second.x, second.y - first.y);\n"
    "    texcoords.z = texcoords.z * scale.z + scale.w;\n"
    "\n"
    "    // Transfer Function lookup\n"
    "    vec4 col = vec4 (texture3D(lut, texcoords));\n"
    "\n"
    "    // Invalidate initialization fragments\n"
    "    vec4 zero = vec4(0.0);\n"
    "    if (first.x <= 0.0) col = zero;\n"
    "    if (second.x <= 0.0) col = zero;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Compositing\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Composite color with the framebuffer: FRONT TO BACK\n"
    "    float transp = 1.0 - fbcolor.a;\n"
    "    vec4 final = col * transp + fbcolor;\n"
    "\n"
    "    // Write the k-buffer entries back into textures\n"
    "    gl_FragData[1] = vec4(second.x, second.y, -1.0, 10000.0);\n"
    "    gl_FragData[0] = final;\n"
    "}\n"
;

const std::string k6 =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "//-----------------------------------------------------------------------------\n"
    "// \n"
    "// The program consists of the following steps:\n"
    "//\n"
    "// 1. Find the first and second entries in the fixed size k-buffer list sorted \n"
    "//    by d (6+1 entries)\n"
    "// 2. Perform a 3D pre-integrated transfer function lookup using front and back\n"
    "//    scalar data values + the segment length computed from the distance values\n"
    "//    of the first and second entries from the k-buffer.\n"
    "// 3. Composite the color and opacity from the transfer function with the\n"
    "//    color and opacity from the framebuffer. Discard winning k-buffer entry,\n"
    "//    write the remaining k-buffer entries.\n"
    "//\n"
    "// The following textures are used:\n"
    "// \n"
    "//   Tex framebuffer: off-screen framebuffer (2D RGBA 16/32 bpp float)\n"
    "//   Tex kbuffer1: k-buffer entries 1 and 2 (same)\n"
    "//   Tex kbuffer2: k-buffer entries 3 and 4 (same)\n"
    "//   Tex kbuffer3: k-buffer entries 5 and 6 (same)\n"
    "//   Tex lut: transfer function lookup table (3D RGBA 8/16 bpp int)\n"
    "//\n"
    "\n"
    "uniform vec4 scale;        // scale and bias parameters (1/pw, 1/ph, \n"
    "                           // (1-1/z_size)/max_length, 1/(2*z_size)\n"
    "uniform sampler2D framebuffer;\n"
    "uniform sampler2D kbuffer1;\n"
    "uniform sampler2D kbuffer2;\n"
    "uniform sampler2D kbuffer3;\n"
    "uniform sampler3D lut;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    // Compute texture coords from window position so that it is not\n"
    "    // interpolated perspective-correct.\n"
    "    vec2 position = gl_FragCoord.xy * scale.xy;\n"
    "    vec4 fbcolor = vec4(texture2D(framebuffer, position));\n"
    "\n"
    "    // Early discard test\n"
    "    if (fbcolor.a > 0.99) discard;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Fragment Ordering via Selection Sort\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Compute fragment-to-eye distance\n"
    "    float dist = length(gl_TexCoord[1]);\n"
    "    // Setup k-buffer entry k0 using the incoming fragment\n"
    "    vec2 k0 = vec2(gl_TexCoord[0].x, dist);\n"
    "\n"
    "    // Read the k-buffer entries k1-k6 from texture.\n"
    "    // Each k-buffer entry contains the scalar data value in x or z\n"
    "    // and the distance value in y or w.\n"
    "    vec4 tmp = vec4(texture2D(kbuffer1, position));\n"
    "    vec2 k1 = tmp.xy;\n"
    "    vec2 k2 = tmp.zw;\n"
    "    tmp = vec4(texture2D(kbuffer2, position));\n"
    "    vec2 k3 = tmp.xy;\n"
    "    vec2 k4 = tmp.zw;\n"
    "    tmp = vec4(texture2D(kbuffer3, position));\n"
    "    vec2 k5 = tmp.xy;\n"
    "    vec2 k6 = tmp.zw;\n"
    "\n"
    "    // Find fragment with minimum distance (first) and save the rest (rest[1-6])\n"
    "    // first = min_distance(k0, k1); rest1 = max_distance(k0, k1);\n"
    "    vec2 first = (k0.y < k1.y) ? k0 : k1;\n"
    "    vec2 rest1 = (k0.y <= k1.y) ? k1 : k0;\n"
    "    // first = min_distance(first, k2); rest2 = max_distance(first, k2);\n"
    "    vec2 rest2 = (first.y <= k2.y) ? k2 : first;\n"
    "    first = (first.y < k2.y) ? first : k2;\n"
    "    // first = min_distance(first, k3); rest3 = max_distance(first, k3);\n"
    "    vec2 rest3 = (first.y <= k3.y) ? k3 : first;\n"
    "    first = (first.y < k3.y) ? first : k3;\n"
    "    // first = min_distance(first, k4); rest4 = max_distance(first, k4);\n"
    "    vec2 rest4 = (first.y <= k4.y) ? k4 : first;\n"
    "    first = (first.y < k4.y) ? first : k4;\n"
    "    // first = min_distance(first, k5); rest5 = max_distance(first, k5);\n"
    "    vec2 rest5 = (first.y <= k5.y) ? k5 : first;\n"
    "    first = (first.y < k5.y) ? first : k5;\n"
    "    // first = min_distance(first, k6); rest6 = max_distance(first, k6);\n"
    "    vec2 rest6 = (first.y <= k6.y) ? k6 : first;\n"
    "    first = (first.y < k6.y) ? first : k6;\n"
    "\n"
    "    // Find fragment with minimum distance (second) from the rest.\n"
    "    // second = min_distance(rest1, rest2);\n"
    "    vec2 second = (rest1.y < rest2.y) ? rest1 : rest2;\n"
    "    second = (second.y < rest3.y) ? second : rest3;\n"
    "    second = (second.y < rest4.y) ? second : rest4;\n"
    "    second = (second.y < rest5.y) ? second : rest5;\n"
    "    second = (second.y < rest6.y) ? second : rest6;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Transfer Function\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Set up texcoords for lookup\n"
    "    vec3 texcoords = vec3(second.x, first.x, second.y - first.y);\n"
    "    texcoords.z = texcoords.z * scale.z + scale.w;\n"
    "\n"
    "    // Transfer function lookup\n"
    "    vec4 col = vec4(texture3D(lut, texcoords));\n"
    "\n"
    "    // Invalidate initialization fragments and fragments with a distance\n"
    "    // greater than unit scale (non-convexity)\n"
    "    vec4 zero = vec4(0.0);\n"
    "    if (first.x <= 0.0) col = zero;\n"
    "    if (texcoords.z > 1.0) col = zero;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Compositing\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Composite color with the framebuffer: FRONT TO BACK\n"
    "    float transp = 1.0 - fbcolor.a;\n"
    "    vec4 final = col * transp + fbcolor;\n"
    "\n"
    "    // Write the k-buffer entries back into textures.\n"
    "    gl_FragData[1] = vec4(rest1.x, rest1.y, rest2.x, rest2.y);\n"
    "    gl_FragData[2] = vec4(rest3.x, rest3.y, rest4.x, rest4.y);\n"
    "    gl_FragData[3] = vec4(rest5.x, rest5.y, rest6.x, rest6.y);\n"
    "    gl_FragData[0] = final;\n"
    "}\n"
;

const std::string k6_begin =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "//\n"
    "// ---------------------------------------------------------------------------\n"
    "// The program consists of the following steps:\n"
    "//\n"
    "// 1. Clear the off-screen framebuffer to 0.0 \n"
    "// 2. Clear the k-buffers entries 1-6 to -1.0\n"
    "// \n"
    "// The following textures are used:\n"
    "//\n"
    "//  Tex 0: off-screen framebuffer\n"
    "//  Tex 1: k-buffer entries 1 and 2 (2D RGBA 16/32 bpp float)\n"
    "//  Tex 2: k-buffer entries 3 and 4 (same)\n"
    "//  Tex 3: k-buffer entries 5 and 6 (same)\n"
    "//\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_FragData[0] = vec4(0.0);\n"
    "    gl_FragData[1] = vec4(-1.0);\n"
    "    gl_FragData[2] = vec4(-1.0);\n"
    "    gl_FragData[3] = vec4(-1.0);\n"
    "}\n"
;

const std::string k6_end =
    "//\n"
    "// The Hardware-Assisted Visibility Ordering Algorithm\n"
    "// Copyright (c) 2005, 2006\n"
    "// University of Utah\n"
    "// All rights reserved.\n"
    "//\n"
    "// This software is licensed under the BSD open-source license. See\n"
    "// http://www.opensource.org/licenses/bsd-license.php for more detail.\n"
    "//\n"
    "// *************************************************************\n"
    "// Redistribution and use in source and binary forms, with or \n"
    "// without modification, are permitted provided that the following \n"
    "// conditions are met:\n"
    "//\n"
    "// Redistributions of source code must retain the above copyright notice, \n"
    "// this list of conditions and the following disclaimer. \n"
    "//\n"
    "// Redistributions in binary form must reproduce the above copyright notice, \n"
    "// this list of conditions and the following disclaimer in the documentation \n"
    "// and/or other materials provided with the distribution. \n"
    "//\n"
    "// Neither the name of the University of Utah nor the names of \n"
    "// the contributors may be used to endorse or promote products derived \n"
    "// from this software without specific prior written permission.\n"
    "//\n"
    "// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \n"
    "// 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \n"
    "// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS \n"
    "// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL \n"
    "// THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, \n"
    "// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL \n"
    "// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE \n"
    "// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS \n"
    "// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, \n"
    "// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \n"
    "// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF \n"
    "// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY \n"
    "// OF SUCH DAMAGE.\n"
    "//-----------------------------------------------------------------------------\n"
    "// \n"
    "// The program consists of the following steps:\n"
    "//\n"
    "// 1. Find the first and second entries in the fixed size k-buffer list sorted \n"
    "//    by d (6 entries)\n"
    "// 2. Perform a 3D pre-integrated transfer function lookup using front and back\n"
    "//    scalar data values + the segment length computed from the distance values\n"
    "//    of the first and second entries from the k-buffer.\n"
    "// 3. Composite the color and opacity from the transfer function with the\n"
    "//    color and opacity from the framebuffer. Discard winning k-buffer entry,\n"
    "//    write the remaining k-buffer entries.\n"
    "//\n"
    "// The following textures are used:\n"
    "// \n"
    "//   Tex framebuffer: off-screen framebuffer (2D RGBA 16/32 bpp float)\n"
    "//   Tex kbuffer: k-buffer entries 1 and 2 (same)\n"
    "//   Tex lut: transfer function lookup table (3D RGBA 8/16 bpp int)\n"
    "//\n"
    "uniform vec4 scale;        // scale and bias parameters (1/pw, 1/ph, \n"
    "                           // (1-1/z_size)/max_length, 1/(2*z_size)\n"
    "uniform sampler2D framebuffer;\n"
    "uniform sampler2D kbuffer1;\n"
    "uniform sampler2D kbuffer2;\n"
    "uniform sampler2D kbuffer3;\n"
    "uniform sampler3D lut;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    // Computer Texture coords from window position so that it is not\n"
    "    // interpolated perspective-correct.\n"
    "    vec2 position = gl_FragCoord.xy * scale.xy;\n"
    "    vec4 fbcolor = vec4 (texture2D(framebuffer, position));\n"
    "\n"
    "    // Early discard test\n"
    "    if(fbcolor.a >= 0.99) discard;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Fragment Ordering via Selection Sort\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Read the k-buffer entries k1-k6 from texture.\n"
    "    // Each k-buffer entry contains the scalar data value in x or z\n"
    "    // And the distance value in y or w.\n"
    "    vec4 tmp = vec4(texture2D(kbuffer1, position));\n"
    "    vec2 k1 = tmp.xy;\n"
    "    vec2 k2 = tmp.zw;\n"
    "    tmp = vec4(texture2D(kbuffer2, position));\n"
    "    vec2 k3 = tmp.xy;\n"
    "    vec2 k4 = tmp.zw;\n"
    "    tmp = vec4(texture2D(kbuffer3, position));\n"
    "    vec2 k5 = tmp.xy;\n"
    "    vec2 k6 = tmp.zw;\n"
    "\n"
    "    // Find fragment with minimum distance (first) and save the rest (rest[1-5])\n"
    "    // first = min_distance(k1,k2); rest1 = max_distance(k1,k2);\n"
    "    vec2 first = (k1.y < k2.y) ? k1 : k2;\n"
    "    vec2 rest1 = (k1.y <= k2.y) ? k2 : k1;\n"
    "    // first = min_distance(first, k3); rest2 = max_distance(first, k3);\n"
    "    vec2 rest2 = (first.y <= k3.y) ? k3 : first;\n"
    "    first = (first.y < k3.y) ? first : k3;\n"
    "    // first = min_distance(first, k4); rest3 = max_distance(first, k4);\n"
    "    vec2 rest3 = (first.y <= k4.y) ? k4 : first;\n"
    "    first = (first.y < k4.y) ? first : k4;\n"
    "    // first = min_distance(first, k5); rest4 = max_distance(first, k5);\n"
    "    vec2 rest4 = (first.y <= k5.y) ? k5 : first;\n"
    "    first = (first.y < k5.y) ? first : k5;\n"
    "    // first = min_distance(first, k6); rest5 = max_distance(first, k6);\n"
    "    vec2 rest5 = (first.y <= k6.y) ? k6 : first;\n"
    "    first = (first.y < k6.y) ? first : k6;\n"
    "\n"
    "    // Find fragment with minimum distance (second) from the rest.\n"
    "    // second = min_distance(rest1, rest2);\n"
    "    vec2 second =  (rest1.y < rest2.y) ? rest1 : rest2;\n"
    "    second = (second.y < rest3.y) ? second : rest3;\n"
    "    second = (second.y < rest4.y) ? second : rest4;\n"
    "    second = (second.y < rest5.y) ? second : rest5;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Transfer Function\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Set up the texcoords for lookup\n"
    "    vec3 texcoords = vec3 (first.x, second.x, second.y - first.y);\n"
    "    texcoords.z = texcoords.z * scale.z + scale.w;\n"
    "\n"
    "    // Transfer Function lookup\n"
    "    vec4 col = vec4 (texture3D(lut, texcoords));\n"
    "\n"
    "    // Invalidate initialization fragments\n"
    "    vec4 zero = vec4(0.0);\n"
    "    if (first.x <= 0.0) col = zero;\n"
    "    if (second.x <= 0.0) col = zero;\n"
    "\n"
    "    // ---------------------------------------------------------------\n"
    "    // Compositing\n"
    "    // ---------------------------------------------------------------\n"
    "\n"
    "    // Composite color with the framebuffer: FRONT TO BACK\n"
    "    float transp = 1.0 - fbcolor.a;\n"
    "    vec4 final = col * transp + fbcolor;\n"
    "\n"
    "    // Write the k-buffer entries back into textures\n"
    "    gl_FragData[1] = vec4(rest1.x, rest1.y, rest2.x, rest2.y);\n"
    "    gl_FragData[2] = vec4(rest3.x, rest3.y, rest4.x, rest4.y);\n"
    "    gl_FragData[3] = vec4(rest5.x, rest5.y, -1.0, 10000.0);\n"
    "    gl_FragData[0] = final;\n"
    "}\n"
;

} // end of namespace Fragment

} // end of namespace HAVSVolumeRenderer

} } } // end of namespace kvs, glew, glsl

#endif // KVS__GLEW__GLSL__HAVSVolumeRenderer_H_INCLUDE