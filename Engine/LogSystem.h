#ifndef _TRILLEK_LOG_SYSTEM_H_
#define _TRILLEK_LOG_SYSTEM_H_

#include "Common.h"

class LogSystem
{
private:
    enum LOG_TYPE
    {
        TYPE_LOG,
        TYPE_WARNING,
        TYPE_ERROR,
        TYPE_DEBUG
    };

public:
    LogSystem(std::string logFile);

    bool init();

    void log(const char *fmt, ...) const;
    void warning(const char *fmt, ...) const;
    void error(const char *fmt, ...) const;
    void debug(const char *fmt, ...) const;

private:
    void printFormatted(const char *label, const char *fmt, va_list args) const;
    void printTime() const;

private:
    FILE logFile;
    std::string logFilename;
};

#endif