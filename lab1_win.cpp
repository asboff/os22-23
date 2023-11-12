#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <csignal>

BOOL WINAPI SignalReceiver(DWORD ctrlType) {
    if (ctrlType == CTRL_CLOSE_EVENT) {
        std::cout << "CTRL close" << std::endl;
    }
    else if (ctrlType == CTRL_C_EVENT) {
        std::cout << "CTRL + C" << std::endl;
    }
    return false;
}

int main() {
    SetConsoleCtrlHandler(SignalReceiver, true);
    while (1);
    return 0;
}