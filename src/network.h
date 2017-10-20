/*
 Kobold - Multiplatform Game Utility Library
 Copyright (C) DNTeam <kobold@dnteam.org>
 
 This file is part of Kobold.
 
 Kobold is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Kobold is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with Kobold.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _kobold_network_h
#define _kobold_network_h

#include "platform.h"

//TODO: implement it for windows.
#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_WINDOWS

#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>
#include <string>
#include "list.h"
#include "koboldconfig.h"
using namespace std;

namespace Kobold
{

/*! Common functions used both for client and servers
 * implementations. It's the base network class. */
class NetCommon
{
   public:

      NetCommon();
      ~NetCommon();

      /*! Get a free socket to use
       * \return integer, representing the socket. -1 on error. */
      int getSocket();

      /*! Resolv, the address
       * \param addr string with the addres to resolv (in x.x.x.x or in name) 
       * \param resolvedAddr returned in_addr struct with 
       *        the resolved address.
       * \return true if resolved, false on error. */
      bool resolvAddress(string addr, struct in_addr* resolvedAddr);

      /*! Send data the vector
       * \param sc Used socket
       * \param data pointer to the data 
       * \param dataSize size of the data
       * \return total data sent (< 0 for error). */
      int sendData(int sc, void* data, int dataSize);

      /*! Receive data to the vector
       * \param sc Used socket
       * \param data pointer to the vector that will contain the received data
       * \param dataSize size of the data to receive
       * \return total data received (<0 for error). */
      int receiveData(int sc, void* data, int dataSize);

      /*! Set the NODELAY option to the socket
       * \param cs socket number
       * \return false on error. */
      bool setNodelay( int cs );

      /*! Set the socket to not block on recv
       * \param sock -> socket number 
       * \return false on error. */
      bool setNonBlocking(int sock);
   
      /*! Set the socket as NO signal.
       * \note: only defined for iOS and OSX. */
      bool setNoSignal(int sock);

      /*! Get error message of the last happened error. */
      string getErrorMessage();

   protected:
      /*! Define an error state message. */
      void error(string msg);

   private:
      string errorMessage;

};

/*! The basic TCP client. */
class NetClient : public NetCommon
{
   public:
      NetClient();
      ~NetClient();

      /*! Create base connection with a server.
       * \param port port number to connect to.
       * \param serverAddr server address to connect to.
       * \return true on success. */
      bool createConnection(unsigned short int port, string serverAddr);

      /*! Close the client connection with the server
       * \return true if ok. */
      bool closeConnection();
   
      /*! Check if the client is connectd to a server. 
       * \return true if connected. */
      bool isConnected();

   protected:
      struct sockaddr_in addr_in;  /**< Client addr_in */
      int usedSocket;              /**< Socket Used by Client */
      bool connected;              /**< Connection status. */
};

/*! The TCP Server implementation */
class NetServer : public NetCommon, public List
{
   public:
      /*! Create the server params.
       * \param port port to listen to.
       * \note: the constructor doesn't init the server,
       *        just its params. You must call init for it. */
      NetServer(unsigned short int port);
      /*! Make sure your destructor will call finish(), otherwise,
       * will close all active connections, without sending bye. */
      virtual ~NetServer();

      /*! Init the server 
       * \return true on success */
      bool init();

      /*! Finish the server 
       * \return true on success */
      bool finish();

      /*! Do a server step, listening and receiveing messages.
       * \return false on error. */
      bool doStep();

      /*! Broadcast a message to all connected clients
       * \param msg message to broadcast
       * \param dataSize size the message to send. */
      void broadcast(void* msg, int dataSize);

      /*! Called when received message from a connected client.
       * \param clientSocket socket where received the message */
      virtual void receivedMessage(unsigned short int clientSocket)=0;

      /*! Called when receives a new client connection
       * \param clientSocket socket to communicate with new client. */
      virtual void receivedNewConnection(unsigned short int clientSocket)=0;

   protected:
 
      class ClientSocket: public ListElement
      {
         public:
            int socket;
      };

      /*! Close all clients connections */
      void closeAllClients();

      /*! Get a new connection on the listen socket.
       * \return new scoket for client */
      int getNewConnection();

      /*! Close the connection to a client.
       *\param sockNumber -> socket number of the client. */
      void closeConnection(int sockNumber, bool sendByeMsg=true);

      /*! Send a goodbye message to the client. It's called just before
       * closing the connection with it. */
      virtual void sendByeMessage(unsigned short int clientSocket)=0;

   private:

      /*! Find a client related to a socket. */
      ClientSocket* findClient(int socketNumber);

      bool initiated;              /**< If server is initiated or not */
      struct sockaddr_in addr_in;  /**< Server addr_in */
      int listenerSocket;          /**< Socket Used to Listen */
      unsigned short int usedPort; /**< Port used for comunication */

      fd_set masterSet;            /**< Master fd list for listen */
      fd_set readSet;              /**< Read fd list for select() */
      int fdmax;                   /**< Max file descriptor number */
};

}

#endif

#endif

