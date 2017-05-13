/*
 * Log.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <iostream>
#include <Log.h>

namespace Flix {

Log* instance = new Log();

Log::Log():
    maxLevel(LogLevel::DEBUG)
{
}

Log::~Log()
{
}

void Log::log(LogLevel level, const std::string& message)
{
    if (level > maxLevel) {
        return;
    }

    std::cout << "[" << level << "] " << message << std::endl;
}

void Log::error(const std::string& message)
{
    log(LogLevel::ERROR, message);
}

void Log::warning(const std::string& message)
{
    log(LogLevel::WARNING, message);
}

void Log::notice(const std::string& message)
{
    log(LogLevel::NOTICE, message);
}

void Log::info(const std::string& message)
{
    log(LogLevel::INFO, message);
}

void Log::debug(const std::string& message)
{
    log(LogLevel::DEBUG, message);
}

Log* Log::getInstance(void) {
    return instance;
}

std::ostream& operator<<(std::ostream& stream, LogLevel level)
{
    switch (level) {
    case LogLevel::ERROR:
        stream << "E";
        break;
    case LogLevel::WARNING:
        stream << "W";
        break;
    case LogLevel::NOTICE:
        stream << "N";
        break;
    case LogLevel::INFO:
        stream << "I";
        break;
    case LogLevel::DEBUG:
        stream << "D";
        break;
    default:
        stream << "?";
        break;
    }
    return stream;
}

} /* namespace Flix */
