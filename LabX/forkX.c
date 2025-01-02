#include <stdio.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            break; // Prevent further forking by the child
        } else if (pid > 0) {
            // Parent process
            printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        } else {
            perror("Fork failed");
            return 1;
        }
    }
    return 0;
}
