#pragma once
#include <string_view>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <fstream>

class ConfigReader
{
public:
    ConfigReader();
    ConfigReader(std::string_view ConfigFileDirectory);
private:
    class ConfigFile{
        public:
            ConfigFile(const std::filesystem::path& p){
                std::ifstream file{p};
                std::string key{}, value{};
                while(file >> key >> value){
                    ParseLine(key, value);
                } 
            }
        private:

        void ParseLine(std::string_view key, std::string_view value){
            //do casting here
            if(value=="0" || value=="1"){
                InsertData(key, (value=="1"));
            }else{
                try{
                    InsertData(key, std::stoi({value}));
                }catch(...){
                    InsertData(key, value);
                };
            }
        };

        template<typename T>
        void InsertData(const std::string_view key, const T& value){
            if constexpr(std::is_same_v<std::string, T>){
                m_stringValues[key] = value;
            }else if(std::is_same_v<bool, T>){
                m_boolValues[key] = value;
            }else if(std::is_arithmetic_v<T>){
                m_intValues[key] = value;
            }else{
                static_assert("No Matching type to store");
            }
        }

        std::unordered_map<std::string, std::string> m_stringValues{};
        std::unordered_map<std::string, int> m_intValues{};
        std::unordered_map<std::string, bool> m_boolValues{};
    };

    std::filesystem::path m_ConfigFileDir{};//Directory to look for files
    std::vector<std::filesystem::path> m_ConfigFilesPaths{};//List of files to parse
    std::unordered_map<std::string, ConfigFile> m_ConfigFiles{};//Fully parsed data used for lookups
};