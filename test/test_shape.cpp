/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <iostream>     //std::cout std::endl

#include "shape.hpp"

void TestSquare();
void TestCircle();

using namespace ilrd;

int main()
{
    TestSquare();
    TestCircle();

    return 0;
}

void TestSquare()
{
    std::cout << "\nTesting Square Class" << std::endl;
    Square s("red", 10, 4);
    std::cout << s << std::endl;

    std::cout << "\nTesting Square To string" << std::endl;
    std::string str_s = s.ToString();
    std::cout << str_s << std::endl;

    std::cout << "\nTesting string To Square" << std::endl;
    Square s_p(StringToSquare(str_s));
    std::cout << s_p << std::endl;
}

void TestCircle()
{
    std::cout << "\nTesting Circle Class" << std::endl;
    Circle c("blue", 10, 4);
    std::cout << c << std::endl;

    std::cout << "\nTesting Circle To string" << std::endl;
    std::string str_c = c.ToString();
    std::cout << str_c << std::endl;

    std::cout << "\nTesting string To Circle" << std::endl;
    Circle c_p(StringToCircle(str_c));
    std::cout << c_p << std::endl;
}