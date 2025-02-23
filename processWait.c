#include <windows.h>
#include <stdio.h>

void createChildProcess(const char *childName)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char command[] = "C:\\Windows\\System32\\cmd.exe";

    // Create a child process (cmd.exe is used as a placeholder)
    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
    }
    else
    {
        printf("PID of child %s is %d\n", childName, pi.dwProcessId);
        printf("PID of the Parent of %s is %d\n", childName, GetCurrentProcessId());

        // Close proces and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

int main()
{
    printf("PID of the parent process is %d\n", GetCurrentProcessId());

    // Create first child (P1)
    createChildProcess("P1");

    // Create second child (P2)
    createChildProcess("P2");

    return 0;
}
