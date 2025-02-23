#include <windows.h>
#include <stdio.h>

void createChildProcessWait(const char *childName)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Run cmd.exe with /c exit so it starts and immediately exits
    char command[] = "C:\\Windows\\System32\\cmd.exe /c exit";

    // Create a child process
    // https://www.geeksforgeeks.org/what-is-createprocess-function-in-windows/
    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
    }
    else
    {
        printf("PID of child %s is %d\n", childName, pi.dwProcessId);
        printf("PID of the Parent of %s is %d\n", childName, GetCurrentProcessId());

        // Wait for the child process to complete
        WaitForSingleObject(pi.hProcess, INFINITE);

        printf("Child Process %s (PID %d) completed\n", childName, pi.dwProcessId);

        // Close process handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

int main()
{
    printf("PID of the parent process is %d\n", GetCurrentProcessId());

    // Create first child (P1)
    createChildProcessWait("P1");

    // Create second child (P2)
    createChildProcessWait("P2");

    return 0;
}
