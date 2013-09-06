#include "InputManager.h"

InputManager::InputManager(const LogSystem &log, const ConfigParser &config)
    : logSys(log), config(config), hasContext(false), window(nullptr), 
    processInput(false)
{

}

bool InputManager::init()
{
    std::unique_ptr<InputContext> c = std::unique_ptr<InputContext>(new InputContext(this->logSys));
    //test context
    std::string context = "fps.ctx";
    if(!c->init(context))
    {
        logSys.error("Failed to load input context: %s", context.c_str());
        return false;
    }

    this->contextMap.insert(std::make_pair(context, std::move(c)));

    if(this->contextMap.size() == 1)
        return this->setActiveContext(context);

    return true;
}

bool InputManager::cleanup()
{
    auto it = this->contextMap.find(this->activeContext);
    if(it == this->contextMap.end())
    {
        this->logSys.error("Attempted to update input manager without context");
        return false;
    }

    it->second->clearRelative();

    return true;
}

void InputManager::setProcessInput(bool process)
{
    SDL_SetWindowGrab(this->window, (SDL_bool)process);
    this->processInput = process;
}

void InputManager::attachWindow(SDL_Window *window)
{
    this->window = window;
}

void InputManager::parseRawInput(SDL_Event event)
{
    if(!this->hasContext)
    {
        this->logSys.error("Input manager has no context");
        return;
    }

    // check if we're even supposed to be handling this input
    if(!this->processInput)
        return;

    switch(event.type)
    {
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        this->contextMap.find(this->activeContext)->second->parseRawKeyboardInput(event.key);
        break;
    case SDL_MOUSEMOTION:
        this->contextMap.find(this->activeContext)->second->parseRawMouseInput(event.motion);
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        this->contextMap.find(this->activeContext)->second->parseRawMouseInput(event.button);
        break;
    case SDL_MOUSEWHEEL:
        this->contextMap.find(this->activeContext)->second->parseRawMouseInput(event.wheel);
        break;
    default: // do nothing
        return;
    }
}

bool InputManager::setActiveContext(const std::string &context)
{
    auto it = this->contextMap.find(context);
    
    if(it == this->contextMap.end())
        return false;

    this->activeContext = context;
    this->hasContext = true;
    return true;
}

bool InputManager::isActionKeyDown(Action a) const
{
    assert(this->hasContext);
    return this->contextMap.find(this->activeContext)->second->isActionKeyDown(a);
}

bool InputManager::wasActionKeyPressed(Action a) const
{
    assert(this->hasContext);
    return this->contextMap.find(this->activeContext)->second->wasActionKeyPressed(a);
}

int InputManager::getMouseHorizontal() const
{
    assert(this->hasContext);
    return this->contextMap.find(this->activeContext)->second->getMouseX();
}

int InputManager::getMouseRelHorizontal() const
{
    assert(this->hasContext);
    return this->contextMap.find(this->activeContext)->second->getMouseRelativeX();
}

int InputManager::getMouseVertical() const
{
    assert(this->hasContext);
    return this->contextMap.find(this->activeContext)->second->getMouseY();
}

int InputManager::getMouseRelVertical() const
{
    assert(this->hasContext);
    return this->contextMap.find(this->activeContext)->second->getMouseRelativeY();
}

void InputManager::setMousePosition(int horizontalPos, int verticalPos) const
{
    if(this->window && this->processInput)
    {
        SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
        SDL_WarpMouseInWindow(this->window, horizontalPos, verticalPos);
        SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
    }
}