#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "config_reader.hpp"

#define PIPE_NAME "\\\\.\\pipe\\my_named_pipe"
#define BUFFER_SIZE 1024

void simulateKeyPress(WORD key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void simulateMultipleKeyPress(WORD key1, WORD key2 = 0, WORD key3 = 0) {
    simulateKeyPress(key1);
    if (key2 != 0) {
        simulateKeyPress(key2);
    }
    if (key3 != 0) {
        simulateKeyPress(key3);
    }
}

void executeKeyPress(const std::string& command) {

    std::map<std::string, WORD> keyMap = {
        {"CTRL", VK_CONTROL},
        {"SHIFT", VK_SHIFT},
        {"ALT", VK_MENU},
        {"LWIN", VK_LWIN}
    };

    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '+')) {
        tokens.push_back(token);
    }

    auto it = keyMap.find(command);
    if (it != keyMap.end()) {
        // If the input exists, retrieve the corresponding value (VK* constant)
        WORD key = it->second;
        std::cout << key << std::endl;

        // Call your function with the retrieved value as an argument
        simulateKeyPress(key);
    } else {
        std::cout << "Key not found in the map." << std::endl;
    }

    // Extracting individual strings
    std::string strOne, strTwo, strThree;
    if (tokens.size() >= 1) {
        strOne = tokens[0];
    }
    if (tokens.size() >= 2) {
        strTwo = tokens[1];
    }
    if (tokens.size() >= 3) {
        strThree = tokens[2];
    }

    // Output
    std::cout << "String one: " << strOne << std::endl;
    std::cout << "String two: " << strTwo << std::endl;
    std::cout << "String three: " << strThree << std::endl;

}

void processCommand(const std::string& command) {
    std::cout << "Received command: " << command << std::endl;
    executeKeyPress(command);
}

int main() {
    HANDLE pipeHandle;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    pipeHandle = CreateNamedPipe(
        TEXT(PIPE_NAME),  // Adjust the pipe name as needed
        PIPE_ACCESS_INBOUND | PIPE_ACCESS_OUTBOUND,  // Bidirectional
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        0,
        0,
        NMPWAIT_USE_DEFAULT_WAIT,
        nullptr
    );

    if (pipeHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error creating named pipe\n";
        return -1;
    }

    std::cout << "C++ Server waiting for connection\n";

    while (ConnectNamedPipe(pipeHandle, nullptr)) {
        while (ReadFile(pipeHandle, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::string receivedCommand(buffer);
            processCommand(receivedCommand);
        }
        // Disconnect from the client to allow another connection
        DisconnectNamedPipe(pipeHandle);
    }

    CloseHandle(pipeHandle);

    return 0;
}
