// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main() {
//     // Prompt the user for input
//     printf("> ");
//     fflush(stdout);

//     // Read a line of input from the user
//     char input[256];
//     if (fgets(input, sizeof(input), stdin) == NULL) {
//         perror("Error reading input");
//         exit(1);
//     }

//     // Remove the newline character at the end of the input
//     input[strcspn(input, "\n")] = '\0';

//     // Redirect stdout and stderr to a file
//     if (freopen("example.txt", "w", stdout) == NULL) {
//         perror("Error redirecting stdout");
//         exit(1);
//     }

//     if (freopen("example.txt", "a", stderr) == NULL) {
//         perror("Error redirecting stderr");
//         exit(1);
//     }

//     // Print the modified input
//     printf("%s\n", input);
//     fflush(stdout);

//     // Close the file
//     fclose(stdout);

//     // Restore stdout and stderr to their original file descriptors
//     freopen("/dev/tty", "a", stdout);
//     freopen("/dev/tty", "a", stderr);

//     // Display the contents of the file
//     FILE *file = fopen("example.txt", "r");
//     if (file == NULL) {
//         perror("Error opening file");
//         exit(1);
//     }

//     char line[256];
//     while (fgets(line, sizeof(line), file)) {
//         printf("%s", line);
//     }

//     fclose(file);

//     return 0;
// }



#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
  
int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <output_filename>\n", argv[0]);
        return 1;
    }

    // open() returns a file descriptor file_desc to the file specified in argv[1]
    int file_desc = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 777);
    
    // Use dup2 to duplicate file_desc to copy_desc
    int copy_desc = dup2(file_desc, STDOUT_FILENO);

    if (copy_desc < 0) {
        printf("Error duplicating file descriptor\n");
        return 1;
    }

    // Now, both file_desc and copy_desc point to the same file

    // write() will write the given string into the file
    // referred by the file descriptors
    write(copy_desc, "This will be output to the file named dup.txt\n", 46);
    write(file_desc, "This will also be output to the file named dup.txt\n", 51);

    // Close the file descriptors when done
    close(file_desc);
    close(copy_desc);

    return 0;
}
