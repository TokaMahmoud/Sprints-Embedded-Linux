#include "LoggerDaemon.h"
#include "../IPC_LIBRARY/include/ErrorHandling.h"
#include "../IPC_LIBRARY/include/MessageQueueReceiver.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_multifile_backend.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/setup/formatting_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <map>

namespace logging = boost::log;

LoggerDaemon::LoggerDaemon(const std::string& configFile) : m_configFile(configFile) {
    SetupLogger();
    ParseConfigFile();
}

void LoggerDaemon::Run() {
    for (const auto& entry : m_appConfig) {
        m_messageQueues[entry.first] = MessageQueueReceiver(entry.second.keyFile, entry.second.identifier);
    }

    // Now handle log messages from each application
    for (const auto& entry : m_appConfig) {
        std::thread(&LoggerDaemon::HandleLogMessages, this, entry.first, entry.second.keyFile, entry.second.identifier).detach();
    }

    // TODO: Add logic to send logs through Ethernet
}

void LoggerDaemon::SetupLogger() {
    // Set up log format
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");
    logging::add_common_attributes();

    // Set up log rotation
    typedef logging::sinks::text_multifile_backend BackendType;
    boost::shared_ptr<BackendType> backend = boost::make_shared<BackendType>();
    backend->set_file_name_composer(
        logging::sinks::file::as_file_name_composer(
            logging::keywords::file_name = "logs/%Y-%m-%d_%5N.log",
            logging::keywords::rotation_size = 1 * 1024
        )
    );

    // Add sink with rotation
    typedef logging::sinks::synchronous_sink<BackendType> SinkType;
    boost::shared_ptr<SinkType> sink(new SinkType(backend));
    logging::core::get()->add_sink(sink);
}

void LoggerDaemon::ParseConfigFile() {
    std::ifstream file(m_configFile);
    std::string line;

    while (std::getline(file, line)) {
        std::string appName;
        char identifier;
        std::string keyFile;

        // Parse each line in the config file, e.g., "App1:A:keyfile.txt"
        size_t pos1 = line.find(':');
        size_t pos2 = line.find(':', pos1 + 1);

        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            appName = line.substr(0, pos1);
            identifier = line[pos1 + 1];
            keyFile = line.substr(pos2 + 1);

            m_appConfig[appName] = {identifier, keyFile};
        }
    }
}

void LoggerDaemon::HandleLogMessages(const std::string& appName, const std::string& keyFile, char identifier) {
    MessageQueueReceiver receiver(keyFile, identifier);
    std::string logMessage;

    while (true) {
        if (receiver.ReceiveMessage(logMessage, true)) {
            size_t separatorPos = logMessage.find(':');
            if (separatorPos != std::string::npos) {
                std::string extractedAppName = logMessage.substr(0, separatorPos);
                std::string message = logMessage.substr(separatorPos + 1);

                std::string modifiedLog = "[" + extractedAppName + "] " + message;

                BOOST_LOG_TRIVIAL(info) << modifiedLog;
                // TODO: Write log to file and send through Ethernet
            } else {
                BOOST_LOG_TRIVIAL(info) << logMessage;
                // TODO: Write log to file and send through Ethernet
            }
        }
    }
}

