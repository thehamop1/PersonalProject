#pragma once

#include "Singleton.hpp"

#include <thread>
#include <mutex>
#include <unordered_map>
#include <chrono>
#include <Logger.hpp>
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
            void UpdateEntry(const std::thread::id& id){
                if(!m_ThreadHeartBeats.contains(id)){
                    LOG(Core::LOGGING_LEVEL::ERROR) << "No thread id found in hang detector.";
                    return;
                }
                m_ThreadHeartBeats[id] = std::chrono::system_clock::now();
            };
            void AddThread(const std::thread::id& id){
                if(m_ThreadHeartBeats.contains(id))
                    LOG(Core::LOGGING_LEVEL::WARNING) << "Duplicate thread id added to hang detector";
                m_ThreadHeartBeats[id] = std::chrono::system_clock::now();
            };
        };
    };
    using HangDetector = Core::Singleton<Core::Internal::HangDetector>;
}
