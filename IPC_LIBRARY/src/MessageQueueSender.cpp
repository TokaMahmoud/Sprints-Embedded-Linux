#include "../include/MessageQueueSender.h"
#include "../include/ErrorHandling.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


MessageQueueSender::MessageQueueSender(const std::string& keyFile, char identifier) {
    // Generate a unique key using ftok
    key_t key = ftok(keyFile.c_str(), identifier);
    if (key == -1) {
        ErrorHandling::ReportError(ErrorCode::IPC_LIBRARY_FTOK_FAILED, "Key file: " + keyFile);
        exit(EXIT_FAILURE);
    }

    // Access the existing message queue using msgget
    m_queue = msgget(key, 0);
    if (m_queue == -1) {
        ErrorHandling::ReportError(ErrorCode::IPC_LIBRARY_MSGGET_FAILED, "Key file: " + keyFile);
        exit(EXIT_FAILURE);
    }
}

MessageQueueSender::~MessageQueueSender() {
    // Nothing specific to clean up
}

bool MessageQueueSender::SendMessage(const std::string& message) {
    // Prepare the message structure
    struct {
        long mtype;
        char mtext[1024];
    } msg;

    msg.mtype = 1; // Message type
    strncpy(msg.mtext, message.c_str(), sizeof(msg.mtext));
    msg.mtext[sizeof(msg.mtext) - 1] = '\0'; // Ensure null-termination

    // Send the message using msgsnd
    if (msgsnd(m_queue, &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) {
        ErrorHandling::ReportError(ErrorCode::IPC_LIBRARY_MSGSND_FAILED, "" );
        return false;
    }

    return true;
}

