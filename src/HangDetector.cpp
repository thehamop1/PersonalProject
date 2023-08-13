#include "HangDetector.hpp"
#include "Global.hpp"

#include <csignal>

const std::chrono::seconds HangDetector::m_TimeOutDuration{5};//If a thread hasn't responded in 10 seconds consider it hung
const std::chrono::seconds HangDetector::m_ExecutionRate{10};//Check the threads every 10 seconds

HangDetector::HangDetector()
{
    m_WatchDog = std::thread([&](){WatchDogFunction();});
};

HangDetector::~HangDetector(){
    G_SHUTDOWN=true;
    m_WatchDog.join();
};

void HangDetector::WatchDogFunction(){
    while (!G_SHUTDOWN)
    {
        std::this_thread::sleep_for(m_ExecutionRate);

        std::scoped_lock localLock{m_HeatBeatsLock};
        for(const auto& heartBeatPair : m_ThreadHeartBeats){
            const auto lastPingDuration = std::chrono::system_clock::now() - heartBeatPair.second;
            if(lastPingDuration > m_TimeOutDuration){
                 std::raise(SIGINT);
            }
        }
    }
    
};