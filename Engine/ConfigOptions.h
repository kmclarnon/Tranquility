#ifndef _CONFIG_OPTIONS_H_
#define _CONFIG_OPTIONS_H_

typedef enum ConfigGroups
{
    Window,
    Graphics,
    Resources,
    Logging
};

// config file parameters
const static std::string CONFIG_GROUP_WINDOW = "[Window]";
const static std::string CONFIG_GROUP_GRAPHICS = "[Graphics]";
const static std::string CONFIG_GROUP_RESOURCES = "[Resources]";
const static std::string CONFIG_GROUP_LOGGING = "[Logging]";
const static char CONFIG_COMMENT_CHAR = '#';
const static std::string WINDOW_OPTION_HEIGHT = "Height";
const static std::string WINDOW_OPTION_WIDTH = "Width";
const static std::string WINDOW_OPTION_TITLE = "Title";
const static std::string GRAPHICS_OPTION_VSYNC = "Vsync";
const static std::string GRAPHICS_OPTION_OPENGL_MAJOR = "OpenGLMajor";
const static std::string GRAPHICS_OPTION_OPENGL_MINOR = "OpenGLMinor";
const static std::string RESOURCE_OPTION_MODEL_PATH = "ModelDir";
const static std::string RESOURCE_OPTION_SHADER_PATH = "ShaderDir";
const static std::string LOGGING_OPTION_LOG_DIR = "LogDir";
const static std::string RESOURCE_PATH = "ResourceDir";
const static std::string FALLBACK_TEXTURE = "FallbackTexture";

// Defaults
const static std::string DEFAULT_CONFIG_FILE = "settings.cfg";
const static int DEFAULT_HEIGHT = 480;
const static int DEFAULT_WIDTH = 720;
const static int DEFAULT_VSYNC = 1;
const static std::string DEFAULT_WINDOW_TITLE = "Tranquility Engine v0.1";
const static int DEFAULT_OPENGL_MAJOR = 3;
const static int DEFAULT_OPENGL_MINOR = 2;
const static std::string DEFAULT_SHADER_DIR = "/Resources/Shaders/";
const static std::string DEFAULT_MODEL_DIR = "/Resources/Models/";
const static std::string DEFAULT_LOG_DIR = "/Logs/";
const static std::string DEFAULT_RESOURCE_DIR = "/Resources/";
const static std::string DEFAULT_FALLBACK_TEXTURE = DEFAULT_RESOURCE_DIR + "white.png";

#endif