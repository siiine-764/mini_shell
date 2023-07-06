#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main() {
    int fd[2];
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(fd[1]);  // Close the write end of the pipe

        char buffer[256];
        int bytesRead = read(fd[0], buffer, sizeof(buffer));
        printf("Child: Read %d bytes from pipe: %s\n", bytesRead, buffer);

        close(fd[0]);  // Close the read end of the pipe
    } else {
        // Parent process
        close(fd[0]);  // Close the read end of the pipe

        char *message = "Hello, child process!";
        int bytesWritten = write(fd[1], message, strlen(message) + 1);
        printf("Parent: Wrote %d bytes to pipe\n", bytesWritten);

        close(fd[1]);  // Close the write end of the pipe
    }

    return 0;
}