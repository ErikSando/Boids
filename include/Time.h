#pragma once

#include <chrono>
#include <thread>

// chrono stuff makes the lines too long so I made this utility

typedef std::chrono::_V2::high_resolution_clock::time_point timestamp;

namespace Time {
    timestamp Now() {
        return std::chrono::high_resolution_clock::now();
    }

    float Difference(timestamp end, timestamp start) {
        return std::chrono::duration<float>(end - start).count();
    }

    std::chrono::milliseconds Milliseconds(int milliseconds) {
        return std::chrono::milliseconds(milliseconds);
    }

    std::chrono::seconds Seconds(int seconds) {
        return std::chrono::seconds(seconds);
    }

    void Wait(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}