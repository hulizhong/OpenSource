/*************************************************************************
	> File Name: bind.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 29 Mar 2019 05:13:27 AM CDT
 ************************************************************************/

#include<iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
using namespace std;

void fun(int)
{
    std::cout << "fun" << std::endl;
}


int main(void)
{

    boost::function<void(int)> func_obj;
    func_obj = boost::bind(&fun,1,_1);
    return 0;
}

