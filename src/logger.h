#pragma once

#include "./include.h"

enum LogType {
    Message,
    Warning,
    Error,
    Critical,
    ALL
};
std::string log_type_string(LogType type) {
    switch(type) {
        case LogType::Message: return "Message";
        case LogType::Warning: return "Warning";
        case LogType::Error: return "Error";
        case LogType::Critical: return "Critical";
        case LogType::ALL: return "ALL";
    }
    return "Unknown";
};

class Logger {
    private:
        std::map<LogType, std::vector<std::string>> LogData;
        void PrintLogs(std::string type, std::vector<std::string> messages) {
            for(size_t i = 0; i < messages.size(); i++) {
                std::cout << "[" << type << " " << i + 1 << "]: " << messages[i] << "\n";
            }
            std::cout << std::endl;
        }
    public:
        Logger() {};
        void Log(LogType type, std::string message) {
            LogData[type].push_back(message);
        };
        void PrintMessages(LogType type) {
            const int LogTypeCount = 4;
            const LogType LogTypes[LogTypeCount] = {
                LogType::Message,
                LogType::Warning,
                LogType::Error,
                LogType::Critical
            };
            if(type == LogType::ALL) {
                for(int i = 0; i < LogTypeCount; i++) PrintLogs(log_type_string(LogTypes[i]), LogData[LogTypes[i]]);
            } else PrintLogs(log_type_string(type), LogData[type]);
        };
        bool any(LogType type) {
            const int LogTypeCount = 4;
            const LogType LogTypes[LogTypeCount] = {
                LogType::Message,
                LogType::Warning,
                LogType::Error,
                LogType::Critical
            };
            bool has = true;
            if(type == LogType::ALL) {
                for(int i = 0; i < LogTypeCount; i++) has = has || LogData[LogTypes[i]].size() > 0;
                return has;
            }
            return LogData[type].size() > 0;
        };
        void clear() {
            const int LogTypeCount = 4;
            const LogType LogTypes[LogTypeCount] = {
                LogType::Message,
                LogType::Warning,
                LogType::Error,
                LogType::Critical
            };
            for(int i = 0; i < LogTypeCount; i++) LogData[LogTypes[i]].clear();
        }
};