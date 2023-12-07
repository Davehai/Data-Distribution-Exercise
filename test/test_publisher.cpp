/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include "publisher.hpp"

void TestNotify();

int main()
{
    TestNotify();
}

void TestNotify()
{
    ilrd::Publisher *pub = ilrd::GetPublisher();

    pub->Notify("subscribe/all/8.8.8.8/8080");

    pub->Notify("unsubscribe/all/8.8.8.8/8080");
}