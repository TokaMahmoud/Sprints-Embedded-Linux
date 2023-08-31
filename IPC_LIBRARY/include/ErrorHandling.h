#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <string>

enum class ErrorCode {
    IPC_LIBRARY_OK,
    IPC_LIBRARY_FTOK_FAILED,
    IPC_LIBRARY_MSGGET_FAILED,
    IPC_LIBRARY_MSGCTL_FAILED,
    IPC_LIBRARY_MSGRCV_FAILED,
    IPC_LIBRARY_MSGSND_FAILED,
    IPC_LIBRARY_UNKNOWN_ERROR, 
};

class ErrorHandling {
public:
    static void ReportError(ErrorCode code, const std::string& additionalInfo = "");
};


#endif // ERROR_HANDLING_H

