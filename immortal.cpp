#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

using namespace std;

void sig_int(int signo) {
    cout << "I AM IMMORTAL!!!" << endl;
}

int main() {

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        exit(1);
    }

    int i = 0;
    while (i++ < 20) {
        sleep(1);
    }
}