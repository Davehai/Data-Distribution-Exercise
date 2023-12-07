/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <iostream>     //std::cerr std::endl
#include <string.h>     //strcmp
#include <arpa/inet.h>  //inet_addr

#include "udp_listener.hpp"
#include "publisher.hpp"

using namespace ilrd;

/*******************************************************************************
 * Error handler function
*******************************************************************************/
void UDPListener::ErrorHandler(std::string error)
{
    std::cerr << error << std::endl;
}

/*******************************************************************************
 * Class public function definition
*******************************************************************************/
UDPListener::UDPListener(std::string ip, int port): m_udp_sock(inet_addr(ip.c_str()), htons(port))
{
    m_thread = std::thread(&UDPListener::RunUDPListener, this);
}

UDPListener::~UDPListener()
{
    std::string msg = "exit";
    m_run = false;
    if(1 == sendto(m_udp_sock.GetSockFD(), reinterpret_cast<const void *>(msg.c_str()), msg.size(), 0,
    reinterpret_cast<const sockaddr*>(&m_udp_sock.GetSockaddr()), sizeof(struct sockaddr_in)))
    {
        ErrorHandler("sendto fail...");
        exit(1);
    }

    m_thread.join();
}

/*******************************************************************************
 * Class private function definition
*******************************************************************************/
void UDPListener::RunUDPListener()
{
    Publisher *p_pub = GetPublisher();
    char buff[100] = {0};
    ssize_t size = 0;
    
    while (m_run)
    {
        size = recv(m_udp_sock.GetSockFD(), buff, 100 - 1, 0);
        if(0 < size)
        {
            buff[size] = '\0';

            if(strcmp(buff, "exit"))
            {
                p_pub->Notify(buff);
            }
        }
        else
        {
            ErrorHandler("recv fail...");
        }
    }
}