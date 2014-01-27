/****************************************************************************/
/**
 *  @file   Module.h
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
/****************************************************************************/
#ifndef KVS__MODULE_H_INCLUDE
#define KVS__MODULE_H_INCLUDE

#include <cstring>

#define KVS_MODULE_IMPORTER kvs::ImporterBase::ModuleTag
#define KVS_MODULE_FILTER   kvs::FilterBase::ModuleTag
#define KVS_MODULE_MAPPER   kvs::MapperBase::ModuleTag
#define KVS_MODULE_OBJECT   kvs::ObjectBase::ModuleTag
#define KVS_MODULE_RENDERER kvs::RendererBase::ModuleTag

#define kvsModuleBase( this_class )                                     \
    public:                                                             \
    struct  ModuleTag{};                                                \
    typedef ModuleTag ModuleCategory;                                   \
    virtual const char* moduleName() const { return #this_class; }

#define kvsModule( category, this_class, super_class )                  \
    public:                                                             \
    typedef kvs:: category##Base::ModuleTag ModuleCategory;             \
    virtual const char* moduleName() const { return #this_class; }      \
    static this_class* DownCast( kvs:: category##Base* m )              \
    {                                                                   \
        if ( m && strcmp( m->moduleName(), #this_class ) )              \
        {                                                               \
            return static_cast<this_class *>( m );                      \
        }                                                               \
        return NULL;                                                    \
    };                                                                  \
    static const this_class* DownCast( const kvs:: category##Base* m )  \
    {                                                                   \
        return DownCast( const_cast<kvs:: category##Base *>( m ) );     \
    }

/* DEPRECATED */
#define kvsModuleCategory( module_category )                            \
    public:                                                             \
    typedef kvs:: module_category##Base::ModuleTag ModuleCategory

/* DEPRECATED */
#define kvsModuleName( module_name )            \
    public:                                     \
    virtual const char* moduleName() const {    \
        return #module_name;                    \
    }

/* DEPRECATED */
#define kvsModuleBaseClass( base_class )        \
    typedef base_class BaseClass

/* DEPRECATED */
#define kvsModuleSuperClass( super_class )      \
    typedef super_class SuperClass

namespace kvs
{

template <typename T>
struct ModuleTraits
{
    typedef typename T::ModuleCategory ModuleCategory;
};

} // end of namespace kvs

#endif // KVS__MODULE_H_INCLUDE
