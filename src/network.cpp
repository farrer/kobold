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


#include "network.h"

#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_WINDOWS

#include <stdio.h>
#include <errno.h>

using namespace Kobold;
using namespace std;

#define COMMON_BACKLOG          15   /**< Simultaneous log of connections */

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                              NetCommon                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/****************************************************************
 *                          Constructor                         *
 ****************************************************************/
NetCommon::NetCommon()
{
   errorMessage = "";
}

/****************************************************************
 *                           Destructor                         *
 ****************************************************************/
NetCommon::~NetCommon()
{
}

/****************************************************************
 *                             error                            *
 ****************************************************************/
void NetCommon::error(string msg)
{
   errorMessage = msg;
}

/****************************************************************
 *                             error                            *
 ****************************************************************/
string NetCommon::getErrorMessage()
{
   return errorMessage;
}

/****************************************************************
 *                           getSocket                          *
 ****************************************************************/
int NetCommon::getSocket()
{
   /* Request Socket */
   int sc = socket( AF_INET, SOCK_STREAM, 0 );
   if(sc == -1)
   {
      error("Couldn't get Socket descriptor!");
      return -1;
   }
   return(sc);
}

/****************************************************************
 *                         resolvAddress                        *
 ****************************************************************/
bool NetCommon::resolvAddress(string addr, struct in_addr* resolvedAddr)
{
   char tadr[200];
   sprintf(tadr, "%s", addr.c_str());
   /* Try to convert to the struct direct*/
   if( inet_aton(tadr, resolvedAddr) == 0)
   {
      /* If can't, will resolv the Name */
      //printf("Resolving the name: %s\n", addr.c_str());
      struct hostent* host;
      if ( (host = gethostbyname(tadr) ) == NULL )
      {
         error("Couldn't resolv host name!");
         return false;
      }
      //printf("Resolved to: %s\n",
      //       inet_ntoa(*((struct in_addr *)host->h_addr)));
      *resolvedAddr = *((struct in_addr *)host->h_addr);
      return true;
   }
   error("Couldn't inet_aton!");
   return false;
}

/****************************************************************
 *                           sendData                           *
 ****************************************************************/
int NetCommon::sendData(int sc, void* data, int dataSize)
{
   int sent = 0;
   ssize_t n;
   char* caux = (char*) data;

   /* Only stop sending, when all data weas sent */
   while( sent < dataSize )
   {
#if KOBOLD_PLATFORM != KOBOLD_PLATFORM_IOS &&\
    KOBOLD_PLATFORM != KOBOLD_PLATFORM_MACOS
      n = send(sc, &caux[sent], dataSize-sent, MSG_NOSIGNAL);
#else
      n = send(sc, &caux[sent], dataSize-sent, 0);
#endif
      if( n < 0 )
      {
         if((errno != EAGAIN) && (errno != EWOULDBLOCK))
         {
            error("Couldn't send data!");
            return (int) n;
         }
         /* EAGAIN: try to send again. */
         n = 0; 
      }
      else if(n == 0)
      {
         /* Probably disconnected. */
         return (int) n;
      }
      sent += n;
   }
   return sent;
}

/****************************************************************
 *                          receiveData                         *
 ****************************************************************/
int NetCommon::receiveData(int sc, void* data, int dataSize)
{
   char* caux = (char*) data;
   int received = 0;
   ssize_t n;
   while( received < dataSize )
   {
      n = recv(sc, caux+received, dataSize-received, 0);
      if(n < 0)
      {
         if((errno != EAGAIN) && (errno != EWOULDBLOCK))
         {
            return -1;
         }
         n = 0;
      }
      else if(n == 0)
      {
         /* Must close the socket! */
         return 0;
      }
      received += n;
   }
   return(received);
}

/****************************************************************
 *                          setNodelay                          *
 ****************************************************************/
bool NetCommon::setNodelay( int cs )
{
    int yes = 1;
    if (setsockopt(cs,IPPROTO_TCP,TCP_NODELAY,&yes,sizeof(yes))<0) 
    {
        error("setsockopt(NODELAY)");
        return false;
    }
    return true;
}

/****************************************************************
 *                          setNoSignal                         *
 ****************************************************************/
bool NetCommon::setNoSignal(int sock)
{
#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS
   int opts;
   
   opts = fcntl(sock,F_GETFL);
   if (opts < 0) {
      error("fcntl(F_GETFL)");
      return false;
   }
   opts = (opts | SO_NOSIGPIPE);
   if (fcntl(sock,F_SETFL,opts) < 0) {
      error("fcntl(F_SETFL)");
      return false;
   }
#endif
   return true;
}

