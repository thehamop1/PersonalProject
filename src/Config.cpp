#include "Config.hpp"
#include "Logger.hpp"

namespace Core
{
    namespace Internal
    {
        Config::Config()
        {
            if(std::filesystem::exists(m_ConfigFileDir)){
                for (const auto &file : std::filesystem::recursive_directory_iterator(m_ConfigFileDir))
                {
                    m_ConfigFilesPaths.push_back(file);
                }
            }else{
                Core::LOG(LOGGING_LEVEL::WARNING) << "Logging directory not found";
            }

            for (const auto &file : m_ConfigFilesPaths)
            {
                m_ConfigFiles.emplace(file.filename().generic_string(), file);
            }

        }
    }
}