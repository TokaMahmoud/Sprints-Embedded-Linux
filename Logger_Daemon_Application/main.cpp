#include <iostream>
#include <map>
#include "LoggerDaemon.h"
#include "../IPC_LIBRARY/include/MessageQueueSender.h"

int main() {
    std::string configFile = "/etc/logger_config.txt"; // Use the correct path to your configuration file
    LoggerDaemon loggerDaemon(configFile);

    // Access m_appConfig and create message queues for each application
    for (const auto& entry : loggerDaemon.m_appConfig) {
        std::string keyFile = entry.second.keyFile;
        char identifier = entry.second.identifier;

        // Create the message queue sender
        MessageQueueSender sender(keyFile, identifier);

        // You can add additional setup logic for each application if needed
        std::cout << "Created message queue for application: " << entry.first << std::endl;
    }

    // Start the logger daemon and begin receiving logs
    loggerDaemon.Run();

    return 0;
}


/*g++ -std=c++11     ../IPC_LIBRARY/src/ErrorHandling.cpp     ../IPC_LIBRARY/src/MessageQueueSender.cpp ../IPC_LIBRARY/src/MessageQueueReceiver.cpp     MathApp.cpp main.cpp     -o math_app     -DBOOST_LOG_DYN_LINK     -lboost_log_setup     -lboost_log     -lboost_thread     -lpthread*/

