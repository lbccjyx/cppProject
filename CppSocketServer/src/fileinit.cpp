#include "fileinit.h"


void init()
{
    system("CHCP 65001");
    if (__cplusplus == 202101L)
        std::cout << "C++23"<<std::endl;
    else if (__cplusplus == 202002L)
        std::cout << "C++20"<<std::endl;
    else if (__cplusplus == 201703L)
        std::cout << "C++17"<<std::endl;
    else if (__cplusplus == 201402L)
        std::cout << "C++14"<<std::endl;
    else if (__cplusplus == 201103L)
        std::cout << "C++11"<<std::endl;
    else if (__cplusplus == 199711L)
        std::cout << "C++98"<<std::endl;
    else
        std::cout << "pre-standard C++." << __cplusplus; 

    std::cout << "pre-standard C++." << __cplusplus<<std::endl;
    std::cout << "\n";
}


