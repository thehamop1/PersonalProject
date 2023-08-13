#pragma once

#include <thread>
#include <mutex>
#include <unordered_map>
#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

class HangDetector
{
private:
    HangDetector();
    ~HangDetector();
    void WatchDogFunction();

    static const std::chrono::seconds m_TimeOutDuration;
    static const std::chrono::seconds m_ExecutionRate;
    std::thread m_WatchDog;
    std::mutex  m_HeatBeatsLock;
    std::unordered_map<std::thread::id, TimePoint> m_ThreadHeartBeats;

public:
    static HangDetector& Instance(){
        static HangDetector Instance{};
        return Instance;
    }
};
