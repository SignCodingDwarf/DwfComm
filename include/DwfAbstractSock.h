/*!
 * @file DwfAbstractSock.h
 * @brief Abstract Socket management class for TCP/IP or UDP protocol
 * @author SignC0dingDw@rf
 * @version 1.1
 * @date 24 April 2017
 *
 * Definition of the abstract class used to manage sockets. It defines the basic interface for communication, the management of WSA DLL initialization and clean up for Windows as well as the typedef required to ensure datatypes consistency between Linux and Windows. <br>
 * Based on examples from : http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedcode1.html <br>
 * Abstract class.
 *
 */

#ifndef DWF_ABSTRACT_SOCK
#define DWF_ABSTRACT_SOCK

#ifdef _WIN32

#include <winsock2.h> // winsock contains everything we need on Windows

#elif __linux__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <unistd.h>
#include <errno.h>

#endif

#include <iostream>
#include <string>
#include "common_defines.h"

#define BACKLOG_SIZE_DEFAULT 5 // Default backlog value on Windows desktops for TCP/IP communication
#define MAX_MSG_LENGTH 1542
#define NO_TIMEOUT 0 // No time out

#ifdef __linux__
	typedef struct sockaddr_in SOCKADDR_IN; // To remain compatible with WIN32 name of the struct
	typedef struct sockaddr SOCKADDR; // To remain compatible with WIN32 name of the struct
	typedef struct in_addr IN_ADDR; // To remain compatible with WIN32 name of the struct
	typedef int SOCKET; //SOCKET type is not defined in Linux but we can use an int instead
	#define INVALID_SOCKET -1 //Definition of an invalid socket for compatibility
	#define SOCKET_ERROR -1 // socket functions on Linux return -1 on error so we define SOCKET_ERROR as -1 for compatibility with Windows apps
#endif

/*! 
* @namespace dwf_comm
* @brief A namespace used to regroup all communication related functions and classes
*/
namespace dwf_comm
{
	enum mode
	{
		SERVER,
		CLIENT
	};

	class DwfAbstractSock
	{
	public:
		DwfAbstractSock(std::string ip_add, int port_num, mode m);

		virtual ~DwfAbstractSock();

		bool isInit();

		bool isSocketReady();

		virtual bool IPSetup(std::string ip_add, int port_num);

		virtual bool setTimeout(const unsigned int timeOut_ms = NO_TIMEOUT);

		virtual bool openSocket();

		virtual void closeSocket();

	protected:
		SOCKADDR_IN m_addr; // Adresse de la socket du serveur (soit pour création côté serveur, soit pour contact côté client)
		SOCKET m_s;
		bool m_socketReady;
		mode m_mode;

		virtual bool initSocket();
		
		virtual bool bindSocket();

		virtual SOCKET setUpSocket() = 0;

	private:
		static int nb_instances;
		static bool is_init;
				
		/************************* Common ************************************/
		bool init(); //Init and check up for Winsocketv2.2 (nothing to do on linux)
		bool cleanup(); //Clean up WS config at the end of the program (nothing to do on linux)
	};
}

#endif
