#include "configparser.h"

ConfigParser::ConfigParser(LogSystem &log) : logSys(log)
{
    this->settings = new std::map<std::string, std::string>();
}

bool ConfigParser::loadConfigFile(std::string file)
{
    std::string line;
    std::vector<std::string> elems;
    std::ifstream configFile(file);

    // empty out any previously held settings
    this->settings->clear();

    if(configFile)
    {
        while(!configFile.eof())
        {
            std::getline(configFile, line);
            trim(line);
            elems = split(line, '=');
            if(elems.size() == 2)
                this->settings->insert(std::pair<std::string, std::string>(elems[0], elems[1]));
            else
                printf("Unknown config format, skipping\n");
        }
    }
    else
    {
        printf("Failed to find specified file: %s\n", file.c_str());
        return false;
    }

    return true;
}

bool ConfigParser::hasSetting(std::string name)
{
    return this->settings->find(name) != this->settings->end();
}

std::string ConfigParser::getSetting(std::string name)
{
    return this->settings->find(name)->second;
}