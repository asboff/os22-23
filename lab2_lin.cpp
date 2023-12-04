#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <signal.h>
#include <algorithm>

pthread_t randomT, reverseT;
pthread_mutex_t mutex;
bool running = true;

void* randomize(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    while (running) {
        double randomNum = (double) rand() / RAND_MAX;
        std::cout << randomNum << std::endl;
        sleep(3);
    }
    return NULL;
}

void* getReversedString(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    while (running) {
        std::string input;
        std::getline(std::cin, input);
        std::reverse(input.begin(), input.end());
        std::cout << input << std::endl;
    }
    return NULL;
}

void signalHandler(int signum) {
    std::cout << "SIGINT " << signum << std::endl;
    running = false;
    pthread_cancel(randomT);
    pthread_cancel(reverseT);
}

int main()
{
    signal(SIGINT, signalHandler);
    pthread_create(&randomT, NULL, randomize, NULL);
    pthread_create(&reverseT, NULL, getReversedString, NULL);
    
    pthread_join(randomT, NULL);
    pthread_join(reverseT, NULL);
    
    return 0;
}

