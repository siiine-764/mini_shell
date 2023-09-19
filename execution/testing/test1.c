#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];  // Pipe file descriptors for communication between processes
    char *wc_args[] = {"/usr/bin/wc", "-l", NULL};
    char *ls_args[] = {"/bin/ls", "-l", NULL};
    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First fork to create the first child process
    pid_t child_pid1 = fork();

    if (child_pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid1 == 0) {
        // Child process 1

        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]); // Close the read end of the pipe
        close(pipe_fd[1]);
        // Execute the command "/usr/bin/wc -l"
        execve("/usr/bin/wc", wc_args, NULL);

        // This code will only run if execve fails
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Second fork to create the second child process
        pid_t child_pid2 = fork();

        if (child_pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid2 == 0) {
            // Child process 2

            // Redirect stdin to the read end of the pipe
            dup2(pipe_fd[1], 1);
            close(pipe_fd[1]); // Close the write end of the pipe
            close(pipe_fd[0]);
            // Execute the command "/bin/ls -l"
            char *ls_args[] = {"/bin/ls", "-l", NULL};
            execve("/bin/ls", ls_args, NULL);

            // This code will only run if execve fails
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process

            // Close the pipe file descriptors
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // Wait for both child processes to complete
            wait(NULL);
        }
    }

    return 0;
}
