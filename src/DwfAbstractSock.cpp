/*!
 * @file DwfAbstractSock.h
 * @brief Abstract Socket management class for TCP/IP or UDP protocol
 * @author SignC0dingDw@rf
 * @version 1.0
 * @date 08 February 2017
 *
 * Implementation of the abstract class used to manage sockets. It defines the basic interface for communication, the management of WSA DLL initialization and clean up for Windows as well as the typedef required to ensure datatypes consistency between Linux and Windows. <br>
 * Based on examples from : http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedcode1.html <br>
 * Abstract class.
 *
 */

#include "DwfAbstractSock.h"

namespace dwf_comm
{
	int DwfAbstractSock::nb_instances = 0;
	bool DwfAbstractSock::is_init = false;

	DwfAbstractSock::DwfAbstractSock(std::string ip_add, int port_num, mode m) : m_socketReady(false), m_mode(m)
	{
		++nb_instances;
		if(!is_init)
		{
			is_init = init();
		}

		IPSetup(ip_add, port_num);
	}

	DwfAbstractSock::~DwfAbstractSock()
	{
		closeSocket();
		--nb_instances;
		if(nb_instances == 0)
		{
			cleanup();
			is_init = false;
		}
	}

	bool DwfAbstractSock::isInit()
	{
		return is_init;
	}

	bool DwfAbstractSock::isSocketReady()
	{
		return m_socketReady;
	}

	bool DwfAbstractSock::IPSetup(std::string ip_add, int port_num)
	{
		if(!isSocketReady())
		{
#if DEBUG
			std::cout << "\n\n********* IPv4 address and port set up *********" << std::endl;
			std::cout << "Will try to connect to address " << ip_add << " on port " << port_num << std::endl;
#endif
	
			m_addr.sin_family = AF_INET; //IP address family
			m_addr.sin_port = htons(port_num);
			m_addr.sin_addr.s_addr = inet_addr(ip_add.c_str());

			return true;
		}
		else
		{
#if DEBUG
			std::cout << "Socket already running. Please disconnect socket before changing set up" << std::endl;
#endif
			return false;
		}
	}

	bool DwfAbstractSock::setTimeout(const unsigned int timeOut_ms)
	{
#if _WIN32
			if(setsockopt(m_s, SOL_SOCKET, SO_RCVTIMEO, (const char*) &timeOut_ms, sizeof(timeOut_ms)) != 0)// Time out = NO_TIMEOUT means blocking
			{
#if DEBUG
				std::cout << WSAGetLastError() << std::endl;
#endif
				return false;
			}
#elif __linux__
			struct timeval timeout;      
			timeout.tv_sec = timeOut_ms/1000;
			timeout.tv_usec = (timeOut_ms-timeout.tv_sec*1000)*1000;
#if DEBUG
			std::cout << "Timeout : " << timeout.tv_sec << " s " << timeout.tv_usec << " us" << std::endl; 
#endif

			if(setsockopt (m_s, SOL_SOCKET, SO_RCVTIMEO, (const char*) &timeout, sizeof(timeout)) < 0)
			{
#if DEBUG
				int lastError = errno;
				std::cout << "Cannot change timeOut value. Error code: " << lastError << std::endl;
#endif
				return false;
			}
#endif

			return true;
	}


	bool DwfAbstractSock::openSocket()
	{
		if(!initSocket())
		{
			return false;
		}
		if(m_mode == SERVER)
		{
			if(!bindSocket())
			{
				return false;
			}
		}
		return true;
	}

	void DwfAbstractSock::closeSocket()
	{
		if(isSocketReady())
		{
#if DEBUG
			std::cout << "\n\n********* End of the Communication Phase *********" << std::endl;
#endif
		// When you are finished sending and receiving data on the
		// NewConnection socket and are finished accepting new connections
		// on ListeningSocket, you should close the sockets using the closesocket API on Windows or close API on Linux
#ifdef _WIN32
			if(closesocket(m_s) == SOCKET_ERROR)
			{
#if DEBUG
				std::cout << "Cannot close \"Listening\" socket. Error code: " << WSAGetLastError() << std::endl;
#endif
			}
			else
			{
#if DEBUG
				std::cout << "Closing \"Listening\" socket..." << std::endl;
#endif
			}
#elif __linux__
			if(close(m_s) == SOCKET_ERROR)
			{
#if DEBUG
				int lastError = errno;
				std::cout << "Cannot close \"Listening\" socket. Error code: " << lastError << std::endl;
#endif
			}
			else
			{
#if DEBUG
				std::cout << "Closing \"Listening\" socket..." << std::endl;
#endif
			}
#endif	
			m_socketReady = false;
		}	
	}

