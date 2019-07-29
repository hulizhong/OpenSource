/*************************************************************************
	> File Name: ptr.cpp
	> Author: 
	> Mail: 
	> Created Time: Tuesday, June 06, 2017 PM05:33:37 HKT
 ************************************************************************/

#include <iostream>
#include <boost/scoped_ptr.hpp>
using namespace std;


class FF
{
public:
    int num = 1;
};


//g++ ptr.cpp -std=c++11 -I /usr/local/include/ -L /usr/local/lib/
int main()
{
    FF *f = NULL;
    {
        boost::scoped_ptr<FF> ptr(new FF);
        ptr->num = 11;

        std::cout << (f = ptr.get()) << std::endl;
        std::cout << ptr.get() << std::endl;
        std::cout << f << std::endl;
    }
    std::cout << sizeof(*f) << std::endl;
    std::cout << f->num << std::endl;
    
    return 0;
}
