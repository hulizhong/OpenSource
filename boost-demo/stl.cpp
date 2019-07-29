/*************************************************************************
	> File Name: stl.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jul 2019 03:53:37 AM CDT
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// g++ --std=c++11 stl.cpp
int main(int argc, char* argv[])
{
    std::vector<int> v = {1, 2, 4, 5, 2, 3, 3, 5, 2};
    for (auto it : v) {
        std::cout << " " << it;
    }
    std::cout << std::endl;

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());

    for (auto it : v) {
        std::cout << " " << it;
    }
    std::cout << std::endl;
    return 0;
}
