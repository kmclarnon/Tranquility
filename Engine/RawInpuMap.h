#ifndef _TRANQUILITY_RAW_INPUT_MAP_H_
#define _TRANQUILITY_RAW_INPUT_MAP_H_

const static std::string KEY_LEFT_STRING = "KEY_LEFT";
const static std::string KEY_RIGHT_STRING = "KEY_RIGHT";
const static std::string KEY_UP_STRING = "KEY_UP";
const static std::string KEY_DOWN_STRING = "KEY_DOWN";
const static std::string KEY_1_STRING = "KEY_1";
const static std::string KEY_2_STRING = "KEY_2";

const static char CONTEXT_COMMENT_CHAR = '#';

typedef enum RawKeyInput
{
    KEY_LEFT = SDLK_LEFT,
    KEY_RIGHT = SDLK_RIGHT,
    KEY_UP = SDLK_UP,
    KEY_DOWN = SDLK_DOLLAR,
    KEY_1 = SDLK_1,
    KEY_2 = SDLK_2,
    //KEY_3 = SDLK_3,
    //KEY_4 = SDLK_4,
    //KEY_5 = SDLK_5,
    //KEY_6 = SDLK_6,
    //KEY_7 = SDLK_7,
    //KEY_8 = SDLK_8,
    //KEY_9 = SDLK_9,
    //KEY_10 = SDLK_0
    MAX_KEYS
};

#endif