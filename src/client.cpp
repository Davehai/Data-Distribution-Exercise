/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <iostream>     //std::cin.get()
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //close
#include <string.h>

#include "subscriber.hpp"

void TestSubscriber();

int main()
{
    TestSubscriber();
}

void TestSubscriber()
{
    ilrd::Subscriber sub;
    int input = 0;

    std::cout << "What will you like to subscribe to:" << std::endl;
    std::cout << "[1] = all" << std::endl;
    std::cout << "[2] = squeare" << std::endl;
    std::cout << "[3] = circle" << std::endl;
    std::cin >> input;
    std::cin.get();

    switch (input)
    {
    case 1:
        sub.Subscribe("127.0.0.1", 4000, "all");
        break;
    case 2:
        sub.Subscribe("127.0.0.1", 4000, "square");
        break;
    case 3:
        sub.Subscribe("127.0.0.1", 4000, "circle");
        break;
    
    default:
        break;
    }

    std::cout << "Press Enter to unsub" << std::endl;
    std::cin.get();

    sub.UnSubscribe();

    std::cout << "Press Enter to end" << std::endl;
    std::cin.get();
}