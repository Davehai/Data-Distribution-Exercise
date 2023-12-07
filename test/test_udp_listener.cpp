/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <iostream>     //std::cin.get()

#include "udp_listener.hpp"

void TestUDPListener();

int main()
{
    TestUDPListener();
}

void TestUDPListener()
{
    ilrd::UDPListener udp("127.0.0.1", 4000);
    std::cin.get();
}