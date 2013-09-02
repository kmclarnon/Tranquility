#include "Shader.h"

Shader::Shader(const LogSystem &log) : logSys(log)
{
    this->shaderId = -1;
    this->stages = ComponentMap();
    this->attributes = AttributeMap();
    this->tempAttrs = TempAttributeList();
    this->uniforms = AttributeMap();
    this->tempUniforms = TempAttributeList();
}

bool Shader::init()
{
    // initialize all of our stages of the shader
    for(auto it = this->stages.begin(); it != this->stages.end(); ++it)
    {
        if(!this->loadComponent((*it).first, (*it).second))
            return false;

        this->attachComponent((*it).second);
    }

    // link the shader into a complete program
    if(!this->linkShader())
        return false;

    // locate all of our previously unlocated attributes
    for(auto it = this->tempAttrs.begin(); it != this->tempAttrs.end(); ++it)
    {
        if(!this->addAttribute((*it)))
        {
            this->logSys.warning("Detected duplicate attribute %s, skipping", (*it).c_str());
        }
    }

    // locate all of our previously unlocated uniforms
    for(auto it = this->tempUniforms.begin(); it != this->tempUniforms.end(); ++it)
    {
        if(!this->addUniform((*it)))
        {
            this->logSys.warning("Detected duplicate uniform %s, skipping", (*it).c_str());
        }
    }

    this->cleanup();

    return true;
}

bool Shader::addStage(GLenum type, std::string filename)
{
    ShaderDesc desc;

    if(this->stages.find(type) != this->stages.end())
        return false;

    desc.filename = filename;
    desc.id = -1;

    this->stages.insert(std::pair<GLenum, ShaderDesc>(type, desc));

    return true;
}

bool Shader::addAttribute(std::string attrib)
{
    const char* att = attrib.c_str();
    int loc = glGetAttribLocation(this->shaderId, att);
    
    if(loc == -1)
    {
        this->tempAttrs.push_back(attrib);
    }
    else
    {
        if(this->attributes.find(loc) != this->attributes.end())
            return false;

        this->attributes.insert(std::pair<int, std::string>(loc, attrib));
    }

    return true;
}

bool Shader::addUniform(std::string uniform)
{
    const char* uni = uniform.c_str();
    int loc = glGetUniformLocation(this->shaderId, uni);

    if(loc == -1)
    {
        this->tempUniforms.push_back(uniform);
    }
    else
    {
        if(this->uniforms.find(loc) != this->uniforms.end())
            return false;

        this->uniforms.insert(std::pair<int, std::string>(loc, uniform));
    }

    return true;
}

bool Shader::loadComponent(GLenum type, ShaderDesc &desc)
{
    std::string shaderSrc;

    if(!this->loadComponentContents(desc.filename, shaderSrc))
        return false;

    if(!this->compileComponent(desc.id, type, shaderSrc))
        return false;

    return true;
}

bool Shader::loadComponentContents(std::string filename, std::string &contents)
{
    std::ifstream ifs(filename);

    if(!ifs)
    {
        this->logSys.error("Failed to find shader source file: %s", filename.c_str());
        return false;
    }

    ifs.seekg(0, std::ios::end);   
    contents.reserve(ifs.tellg());
    ifs.seekg(0, std::ios::beg);

    contents.assign((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());

    return true;
}

bool Shader::compileComponent(int &id, GLenum type, std::string contents)
{
    int status;
    const char *src = contents.c_str();
    id = glCreateShader(type);

    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if(status != 1)
    {
        this->getShaderError(id);
        return false;
    }

    return true;
}

void Shader::attachComponent(ShaderDesc desc)
{
    if(this->shaderId < 0)
        this->shaderId = glCreateProgram();

    glAttachShader(this->shaderId, desc.id);
}

bool Shader::linkShader()
{
    GLint status;
    glLinkProgram(this->shaderId);
    glGetProgramiv(this->shaderId, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        this->getShaderError(this->shaderId);
        return false;
    }

    return true;
}

void Shader::cleanup()
{
    for(auto it = this->stages.begin(); it != this->stages.end(); ++it)
    {
        glDeleteShader((*it).second.id);
    }
}

void Shader::useShader()
{
    glUseProgram(this->shaderId);
}

void Shader::shutdown()
{

}

void Shader::getShaderError(int componentId)
{
    int logSize, i;
    char* infoLog;
    std::ofstream fout;

    // get the compilation error
    glGetShaderiv(componentId, GL_INFO_LOG_LENGTH, &logSize);
    if(logSize <= 1)
    {
        // check if it was link error instead
        glGetProgramiv(componentId, GL_INFO_LOG_LENGTH, &logSize);
        if(logSize <= 1)
        {
            printf("Failed to determine shader error\n");
            return;
        }
        else
        {
            infoLog = new char[logSize + 1];
            glGetProgramInfoLog(componentId, logSize, NULL, infoLog);
        }
    }
    else
    {
        infoLog = new char[logSize + 1];
        glGetShaderInfoLog(componentId, logSize, NULL, infoLog);
    }


    // Open a file to write the error message to.
    fout.open("shader-error.txt");

    // Write out the error message.
    for(i=0; i<logSize; i++)
    {
        fout << infoLog[i];
    }

    // Close the file.
    fout.close();
    
    delete [] infoLog;

    printf("Error building shader, see error log for more info\n");

}

bool Shader::getUniformLoc(std::string name, GLint &loc)
{
    loc = glGetUniformLocation(this->shaderId, name.c_str());
    
    if(loc < 0)
        return false;

    return true;
}

bool Shader::setShaderUniform(std::string name, glm::mat4 val)
{
    return this->setShaderUniform(name, 4, 4, 1, false, glm::value_ptr(val));
}

bool Shader::setShaderUniform(std::string name, glm::vec3 val)
{
    return this->setShaderUniform(name, val.r, val.b, val.g);
}

bool Shader::setShaderUniform(std::string name, glm::vec4 val)
{
    return this->setShaderUniform(name, val.r, val.g, val.b, val.a);
}

bool Shader::setShadderCameraUniforms(glm::mat4 world, glm::mat4 view, glm::mat4 projection)
{
    bool res;
    res = this->setShaderUniform(SHADER_UNIFORM_WORLD, world) &&
          this->setShaderUniform(SHADER_UNIFORM_VIEW, view) &&
          this->setShaderUniform(SHADER_UNIFORM_PROJECTION, projection);

    return res;
}

bool Shader::setShaderUniform(std::string name, GLfloat v0)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform1f(loc, v0);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLfloat v0, GLfloat v1)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform2f(loc, v0, v1);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLfloat v0, GLfloat v1, GLfloat v2)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform3f(loc, v0, v1, v2);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform4f(loc, v0, v1, v2, v3);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLint v0)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform1i(loc, v0);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLint v0, GLint v1)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform2i(loc, v0, v1);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLint v0, GLint v1, GLint v2)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform3i(loc, v0, v1, v2);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLint v0, GLint v1, GLint v2, GLint v3)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform4i(loc, v0, v1, v2, v3);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLuint v0)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform1ui(loc, v0);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLuint v0, GLuint v1)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform2ui(loc, v0, v1);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLuint v0, GLuint v1, GLuint v2)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform3ui(loc, v0, v1, v2);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    glUniform4ui(loc, v0, v1, v2, v3);

    return true;
}

