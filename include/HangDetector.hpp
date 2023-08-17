#pragma once

#include "Singleton.hpp"

#include <thread>
#include <mutex>
#include <unordered_map>
#include <chrono>
namespace Core{
    namespace Internal{
        class HangDetector
        {
        private:
            using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
            static const std::chrono::seconds m_TimeOutDuration;
            static const std::chrono::seconds m_ExecutionRate;

            void WatchDogFunction();

            std::thread m_WatchDog;
            std::mutex  m_HeatBeatsLock;
            std::unordered_map<std::thread::id, TimePoint> m_ThreadHeartBeats;
        public:
            HangDetector();
            ~HangDetector();
        };
    };
    using HangDetector = Core::Singleton<Core::Internal::HangDetector>;
}
