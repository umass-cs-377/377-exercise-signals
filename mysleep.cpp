#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

using namespace std;

void sig_alarm(int signo) {
    cout << "WAKE UP" << endl;
}

void my_sleep(int time){
    // implement sleep using alarm/pause
}

int main() {

    if (signal(SIGALRM, sig_alarm) == SIG_ERR) {
        exit(1);
    }

    cout << "Going to sleep!" << endl;

    alarm(4);
    sleep(10);

    cout << "Where is my coffee? " << endl;
}