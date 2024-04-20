#include "ConfigReader.hpp"

ConfigReader::ConfigReader(){
    ConfigReader("./");
};

ConfigReader::ConfigReader(std::string_view ConfigFileDirectory)
{
    m_ConfigFileDir = {ConfigFileDirectory};

    for(const auto& file: std::filesystem::recursive_directory_iterator(m_ConfigFileDir)){
        m_ConfigFilesPaths.push_back(file);
    }


}