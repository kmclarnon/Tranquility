#ifndef _TRILLEK_SHADER_MANAGER_H_
#define _TRILLEK_SHADER_MANAGER_H_

#include "Common.h"
#include "LogSystem.h"
#include "ShaderDict.h"

class Shader
{
private:
    struct ShaderDesc
    {
        int id;
        std::string filename;
    };

    typedef std::map<GLenum, ShaderDesc> ComponentMap;
    typedef std::map<int, std::string> AttributeMap;
    typedef std::vector<std::string> TempAttributeList;

public:
    Shader(const LogSystem &logSys);

    bool init();
    void shutdown();

    bool addStage(GLenum type, std::string filename);
    bool addAttribute(std::string attrib);
    bool addUniform(std::string uniform);

    void useShader();


    // glm convenience functions
    bool setShaderUniform(std::string name, glm::mat4 val);
    bool setShaderUniform(std::string name, glm::vec3 val);
    bool setShaderUniform(std::string name, glm::vec4 val);
    bool setShadderCameraUniforms(glm::mat4 world, glm::mat4 view, glm::mat4 perspective);

    // openGL call translation functions
    bool setShaderUniform(std::string name, GLfloat v0);
    bool setShaderUniform(std::string name, GLfloat v0, GLfloat v1);
    bool setShaderUniform(std::string name, GLfloat v0, GLfloat v1, GLfloat v2);
    bool setShaderUniform(std::string name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    bool setShaderUniform(std::string name, GLint v0);
    bool setShaderUniform(std::string name, GLint v0, GLint v1);
    bool setShaderUniform(std::string name, GLint v0, GLint v1, GLint v2);
    bool setShaderUniform(std::string name, GLint v0, GLint v1, GLint v2, GLint v3);
    bool setShaderUniform(std::string name, GLuint v0);
    bool setShaderUniform(std::string name, GLuint v0, GLuint v1);
    bool setShaderUniform(std::string name, GLuint v0, GLuint v1, GLuint v2);
    bool setShaderUniform(std::string name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    bool setShaderUniform(std::string name, GLsizei uniSize, GLsizei len, const GLfloat *value);
    bool setShaderUniform(std::string name, GLsizei uniSize, GLsizei len, const GLint *value);
    bool setShaderUniform(std::string name, GLsizei uniSize, GLsizei len, const GLuint *value);
    bool setShaderUniform(std::string name, GLsizei row, GLsizei column, GLsizei count, GLboolean transpose, const GLfloat *value);
    
private:
    bool loadComponent(GLenum type, ShaderDesc &desc);
    bool loadFromFile(std::string vertFilename, std::string fragFilename);
    bool loadComponentContents(std::string filename, std::string &contents);
    bool compileComponent(int &id, GLenum type, std::string filename);
    void attachComponent(ShaderDesc desc);
    bool linkShader();
    bool getUniformLoc(std::string name, GLint &loc);
    void cleanup();
    void getShaderError(int componentId);
    
private:
    int shaderId;

    ComponentMap stages;
    AttributeMap attributes;
    AttributeMap uniforms;
    TempAttributeList tempAttrs;
    TempAttributeList tempUniforms;

    // we do not own this
    const LogSystem &logSys;
};

#endif