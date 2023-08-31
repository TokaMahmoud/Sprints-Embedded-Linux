#include "../include/ErrorHandling.h"
#include <iostream>
#include <cstring>

void ErrorHandling::ReportError(ErrorCode code, const std::string& additionalInfo) {
    std::string errorMessage;

    switch (code) {
        case ErrorCode::IPC_LIBRARY_OK:
            errorMessage = "No error.";
            break;
        case ErrorCode::IPC_LIBRARY_FTOK_FAILED:
            errorMessage = "ftok failed.";
            break;
        case ErrorCode::IPC_LIBRARY_MSGGET_FAILED:
            errorMessage = "msgget failed.";
            break;
        case ErrorCode::IPC_LIBRARY_MSGCTL_FAILED:
            errorMessage = "msgctl failed.";
            break;
        case ErrorCode::IPC_LIBRARY_MSGRCV_FAILED:
            errorMessage = "msgrcv failed.";
            break;        
        case ErrorCode::IPC_LIBRARY_MSGSND_FAILED:
            errorMessage = "msgsnd failed.";
            break;            
        case ErrorCode::IPC_LIBRARY_UNKNOWN_ERROR:
            errorMessage = "Unknown error.";
            break;
        
    }

    if (!additionalInfo.empty()) {
        errorMessage += " " + additionalInfo;
    }

    std::cerr << "IPC_LIBRARY Error: " << errorMessage << std::endl;
}

