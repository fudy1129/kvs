/*****************************************************************************/
/**
 *  @file   Acceptor.h
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
#ifndef KVS__ACCEPTOR_H_INCLUDE
#define KVS__ACCEPTOR_H_INCLUDE

#include <kvs/TCPServer>
#include <kvs/IPAddress>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Acceptor class.
 */
/*===========================================================================*/
class Acceptor
{
private:

    kvs::TCPServer* m_handler; //< handler

public:

    Acceptor( void );

    Acceptor( const int port, const size_t ntrials );

    ~Acceptor( void );

public:

    const bool open( void );

    void close( void );

    const bool bind( const int port, const size_t ntrials );

    kvs::TCPSocket* newConnection( void );

    const int receive( kvs::MessageBlock* block, kvs::SocketAddress* client_address = 0 );

private:

    const bool create_handler( void );

    void delete_handler( void );
};

} // end of namespace kvs

#endif // KVS__ACCEPTOR_H_INCLUDE