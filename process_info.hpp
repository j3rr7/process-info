#include <Windows.h>
#include <string>
#include <vector>
#include <TlHelp32.h>

class ProcessInfo {
private:
    HANDLE hProcess;
    DWORD pid;
    LPVOID baseAddress;

    bool findProcessByName(const std::wstring& processName) {
        bool foundProcess = false;

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 processEntry;
            processEntry.dwSize = sizeof(processEntry);

            if (Process32First(snapshot, &processEntry)) {
                do {
                    if (wcscmp(processEntry.szExeFile, processName.c_str()) == 0) {
                        pid = processEntry.th32ProcessID;
                        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
                        if (hProcess != NULL) {
                            foundProcess = true;
                        }
                        break;
                    }
                } while (Process32Next(snapshot, &processEntry));
            }
            CloseHandle(snapshot);
        }

        return foundProcess;
    }

    bool findProcessModule(const std::wstring& moduleName) {
        bool foundModule = false;

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
        if (snapshot != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 moduleEntry;
            moduleEntry.dwSize = sizeof(moduleEntry);

            if (Module32First(snapshot, &moduleEntry)) {
                do {
                    if (wcscmp(moduleEntry.szModule, moduleName.c_str()) == 0) {
                        baseAddress = moduleEntry.modBaseAddr;
                        foundModule = true;
                        break;
                    }
                } while (Module32Next(snapshot, &moduleEntry));
            }
            CloseHandle(snapshot);
        }

        return foundModule;
    }

public:
    ProcessInfo(const std::wstring& processName) {
        // add error handler or modify here as you like
        if (!findProcessByName(processName) || !findProcessModule(processName)) {
            throw std::exception("Could not find process");
        }
    }

    ~ProcessInfo() {
        CloseHandle(hProcess);
    }

    HANDLE getProcessHandle() const {
        return hProcess;
    }

    DWORD getProcessId() const {
        return pid;
    }

    LPVOID getBaseAddress() const {
        return baseAddress;
    }
};
