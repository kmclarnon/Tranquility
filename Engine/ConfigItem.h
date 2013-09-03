#ifndef _TRILLEK_CONFIG_ITEM_H_
#define _TRILLEK_CONFIG_ITEM_H_

#include "Common.h"

class ConfigItem
{
public:
    ConfigItem(std::string val);

    int asInt();
    float asFloat();
    bool asBool();
    std::string asString();

private:
    std::string val;
};

#endif