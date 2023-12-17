/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include<unistd.h>      //sleep
#include <iostream>     //std::cin.get()

#include "publisher.hpp"
#include "udp_listener.hpp"
#include "subscriber.hpp"

void TestServer();

int main()
{
    TestServer();
}

void TestServer()
{
    ilrd::UDPListener udp("127.0.0.1", 4000);
    ilrd::Publisher *pub = ilrd::GetPublisher();

    std::cout << "Press Enter to messages mess" << std::endl;
    std::cout << "There will be 10 messages" << std::endl;
    std::cout << "5 for squeares" << std::endl;
    std::cout << "5 for circles" << std::endl;
    std::cin.get();

    for(;;)
    {
        sleep(2);
        std::cout << "Sending" <<std::endl;
        pub->Publish("squeares blue 2\n");
        pub->Publish("circles green 1\n");
    }

    std::cin.get();
}