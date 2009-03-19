/****************************************************************************/
/**
 *  @file TCPSocket.h
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
#ifndef KVS_CORE_TCP_SOCKET_H_INCLUDE
#define KVS_CORE_TCP_SOCKET_H_INCLUDE

#include "Socket.h"
#include "IPAddress.h"
#include "SocketAddress.h"
#include "SocketTimer.h"
#include "MessageBlock.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  TCP socket class.
 */
/*==========================================================================*/
class TCPSocket : public kvs::Socket
{
protected:

    bool m_is_connected; ///< check flag for connection

public:

    TCPSocket( void );

    TCPSocket( const kvs::IPAddress& ip, const int port, const kvs::SocketTimer* timeout = 0 );

    TCPSocket( const kvs::SocketAddress& socket_address, const kvs::SocketTimer* timeout = 0 );

    TCPSocket( const kvs::Socket::id_type& id, const kvs::SocketAddress& address );

    virtual ~TCPSocket( void );

public:

    bool isConnected( void );

    void open( void );

    bool connect( const kvs::IPAddress& ip, const int port, const kvs::SocketTimer* timeout = 0 );

    bool connect( const kvs::SocketAddress& socket_address, const kvs::SocketTimer* timeout = 0 );

    bool complete( const kvs::SocketTimer* timer = 0 );

    int send( const void* message, const int message_size );

    int send( const kvs::MessageBlock& message );

    int receive( void* message, const int message_size );

    int receive( kvs::MessageBlock* message );

    int receiveOnce( void* message, const int message_size );

    int receiveLine( std::string& line );
};

} // end of namespace kvs

#endif // KVS_CORE_TCP_SOCKET_H_INCLUDE
