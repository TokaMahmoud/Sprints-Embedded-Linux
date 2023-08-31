#include "MathApp.h"
#include "../IPC_LIBRARY/include/IPC_LIBRARY.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
int main(int argc, char* argv[]) {
    
    
    
   // Create a MessageQueueReceiver instance
    MessageQueueReceiver receiver("key_file.txt", 'A');
  
    // Create an instance of MessageQueueSender (replace with your actual configuration)
    MessageQueueSender ipcSender("key_file.txt", 'A'); // Example parameters

    // Create a MathApp instance with the MessageQueueSender
    MathApp mathApp(ipcSender);

    // Run the MathApp with command-line arguments
    mathApp.run(argc, argv);

    std::string receivedMessage;
    if (receiver.ReceiveMessage(receivedMessage, false)) {
	std::cout << "Received message: " << receivedMessage << std::endl;
    } else {
	std::cout << "No message received" << std::endl;
    }
    
    return 0;
}

