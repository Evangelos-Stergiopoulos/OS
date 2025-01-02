#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal) {
    printf("Child received signal: %d\n", signal);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        signal(SIGUSR1, signal_handler);
        pause(); // Wait for signal
    } else if (pid > 0) {
        // Parent process
        sleep(1); // Allow the child to set up signal handler
        kill(pid, SIGUSR1);
        printf("Parent sent SIGUSR1 to child\n");
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
