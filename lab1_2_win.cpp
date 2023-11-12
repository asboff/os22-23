#include <Windows.h>
#include <stdio.h>
#include <csignal>
#include <iostream>

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
    if (SetConsoleCtrlHandler(SignalReceiver, TRUE)) {
        std::cout << "Waiting for signal.";
        while (1);
        return 0;
    }
    else {
        std::cerr << "Error with handling.";
        return 1;
    }
    while (1);
    return 0;
}