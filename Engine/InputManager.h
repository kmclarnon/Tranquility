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

    bool setActiveContext(const std::string &context);
    bool isActionKeyDown(Action a) const;

private:
    std::map<std::string, InputContext> contextMap;
    std::string activeContext;
    bool hasContext;

    // we don't own these
    const LogSystem &logSys;
    const ConfigParser &config;
};

#endif