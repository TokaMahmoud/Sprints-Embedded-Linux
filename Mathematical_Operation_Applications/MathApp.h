#ifndef MATHAPP_H
#define MATHAPP_H

#include <string>
#include <boost/log/trivial.hpp>  // Include Boost Logging header
#include "../IPC_LIBRARY/include/MessageQueueSender.h"

class MathApp {
public:
    MathApp(MessageQueueSender& sender);

    void run(int argc, char* argv[]);
    void printHelp();

private:
    MessageQueueSender& ipcSender;
};

#endif // MATHAPP_H

