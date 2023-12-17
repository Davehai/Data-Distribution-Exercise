/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <unistd.h>      //sleep
#include <iostream>     //std::cin.get()
#include <thread>

#include "publisher.hpp"
#include "udp_listener.hpp"
#include "subscriber.hpp"
#include "shape.hpp"

void ServerSquare();
void ServerCircle();

bool run = true;

int main()
{
    ilrd::UDPListener udp("127.0.0.1", 4000);
    ilrd::Publisher *pub = ilrd::GetPublisher();

    pub->AddNewKey("square");
    pub->AddNewKey("circle");

    std::thread thread_square = std::thread(&ServerSquare);
    std::thread thread_circle = std::thread(&ServerCircle);

    std::cout << "Server is runing you may press enter to stop:" << std::endl;
    std::cin.get();
    run = false;

    thread_square.join();
    thread_circle.join();
}

void ServerSquare()
{
    ilrd::Publisher *pub = ilrd::GetPublisher();
    ilrd::Square square("blue", 3, 10);

    while(run)
    {
        sleep(1);
        pub->Publish(square.GetType(), square.ToString());
    }
}

void ServerCircle()
{
    ilrd::Publisher *pub = ilrd::GetPublisher();
    ilrd::Circle circle("green", 3, 10);

    while(run)
    {
        sleep(2);
        pub->Publish(circle.GetType(), circle.ToString());
    }
}