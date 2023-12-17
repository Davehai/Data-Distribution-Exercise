/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <iostream>     //std::cerr  std::endl
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //close

#include "subscriber.old.hpp"

using namespace ilrd;
/*******************************************************************************
 * Error handler function
*******************************************************************************/
void Subscriber::ErrorHandler(std::string error)
{
    std::cerr << error << std::endl;
}

/*******************************************************************************
 * Class public function definition
*******************************************************************************/
Subscriber::Subscriber(std::string ip, int port):   m_udp_sock(inet_addr(ip.c_str()), htons(port)), m_ip(ip), m_port(port),
                                                    m_server_ip(""), m_server_port(0), m_server_shape(""), m_run(true)
{
    m_thread = std::thread(&Subscriber::RunListen, this);
}

Subscriber::~Subscriber()
{
    std::string msg = "exit";
    m_run = false;
    UnSubscribe();
    if(1 == sendto(m_udp_sock.GetSockFD(), reinterpret_cast<const void *>(msg.c_str()), msg.size(), 0,
    reinterpret_cast<const sockaddr*>(&m_udp_sock.GetSockaddr()), sizeof(struct sockaddr_in)))
    {
        ErrorHandler("sendto fail...");
        exit(1);
    }

    m_thread.join();
}

bool Subscriber::Subscribe(std::string ip, int port, std::string shape)
{
    if("" != m_server_ip)
    {
        return false;
    }
    m_server_ip = ip;
    m_server_port = port;
    m_server_shape = shape;
    return MsgServer("subscribe", m_server_ip, m_server_port, m_server_shape);
}

void Subscriber::UnSubscribe()
{
    if("" == m_server_ip)
    {
        return;
    }

    MsgServer("unsubscribe", m_server_ip, m_server_port, m_server_shape);
    m_server_ip = "";
    m_server_port = 0;
    m_server_shape = "";
}

/*******************************************************************************
 * Class private function definition
*******************************************************************************/
void Subscriber::RunListen()
{
    char buff[100] = {0};
    ssize_t size = 0;

    while(m_run)
    {
        size = recv(m_udp_sock.GetSockFD(), buff, 100 - 1, 0);
        if(-1 != size)
        {
            buff[size] = '\0';
            std::cout << buff << std::endl;
        }
        else
        {
            ErrorHandler("recv fail...");
        }
    }
}

bool Subscriber::MsgServer(std::string msg_type, std::string ip, int port, std::string shape)
{
    struct sockaddr_in servaddr = {};

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    servaddr.sin_port = htons(port);

    std::string msg = msg_type + "/" + shape + "/" + m_ip + "/" + std::to_string(m_port);
    if(1 == sendto(m_udp_sock.GetSockFD(), reinterpret_cast<const void *>(msg.c_str()), msg.size(), 0,
    reinterpret_cast<sockaddr*>(&servaddr), sizeof(struct sockaddr_in)))
    {
        ErrorHandler("Message fail");
        return false;
    }

    return true;
}