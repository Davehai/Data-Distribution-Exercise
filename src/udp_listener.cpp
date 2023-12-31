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
#include <unistd.h>     //close

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

    shutdown(m_udp_sock.GetSockFD(), SHUT_RDWR);
    close(m_udp_sock.GetSockFD());

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
    struct sockaddr_in clinetaddr;
    int len = sizeof(struct sockaddr);
    char *ip_buff = nullptr;
    int port = 0;
    
    while (m_run)
    {
        size = recvfrom(m_udp_sock.GetSockFD(), buff, 100 - 1, 0,
        (struct sockaddr *) &clinetaddr, (socklen_t *)&len);
        if(0 < size)
        {
            buff[size] = '\0'; 
            ip_buff = inet_ntoa(clinetaddr.sin_addr);
            port = ntohs(clinetaddr.sin_port);

            std::string ip_string = ip_buff;
            std::string to_send = buff;

            to_send += '/' + ip_string + '/' + std::to_string(port);

            if(strcmp(buff, "exit"))
            {
                p_pub->Notify(to_send);
            }
        }
        else
        {
            if(m_run)
            {
                ErrorHandler("recv fail...");
            }
        }
    }
}