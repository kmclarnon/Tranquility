#ifndef _TRANQUILITYINPUT_MANAGER_H_
#define _TRANQUILITYINPUT_MANAGER_H_

#include "Common.h"
#include "InputContext.h"
#include "LogSystem.h"
#include "ConfigParser.h"
#include "Actions.h"

class InputManager
{
public:
    InputManager(const LogSystem &log, const ConfigParser &config);

    bool init();

    void parseRawInput(SDL_Event event);
    void attachWindow(SDL_Window *window);

    bool setActiveContext(const std::string &context);

    // keyboard
    bool isActionKeyDown(Action a) const;

    // mouse
    int getMouseX() const;
    int getMouseRelativeX() const;
    int getMouseY() const;
    int getMouseRelativeY() const;
    void setMousePosition(int x, int y);

private:
    std::map<std::string, std::unique_ptr<InputContext>> contextMap;
    std::string activeContext;
    bool hasContext;

    // we don't own these
    const LogSystem &logSys;
    const ConfigParser &config;
    SDL_Window *window;
};

#endif