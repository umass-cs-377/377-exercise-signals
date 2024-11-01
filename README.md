
# COMPSCI 377 LAB: Signals

## Purpose

The purpose of this lab is to gain a deeper understanding of how to use signals function and the role they play in interprocess
communication.
Please make sure that you do all your work in the Edlab environment, otherwise, there may be inconsistent results and you will not receive
points. Please read through this exercise and follow the instructions. After you do that, visit Gradescope and complete the questions
associated with this exercise by the assigned due date.

The TA present in your lab will do a brief explanation of the various parts of this lab, but you are expected to answer all questions by
yourself. Please raise your hand if you have any questions during the lab section. Questions and Parts have a number of points marked 
next to them to signify their weight in this lab’s final grade.

## Setup

Once you have logged in to Edlab, you can clone this repo using

```bash
git clone https://github.com/umass-cs-377/377-exercise-signals
```

Then you can use `cd` to open the directory you just cloned:

```bash
cd 377-exercise-signals
```

This repo includes a `Makefile` that allows you to locally compile and run all the sample code listed in this tutorial. You can compile
them by running `make`. Feel free to modify the source files yourself, after making changes you can run `make` again to build new
binaries from your modified files. You can also use `make clean` to remove all the built files, this command is usually used when something
went wrong during the compilation so that you can start fresh.


## Part 1

Signal handlers in C/C++ are functions that are used to handle asynchronous events known as signals. Signals are software interrupts delivered
to a running process to notify it of various events or conditions. These events can range from user-generated interruptions (e.g., Ctrl+C
for SIGINT) to system-level events (e.g., segmentation fault for SIGSEGV). Signal handlers allow a program to respond to these events in a
controlled manner.

The code below demonstrates how to handle the SIGINT (Signal Interrupt) signal, generated when a user presses Ctrl+C in a terminal to interrupt
a running program. First, we define a function void sig_int(int signo). This is a signal handler function designed to capture the SIGINT signal.
When the program receives a SIGINT signal, the operating system calls this function. In this case, it simply prints the message "I AM IMMORTAL!!!"
to the console and doesn't perform any other actions. Next, in `main()`, we tell the OS which function it should invoke if the program receives a
`SIGINT`. We do this with `signal(SIGINT, sig_int)`.


```cpp
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
```

## Part 2

Occasionally, it can be beneficial for a program to trigger a signal within its own execution. This can be achieved using the 
`alarm(unsigned int seconds)` function. This function accepts the number of seconds from the current moment to set an alarm. If the 
provided value is greater than 0, it schedules an alarm. If the value is 0, it cancels all pending alarms.

Another valuable function is `pause()`. This function will remain in a sleep state indefinitely, or until a signal is received that 
either terminates the process or triggers the execution of a signal-handling function.

```cpp
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
```

## Part 3
While the signal function is straightforward to use, it suffers from portability issues, particularly in cases involving slow system
calls (refer to 'man 2 signal' for more information). To address this limitation, Linux introduced the sigaction function, which
offers a more robust approach to handling signals.

Linux provides various predefined signals with specific behaviors, but it also grants users the flexibility to define custom 
actions for `SIGUSR1` and `SIGUSR2` signals.

In this illustrative example, we will create a child process using fork(). The child process will iterate ten times, pausing until it 
receives a `SIGUSR2` signal. Upon completing its iterations, the child will signal the parent with `SIGUSER1` to indicate its completion. 
Meanwhile, the parent will continuously loop until the child has finished, as determined by the global variable 'run.' During each iteration, 
the parent will sleep for one second and then send a `SIGUSR2` signal to the child.

One way to conceptualize this scenario is in the context of a scheduler. The scheduler (the child) responds to timer interrupts (as received 
from the parent), leading to a context switch. Your objective is to implement the two functions, `cpu()` and `kernel()`, as directed by the comments.


```cpp
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
        return 1;
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
```
