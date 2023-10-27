#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include<sys/wait.h>

using namespace std;

int run = 1;
pid_t child_pid;

// Signal handler for SIGUSR1
void sigusr_handler(int signum) {
    
    if (signum == SIGUSR1) { 
        cout << "Kernel received SIGUSR1 signal from child. Setting run=0." << endl;
        run = 0;
    }

    if (signum == SIGUSR2) {
        cout << "CPU received SIGUSR2, do context switch" << endl;
    }
}

void cpu() {
    // Set up the signal handler for SIGUSR2
    struct sigaction sa;
    sa.sa_handler = sigusr_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register the signal handler
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    for (int i = 1; i <= 10; i++) {
        // puase until got sigusr2
    }
    // send signal to parent

}

void kernel() {
    // Set up the signal handler for SIGUSR1
    

    // TODO: Loop until run == 0
    // sleep (1)
    // send signal to child

}

int main() {

    // Fork a child process
    if ((child_pid = fork()) < 0) {
        exit(1);
    }

    if (child_pid == 0) {
        cpu();
    } else {
        kernel();
        waitpid(child_pid, NULL, 0);
    }

    return 0;
}
