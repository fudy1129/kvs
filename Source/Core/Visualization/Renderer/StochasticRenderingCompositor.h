/*****************************************************************************/
/**
 *  @file   StochasticRenderingCompositor.h
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
#ifndef KVS__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE
#define KVS__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE

#include <kvs/PaintEventListener>
#include <kvs/Matrix44>
#include <kvs/Vector3>
#include "EnsembleAverageBuffer.h"


namespace kvs
{

class Scene;

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering compositor class.
 */
/*===========================================================================*/
class StochasticRenderingCompositor : public kvs::PaintEventListener
{
private:

    kvs::Scene* m_scene; ///< pointer to the scene
    size_t m_width; ///< window width
    size_t m_height; ///< window height
    size_t m_repetition_level; ///< repetition level
    size_t m_coarse_level; ///< repetition level for the coarse rendering (LOD)
    bool m_enable_lod; ///< flag for LOD rendering
    bool m_enable_refinement; ///< flag for progressive refinement rendering
    bool m_enable_shading; ///< shading flag
    kvs::Mat4 m_object_xform; ///< object xform matrix used for LOD control
    kvs::Vec3 m_light_position; ///< light position used for LOD control
    kvs::Vec3 m_camera_position; ///< camera position used for LOD control
    kvs::EnsembleAverageBuffer m_ensemble_buffer; ///< ensemble averaging buffer

public:

    StochasticRenderingCompositor( kvs::Scene* scene );

    size_t repetitionLevel() const { return m_repetition_level; }
    bool isEnabledLODControl() const { return m_enable_lod; }
    bool isEnabledRefinement() const { return m_enable_refinement; }
    bool isEnabledShading() const { return m_enable_shading; }
    void setRepetitionLevel( const size_t repetition_level ) { m_repetition_level = repetition_level; }
    void setEnabledLODControl( const bool enable ) { m_enable_lod = enable; }
    void setEnabledRefinement( const bool enable ) { m_enable_refinement = enable; }
    void setEnabledShading( const bool enable ) { m_enable_shading = enable; }
    void enableLODControl() { this->setEnabledLODControl( true ); }
    void enableRefinement() { this->setEnabledRefinement( true ); }
    void enableShading() { this->setEnabledShading( true ); }
    void disableLODControl() { this->setEnabledLODControl( false ); }
    void disableRefinement() { this->setEnabledRefinement( false ); }
    void disableShading() { this->setEnabledShading( false ); }

private:

    StochasticRenderingCompositor();
    void update();
    void draw();
    void check_window_created();
    void check_window_resized();
    void check_object_changed();
    kvs::Mat4 object_xform();
    void engines_create();
    void engines_update();
    void engines_setup( const bool reset_count );
    void engines_draw();
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE
