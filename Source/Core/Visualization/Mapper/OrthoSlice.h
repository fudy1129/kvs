/****************************************************************************/
/**
 *  @file OrthoSlice.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_CORE_ORTHO_SLICE_H_INCLUDE
#define KVS_CORE_ORTHO_SLICE_H_INCLUDE

#include <kvs/SlicePlane>
#include <kvs/VolumeObjectBase>
#include <kvs/ClassName>
#include <kvs/Module>


namespace kvs
{

/*==========================================================================*/
/**
 *  Axis aligned slice plane class.
 */
/*==========================================================================*/
class OrthoSlice : public kvs::SlicePlane
{
    // Class name.
    kvsClassName( OrthoSlice );

    // Module information.
    kvsModuleCategory( Mapper );
    kvsModuleSuperClass( kvs::SlicePlane );

public:

    enum AlignedAxis
    {
        XAxis = 0,
        YAxis = 1,
        ZAxis = 2
    };

protected:

    AlignedAxis m_aligned_axis; ///< aligned axis

public:

    OrthoSlice( void );

    OrthoSlice(
        const kvs::VolumeObjectBase* volume,
        const float                  position,
        const AlignedAxis            aligned_axis,
        const kvs::TransferFunction& transfer_function );

public:

    void setPlane( const float position, const kvs::OrthoSlice::AlignedAxis axis );
};

} // end of namespace kvs

#endif // KVS_CORE_ORTHO_SLICE_H_INCLUDE