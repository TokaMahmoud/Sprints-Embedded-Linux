#ifndef MESSAGE_QUEUE_RECEIVER_H
#define MESSAGE_QUEUE_RECEIVER_H

#include <string>

class MessageQueueReceiver {
public:
    MessageQueueReceiver(const std::string& keyFile, char identifier);
    ~MessageQueueReceiver();

    bool ReceiveMessage(std::string& message, bool isBlocking);

private:
    int m_queue; // Message queue identifier
};

#endif // MESSAGE_QUEUE_RECEIVER_H

