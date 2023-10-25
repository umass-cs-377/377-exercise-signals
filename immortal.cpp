#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

using namespace std;

void sig_int(int signo) {
    if (signo == SIGINT)
        cout << "I AM IMMORTAL!!!" << endl;
}

void my_sleep(){
    // implement sleep using alarm/puase
}

int main() {

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        exit(1);
    }

    while (1) {
        // do nothing
    }
}