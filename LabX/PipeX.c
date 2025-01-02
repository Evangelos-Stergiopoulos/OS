#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    char message[] = "Hello from parent!";
    char buffer[100];

    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        close(pipe_fd[1]); // Close write end
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipe_fd[0]);
    } else if (pid > 0) {
        // Parent process
        close(pipe_fd[0]); // Close read end
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]);
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
