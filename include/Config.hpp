#pragma once

#include "Singleton.hpp"

#include <iostream>
#include <string_view>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <fstream>

static const std::string BASE_CONFIG_FILE{"base.cfg"};

namespace Core
{
    namespace Internal
    {
        class Config
        {
        public:
            Config();

            template <typename T>
            bool GetValue(const std::string& file, const std::string &key, T &val){
                auto it{m_ConfigFiles.find(file)};
                if(it!=m_ConfigFiles.end()){
                    auto& [_, configFile]{*it};
                    configFile.GetValue(key, val);
                    return true;
                }
                return false;
            };

        private:
            class ConfigFile
            {
            public:
                template <typename T>
                bool GetValue(const std::string &key, T &val)
                {
                    if constexpr (std::is_same_v<std::string, T>)
                    {
                        val = m_stringValues[key];
                        return true;
                    }
                    else if (std::is_same_v<bool, T>)
                    {
                        val = m_boolValues[key];
                        return true;
                    }
                    else if (std::is_arithmetic_v<T>)
                    {
                        val = m_intValues[key];
                        return true;
                    }
                    else
                    {
                        static_assert("No Matching type to store");
                    }

                    return false;
                };

                ConfigFile(const std::filesystem::path &p)
                {
                    std::ifstream file{p};
                    std::string key{}, value{};
                    while (file >> key >> value)
                    {
                        ParseLine(key, value);
                    }
                }

            private:
                void ParseLine(const std::string &key, const std::string &value)
                {
                    // do casting here
                    if (value == "0" || value == "1")
                    {
                        InsertData(key, (value == "1"));
                    }
                    else
                    {
                        try
                        {
                            InsertData(key, std::stoi(value));
                        }
                        catch (...)
                        {
                            InsertData(key, value);
                        };
                    }
                };

                template <typename T>
                void InsertData(const std::string &key, const T &value)
                {
                    if constexpr (std::is_same_v<std::string, T>)
                    {
                        m_stringValues[key] = value;
                    }
                    else if (std::is_same_v<bool, T>)
                    {
                        m_boolValues[key] = value;
                    }
                    else if (std::is_arithmetic_v<T>)
                    {
                        m_intValues[key] = value;
                    }
                    else
                    {
                        static_assert("No Matching type to store");
                    }
                }

                std::unordered_map<std::string, std::string> m_stringValues{};
                std::unordered_map<std::string, int> m_intValues{};
                std::unordered_map<std::string, bool> m_boolValues{};
            };

            std::filesystem::path m_ConfigFileDir{"./config"};                     // Directory to look for files
            std::vector<std::filesystem::path> m_ConfigFilesPaths{};     // List of files to parse
            std::unordered_map<std::string, ConfigFile> m_ConfigFiles{}; // Fully parsed data used for lookups
        };
    }

    using Config = Core::Singleton<Core::Internal::Config>;
}