#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <bitset>    
#include <queue>
#include "json.hpp"
#include "socket.h"
#include <string>
#include <mutex>
#pragma once


using json = nlohmann::json;
static json myCmdDataJson;

static std::mutex threadPrintMtx;
static std::queue<std::function<void()>> threadPrintTasks;
static std::condition_variable threadPrintCv;
static bool threadPrintDone = false;

void init();

class threadPrint
{
public:
    static threadPrint* instance;
    threadPrint(){instance = this;};
    
    template <typename T, typename... Types>
    void NewPrint(const T& firstArg, const Types&... args)
    {
        auto task = [firstArg](){
            (std::cout << firstArg);
        };
        {
            std::lock_guard<std::mutex> lock(threadPrintMtx);
            threadPrintTasks.push(task);
        }
        threadPrintCv.notify_one();
        // recursive   tuple
        NewPrint(args...);
    };
    void NewPrint(){};
    void worker(){
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(threadPrintMtx);
                threadPrintCv.wait(lock, []{ return !threadPrintTasks.empty() || threadPrintDone; });
                if (threadPrintDone && threadPrintTasks.empty()) return;
                task = std::move(threadPrintTasks.front());
                threadPrintTasks.pop();
            }
            task();
        }
    };
    void over()
    {
        std::lock_guard<std::mutex> lock(threadPrintMtx);
        threadPrintDone = true;
        threadPrintCv.notify_one();
    }

};
// threadPrint* MyThreadPrint = threadPrint::instance;
#define XXPrint(...) threadPrint::instance->NewPrint(__VA_ARGS__)

