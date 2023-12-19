#include "key_utils.hpp"

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

WORD getVirtualKeyCode(const std::map<std::string, WORD>& keyMap, const std::string& keyString) {
    auto it = keyMap.find(keyString);
    return (it != keyMap.end()) ? it->second : 0;
}

void executeKeyPress(const std::string& command) {
    
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

    std::vector<WORD> keyCodes;

    for (const auto& token : tokens) {
        WORD keyCode = getVirtualKeyCode(keyMap, token);
        if (keyCode != 0) {
            keyCodes.push_back(keyCode);
            std::cout << keyCode << std::endl;
        } else {
            std::cout << "Key not found in the map." << std::endl;
            return; 
        }
    }

    if (keyCodes.empty()) {
        std::cout << "No valid input" << std::endl;
    } else if (keyCodes.size() == 1) {
        simulateKeyPress(keyCodes[0]);
    } else if (keyCodes.size() == 2) {
        simulateTwoKeyPresses(keyCodes[0], keyCodes[1]);
    } else {
        simulateThreeKeyPresses(keyCodes[0], keyCodes[1], keyCodes[2]);
    }
}

void releaseAllKeyPresses() {
        for (int key = 0; key < 256; ++key) {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = key;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}

void processCommand(const std::string& command) {
    std::cout << "Received command: " << command << std::endl;

    // Capture 'command' by value in the lambda capture list
    std::thread keyPressThread([&command] {
        executeKeyPress(command);
        releaseAllKeyPresses();
    });

    // Wait for the keyPressThread to finish
    keyPressThread.join();
}