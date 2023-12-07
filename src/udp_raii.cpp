/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <unistd.h>     //close

#include "udp_raii.hpp"

using namespace ilrd;

UDPSock::UDPSock(in_addr_t addr, in_port_t port)
{
    m_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == m_sock_fd)
    {
        throw std::runtime_error("Socket creation failed...");
    }
    m_sockaddr.sin_family = AF_INET;
    m_sockaddr.sin_addr.s_addr = addr;
    m_sockaddr.sin_port = port;

    if (0 != (bind(m_sock_fd, (struct sockaddr *)&m_sockaddr, sizeof(m_sockaddr))))
    {
        close(m_sock_fd);
        throw std::runtime_error("Socket bind failed in server...");
    }
}

UDPSock::~UDPSock()
{
    close(m_sock_fd);
}

const struct sockaddr_in& UDPSock::GetSockaddr()
{
    return m_sockaddr;
}

const int& UDPSock::GetSockFD()
{
    return m_sock_fd;
}