/****************************************************************
 *                         setNonBlocking                       *
 ****************************************************************/
bool NetCommon::setNonBlocking(int sock)
{
	int opts;

	opts = fcntl(sock,F_GETFL);
	if (opts < 0) {
		error("fcntl(F_GETFL)");
		return false;
	}
	opts = (opts | O_NONBLOCK);
	if (fcntl(sock,F_SETFL,opts) < 0) {
		error("fcntl(F_SETFL)");
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                              NetClient                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/****************************************************************
 *                          Constructor                         *
 ****************************************************************/
NetClient::NetClient() : NetCommon()
{
   usedSocket = -1;
   connected = false;
}

/****************************************************************
 *                           Destructor                         *
 ****************************************************************/
NetClient::~NetClient()
{
   /* Close any existent connection. */
   if(connected)
   {
      closeConnection();
   }
}

/****************************************************************
 *                          isConnected                         *
 ****************************************************************/
bool NetClient::isConnected()
{
   return connected;
}

/****************************************************************
 *                        closeConnection                       *
 ****************************************************************/
bool NetClient::closeConnection()
{
   if(connected)
   {
      if(close(usedSocket) == -1 )
      {
         error("Couldn't close socket!");
         return false;
      }
      connected = false;
      usedSocket = -1;
      return true;
   }

   return false;
}

/****************************************************************
 *                       createConnection                       *
 ****************************************************************/
bool NetClient::createConnection(unsigned short int port, string serverAddr)
{
   if(connected)
   {
      /* Already connected, must close it. */
      if(!closeConnection())
      {
         /*! Couldn't close connection! */
         return false;
      }
   }

   /* Init Net Structs */
   usedSocket = getSocket();
   addr_in.sin_family = AF_INET;
   addr_in.sin_port = htons(port);
   resolvAddress(serverAddr, (struct in_addr*)&addr_in.sin_addr);
   
   if(!setNonBlocking(usedSocket))
   {
      return false;
   }


   /* Try to Connect */
   //printf("Connecting to server %s ( port %d, through socket %d ) ",
   //      inet_ntoa((struct in_addr)addr_in.sin_addr), port,
   //      usedSocket);
   int ret = connect(usedSocket,(struct sockaddr*)&addr_in,sizeof(addr_in));
   if(ret == -1)
   {
      if (errno != EINPROGRESS)
      {
         printf(": Error.\n");
         error("Couldn't connect to server!");
         return false;
      }
      /* EINPROGRESS: we shall wait for the connection. */
      int error = 0, ret = 0;
      fd_set  rset, wset;
      socklen_t   len = sizeof(error);
      struct timeval  ts;
      
      ts.tv_sec = 2; /* 2 seconds timeout */
      ts.tv_usec = 0;
      
      /* define the set for select */
      FD_ZERO(&rset);
      FD_SET(usedSocket, &rset);
      wset = rset;
      /* wait to be ready or timedout. */
      if( (ret = select(usedSocket + 1, &rset, &wset, NULL, &ts)) < 0)
      {
         return false;
      }
      if(ret == 0)
      {
         errno = ETIMEDOUT;
         return false;
      }
      
      /* ret > 0, so connected! */
      if (FD_ISSET(usedSocket, &rset) || FD_ISSET(usedSocket, &wset))
      {
         /* try to get options, to make sure everything is ok. */
         if(getsockopt(usedSocket, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
         {
            return false;
         }
      }
      else
      {
         /* usedSocket not in the set, not connected! */
         return false;
      }
      
      /* Check if we had a socket error */
      if(error)
      {
         errno = error;
         return false;
      }
      
      /* If we are here, connected! */
      connected = true;
   } else if(ret == 0)
   {
      connected = true;
   }
   
   if(connected)
   {
      //printf(": Connected\n");
      if(!setNodelay(usedSocket))
      {
         return false;
      }
   
#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS
      if(!setNoSignal(usedSocket))
      {
         return false;
      }
#endif
   }

   return connected;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                              NetServer                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/****************************************************************
 *                          Constructor                         *
 ****************************************************************/
NetServer::NetServer(unsigned short int port) : NetCommon()
{
   /* Init values */
   listenerSocket = -1;
   initiated = false;
   usedPort = port;

   /* Clear structs */
   FD_ZERO(&masterSet);
   FD_ZERO(&readSet);

}

/****************************************************************
 *                           Destructor                         *
 ****************************************************************/
NetServer::~NetServer()
{
   /* Close any existent connection. */
   if(initiated)
   {
      finish();
   }
}

/****************************************************************
 *                              init                            *
 ****************************************************************/
bool NetServer::init()
{
   listenerSocket = getSocket();
   addr_in.sin_family = AF_INET;
   addr_in.sin_port = htons(usedPort);
   addr_in.sin_addr.s_addr = INADDR_ANY;
   if( bind(listenerSocket,(struct sockaddr*)&addr_in,sizeof(addr_in)) == -1)
   {
      error("Couldn't Bind!");
      return false;
   }
   if ( listen(listenerSocket, COMMON_BACKLOG) == -1 )
   {
      error("Coldn't Listen!");
      return false;
   }
   
#if KOBOLD_PLATFORM == KOBOLD_PLATFORM_IOS
   if(!setNoSignal(listenerSocket))
   {
      return false;
   }
#endif

   /* Add Listener */
   FD_SET(listenerSocket, &masterSet);
   fdmax = listenerSocket;

   //printf("Server listenning for connections on port: %d\n\n", usedPort);
   initiated = true;

   return true;
}

/****************************************************************
 *                            finish                            *
 ****************************************************************/
bool NetServer::finish()
{
   /* Remove clients */
   closeAllClients();

   /* Stop listening */
   //printf("Close Listenning");
   if( close(listenerSocket ) == -1 )
   {
      error("Couldn't close listener socket!\n");
      return false;
   }
   //printf( ": Done\n" );
   initiated = false;
   return true;
}

/****************************************************************
 *                         freeElement                          *
 ****************************************************************/
void NetServer::closeAllClients()
{
   while(getTotal() > 0)
   {
      ClientSocket* cs = (ClientSocket*)getFirst();
      closeConnection(cs->socket, false);
   }
}

/****************************************************************
 *                       closeConnection                        *
 ****************************************************************/
void NetServer::closeConnection(int sockNumber, bool sendByeMsg)
{
   /* Remove from the client list (if is one) */
   ClientSocket* cs = findClient(sockNumber);
   if(cs != NULL)
   {
      if(sendByeMsg)
      {
         /* Send a goodbye message to the client. */
         sendByeMessage(sockNumber);
      }
      /* Remove client from list */
      remove(cs);
   }

   /* Close the socket and remove from the set. */
   close(sockNumber);
   FD_CLR(sockNumber, &masterSet);
}

/****************************************************************
 *                         findClient                           *
 ****************************************************************/
NetServer::ClientSocket* NetServer::findClient(int socketNumber)
{
   int i;
   ClientSocket* cs = (ClientSocket*)getFirst();
   for(i=0; i < getTotal(); i++)
   {
      if(cs->socket == socketNumber)
      {
         return cs;
      }
   }

   return NULL;
}

/****************************************************************
 *                         broadcast                            *
 ****************************************************************/
void NetServer::broadcast(void* msg, int dataSize)
{
   int i;
   ClientSocket* cs = (ClientSocket*)getFirst();
   for(i=0; i < getTotal(); i++)
   {
      sendData(cs->socket, msg, dataSize);
   }

}


/****************************************************************
 *                      getNewConnection                        *
 ****************************************************************/
int NetServer::getNewConnection()
{
   socklen_t addrLen;
   struct sockaddr_in remoteAddr; /* Client addres */
   int newSock;

   addrLen = sizeof(remoteAddr);
   if( (newSock = accept(listenerSocket, (struct sockaddr*)&remoteAddr,
                         &addrLen)) == -1)
   {
      error("Couldn't accept!\n");
      return -1;
   }
   else
   {
      /* Add to the master set */
      FD_SET(newSock, &masterSet);
      if(newSock > fdmax)
      {
         fdmax = newSock;
      }

      /* Add to the clients list */
      ClientSocket* cs = new ClientSocket();
      cs->socket = newSock;
      insert(cs);
      return newSock;
   }
}

/****************************************************************
 *                           doStep                             *
 ****************************************************************/
bool NetServer::doStep()
{
   int i;
   readSet = masterSet;
   struct timeval timeout;
   timeout.tv_sec = 0;
   timeout.tv_usec = 1000;
   if(select(fdmax+1, &readSet, NULL, NULL, &timeout) == -1)
   {
      error("Error on select!");
      return false;
   }
   for(i = 0; i <= fdmax; i++)
   {
      /* Verify Event on socket */
      if (FD_ISSET(i, &readSet))
      {
         /* New Connection */
         if (i == listenerSocket)
         {
            int sock = getNewConnection();
            if(sock > 0)
            {
               receivedNewConnection(sock);
            }
         }
         /* Know Connection */
         else
         {
            receivedMessage(i);
         }
      }
   }
   return true;
}

#endif

