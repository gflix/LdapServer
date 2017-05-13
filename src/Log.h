/*
 * Log.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include <ostream>
#include <sstream>
#include <string>

namespace Flix {

enum class LogLevel {
    ERROR = 0,
    WARNING = 1,
    NOTICE = 2,
    INFO = 3,
    DEBUG = 4,
};

std::ostream& operator<<(std::ostream& stream, LogLevel level);

class Log {
public:
    Log();
    virtual ~Log();

    void log(LogLevel level, const std::string& message);
    void error(const std::string& message);
    void warning(const std::string& message);
    void notice(const std::string& message);
    void info(const std::string& message);
    void debug(const std::string& message);

    static Log* getInstance(void);

private:
    LogLevel maxLevel;
};

#define LOG_ERROR(message) { std::stringstream stream; stream << message; Flix::Log::getInstance()->error(stream.str()); }
#define LOG_WARNING(message) { std::stringstream stream; stream << message; Flix::Log::getInstance()->warning(stream.str()); }
#define LOG_NOTICE(message) { std::stringstream stream; stream << message; Flix::Log::getInstance()->notice(stream.str()); }
#define LOG_INFO(message) { std::stringstream stream; stream << message; Flix::Log::getInstance()->info(stream.str()); }
#define LOG_DEBUG(message) { std::stringstream stream; stream << message; Flix::Log::getInstance()->debug(stream.str()); }

} /* namespace Flix */

#endif /* SRC_LOG_H_ */
