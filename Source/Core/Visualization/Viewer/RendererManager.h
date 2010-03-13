/****************************************************************************/
/**
 *  @file RendererManager.h
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
#ifndef KVS_CORE_RENDERER_MANAGER_H_INCLUDE
#define KVS_CORE_RENDERER_MANAGER_H_INCLUDE

#include <list>
#include <map>
#include <kvs/ClassName>
#include <kvs/RendererBase>


namespace kvs
{

typedef std::list<kvs::RendererBase*> RendererManagerBase;

/*==========================================================================*/
/**
*  Renderer manager class.
*/
/*==========================================================================*/
class RendererManager : public RendererManagerBase
{
    kvsClassName( RendererManager );

public:

    typedef RendererManagerBase::iterator  RendererIterator;
    typedef std::map<int,RendererIterator> RendererMap;

protected:

    RendererMap m_renderer_map; ///< renderer map

public:

    RendererManager( void );

    virtual ~RendererManager( void );

public:

    int insert( kvs::RendererBase* renderer );

    void erase( bool delete_flg = true );

    void erase( int renderer_id, bool delete_flg = true );

    void change( int renderer_id, kvs::RendererBase* renderer, bool delete_flg = true );

    const int nrenderers( void ) const;

    kvs::RendererBase* renderer( void );

    kvs::RendererBase* renderer( int renderer_id );

    const bool hasRenderer( void ) const;
};

} // end of namespace kvs

#endif // KVS_CORE_RENDERER_MANAGER_H_INCLUDE