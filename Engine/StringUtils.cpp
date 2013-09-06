#include "StringUtils.h"

std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

// trim from the left
std::string& ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from the right
std::string& rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string& trim(std::string &s) {
    return ltrim(rtrim(s));
}

// process a string into a path directory and filename
StringPathUPtr processPath(std::string &path)
{
    StringPathUPtr s = StringPathUPtr(new StringPath);
    std::string::size_type slashIndex = path.find_last_of("/");
    if(slashIndex == std::string::npos)
    {
        s->path = "";
        s->filename = path;
    }
    else if(slashIndex == 0)
    {
        s->path = "/";
        s->filename = (1, path.length());
    }
    else
    {
        s->path = path.substr(0, slashIndex);
        s->filename = path.substr(slashIndex + 1, path.length());
    }

    return s;
}