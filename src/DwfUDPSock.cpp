/*!
 * @file DwfUDPSock.cpp
 * @brief Socket management class for UDP protocol
 * @author SignC0dingDw@rf
 * @version 1.0
 * @date 08 February 2017
 *
 * Implementation of the class used to manage UDP sockets. <br>
 * Inherits from DwfAbstractSock class.
 *
 */

#include "DwfUDPSock.h"

namespace dwf_comm
{
	DwfUDPSock::DwfUDPSock(std::string ip_add, int port_num, mode m) : DwfAbstractSock(ip_add, port_num, m)
	{
		openSocket();
	}

	DwfUDPSock::DwfUDPSock(int port_num) : DwfAbstractSock("", port_num, SERVER)
	{
		openSocket();
	}

	DwfUDPSock::~DwfUDPSock()
	{
	}

	bool DwfUDPSock::IPSetup(std::string ip_add, int port_num)
	{
		if(!isSocketReady())
		{
#if DEBUG
			std::cout << "\n\n********* IPv4 address and port set up *********" << std::endl;
			std::cout << "Will try to connect to address " << ip_add << " on port " << port_num << std::endl;
#endif
	
			m_addr.sin_family = AF_INET; //IP address family
			m_addr.sin_port = htons(port_num);
			if(m_mode == CLIENT) // Added for the management of SERVER address is any incoming connexion
			{
				m_addr.sin_addr.s_addr = inet_addr(ip_add.c_str());
			}
			else
			{
				m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			}

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

	int DwfUDPSock::send(const std::string& data)
	{
		int data_size = -1;
		if(m_mode == CLIENT)
		{
			data_size = sendto(m_s, data.c_str(), data.length()*sizeof(char), 0, (SOCKADDR *) &m_addr, sizeof(m_addr));
		}
		else
		{
			data_size = sendto(m_s, data.c_str(), data.length()*sizeof(char), 0, &m_clientAddr, sizeof(m_clientAddr));
		}

#if DEBUG
		if(data_size < 0)
		{
#if __linux__
			int lastError = errno; //errno contains the last error code (safer to store it before rendering see errno(3) in linux documentation)
#endif

			std::cout << "No data could be received! Error code: ";
#ifdef _WIN32
			std::cout << WSAGetLastError() << std::endl;
#elif __linux__
			std::cout << lastError << std::endl; 
#endif
		}
#endif

		return data_size;
	}

	int DwfUDPSock::recv(std::string& data)
	{
		int data_size = -1;
		char buf[MAX_MSG_LENGTH];
		if(m_mode == CLIENT)
		{
			socklen_t addr_len = sizeof(m_addr);
			data_size = recvfrom(m_s, buf, MAX_MSG_LENGTH, 0, (SOCKADDR *) &m_addr, &addr_len);
		}
		else
		{
			socklen_t addr_len =  sizeof(m_clientAddr);
			data_size = recvfrom(m_s, buf, MAX_MSG_LENGTH, 0, &m_clientAddr, &addr_len);
		}

		if(data_size < 0)
		{
#if DEBUG
#if __linux__
			int lastError = errno; //errno contains the last error code (safer to store it before rendering see errno(3) in linux documentation)
#endif

			std::cout << "No data could be received! Error code: ";
#ifdef _WIN32
			std::cout << WSAGetLastError() << std::endl;
#elif __linux__
			std::cout << lastError << std::endl; 
#endif
#endif
			data = "";
		}
		else
		{
			data = std::string(buf,data_size);
		}

		return data_size;
	}

	SOCKET DwfUDPSock::setUpSocket()
	{
		return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  
	}
}
