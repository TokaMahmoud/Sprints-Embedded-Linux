#ifndef MESSAGE_QUEUE_SENDER_H
#define MESSAGE_QUEUE_SENDER_H

#include <string>

class MessageQueueSender {
public:
    MessageQueueSender(const std::string& keyFile, char identifier);
    ~MessageQueueSender();

    bool SendMessage(const std::string& message);

private:
    int m_queue; // Message queue identifier
};

#endif // MESSAGE_QUEUE_SENDER_H

