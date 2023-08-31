#include "MathApp.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
MathApp::MathApp(MessageQueueSender& sender) : ipcSender(sender) {
    // Configure Boost Logging to save logs to a file and console
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
    boost::log::add_file_log(
        boost::log::keywords::file_name = "mathapp_log_%N.log",  // File name pattern
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,   // Max file size
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),  // Rotate at midnight
        boost::log::keywords::format = "[%TimeStamp%] [%Severity%] %Message%"
    );
    
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
}

void MathApp::run(int argc, char* argv[]) {
    if (argc < 2) {
        BOOST_LOG_TRIVIAL(error) << "Error: Insufficient arguments provided.";
        printHelp();
        return;
    }

    std::string arg1 = argv[1];

    if (arg1 == "--help") {
        printHelp();
        return;
    }

    if (argc < 4) {
        BOOST_LOG_TRIVIAL(error) << "Error: Insufficient arguments provided.";
        return;
    }

    std::string operation = arg1;
    double operand1, operand2;

    std::istringstream(argv[2]) >> operand1;
    std::istringstream(argv[3]) >> operand2;

    double result = 0.0;

    if (operation == "add") {
        result = operand1 + operand2;
    } else if (operation == "subtract") {
        result = operand1 - operand2;
    } else if (operation == "multiply") {
        result = operand1 * operand2;
    } else if (operation == "divide") {
        if (operand2 != 0) {
            result = operand1 / operand2;
        } else {
            BOOST_LOG_TRIVIAL(error) << "Error: Division by zero is not allowed.";
            return;
        }
    } else {
        BOOST_LOG_TRIVIAL(error) << "Error: Unknown operation '" << operation << "'";
        printHelp();
        return;
    }

    BOOST_LOG_TRIVIAL(info) << "Result: " << std::setprecision(4) << result;

    // Log the operation and operands
    std::string logMessage = "Operation: " + operation + ", Operand1: " + std::to_string(operand1) +
                             ", Operand2: " + std::to_string(operand2);

    // Send log message using the MessageQueueSender
    ipcSender.SendMessage(logMessage);
}

void MathApp::printHelp() {
    BOOST_LOG_TRIVIAL(info) << "Mathematical Operation Application";
    BOOST_LOG_TRIVIAL(info) << "Usage: mathapp <operation> <operand1> <operand2>";
    BOOST_LOG_TRIVIAL(info) << "Supported operations: add, subtract, multiply, divide";
}

