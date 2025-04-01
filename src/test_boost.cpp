/**
 * @file test_boost.cpp
 * @author BusyBox (busybox177634@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <boost/filesystem.hpp>


int main()
{
    std::cout << "hello world" << std::endl;
    if (!boost::filesystem::exists("demo.png")) {
        std::cerr << "demo.png not exist" << std::endl;
    }
    return 0;
}