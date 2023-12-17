/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#ifndef PUBLISHER
#define PUBLISHER

#include <unordered_map>    //std::unordered_map
#include <list>             //std::list
#include <string>           //std::string
#include <thread>           //std::thread
#include <execution>        //std::runtime_error

#include "udp_raii.hpp"

namespace ilrd
{
class Publisher
{
public:
struct Subscriber
{
    std::string ip;
    std::string port;
    struct sockaddr_in sockaddr;
};
    friend Publisher *GetPublisher();
    //~Publisher(); = default
    void Notify(std::string subscriber);    //chose "all" to get notify on all shapes
    void Publish(std::string key, std::string shape);
    void AddNewKey(std::string key);
private:
    Publisher();
    void Subscribe(std::string &key, Subscriber &sub);
    void UnSubscribe(std::string &key, Subscriber &sub);
    void ErrorHandler(std::string error);
    std::unordered_map<std::string, std::list<Subscriber>> m_subscribers;
    UDPSock m_udp_sock;
};

Publisher *GetPublisher();

}

#endif      //PUBLISHER