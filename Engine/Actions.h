#ifndef _TRANQUILITY_ACTIONS_H_
#define _TRANQUILITY_ACTIONS_H_

const static std::string ACTION_QUIT_STRING = "ACTION_QUIT";
const static std::string ACTION_FORWARD_STRING = "ACTION_FORWARD";
const static std::string ACTION_BACKWARD_STRING = "ACTION_BACKWARD";
const static std::string ACTION_LEFT_STRING = "ACTION_LEFT";
const static std::string ACTION_RIGHT_STRING = "ACTION_RIGHT";

typedef enum Action
{
    ACTION_QUIT,
    ACTION_FORWARD,
    ACTION_BACKWARD,
    ACTION_LEFT,
    ACTION_RIGHT,
    MAX_ACTIONS
};

#endif