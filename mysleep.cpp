#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

using namespace std;

void sig_alarm(int signo) {
    cout << "interrupted" << endl;
}

void my_sleep(){
    // implement sleep using alarm/puase
}

int main() {

    if (signal(SIGINT, sig_alarm) == SIG_ERR) {
        exit(1);
    }

    cout << "Going to sleep!" << endl;

    sleep(2);

    cout << "Where is my coffee? " << endl;
}