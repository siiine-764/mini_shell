#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Prompt the user for input
    printf("> ");
    fflush(stdout);

    // Read a line of input from the user
    char input[256];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        perror("Error reading input");
        exit(1);
    }

    // Remove the newline character at the end of the input
    input[strcspn(input, "\n")] = '\0';

    // Redirect stdout and stderr to a file
    if (freopen("example.txt", "w", stdout) == NULL) {
        perror("Error redirecting stdout");
        exit(1);
    }

    if (freopen("example.txt", "a", stderr) == NULL) {
        perror("Error redirecting stderr");
        exit(1);
    }

    // Print the modified input
    printf("%s\n", input);
    fflush(stdout);

    // Close the file
    fclose(stdout);

    // Restore stdout and stderr to their original file descriptors
    freopen("/dev/tty", "a", stdout);
    freopen("/dev/tty", "a", stderr);

    // Display the contents of the file
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);

    return 0;
}
