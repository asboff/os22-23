#include <Windows.h>
#include <iostream>
#include <processthreadsapi.h>
#include <stdio.h>

void randomize() {
    while (1) {
        double randomNum = (double) rand() / RAND_MAX;
        std::cout << randomNum << std::endl;
        Sleep(3000);
    }
}

void getReversedString() {
    while (1) {
        char str[50];
        scanf_s("%s", str, 50);
        std::cout << _strrev(str) << std::endl;
    }
}

BOOL WINAPI SignalReceiver(DWORD ctrlType) {
    if (ctrlType == CTRL_CLOSE_EVENT) {
        std::cout << "CTRL close" << std::endl;
    }
    else if (ctrlType == CTRL_C_EVENT) {
        std::cout << "CTRL + C" << std::endl;
    }
    return false;
}

int main()
{
    SetConsoleCtrlHandler(SignalReceiver, TRUE);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)getReversedString, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)randomize, NULL, 0, NULL);
    while (true);
    return 0;
}
