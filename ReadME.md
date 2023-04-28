# Process Info Class for Windows

An example of a convenient way to retrieve information about a running process in Windows. 
This class encapsulates the Windows API functions used to retrieve information about a process, including the process handle, process ID, and base address.

## Prerequisites

To use the `ProcessInfo` class, you will need a C++ compiler that supports the C++11 standard and the Windows API. 

## Usage 

To use the `ProcessInfo` class, simply include the "process_info.h" header file in your C++ program:
```cpp
#include "process_info.hpp"
```
You can then create a ProcessInfo object for a running process by specifying the name of the process as a parameter:
```cpp
ProcessInfo processInfo("notepad.exe");
```
you can retrieve the process handle, process ID, and base address using the getProcessHandle, getProcessId, and getBaseAddress methods, respectively:
```cpp
HANDLE hProcess = processInfo.getProcessHandle();
DWORD pid = processInfo.getProcessId();
LPVOID baseAddress = processInfo.getBaseAddress();
```

## Limitations

Note that the ProcessInfo class only works on the Windows operating system. 
If you need to retrieve information about a process in a different operating system, you will need to use a different method.

# Note

I'm sure that most of you seeing this is already known a better way of finding and storing process info for whatever reason 

so i put this here just to show my example, have fun and happy hacking.
