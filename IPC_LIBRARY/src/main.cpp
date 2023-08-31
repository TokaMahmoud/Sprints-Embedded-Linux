#include "../include/IPC_LIBRARY.h"

#include <iostream>

int main() {
    // Create a MessageQueueReceiver instance
    MessageQueueReceiver receiver("./keyFile", 'A');
    	
    // Create a MessageQueueSender instance
    MessageQueueSender sender("./keyFile", 'A');



    std::string messageToSend = "Hello, Receiver!";
    if (sender.SendMessage(messageToSend)) {
	std::cout << "Message sent successfully: " << messageToSend << std::endl;
    } else {
	std::cout << "Failed to send message" << std::endl;
    }

    std::string receivedMessage;
    if (receiver.ReceiveMessage(receivedMessage, false)) {
	std::cout << "Received message: " << receivedMessage << std::endl;
    } else {
	std::cout << "No message received" << std::endl;
    }


   return 0;
}

