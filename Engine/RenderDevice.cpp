#include "RenderDevice.h"

RenderDevice::RenderDevice(LogSystem &log) : logSys(log)
{
    this->device = nullptr;
    this->shader = nullptr;
}

bool RenderDevice::init(bool vsync, int width, int height, SDL_Window *window)
{
    // initialize our graphics device
    this->device = new GLDevice(this->logSys, window);
    if(!this->device->init(vsync))
    {
        printf("Failed to initialize graphics device\n");
        return false;
    }

    // initialize our shader
    this->shader = new Shader(this->logSys);
    this->shader->addStage(GL_VERTEX_SHADER, "shader.vert");
    this->shader->addStage(GL_FRAGMENT_SHADER, "shader.frag");
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

    /*
    // initialize our camera
    this->camera = new Camera(45.0f, width, height, 0.1f, 1000.0f);
    this->camera->setPosition(0.0f, 0.0f, -10.0f);

    // set up our light
    this->light = Light();
    this->light.setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    this->light.setLightDirection(1.0f, 0.0f, 0.0f);
    this->light.setAmbientLight(0.15f, 0.15f, 0.15f, 1.0f);

    // load our model
    this->mesh.LoadMesh("Models/cube.obj");
    */

    this->scene.init(width, height);

    return true;
}

bool RenderDevice::update()
{
    static float rotation = 0.0f;
    glm::mat4 worldMatrix = glm::mat4();

    // clear our device for the new scene
    this->device->beginScene(0.5f, 0.5f, 0.5f, 1.0f);

    // Render code goes here
    this->shader->useShader();

    // update our scene (temp)
    this->scene.update();

    // Update the rotation variable each frame.
    rotation += 0.0174532925f * 1.0f;
    if(rotation > 360.0f)
    {
        rotation -= 360.0f;
    }

    // rotate our world matrix
    worldMatrix = glm::mat4(glm::vec4(cosf(rotation), 0.0, sinf(rotation), 0.0),
                            glm::vec4(0.0, 1.0, 0.0, 0.0),
                            glm::vec4(-sinf(rotation), 0.0, cos(rotation), 0.0),
                            glm::vec4(0.0, 0.0, 0.0, 1.0));

    // set our camera matricies
    if(!this->shader->setShadderCameraUniforms(worldMatrix, this->scene.getCamera().getViewMatrix(), this->scene.getCamera().getProjectionMatrix()))
        return false;

    // set our light data
    if(!this->shader->setShaderUniform(SHADER_UNIFORM_LIGHT_DIR, this->scene.getLight().getLightDirection()))
        return false;

    if(!this->shader->setShaderUniform(SHADER_UNIFORM_DIFFUSE_COLOR, this->scene.getLight().getDiffuseColor()))
        return false;

    if(!this->shader->setShaderUniform(SHADER_UNIFORM_AMBIENT, this->scene.getLight().getAmbientLight()))
        return false;

    // set texture unit
    if(!this->shader->setShaderUniform(SHADER_UNIFORM_TEXTURE, 0))
        return false;

    this->scene.getMesh().Render();

    // present the rendered screen
    this->device->endScene();

    return true;
}

void RenderDevice::shutdown()
{
    // destroy our graphics device
    if(this->device)
    {
        this->device->shutdown();
        delete this->device;
    }

    // destroy our shader manager
    if(this->shader)
    {
        this->shader->shutdown();
        delete this->shader;
    }
}

