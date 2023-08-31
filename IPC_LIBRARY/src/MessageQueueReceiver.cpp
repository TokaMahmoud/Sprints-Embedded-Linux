#include "../include/MessageQueueReceiver.h"
#include "../include/ErrorHandling.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


MessageQueueReceiver::MessageQueueReceiver(const std::string& keyFile, char identifier) {
    // Generate a unique key using ftok
    key_t key = ftok(keyFile.c_str(), identifier);
    if (key == -1) {
        ErrorHandling::ReportError(ErrorCode::IPC_LIBRARY_FTOK_FAILED, "Key file: " + keyFile);
        exit(EXIT_FAILURE);
    }

    // Create or get the message queue using msgget
    m_queue = msgget(key, IPC_CREAT | 0666);
    if (m_queue == -1) {
         ErrorHandling::ReportError(ErrorCode::IPC_LIBRARY_MSGGET_FAILED, "Key file: " + keyFile);
        exit(EXIT_FAILURE);
    }
}

MessageQueueReceiver::~MessageQueueReceiver() {
    // Delete the message queue
    if (msgctl(m_queue, IPC_RMID, nullptr) == -1) {
        ErrorHandling::ReportError(ErrorCode::IPC_LIBRARY_MSGCTL_FAILED, "");
    }
}

bool MessageQueueReceiver::ReceiveMessage(std::string& message, bool isBlocking) {
    long messageType = 1; // Message type

    // Receive message using msgrcv
    struct {
        long mtype;
        char mtext[1024];
    } msg;

    int flags = 0;
    if (!isBlocking) {
        flags |= IPC_NOWAIT;
    }

    ssize_t bytesRead = msgrcv(m_queue, &msg, sizeof(msg.mtext), messageType, flags);

    if (bytesRead >= 0) {
        msg.mtext[bytesRead] = '\0'; // Null-terminate the received message
        message = msg.mtext;
        return true;
    } else {
        if (errno == ENOMSG) {
            // No message available if non-blocking
            return false;
        } else {
            ErrorHandling::ReportError(ErrorCode::IPC_LIBRARY_MSGRCV_FAILED, "" );
            return false;
        }
    }
}

