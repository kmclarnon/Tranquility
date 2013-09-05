#ifndef _TRANQUILITY_INPUT_CONTEXT_H_
#define _TRANQUILITY_INPUT_CONTEXT_H_

#include "Common.h"
#include "Actions.h"
#include "RawInputMap.h"
#include "StringUtils.h"

class InputContext
{
private:
    typedef std::map<std::string, Action> ActionConversionMap;
    typedef std::map<std::string, RawKeyInput> RawKeyConversionMap;

public:
    InputContext();

    bool init(std::string &context);
    bool isActionKeyDown(Action a) const;

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
    std::vector<bool> actionState;
    std::map<RawKeyInput, Action> actionMap;
    static ActionConversionMap acMap;
    static RawKeyConversionMap rkcMap;
};

#endif