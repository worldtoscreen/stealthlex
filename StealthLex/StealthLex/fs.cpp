#pragma once

#include "fs.hpp"

using json = nlohmann::json;

bool directoryExists(const std::filesystem::path& path)
{
    return std::filesystem::is_directory(path);
}

bool fileExists(const std::filesystem::path& path)
{
    return std::filesystem::exists(path);
}

bool writeToFile(const std::filesystem::path& path, json data) {
    try {
        // Open the file for writing
        std::ofstream file(path);

        if (!file.is_open()) {
            std::cerr << "Failed to open the file for writing: " << path << std::endl;
            return false;
        }

        // Write the JSON data to the file
        file << data.dump(4); // Optional: Pretty-print with an indentation of 4 spaces

        // Close the file
        file.close();

        std::cout << "Data written to file: " << path << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error writing to file: " << e.what() << std::endl;
        return false;
    }
}

bool createDirectory(const std::filesystem::path& path)
{
	return std::filesystem::create_directory(path);
}

bool createFile(const std::filesystem::path& path)
{
	std::ofstream file(path);
	return file.good();
}

bool loadConfig(const std::filesystem::path& path)
{
    try {
        // Check if the JSON file exists
        if (!std::filesystem::exists(path)) {
            std::cerr << "JSON configuration file does not exist." << std::endl;
            return false;
        }

        // Read the JSON configuration from the file
        json configData;
        std::ifstream configFile(path);

        if (!configFile.is_open()) {
            std::cerr << "Failed to open the JSON configuration file." << std::endl;
            return false;
        }

        configFile >> configData;
        configFile.close();

        // Update the values in the namespaces
        injectionConfig::injectionBind = configData["injectionConfig"]["injectionBind"];
        injectionConfig::beepOnInjection = configData["injectionConfig"]["beepOnInjection"];
        injectionConfig::beepFreq = configData["injectionConfig"]["beepFreq"];
        injectionConfig::beepDur = configData["injectionConfig"]["beepDur"];

        uninjectConfig::uninjectBind = configData["uninjectConfig"]["uninjectBind"];
        uninjectConfig::beepOnUninjection = configData["uninjectConfig"]["beepOnUninjection"];
        uninjectConfig::beepFreq = configData["uninjectConfig"]["beepFreq"];
        uninjectConfig::beepDur = configData["uninjectConfig"]["beepDur"];

        deleteTracesConfig::deleteTracesBind = configData["deleteTracesConfig"]["deleteTracesBind"];
        deleteTracesConfig::beepOnDeleteTraces = configData["deleteTracesConfig"]["beepOnDeleteTraces"];
        deleteTracesConfig::beepFreq = configData["deleteTracesConfig"]["beepFreq"];
        deleteTracesConfig::beepDur = configData["deleteTracesConfig"]["beepDur"];

        return true;
    }
    catch (const json::exception& e) {
        std::cerr << "Error while updating the values from the JSON configuration: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
        return false;
    }
}

bool runFile(const std::filesystem::path& path)
{
    //Run File: path
    if (std::filesystem::exists(path) && path.extension() == ".exe") {
        std::string command = path.string();
        int return_code = std::system(command.c_str());
        if (return_code == 0) {
            //Injection Started!
            return true;
        }
        else {
            //Failed to inject
            return false;
        }
    }
    else {
        //Failed to inject - file does not exist or is not an executable
        return false;
    }
    
}

bool IOCTL_SYSTEM_COMMAND(const char* command)
{
    //I LOVE IOCTL
    //I LOVE DeviceIoControl!!

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // I'm calling this ioctl even though its literally a system command
    if (CreateProcess(NULL, (LPWSTR)command, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close da thread & process :money_mouth:
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::cerr << "Failed to create the process." << std::endl;
        return 1;
    }
}