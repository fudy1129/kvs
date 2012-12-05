/*****************************************************************************/
/**
 *  @file   SphereGlyph.h
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
#ifndef KVS__SPHERE_GLYPH_H_INCLUDE
#define KVS__SPHERE_GLYPH_H_INCLUDE

#include "GlyphBase.h"
#include <kvs/PointObject>
#include <kvs/Module>
#include <kvs/OpenGL>


namespace kvs
{

class ObjectBase;
class Camera;
class Light;
class PointObject;
class VolumeObjectBase;
class TransferFunction;
class RGBColor;

/*===========================================================================*/
/**
 *  @brief  Sphere glyph class.
 */
/*===========================================================================*/
class SphereGlyph : public kvs::GlyphBase
{
    kvsModuleName( kvs::SphereGlyph );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::GlyphBase );

private:

    GLUquadricObj* m_sphere; ///< glyph primitive
    size_t m_nslices; ///< number of subdivisions around the z-axis (lines of longitude)
    size_t m_nstacks; ///< number of subdivisions along the z-axis (lines of latitude)
    const kvs::PointObject* m_point; ///< pointer to the point object (reference)
    const kvs::VolumeObjectBase* m_volume; ///< pointer to the volume object (reference)

public:

    SphereGlyph();
    SphereGlyph( const kvs::PointObject* point );
    SphereGlyph( const kvs::VolumeObjectBase* volume );
    SphereGlyph( const kvs::VolumeObjectBase* volume, const kvs::TransferFunction& transfer_function );
    virtual ~SphereGlyph();

    void setNumberOfSlices( const size_t nslices );
    void setNumberOfStacks( const size_t nstacks );

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

private:

    void attach_point( const kvs::PointObject* point );
    void attach_volume( const kvs::VolumeObjectBase* volume );
    void draw();
    void draw_element( const kvs::RGBColor& color, const kvs::UInt8 opacity );
    void initialize();

#if 1 // KVS_ENABLE_DEPRECATED
public:
    void setNSlices( const size_t nslices ) { this->setNumberOfSlices( nslices ); }
    void setNStacks( const size_t nstacks ) { this->setNumberOfStacks( nstacks ); }
#endif
};

} // end of namespace kvs

#endif // KVS__SPHERE_GLYPH_H_INCLUDE
