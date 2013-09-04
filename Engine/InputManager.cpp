#include "InputManager.h"

InputManager::InputManager(const LogSystem &log, const ConfigParser &config)
    : logSys(log), config(config), hasContext(false)
{

}

bool InputManager::init()
{
    InputContext c = InputContext();
    //test string
    std::string context = "fps.ctx";
    if(!c.init(context))
    {
        logSys.error("Failed to load input context: %s", context.c_str());
        return false;
    }

    this->contextMap.insert(std::make_pair(context, c));

    if(this->contextMap.size() == 1)
        return this->setActiveContext(context);

    return true;
}

void InputManager::parseRawInput(SDL_Event event)
{
    if(!this->hasContext)
    {
        this->logSys.error("Input manager has no context");
        return;
    }

    switch(event.type)
    {
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        this->contextMap.find(this->activeContext)->second.parseRawKeyboardInput(event.key);
        break;
    case SDL_MOUSEMOTION:
        this->contextMap.find(this->activeContext)->second.parseRawMouseInput(event.motion);
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        this->contextMap.find(this->activeContext)->second.parseRawMouseInput(event.button);
        break;
    case SDL_MOUSEWHEEL:
        this->contextMap.find(this->activeContext)->second.parseRawMouseInput(event.wheel);
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
    return this->contextMap.find(this->activeContext)->second.isActionKeyDown(a);
}