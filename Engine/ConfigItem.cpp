#include "ConfigItem.h"

ConfigItem::ConfigItem(std::string val) : val(val)
{
}

int ConfigItem::asInt()
{
    return std::stoi(this->val);
}

float ConfigItem::asFloat()
{
    return std::stof(this->val);
}

bool ConfigItem::asBool()
{ 
    return this->val.at(0) != '0';
}

std::string ConfigItem::asString()
{
    return this->val;
}