	bool DwfAbstractSock::initSocket()
	{
		SOCKET temp;
#if DEBUG
		std::cout << "\n\n********* IP socket set up *********" << std::endl;
#endif
		temp = setUpSocket();

	     // Check for errors to ensure that the socket is a valid socket.
	     	if (temp == INVALID_SOCKET)
		{
#if DEBUG
#if __linux__
			int lastError = errno; //errno contains the last error code (safer to store it before rendering see errno(3) in linux documentation)
#endif

			std::cout << "Error at socket(), error code: ";
#ifdef _WIN32
			std::cout << WSAGetLastError() << std::endl;
#elif __linux__
			std::cout << lastError << std::endl; 
#endif
#endif
			m_socketReady = false;
		 	return false;
	     	}
	     	else
		{
#if DEBUG
			std::cout << "socket() is OK!" << std::endl;
#endif
			m_s = temp;
			m_socketReady = true;
			return true;
		}
	}

	bool DwfAbstractSock::bindSocket()
	{
#if DEBUG
		std::cout << "\n\n********* Socket configuration in server mode *********" << std::endl;
#endif
		// Associate the address information with the socket using bind.
	    	// Call the bind function, passing the created socket and the sockaddr_in
	    	// structure as parameters. Check for general errors.
		if (bind(m_s, (SOCKADDR *)&m_addr, sizeof(m_addr)) == SOCKET_ERROR)
		{
#if DEBUG
#if __linux__
			int lastError = errno; //errno contains the last error code (safer to store it before rendering see errno(3) in linux documentation)
#endif

			std::cout << "Server: bind() failed! Error code: ";
#ifdef _WIN32
			std::cout << WSAGetLastError() << std::endl;
#elif __linux__
			std::cout << lastError << std::endl; 
#endif
#endif
			// Close the socket
			closeSocket();
			return false;
		}
		else
		{
#if DEBUG
			std::cout << "Server: bind() is OK!" << std::endl;
#endif
			m_socketReady = true;
			return true;
		}
	}

	bool DwfAbstractSock::init()
	{
#ifdef _WIN32 //Initialization of Winsock and get its status
		WSADATA wsaData;
		int RetCode;

#if DEBUG
		std::cout << "\n\n********* Initialization of Winsock 2.2 *********" << std::endl;
#endif

		// Initialize Winsock version 2.2
		if ((RetCode = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
		{
#if DEBUG
			std::cout << "WSAStartup failed with error " << RetCode << std::endl;
#endif
			return false;
		}
		else
		{
			std::cout << "The Winsock dll found!" << std::endl;
			std::cout << "The current status is: " << wsaData.szSystemStatus << "." << std::endl;

			if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 )
			{
#if DEBUG
				//Tell the user that we could not find a usable WinSock DLL
				std::cout << "The dll do not support the Winsock version " << (int) LOBYTE(wsaData.wVersion) << "." << (int) HIBYTE(wsaData.wVersion) << "!" << std::endl;
#endif
				return false;
			}
			else
			{
#if DEBUG
				std::cout << "The dll supports the Winsock version " << (int) LOBYTE(wsaData.wVersion) << "." << (int) HIBYTE(wsaData.wVersion) << "!" << std::endl;
				std::cout << "The highest version this dll can support: " << (int) LOBYTE(wsaData.wHighVersion) << "." << (int) HIBYTE(wsaData.wHighVersion) << std::endl;
#endif
				return true;
			}
		}
#elif __linux__
		return true; // Nothing to do on initialization on linux for the moment
#endif
	}

	bool DwfAbstractSock::cleanup()
	{
#ifdef _WIN32 // Properly clean up WinSocket application
		std::cout << "\n\n********* Winsocket Cleanup phase *********" << std::endl;
		if (WSACleanup() == SOCKET_ERROR)
		{
#if DEBUG
			std::cout << "WSACleanup failed with error " << WSAGetLastError() << std::endl;
#endif
			return false;
		}
		else
		{
#if DEBUG
			std::cout << "WSA successfully cleaned up" << std::endl;
#endif
			return true;
		}
#elif __linux__
		return true; // Nothing to do for cleanup on linux for the moment
#endif
	}
}
