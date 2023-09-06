#pragma once

#include <iostream>
#include <chrono>
#include <string>

#define LOG_DURATION(x) LogDuration profile_guard(x)

class LogDuration
{
    using Clock = std::chrono::steady_clock;

public:

    LogDuration(std::string operation) : operation_name_(operation) {}

    ~LogDuration()
    {
        using namespace std::chrono;

        const Clock::time_point end_time = Clock::now();
        const Clock::duration duration = end_time - start_time_;
        std::cerr << operation_name_ << ": " << duration_cast<milliseconds>(duration).count() << " ms" << std::endl;
    }

private:
    std::string operation_name_;
    const Clock::time_point start_time_ = Clock::now();
};