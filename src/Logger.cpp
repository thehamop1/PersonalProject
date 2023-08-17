#include "Logger.hpp"

namespace Core{
    namespace Internal{
        LoggingSystem::LoggingSystem()
        {
            std::string fileName{"SystemLog_" + FileName() + ".txt"};
            m_file.open(fileName, std::ofstream::out | std::ofstream::app);
            m_loggingThread = std::thread([&](){LoggingThread();});
        }

        std::string LoggingSystem::FileName()
        {
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
            return ss.str();
        }

        LoggingSystem::~LoggingSystem()
        {
        }

        void LoggingSystem::LoggingThread(){
            std::string logLine{};
            while(!G_SHUTDOWN){
                {
                    std::scoped_lock lock{m_queueLock};
                    logLine = m_loggingStatements.front();
                    m_loggingStatements.pop();
                }
                m_file << logLine;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            m_file.close();
        };

        void LoggingSystem::QueueLog(const std::string&& log){
            if(!m_enabled){
                std::cout << "Logging Disabled" << std::endl;
                return;
            }
            std::scoped_lock lock(m_queueLock);
            m_loggingStatements.push(log);
        };

        LogBuilder::LogBuilder(const LOGGING_LEVEL& LogLevel){
            m_logLevel = LogLevel;
        };

        LogBuilder::~LogBuilder(){
            m_logLine << "\n";
            Logger::Instance().QueueLog(m_logLine.str());
        };

    };
};