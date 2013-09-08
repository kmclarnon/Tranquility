#ifndef _TRANQUILITYSHADER_DIC_H_
#define _TRANQUILITYSHADER_DIC_H_

#include "Common.h"

// shader input attributes
const static std::string SHADER_IN_POSITION = "inputPosition";
const static std::string SHADER_IN_TEXCOORD = "inputTexCoord";
const static std::string SHADER_IN_NORMAL = "inputNormal";
const static std::string SHADER_IN_COLOR = "inputColor";

// shader uniforms
const static std::string SHADER_UNIFORM_WORLD = "worldMatrix";
const static std::string SHADER_UNIFORM_PROJECTION = "projectionMatrix";
const static std::string SHADER_UNIFORM_VIEW = "viewMatrix";
const static std::string SHADER_UNIFORM_TEXTURE = "shaderTexture";
const static std::string SHADER_UNIFORM_LIGHT_DIR = "lightDirection";
const static std::string SHADER_UNIFORM_DIFFUSE_COLOR = "diffuseLightColor";
const static std::string SHADER_UNIFORM_AMBIENT = "ambientLight";

#endif