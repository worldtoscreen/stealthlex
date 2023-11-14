#pragma once

#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include "config.hpp"
#include "windows.h"

using json = nlohmann::json;

bool directoryExists(const std::filesystem::path& path);
bool writeToFile(const std::filesystem::path& path, json data);
bool createDirectory(const std::filesystem::path& path);
bool createFile(const std::filesystem::path& path);
bool fileExists(const std::filesystem::path& path);
bool loadConfig(const std::filesystem::path& path);
bool runFile(const std::filesystem::path& path);
bool IOCTL_SYSTEM_COMMAND(const char* command);