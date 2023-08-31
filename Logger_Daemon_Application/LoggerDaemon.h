#ifndef LOGGER_DAEMON_H
#define LOGGER_DAEMON_H

#include <string>
#include <map>
#include <thread>
#include "../IPC_LIBRARY/include/MessageQueueReceiver.h"

struct AppConfig {
    char identifier;
    std::string keyFile;
};

class LoggerDaemon {
public:
    explicit LoggerDaemon(const std::string& configFile);
    void Run();


    void SetupLogger();
    void ParseConfigFile();
    void HandleLogMessages(const std::string& appName, const std::string& keyFile, char identifier);

    std::string m_configFile;
    std::map<std::string, AppConfig> m_appConfig;
    std::map<std::string, MessageQueueReceiver> m_messageQueues;
};

#endif // LOGGER_DAEMON_H

