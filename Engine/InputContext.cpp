#include "InputContext.h"

InputContext::ActionConversionMap InputContext::acMap = InputContext::initACMap();
InputContext::RawKeyConversionMap InputContext::rkcMap = InputContext::initRKCMap();

InputContext::InputContext(const LogSystem &log) 
    : logSys(log), relX(0), relY(0), absX(0), absY(0), scrollX(0), scrollY(0)
{
    this->actionState.resize(MAX_ACTIONS + 1, false);
}

bool InputContext::init(std::string &contextFile)
{
    std::ifstream ifs(contextFile);
    std::string line;
    int lineIndex = 1;
    bool res = false;

    if(!ifs)
        return false;

    this->logSys.debug("Parsing InputContext file: %s", contextFile.c_str());

    while(std::getline(ifs, line))
    {
        if((line.size() > 0) && (line.at(0) != CONTEXT_COMMENT_CHAR))
        {
            try
            {
                res = this->parseLine(line);
            }
            catch (std::exception* e)
            {
                this->logSys.error("Failed to parse line %i of %s: %s\n", line, contextFile.c_str(), e->what());
                return false;;
            }

            if(!res)
                return false;
        }
    }

    return true;
}

bool InputContext::parseLine(std::string &line)
{
    std::vector<std::string> elems = split(line, '=');
    if(elems.size() != 2)
        return false;

    this->logSys.debug("Mapping %s to %s", elems.at(0).c_str(), elems.at(1).c_str());
    Action a = this->getAction(elems.at(0));
    if(a == Action::MAX_ACTIONS)
        return false;

    RawKeyInput k = this->getRawKeyInput(elems.at(1));
    if(k == RawKeyInput::MAX_KEYS)
        return false;

    this->actionMap.insert(std::pair<RawKeyInput, Action>(k, a));

    return true;
}

Action InputContext::getAction(std::string &action)
{
   std::string a = trim(action);
   auto it = InputContext::acMap.find(action);
   if(it == InputContext::acMap.end())
       return Action::MAX_ACTIONS;

   return it->second;
}

RawKeyInput InputContext::getRawKeyInput(std::string &key)
{
    std::string k = trim(key);
    auto it = InputContext::rkcMap.find(k);
    if(it == InputContext::rkcMap.end())
        return RawKeyInput::MAX_KEYS;

    return it->second;
}

bool InputContext::isActionKeyDown(Action a) const
{
    return this->actionState[a];
}

int InputContext::getMouseX() const
{
    return this->absX;
}

int InputContext::getMouseRelativeX() const
{
    return this->relX;
}

int InputContext::getMouseY() const
{
    return this->absY;
}

int InputContext::getMouseRelativeY() const
{
    return this->relY;
}

void InputContext::parseRawKeyboardInput(SDL_KeyboardEvent event)
{
    auto it = this->actionMap.find((RawKeyInput)event.keysym.sym);
    if(it == this->actionMap.end())
        return;

    this->actionState[it->second] = (event.type == SDL_KEYDOWN);
}

void InputContext::parseRawMouseInput(SDL_MouseButtonEvent event)
{

}

void InputContext::parseRawMouseInput(SDL_MouseWheelEvent event)
{
    this->scrollX = event.x;
    this->scrollY = event.y;
}

void InputContext::parseRawMouseInput(SDL_MouseMotionEvent event)
{
    this->absX = event.x;
    this->absY = event.y;
    this->relX = event.xrel;
    this->relY = event.yrel;
}

InputContext::ActionConversionMap InputContext::initACMap()
{
    ActionConversionMap m;
    m[ACTION_QUIT_STRING] = ACTION_QUIT;
    m[ACTION_FORWARD_STRING] = ACTION_FORWARD;
    m[ACTION_BACKWARD_STRING] = ACTION_BACKWARD;
    m[ACTION_LEFT_STRING] = ACTION_LEFT;
    m[ACTION_RIGHT_STRING] = ACTION_RIGHT;
    return m;
}

InputContext::RawKeyConversionMap InputContext::initRKCMap()
{
    RawKeyConversionMap m;
    m[KEY_LEFT_STRING] = KEY_LEFT;
    m[KEY_RIGHT_STRING] = KEY_RIGHT;
    m[KEY_UP_STRING] = KEY_UP;
    m[KEY_DOWN_STRING] = KEY_DOWN;
    m[KEY_1_STRING] = KEY_1;
    m[KEY_2_STRING] = KEY_2;
    m[KEY_ESC_STRING] = KEY_ESC;
    return m;
}