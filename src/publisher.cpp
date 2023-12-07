/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <netdb.h>      //socket, htons, struct sockaddr_in, bind, listen, accept
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //close
#include <iostream>     //std::cerr
#include <sstream>      //std::stringstream

#include "publisher.hpp"

using namespace ilrd;

/*******************************************************************************
 * Error handler function
*******************************************************************************/
void Publisher::ErrorHandler(std::string error)
{
    std::cerr << error << std::endl;
}

/*******************************************************************************
 * Class public function definition
*******************************************************************************/
Publisher * ilrd::GetPublisher()
{
    static Publisher pub;

    return &pub;
}

void Publisher::Notify(std::string subscriber)
{
    std::stringstream strstream(subscriber);
    std::string request_type;
    std::string shape_type;
    Subscriber sub;

    std::getline(strstream, request_type, '/');
    std::getline(strstream, shape_type, '/');
    std::getline(strstream, sub.ip, '/');
    std::getline(strstream, sub.port, '/');
    sub.port += "\0";

    sub.sockaddr.sin_family = AF_INET;
    sub.sockaddr.sin_addr.s_addr = inet_addr(sub.ip.c_str());

    if((in_addr_t)(-1) != sub.sockaddr.sin_addr.s_addr)
    {
        try
        {
            sub.sockaddr.sin_port = htons(std::stoi(sub.port));

            if("subscribe" == request_type)
            {
                Subscribe(shape_type, sub);
                std::cout << "subscribed" << std::endl;
            }
            else if(("unsubscribe" == request_type))
            {
                UnSubscribe(shape_type, sub);
                std::cout << "unsubscribe" << std::endl;
            }
            else
            {
                ErrorHandler("Invalid request...");
            }
        }
        catch(...)
        {
            ErrorHandler("Invalid port...");
        }
    }
    else
    {
        ErrorHandler("Invalid IP...");
    }
}

void Publisher::Publish(std::string shape)
{
    for(auto runner : m_subscribers["all"])
    {
        if(1 == sendto(m_udp_sock.GetSockFD(), reinterpret_cast<const void *>(shape.c_str()), shape.size(), 0,
        reinterpret_cast<const sockaddr*>(&runner.sockaddr), sizeof(struct sockaddr_in)))
        {
            ErrorHandler("sendto fail...");
        }
    }

    std::stringstream strstream(shape);
    std::string key;
    std::getline(strstream, key, ' ');
    if(m_subscribers.find(key) == m_subscribers.end())
    {
        return;
    }

    for(auto runner : m_subscribers[key])
    {
        if(1 == sendto(m_udp_sock.GetSockFD(), reinterpret_cast<const void *>(shape.c_str()), shape.size(), 0,
        reinterpret_cast<const sockaddr*>(&runner.sockaddr), sizeof(struct sockaddr_in)))
        {
            ErrorHandler("sendto fail...");
        }
    }
}

/*******************************************************************************
 * Class private function definition
*******************************************************************************/
Publisher::Publisher(): m_udp_sock(INADDR_ANY, htons(8080))
{
    //Empty
}

void Publisher::Subscribe(std::string &key, Subscriber &sub)
{
    m_subscribers[key].push_back(sub);
}

void Publisher::UnSubscribe(std::string &key, Subscriber &sub)
{
    if(m_subscribers.find(key) == m_subscribers.end())
    {
        ErrorHandler("Invalid key...");
        return;
    }

    auto iter = m_subscribers.at(key).begin();
    auto end = m_subscribers.at(key).end();

    for(auto runner : m_subscribers.at(key))
    {
        if((runner.ip == sub.ip) && (runner.port == sub.port))
        {
            break;
        }
        ++iter;
    }

    if(iter != end)
    {
        m_subscribers.at(key).erase(iter);
    }
}