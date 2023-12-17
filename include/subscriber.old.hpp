/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <unordered_map>    //std::unordered_map
#include <string>           //std::string
#include <thread>           //std::thread
#include <execution>        //std::runtime_error

#include "udp_raii.hpp"

namespace ilrd
{

class Subscriber
{
public:
    Subscriber(std::string ip, int port);
    ~Subscriber();
    bool Subscribe(std::string ip, int port, std::string shape);
    void UnSubscribe();
private:
    void RunListen();
    void ErrorHandler(std::string error);
    bool MsgServer(std::string msg_type, std::string ip, int port, std::string shape);
    std::thread m_thread;
    UDPSock m_udp_sock;
    std::string m_ip;
    int m_port;
    std::string m_server_ip;
    int m_server_port;
    std::string m_server_shape;
    bool m_run;
};

}

#endif      //SUBSCRIBER