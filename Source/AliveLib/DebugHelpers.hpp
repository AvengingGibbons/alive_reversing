#pragma once

#include "FunctionFwd.hpp"
#include "BaseGameObject.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Function.hpp"
#include "BaseAliveGameObject.hpp"
#include "DDCheat.hpp"

void DebugHelpers_Init();

#ifdef DEVELOPER_MODE
#define DEV_CONSOLE_MESSAGE(message, duration) ShowDebugConsoleMessage(message, duration);
#else
#define DEV_CONSOLE_MESSAGE(message, duration)
#endif

// File System
namespace FS
{
    std::vector<BYTE> ReadFile(std::string filePath);
}

// Duration in seconds
void ShowDebugConsoleMessage(std::string message, float duration);

std::vector<std::string> SplitString(const std::string& s, char seperator);
bool StringStartsWith(std::string mainStr, std::string toMatch);
std::string StringToLower(std::string s);