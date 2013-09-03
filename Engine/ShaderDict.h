#ifndef _TRANQUILITYSHADER_DIC_H_
#define _TRANQUILITYSHADER_DIC_H_

// shader input attributes
#define SHADER_IN_POSITION "inputPosition"
#define SHADER_IN_TEXCOORD "inputTexCoord"
#define SHADER_IN_NORMAL "inputNormal"
#define SHADER_IN_COLOR "inputColor"

// shader uniforms
#define SHADER_UNIFORM_WORLD "worldMatrix"
#define SHADER_UNIFORM_PROJECTION "projectionMatrix"
#define SHADER_UNIFORM_VIEW "viewMatrix"
#define SHADER_UNIFORM_TEXTURE "shaderTexture"
#define SHADER_UNIFORM_LIGHT_DIR "lightDirection"
#define SHADER_UNIFORM_DIFFUSE_COLOR "diffuseLightColor"
#define SHADER_UNIFORM_AMBIENT "ambientLight"

#endif