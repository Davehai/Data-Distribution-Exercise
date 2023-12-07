/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#ifndef UDP_LISTENER
#define UDP_LISTENER

#include <thread>       //thread

#include "udp_raii.hpp"

namespace ilrd
{
class UDPListener
{
public:
    UDPListener(std::string ip, int port);
    ~UDPListener();
private:
    void RunUDPListener();
    void ErrorHandler(std::string error);
    std::thread m_thread;
    UDPSock m_udp_sock;
    bool m_run;
};
}

#endif      //UDP_LISTENER