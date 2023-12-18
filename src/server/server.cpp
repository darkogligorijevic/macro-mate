#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#define PIPE_NAME "\\\\.\\pipe\\my_named_pipe"
#define BUFFER_SIZE 1024

void simulateKeyPress(WORD key) {
    INPUT input[2] = {0};
    
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = key;
    
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = key;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

void simulateTwoKeyPresses(WORD key1, WORD key2) {
    INPUT input[4] = {0};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = key1;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = key2;

    input[2].type = INPUT_KEYBOARD;
    input[2].ki.wVk = key1;
    input[2].ki.dwFlags = KEYEVENTF_KEYUP;

    input[3].type = INPUT_KEYBOARD;
    input[3].ki.wVk = key2;
    input[3].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(3, input, sizeof(INPUT));
}

void simulateThreeKeyPresses(WORD key1, WORD key2, WORD key3) {
    INPUT input[6] = {0};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = key1;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = key2;

    input[2].type = INPUT_KEYBOARD;
    input[2].ki.wVk = key3;

    input[3].type = INPUT_KEYBOARD;
    input[3].ki.wVk = key1;
    input[3].ki.dwFlags = KEYEVENTF_KEYUP;

    input[4].type = INPUT_KEYBOARD;
    input[4].ki.wVk = key2;
    input[4].ki.dwFlags = KEYEVENTF_KEYUP;

    input[5].type = INPUT_KEYBOARD;
    input[5].ki.wVk = key3;
    input[5].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(4, input, sizeof(INPUT));
}

void executeKeyPress(const std::string& command) {

    WORD key1;
    WORD key2;
    WORD key3;

    std::map<std::string, WORD> keyMap = {
        {"CTRL", VK_CONTROL},
        {"SHIFT", VK_SHIFT},
        {"ALT", VK_MENU},
        {"LWIN", VK_LWIN},
        {"RWIN", VK_RWIN},
        {"A", 0x41},
        {"B", 0x42},
        {"C", 0x43},
        {"D", 0x44},
        {"E", 0x45},
        {"F", 0x46},
        {"G", 0x47},
        {"H", 0x48},
        {"I", 0x49},
        {"J", 0x4A},
        {"K", 0x4B},
        {"L", 0x4C},
        {"M", 0x4D},
        {"N", 0x4E},
        {"O", 0x4F},
        {"P", 0x50},
        {"Q", 0x51},
        {"R", 0x52},
        {"S", 0x53},
        {"T", 0x54},
        {"U", 0x55},
        {"V", 0x56},
        {"W", 0x57},
        {"X", 0x58},
        {"Y", 0x59},
        {"Z", 0x5A},
        {"0", 0x30},
        {"1", 0x31},
        {"2", 0x32},
        {"3", 0x33},
        {"4", 0x34},
        {"5", 0x35},
        {"6", 0x36},
        {"7", 0x37},
        {"8", 0x38},
        {"9", 0x39},
        {"SPACE", VK_SPACE},
        {"ENTER", VK_RETURN},
        {"BACKSPACE", VK_BACK},
        {"TAB", VK_TAB},
        {"ESCAPE", VK_ESCAPE},
        {"DELETE", VK_DELETE},
        {"INSERT", VK_INSERT},
        {"HOME", VK_HOME},
        {"END", VK_END},
        {"PAGEUP", VK_PRIOR},
        {"PAGEDOWN", VK_NEXT},
        {"UP", VK_UP},
        {"DOWN", VK_DOWN},
        {"LEFT", VK_LEFT},
        {"RIGHT", VK_RIGHT},
        {"F1", VK_F1},
        {"F2", VK_F2},
        {"F3", VK_F3},
        {"F4", VK_F4},
        {"F5", VK_F5},
        {"F6", VK_F6},
        {"F7", VK_F7},
        {"F8", VK_F8},
        {"F9", VK_F9},
        {"F10", VK_F10},
        {"F11", VK_F11},
        {"F12", VK_F12}
        // Add more keys as need
    };

    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '+')) {
        tokens.push_back(token);
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

    auto it1 = keyMap.find(strOne);
    if (it1 != keyMap.end()) {
        // If the input exists, retrieve the corresponding value (VK* constant)
        key1 = it1->second;
        std::cout << key1 << std::endl;

        // Call your function with the retrieved value as an argument
    } else {
        std::cout << "Key not found in the map." << std::endl;
    }

    auto it2 = keyMap.find(strTwo);
    if (it2 != keyMap.end()) {
        // If the input exists, retrieve the corresponding value (VK* constant)
        key2 = it2->second;
        std::cout << key2 << std::endl;

        // Call your function with the retrieved value as an argument
    } else {
        std::cout << "Key not found in the map." << std::endl;
    }

    auto it3 = keyMap.find(strThree);
    if (it3 != keyMap.end()) {
        // If the input exists, retrieve the corresponding value (VK* constant)
        key3 = it3->second;
        std::cout << key3 << std::endl;

        // Call your function with the retrieved value as an argument
    } else {
        std::cout << "Key not found in the map." << std::endl;
    }


    if (strOne.empty() && strTwo.empty() && strThree.empty()) {
        std::cerr << "No valid input" << std::endl;
    } else if (strTwo.empty() && strThree.empty()) {
        simulateKeyPress(key1);
    } else if (strThree.empty()) {
        simulateTwoKeyPresses(key1, key2);
    } else {
        simulateThreeKeyPresses(key1, key2, key3);
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

    executeKeyPress("CTRL+LWIN+F");

    // HANDLE pipeHandle;
    // char buffer[BUFFER_SIZE];
    // DWORD bytesRead;

    // pipeHandle = CreateNamedPipe(
    //     TEXT(PIPE_NAME),  // Adjust the pipe name as needed
    //     PIPE_ACCESS_INBOUND | PIPE_ACCESS_OUTBOUND,  // Bidirectional
    //     PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
    //     1,
    //     0,
    //     0,
    //     NMPWAIT_USE_DEFAULT_WAIT,
    //     nullptr
    // );

    // if (pipeHandle == INVALID_HANDLE_VALUE) {
    //     std::cerr << "Error creating named pipe\n";
    //     return -1;
    // }

    // std::cout << "C++ Server waiting for connection\n";

    // while (ConnectNamedPipe(pipeHandle, nullptr)) {
    //     while (ReadFile(pipeHandle, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
    //         buffer[bytesRead] = '\0';
    //         std::string receivedCommand(buffer);
    //         processCommand(receivedCommand);
    //     }
    //     // Disconnect from the client to allow another connection
    //     DisconnectNamedPipe(pipeHandle);
    // }

    // CloseHandle(pipeHandle);

    return 0;
}
