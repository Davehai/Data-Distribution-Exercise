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
    ilrd::Subscriber sub_1("127.0.0.1", 9999);
    ilrd::Subscriber sub_2("127.0.0.1", 9000);
    ilrd::Subscriber sub_3("127.0.0.1", 7000);

    std::cout << "Press Enter to sub" << std::endl;
    std::cin.get();

    sub_1.Subscribe("127.0.0.1", 4000, "all");
    sub_2.Subscribe("127.0.0.1", 4000, "squeares");
    sub_3.Subscribe("127.0.0.1", 4000, "squeares");

    std::cout << "Press Enter to unsub" << std::endl;
    std::cin.get();

    sub_1.UnSubscribe();
    sub_2.UnSubscribe();
    sub_3.UnSubscribe();

    std::cout << "Press Enter to end" << std::endl;
    std::cin.get();
}