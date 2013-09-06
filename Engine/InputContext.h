#ifndef _TRANQUILITY_INPUT_CONTEXT_H_
#define _TRANQUILITY_INPUT_CONTEXT_H_

#include "Common.h"
#include "Actions.h"
#include "RawInputMap.h"
#include "StringUtils.h"
#include "LogSystem.h"

class InputContext
{
private:
    typedef std::map<std::string, Action> ActionConversionMap;
    typedef std::map<std::string, RawKeyInput> RawKeyConversionMap;

public:
    InputContext(const LogSystem &log);

    bool init(std::string &context);
    void calcMouse();
    
    // keyboard
    bool isActionKeyDown(Action a) const;
    bool wasActionKeyPressed(Action a) const;

    // mouse
    int getMouseX() const;
    int getMouseRelativeX() const;
    int getMouseY() const;
    int getMouseRelativeY() const;

    // event processing
    void parseRawKeyboardInput(SDL_KeyboardEvent event);
    void parseRawMouseInput(SDL_MouseButtonEvent event);
    void parseRawMouseInput(SDL_MouseWheelEvent event);
    void parseRawMouseInput(SDL_MouseMotionEvent event);

private:
    static ActionConversionMap initACMap();
    static RawKeyConversionMap initRKCMap();
    bool parseLine(std::string &line);
    Action getAction(std::string &action);
    RawKeyInput getRawKeyInput(std::string &key);

private:
    // keyboard state
    std::vector<bool> actionState;
    std::vector<bool> actionStateNew;
    std::map<RawKeyInput, Action> actionMap;

    // context key mapping
    static ActionConversionMap acMap;
    static RawKeyConversionMap rkcMap;

    // mouse state
    int relX, relY;
    int absX, absY;
    int lastAbsX, lastAbsY;
    int scrollX, scrollY;

    // we don't own this
    const LogSystem &logSys;
};

#endif