/*************************************************************************
	> File Name: time.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Jul 2019 03:22:09 AM CDT
 ************************************************************************/

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
using namespace std;

// g++ time.cpp -std=c++11 -lboost_date_time -lboost_system -lboost_thread -I /usr/local/include/ -L /usr/local/lib/
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
int main()
{
    boost::posix_time::ptime pt(boost::posix_time::second_clock::local_time());
    std::cout << to_simple_string(pt) << std::endl;
    std::cout << to_iso_string(pt) << std::endl;
    std::cout << to_iso_extended_string(pt) << std::endl;
    std::cout << pt.date().day_of_week().as_short_string() << std::endl;

    boost::this_thread::sleep(boost::posix_time::millisec(100));
    //boost::posix_time::ptime pt2(boost::posix_time::second_clock::local_time());
    boost::posix_time::ptime pt2 = pt + boost::posix_time::time_duration(0, 0, 3, 4);

    boost::posix_time::hours h(1);
    boost::posix_time::minutes m(10);
    boost::posix_time::seconds s(30);
    boost::posix_time::millisec ms(1);
    boost::posix_time::microsec mcs(1);
    //boost::posix_time::nanosec ns(1);

    boost::posix_time::time_duration td = pt2 - pt;
    std::cout << "h." << td.hours() << std::endl;
    std::cout << "m." << td.minutes() << std::endl;
    std::cout << "s." << td.seconds() << std::endl;
    std::cout << "ts." << td.total_seconds() << std::endl;
    std::cout << "tms." << td.total_milliseconds() << std::endl;
    std::cout << "  tk." << td.ticks() << std::endl;
    std::cout << "tmcs." << td.total_microseconds() << std::endl;
    //hours、minutes、seconds、millisec、microsec、nanosec
    //std::cout << td.millisec() << std::endl;
    //std::cout << td.microsec() << std::endl;
    //std::cout << td.nanosec() << std::endl;

    return 0;
}
