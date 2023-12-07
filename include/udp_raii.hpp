/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#ifndef UDP_RAII
#define UDP_RAII

#include <netdb.h>      //socket, htons, struct sockaddr_in, bind, listen, accept
#include <stdexcept>    //std::runtime_error

namespace ilrd
{
class UDPSock
{
public:
    UDPSock(in_addr_t addr = INADDR_ANY, in_port_t port = 4000);
    ~UDPSock();
    const struct sockaddr_in& GetSockaddr();
    const int& GetSockFD();
private:
    struct sockaddr_in m_sockaddr;
    int m_sock_fd;
};

}

#endif      //UDP_RAII