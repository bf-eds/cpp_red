//
// Created by human on 30.12.2018.
//

#pragma once

#include <chrono>
#include <iostream>

#define UNIQ_ID_IMPL(lineno) _a_local_var_ ## lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL (lineno)
#define LOG_DURATION(message) \
LogDuration UNIQ_ID( __LINE__){message };

using namespace std::chrono;

class LogDuration
{
public:
    explicit LogDuration(const string &msg = "") : message(msg + ": "), start(steady_clock::now())
    {
    }

    ~ LogDuration()
    {
        auto finish = steady_clock::now();
        auto dur = finish - start;
        std::cerr << message << duration_cast<milliseconds>(dur).count() << " ms" << endl;
    }

private:
    string message;
    steady_clock::time_point start;
};
