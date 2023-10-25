#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include<sys/wait.h>

using namespace std;

// Global variable to control the parent's loop
int run = 1;

// Signal handler for SIGUSR1
void sigusr_handler(int signum) {
    printf("Parent received SIGUSR1 signal from child. Setting run=0.\n");
    
    if (signum == SIGUSR1) {
        cout << "Kernel received SIGUSR1 signal from child. Setting run=0." << endl;
    }

    if (signum == SIGUSR2) {
        cout << "CPU received SIGUSR2, waking up" << endl;
    }
}

void cpu() {
    for (int i = 1; i <= 10; i++) {
        printf("Child: Loop %d\n", i);
        // puase until got sigusr2
    }
    // send signal to parent
}

void kernel() {

    // TODO: Loop until run == 0
    // sleep (1)
    // send signal to child
}

int main() {
    // Set up the signal handler for SIGUSR1
    struct sigaction sa;
    sa.sa_handler = sigusr_handler;
    sigaction(SIGUSR1, &sa, NULL);

    pid_t child_pid;

    // Fork a child process
    if ((child_pid = fork()) < 0) {
        exit(1);
    }

    if (child_pid == 0) {
        cpu();
    } else {
        kernel();
        wait(&child_pid);
    }

    return 0;
}
