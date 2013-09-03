#ifndef _CONFIG_OPTIONS_H_
#define _CONFIG_OPTIONS_H_

static std::string CONFIG_GROUP_WINDOW = "[Window]";
static std::string CONFIG_GROUP_GRAPHICS = "[Graphics]";
static std::string CONFIG_GROUP_ASSETS = "[Assets]";
static std::string CONFIG_GROUP_LOGGING = "[Logging]";
static char CONFIG_COMMENT_CHAR = '#';

typedef enum ConfigGroups
{
    Window,
    Graphics,
    Assets,
    Logging,
    MaxConfigGroups
};

static std::string WINDOW_OPTION_HEIGHT = "Height";
static std::string WINDOW_OPTION_WIDTH = "Width";
static std::string WINDOW_OPTION_TITLE = "Title";

typedef enum WindowOptions
{
    Height,
    Width,
    Title,
    MaxWindowOptions
};

static std::string GRAPHICS_OPTION_VSYNC = "Vsync";
static std::string GRAPHICS_OPTION_OPENGL_MAJOR = "OpenGLMajor";
static std::string GRAPHICS_OPTION_OPENGL_MINOR = "OpenGLMinor";

typedef enum GraphicsOptions
{
    Vsync,
    OpenGLMajor,
    OpenGLMinor,
    MaxGraphicsOptions
};

static std::string ASSET_OPTION_MODEL_PATH = "ModelDir";
static std::string ASSET_OPTION_SHADER_PATH = "ShaderDir";

typedef enum AssetOptions
{
    ModelPath,
    ShaderPath,
    MaxAssetOptions
};

static std::string LOGGING_OPTION_LOG_DIR = "LogDir";

typedef enum LoggingOptions
{
    LogDir
};

// Defaults
static std::string DEFAULT_CONFIG_FILE = "../Config/settings.cfg";
static int DEFAULT_HEIGHT = 480;
static int DEFAULT_WIDTH = 720;
static int DEFAULT_VSYNC = 1;
static std::string DEFAULT_WINDOW_TITLE = "Trillek Prototype";
static int DEFAULT_OPENGL_MAJOR = 3;
static int DEFAULT_OPENGL_MINOR = 2;
static std::string DEFAULT_SHADER_DIR = "../Shaders/";
static std::string DEFAULT_MODEL_DIR = "../Models/";
static std::string DEFAULT_LOG_DIR = "../Logs/";

#endif