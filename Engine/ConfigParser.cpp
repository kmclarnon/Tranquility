#include "ConfigParser.h"

ConfigParser::ConfigParser(const LogSystem &log) : logSys(log)
{
    this->settings = std::unique_ptr<ConfigMap>(new ConfigMap());
}

bool ConfigParser::loadConfig(std::string file)
{
    if(!loadConfigFile(file))
    {
        this->logSys.warning("Failed to load configuration from: %s", file.c_str());
        this->logSys.warning("Falling back on default configuration");

        this->settings->insert(std::make_pair(CONFIG_RESOLUTION_HEIGHT, ConfigItem(DEFAULT_HEIGHT)));
        this->settings->insert(std::make_pair(CONFIG_RESOLUTION_WIDTH, ConfigItem(DEFAULT_WIDTH)));
        this->settings->insert(std::make_pair(CONFIG_WINDOW_TITLE, ConfigItem(DEFAULT_WINDOW_TITLE)));
        this->settings->insert(std::make_pair(CONFIG_VSYNC, ConfigItem(DEFAULT_VSYNC)));
        this->settings->insert(std::make_pair(CONFIG_OPENGL_MAJOR, ConfigItem(DEFAULT_OPENGL_MAJOR)));
        this->settings->insert(std::make_pair(CONFIG_OPENGL_MINOR, ConfigItem(DEFAULT_OPENGL_MINOR)));
        this->settings->insert(std::make_pair(CONFIG_SHADER_DIR, ConfigItem(DEFAULT_SHADER_DIR)));
        this->settings->insert(std::make_pair(CONFIG_MODEL_DIR, ConfigItem(DEFAULT_MODEL_DIR)));
    }

    return true;
}

bool ConfigParser::loadConfigFile(std::string file)
{
    // return false for now until the config layout is more well-defined
    return false;

    tinyxml2::XMLDocument doc;

    if(doc.LoadFile(file.c_str()))
        return false;

    tinyxml2::XMLElement *elem = doc.FirstChildElement(CONFIG_ENGINE_BASE_ELEMENT);
    if(!elem)
        return false;

    // first get our window configs
    tinyxml2::XMLElement *window = elem->FirstChildElement(CONFIG_WINDOW_ELEMENT);
    if(!window)
        return false;

    return true;
}

ConfigItem ConfigParser::getSetting(std::string name)
{
    return this->settings->find(name)->second;
}