#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
#include <vector>
#include <TlHelp32.h>

#include "process_info.h"

int main() {
  try {
    ProcessInfo processInfo(L"CalculatorApp.exe");
    auto hProcess = processInfo.getProcessHandle();
    auto pid = processInfo.getProcessId();  
    auto baseAddress = processInfo.getBaseAddress();  
    std::string handleStr = std::to_string(reinterpret_cast<intptr_t>(hProcess));
    std::string pidStr = std::to_string(pid); 

    std::stringstream stream{};
    stream << std::hex << reinterpret_cast<intptr_t>(baseAddress);
    std::string baseAddrStr = "0x" + stream.str();
    
     std::string message = "Process handle: " + handleStr + "\n"
            + "Process ID: " + pidStr + "\n"
            + "Base address: " + baseAddrStr;
    
    MessageBoxA(NULL, message.c_str(), "Process Info", MB_OK);
    
  } catch (const std::exception&) {
    MessageBoxA(NULL, "Error", "ERROR", MB_ICONERROR | MB_OK);
  }
  return 0;
}
