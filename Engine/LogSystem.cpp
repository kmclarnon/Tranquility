#include "LogSystem.h"

LogSystem::LogSystem(std::string logFile)
{
    this->logFilename = logFile;
}

bool LogSystem::init()
{
    //this->logFile = fopen(this->logFilename.c_str());
    return true;
}


void LogSystem::log(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    this->printFormatted("L", format, args);
    va_end(args);
}

void LogSystem::warning(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    this->printFormatted("W", format, args);
    va_end(args);
}

void LogSystem::error(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    this->printFormatted("E", format, args);
    va_end(args);
}

void LogSystem::debug(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    this->printFormatted("D", format, args);
    va_end(args);
}

void LogSystem::printFormatted(const char *label, const char *format, va_list args)
{
    this->printTime();

    printf(" %s: ", label);

    vprintf(format, args);

    //vprintf(this->logFile, format, args);

    printf("\n");
}

void LogSystem::printTime()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    printf("%02d:%02d", st.wHour, st.wMinute);
}