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

#include "subscriber.hpp"
#include "shape.hpp"

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
Subscriber::Subscriber(): m_sock_fd(0), m_server_ip(""), m_server_port(0), m_server_shape(""), m_run(true)
{
    m_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == m_sock_fd)
    {
        throw std::runtime_error("Socket creation failed...");
    }

    m_thread = std::thread(&Subscriber::RunListen, this);
}

Subscriber::~Subscriber()
{
    m_run = false;
    UnSubscribe();
    shutdown(m_sock_fd, SHUT_RDWR);
    close(m_sock_fd);

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
    Shape *shape = nullptr;

    while(m_run)
    {
        size = recv(m_sock_fd, buff, 100 - 1, 0);
        if(-1 != size)
        {
            buff[size] = '\0';
            shape = StringToShape(buff);
            if(nullptr != shape)
            {
                shape->Print();
                delete shape;
            }
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

    std::string msg = msg_type + "/" + shape;
    if(1 == sendto(m_sock_fd, reinterpret_cast<const void *>(msg.c_str()), msg.size(), 0,
    reinterpret_cast<sockaddr*>(&servaddr), sizeof(struct sockaddr_in)))
    {
        ErrorHandler("Message fail");
        return false;
    }

    return true;
}