bool Shader::setShaderUniform(std::string name, GLsizei uniSize, GLsizei len, const GLfloat *value)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    switch(uniSize)
    {
    case 1: glUniform1fv(loc, len, value); break;
    case 2: glUniform2fv(loc, len, value);break;
    case 3: glUniform3fv(loc, len, value);break;
    case 4: glUniform4fv(loc, len, value);break;
    default: return false;
    }

    return true;
}

bool Shader::setShaderUniform(std::string name, GLsizei uniSize, GLsizei len, const GLint *value)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    switch(uniSize)
    {
    case 1: glUniform1iv(loc, len, value); break;
    case 2: glUniform2iv(loc, len, value);break;
    case 3: glUniform3iv(loc, len, value);break;
    case 4: glUniform4iv(loc, len, value);break;
    default: return false;
    }

    return true;
}

bool Shader::setShaderUniform(std::string name, GLsizei uniSize, GLsizei len, const GLuint *value)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    switch(uniSize)
    {
    case 1: glUniform1uiv(loc, len, value); break;
    case 2: glUniform2uiv(loc, len, value);break;
    case 3: glUniform3uiv(loc, len, value);break;
    case 4: glUniform4uiv(loc, len, value);break;
    default: return false;
    }

    return true;
}

bool Shader::setShaderUniform(std::string name, GLsizei row, GLsizei column, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    GLint loc;
    if(!this->getUniformLoc(name, loc))
        return false;

    if(count > (row * column))
        return false;

    // TODO: check veracity of this decision tree

    switch(column)
    {
        case 1: 
        {
            switch(row)
            {
            case 1: glUniform1f(loc, value[0]); break;
            case 2: glUniform2f(loc, value[0], value[1]); break;
            case 3: glUniform3f(loc, value[0], value[1], value[2]); break;
            case 4: glUniform4f(loc, value[0], value[1], value[2], value[3]); break;
            default: return false;
            }

            break;
        }
        case 2: 
        {
            switch(column)
            { 
            case 2: glUniformMatrix2fv(loc, count, transpose, value); break;
            case 3: glUniformMatrix2x3fv(loc, count, transpose, value); break;
            case 4: glUniformMatrix2x4fv(loc, count, transpose, value); break;
            default: return false;
            }

            break;
        }
        case 3:
        {
            switch(column)
            {
            case 2: glUniformMatrix3x2fv(loc, count, transpose, value); break;
            case 3: glUniformMatrix3fv(loc, count, transpose, value); break;
            case 4: glUniformMatrix3x4fv(loc, count, transpose, value); break;
            default: return false;
            }

            break;
        }
        case 4: 
        {
            switch(column)
            {
            case 2: glUniformMatrix4x2fv(loc, count, transpose, value);
            case 3: glUniformMatrix4x3fv(loc, count, transpose, value); break;
            case 4: glUniformMatrix4fv(loc, count, transpose, value); break;
            default: return false;
            }

            break;
        }
        default: 
            return false;
    }

    return true;
}