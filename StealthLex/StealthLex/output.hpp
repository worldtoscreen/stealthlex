#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>
#include "binding.hpp"

#include "config.hpp"

void outputDebug(std::string info);
void failed();
void getConfig(std::string configType, std::string triggerEvent, int& keyCodeBuf, bool& beepBuf, int& beepFreqBuf, int& beepDurBuf, int delay); //delay in ms: 3 sec