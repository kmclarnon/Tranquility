#include "RenderDevice.h"

RenderDevice::RenderDevice(const LogSystem &log, SceneManager &sceneManager, std::string shaderDir) : logSys(log), sceneManager(sceneManager), shaderDir(shaderDir)
{

}

bool RenderDevice::init(bool vsync, int width, int height, SDL_Window *window)
{
    // initialize our graphics device
    this->device = std::unique_ptr<GLDevice>(new GLDevice(this->logSys, window));
    if(!this->device->init(vsync))
    {
        printf("Failed to initialize graphics device\n");
        return false;
    }

    // initialize our shader
    this->shader = std::unique_ptr<Shader>(new Shader(this->logSys));
    this->shader->addStage(GL_VERTEX_SHADER, this->shaderDir + "shader.vert");
    this->shader->addStage(GL_FRAGMENT_SHADER, this->shaderDir + "shader.frag");
    // vertex attributes
    this->shader->addAttribute(SHADER_IN_POSITION);
    this->shader->addAttribute(SHADER_IN_TEXCOORD);
    this->shader->addAttribute(SHADER_IN_NORMAL);

    // view uniforms
    this->shader->addUniform(SHADER_UNIFORM_WORLD);
    this->shader->addUniform(SHADER_UNIFORM_VIEW);
    this->shader->addUniform(SHADER_UNIFORM_PROJECTION);

    // light/texture uniforms
    this->shader->addUniform(SHADER_UNIFORM_TEXTURE);
    this->shader->addUniform(SHADER_UNIFORM_LIGHT_DIR);
    this->shader->addUniform(SHADER_UNIFORM_DIFFUSE_COLOR);
    this->shader->addUniform(SHADER_UNIFORM_AMBIENT);

    if(!this->shader->init())
    {
        printf("Failed to initialize shader\n");
        return false;
    }

    //this->scene.init(width, height);

    return true;
}

bool RenderDevice::update()
{
    static float rotation = 0.0f;

    // clear our device for the new scene
    this->device->beginScene(0.5f, 0.5f, 0.5f, 1.0f);

    // Render code goes here
    this->shader->useShader();

    // get our renderable scene
    Scene &s = sceneManager.getActiveScene();

    // set our camera matricies
    if(!this->shader->setShadderCameraUniforms(s.getModel().getModelMatrix(), s.getCamera().getViewMatrix(), s.getCamera().getProjectionMatrix()))
        return false;

    // set our light data
    if(!this->shader->setShaderUniform(SHADER_UNIFORM_LIGHT_DIR, s.getLight().getLightDirection()))
        return false;

    if(!this->shader->setShaderUniform(SHADER_UNIFORM_DIFFUSE_COLOR, s.getLight().getDiffuseColor()))
        return false;

    if(!this->shader->setShaderUniform(SHADER_UNIFORM_AMBIENT, s.getLight().getAmbientLight()))
        return false;

    // set texture unit
    if(!this->shader->setShaderUniform(SHADER_UNIFORM_TEXTURE, 0))
        return false;

    s.getModel().render();

    // present the rendered screen
    this->device->endScene();

    return true;
}

