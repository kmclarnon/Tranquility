#ifndef _CONFIG_OPTIONS_H_
#define _CONFIG_OPTIONS_H_

// config file parameters
const static std::string CONFIG_GROUP_WINDOW = "[Window]";
const static std::string CONFIG_GROUP_GRAPHICS = "[Graphics]";
const static std::string CONFIG_GROUP_ASSETS = "[Assets]";
const static std::string CONFIG_GROUP_LOGGING = "[Logging]";
const static char CONFIG_COMMENT_CHAR = '#';
const static std::string WINDOW_OPTION_HEIGHT = "Height";
const static std::string WINDOW_OPTION_WIDTH = "Width";
const static std::string WINDOW_OPTION_TITLE = "Title";
const static std::string GRAPHICS_OPTION_VSYNC = "Vsync";
const static std::string GRAPHICS_OPTION_OPENGL_MAJOR = "OpenGLMajor";
const static std::string GRAPHICS_OPTION_OPENGL_MINOR = "OpenGLMinor";
const static std::string ASSET_OPTION_MODEL_PATH = "ModelDir";
const static std::string ASSET_OPTION_SHADER_PATH = "ShaderDir";
static std::string LOGGING_OPTION_LOG_DIR = "LogDir";


// Defaults
const static std::string DEFAULT_CONFIG_FILE = "Config/settings.cfg";
const static int DEFAULT_HEIGHT = 480;
const static int DEFAULT_WIDTH = 720;
const static int DEFAULT_VSYNC = 1;
const static std::string DEFAULT_WINDOW_TITLE = "Trillek Prototype";
const static int DEFAULT_OPENGL_MAJOR = 3;
const static int DEFAULT_OPENGL_MINOR = 2;
const static std::string DEFAULT_SHADER_DIR = "../Shaders/";
const static std::string DEFAULT_MODEL_DIR = "../Models/";
const static std::string DEFAULT_LOG_DIR = "../Logs/";

#endif