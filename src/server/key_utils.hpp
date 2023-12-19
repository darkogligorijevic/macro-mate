#pragma once

#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <thread>

void simulateKeyPress(WORD key);
void simulateTwoKeyPresses(WORD key1, WORD key2);
void simulateThreeKeyPresses(WORD key1, WORD key2, WORD key3);
WORD getVirtualKeyCode(const std::map<std::string, WORD>& keyMap, const std::string& keyString);
void executeKeyPress(const std::string& command);
void releaseAllKeyPresses();
void processCommand(const std::string& command);