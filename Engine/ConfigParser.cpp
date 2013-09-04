#include "ConfigParser.h"

ConfigParser::ConfigParser() 
    : windowWidth(-1), windowHeight(-1), 
    openGLMajor(-1), openGLMinor(-1), vsync(false)
{
}

int ConfigParser::getWindowWidth() const
{
    return this->windowWidth;
}

int ConfigParser::getWindowHeight() const
{
    return this->windowHeight;
}

int ConfigParser::getGLMajorVer() const
{
    return this->openGLMajor;
}

int ConfigParser::getGLMinorVer() const
{
    return this->openGLMinor;
}

const std::string& ConfigParser::getWindowName() const
{
    return this->windowName;
}

bool ConfigParser::getVsync() const
{
    return this->vsync;
}

const std::string& ConfigParser::getModelDir() const
{
    return this->modelDir;
}

const std::string& ConfigParser::getShaderDir() const
{
    return this->shaderDir;
}

const std::string& ConfigParser::getLogDir() const
{
    return this->logDir;
}

const std::string& ConfigParser::getResourceDir() const
{
    return this->resourceDir;
}


void ConfigParser::loadConfig(std::string configFile)
{
    std::ifstream ifs(configFile);
    std::string line;
    int lineIndex = 1;
    bool loadFromDefaults = false;

    if(!ifs)
        loadFromDefaults = true;

    while(std::getline(ifs, line))
    {
        if((line.size() > 0) && (line.at(0) != CONFIG_COMMENT_CHAR))
        {
            try
            {
                this->parseLine(line);
            }
            catch (std::exception* e)
            {
                printf("Failed to parse line %i of %s: %s\n", lineIndex,configFile.c_str(), e->what());
                loadFromDefaults = true;
            }
        }
    }

    if(loadFromDefaults)
    {
        printf("Error detected in config parsing, filling in missing data from defaults\n");
        this->loadDefaults();
    }
}

bool ConfigParser::parseLine(std::string &line)
{
    std::string l = trim(line);
    //printf("Parsing line: %s\n", line.c_str());

    if(l.at(0) == '[')
    {
        if(l == CONFIG_GROUP_WINDOW)
        {
            this->currentGroup = Window;
            return true;
        }
        else if(l == CONFIG_GROUP_GRAPHICS)
        {
            this->currentGroup = Graphics;
            return true;
        }
        else if(l == CONFIG_GROUP_RESOURCES)
        {
            this->currentGroup = Resources;
            return true;
        }
        else if(l == CONFIG_GROUP_LOGGING)
        {
            this->currentGroup = Logging;
            return true;
        }
        else
            return false;
    }

    switch(this->currentGroup)
    {
    case Window:    return this->parseWindowLine(l);        break;
    case Graphics:  return this->parseGraphicsLine(l);      break;
    case Resources: return this->parseResourceLine(l);         break;
    case Logging:   return this->parseLoggingLine(l);       break;
    default:
        return false;
    }

    return false;
}

bool ConfigParser::parseWindowLine(std::string &line)
{
    std::vector<std::string> elems = split(line, '=');
    if(elems.size() != 2)
        return false;

    if(elems.at(0) == WINDOW_OPTION_WIDTH)
    {
        this->windowWidth = std::stoi(elems.at(1));
    }
    else if(elems.at(0) == WINDOW_OPTION_HEIGHT)
    {
        this->windowHeight = std::stoi(elems.at(1));
    }
    else if(elems.at(0) == WINDOW_OPTION_TITLE)
    {
        this->windowName = elems.at(1);
    }

    return false;
}

bool ConfigParser::parseGraphicsLine(std::string &line)
{
    std::vector<std::string> elems = split(line, '=');
    if(elems.size() != 2)
        return false;

    if(elems.at(0) == GRAPHICS_OPTION_VSYNC)
    {
        this->vsync = this->parseBool(elems.at(1));
    }
    else if(elems.at(0) == GRAPHICS_OPTION_OPENGL_MAJOR)
    {
        this->openGLMajor = std::stoi(elems.at(1));
    }
    else if(elems.at(0) == GRAPHICS_OPTION_OPENGL_MINOR)
    {
        this->openGLMinor = std::stoi(elems.at(1));
    }

    return false;
}

bool ConfigParser::parseResourceLine(std::string &line)
{
    std::vector<std::string> elems = split(line, '=');
    if(elems.size() != 2)
        return false;

    if(elems.at(0) == RESOURCE_OPTION_MODEL_PATH)
    {
        this->modelDir = elems.at(1);
        return true;
    }
    else if(elems.at(0) == RESOURCE_OPTION_SHADER_PATH)
    {
        this->shaderDir = elems.at(1);
        return true;
    }
    else if(elems.at(0) == RESOURCE_PATH)
    {
        this->resourceDir = elems.at(1);
        return true;
    }

    return false;;
}

bool ConfigParser::parseLoggingLine(std::string &line)
{
    std::vector<std::string> elems = split(line, '=');
    if(elems.size() != 2)
        return false;

    if(elems.at(0) == LOGGING_OPTION_LOG_DIR)
    {
        this->logDir = elems.at(1);
        return true;
    }

    return false;
}

bool ConfigParser::parseBool(std::string &line)
{
    if(line == "on" || line == "yes" || line == "1" ||
        line == "On" || line == "Yes" ||
        line == "ON" || line == "YES")
    {
        return true;
    }
    else
        return false;
}

void ConfigParser::loadDefaults()
{
    // check width and height
    if(this->windowWidth < 0 || this->windowHeight < 0)
    {
        this->windowWidth = DEFAULT_WIDTH;
        this->windowHeight = DEFAULT_HEIGHT;
    }

    // check window title
    if(this->windowName.size() == 0)
        this->windowName = DEFAULT_WINDOW_TITLE;

    // check opengl version
    if(this->openGLMajor < 0 || this->openGLMinor < 0)
    {
        this->openGLMajor = DEFAULT_OPENGL_MAJOR;
        this->openGLMinor = DEFAULT_OPENGL_MINOR;
    }

    // check model path
    if(this->modelDir.size() == 0)
        this->modelDir = DEFAULT_MODEL_DIR;

    // check shader path
    if(this->shaderDir.size() == 0)
        this->shaderDir = DEFAULT_SHADER_DIR;

    // check log path
    if(this->logDir.size() == 0)
        this->logDir = DEFAULT_LOG_DIR;

    // check resource path
    if(this->resourceDir.size() == 0)
        this->resourceDir = DEFAULT_RESOURCE_DIR;
}