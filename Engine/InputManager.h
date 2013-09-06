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
    bool update();

    void setProcessInput(bool process);

    void parseRawInput(SDL_Event event);
    void attachWindow(SDL_Window *window);

    bool setActiveContext(const std::string &context);

    // keyboard
    bool isActionKeyDown(Action a) const;
    bool wasActionKeyPressed(Action a) const;

    // mouse
    int getMouseHorizontal() const;
    int getMouseRelHorizontal() const;
    int getMouseVertical() const;
    int getMouseRelVertical() const;
    void setMousePosition(int horizontalPos, int vertialPos) const;

private:
    std::map<std::string, std::unique_ptr<InputContext>> contextMap;
    std::string activeContext;
    bool hasContext;
    bool processInput;

    // we don't own these
    const LogSystem &logSys;
    const ConfigParser &config;
    SDL_Window *window;
};

#endif