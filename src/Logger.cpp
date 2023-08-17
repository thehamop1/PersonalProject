#include "Logger.hpp"

namespace Core{
    namespace Internal{
        LoggingSystem::LoggingSystem()
        {

        }

        LoggingSystem::~LoggingSystem()
        {
        }

        void LoggingSystem::QueueLog(const std::string&& log){
            std::scoped_lock lock(m_queueLock);
            m_loggingStatements.push(log);
            return true;
        };

        LogBuilder::LogBuilder(const LOGGING_LEVEL& LogLevel){
            m_logLevel = LogLevel;
        };

        LogBuilder::~LogBuilder(){
            Logger::Instance().QueueLog(m_logLine.str());
        };

    };
};