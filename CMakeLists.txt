cmake_minimum_required(VERSION 3.0)
project(LoggerApp)

set(CMAKE_CXX_STANDARD 11)

# Find the Boost library
find_package(Boost REQUIRED COMPONENTS log_setup log thread)

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

add_executable(LoggerApp
        ./Logger_Daemon_Application/main.cpp
        ./Logger_Daemon_Application/LoggerDaemon.cpp
        ./IPC_LIBRARY/src/MessageQueueReceiver.cpp
        ./IPC_LIBRARY/src/MessageQueueSender.cpp
        ./IPC_LIBRARY/src/ErrorHandling.cpp
        ./Mathematical_Operation_Applications/MathApp.cpp)

# Link against Boost libraries and other necessary libraries
target_link_libraries(LoggerApp
    ${Boost_LIBRARIES}
    pthread
)
