/*!
 * @file DwfUDPSock.h
 * @brief Socket management class for UDP protocol
 * @author SignC0dingDw@rf
 * @version 1.0
 * @date 08 February 2017
 *
 * Definition of the class used to manage UDP sockets. <br>
 * Inherits from DwfAbstractSock class.
 *
 */

#ifndef DWF_UDP_SOCK
#define DWF_UDP_SOCK

#include "DwfAbstractSock.h"

/*! 
* @namespace dwf_comm
* @brief A namespace used to regroup all communication related functions and classes
*/
namespace dwf_comm
{
	class DwfUDPSock : public DwfAbstractSock
	{
	public:
		DwfUDPSock(std::string ip_add, int port_num, mode m);
		DwfUDPSock(int port_num);

		virtual ~DwfUDPSock();

		virtual bool IPSetup(std::string ip_add, int port_num);

		template<typename T>
		int send(const T& data);

		int send(const std::string& data);

		template<typename T>
		int recv(T& data);

		int recv(std::string& data);
	protected:
		SOCKADDR m_clientAddr;
		virtual SOCKET setUpSocket();
	};

	template<typename T>
	int DwfUDPSock::send(const T& data)
	{
		int data_size = -1;
#ifdef _WIN32
		if(m_mode == CLIENT)
		{
			data_size = sendto(m_s, (const char*)&data, sizeof(data), 0, (SOCKADDR *) &m_addr, sizeof(m_addr));
		}
		else
		{
			data_size = sendto(m_s, (const char*)&data, sizeof(data), 0, &m_clientAddr, sizeof(m_clientAddr));
		}
#elif __linux__
		if(m_mode == CLIENT)
		{
			data_size = sendto(m_s, &data, sizeof(data), 0, (SOCKADDR *) &m_addr, sizeof(m_addr)); // data pointer is void* so conversion is always implicit
		}
		else
		{
			data_size = sendto(m_s, &data, sizeof(data), 0, &m_clientAddr, sizeof(m_clientAddr)); // data pointer is void* so conversion is always implicit
		}
#endif

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

	template<typename T>
	int DwfUDPSock::recv(T& data)
	{
		int data_size = -1;
#ifdef _WIN32
		if(m_mode == CLIENT)
		{
			socklen_t addr_len = sizeof(m_addr);
			data_size = recvfrom(m_s, (char*)&data, sizeof(data), 0, (SOCKADDR *) &m_addr, &addr_len); 
		}
		else
		{
			socklen_t addr_len =  sizeof(m_clientAddr);
			data_size = recvfrom(m_s, (char *)&data, sizeof(data), 0, &m_clientAddr, &addr_len);
		}
#elif __linux__
		if(m_mode == CLIENT)
		{
			socklen_t addr_len = sizeof(m_addr);
			data_size = recvfrom(m_s, &data, sizeof(data), 0, (SOCKADDR *) &m_addr, &addr_len); // data pointer is void* so conversion is always implicit
		}
		else
		{
			socklen_t addr_len =  sizeof(m_clientAddr);
			data_size = recvfrom(m_s, &data, sizeof(data), 0, &m_clientAddr, &addr_len); // data pointer is void* so conversion is always implicit
		}
#endif

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
}
#endif
