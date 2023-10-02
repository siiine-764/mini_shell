// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Function to process the heredoc-like input
// void processHeredoc(const char *input) {
//     printf("Received Heredoc:\n%s\n", input);
//     // You can process the input here as needed
// }

// // Function to read heredoc input until "END" is encountered
// char *readHeredoc() {
//     char *heredocInput = NULL;
//     size_t heredocInputSize = 0;

//     while (1) {
//         char *line = NULL;
//         size_t lineSize = 0;
//         ssize_t bytesRead = getline(&line, &lineSize, stdin);

//         if (bytesRead == -1) {
//             fprintf(stderr, "Error reading input.\n");
//             free(line);
//             free(heredocInput);
//             return NULL;
//         }

//         // Check for the "END" line to terminate input
//         if (strcmp(line, "END\n") == 0) {
//             free(line);
//             break;
//         }

//         // Append the line to the heredoc input
//         heredocInput = realloc(heredocInput, heredocInputSize + bytesRead);
//         if (heredocInput == NULL) {
//             fprintf(stderr, "Memory allocation failed.\n");
//             free(line);
//             return NULL;
//         }
//         memcpy(heredocInput + heredocInputSize, line, bytesRead);
//         heredocInputSize += bytesRead;

//         free(line);
//     }

//     // Null-terminate the heredoc input string
//     if (heredocInputSize > 0) {
//         heredocInput[heredocInputSize] = '\0';
//     } else {
//         fprintf(stderr, "No input provided.\n");
//         free(heredocInput);
//         return NULL;
//     }

//     return heredocInput;
// }

// int main(int argc, char **argv) {
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s << END\n", argv[0]);
//         return 1;
//     }

//     if (strcmp(argv[1], "<< END") != 0) {
//         fprintf(stderr, "Usage: %s << END\n", argv[0]);
//         return 1;
//     }

//     // Read and process the heredoc input
//     char *heredocInput = readHeredoc();
//     if (heredocInput == NULL) {
//         return 1;
//     }

//     // Process the heredoc input
//     processHeredoc(heredocInput);

//     // Clean up
//     free(heredocInput);

//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Function to read lines of input until an "END" line is encountered
// char *readHeredoc() {
//     char *heredocInput = NULL;
//     size_t heredocInputSize = 0;

//     while (1) {
//         char *line = NULL;
//         size_t lineSize = 0;
//         ssize_t bytesRead = getline(&line, &lineSize, stdin);

//         if (bytesRead == -1) {
//             perror("Error reading input");
//             free(line);
//             free(heredocInput);
//             return NULL;
//         }

//         if (strcmp(line, "END\n") == 0) {
//             free(line);
//             break;
//         }

//         heredocInput = realloc(heredocInput, heredocInputSize + bytesRead);
//         if (heredocInput == NULL) {
//             perror("Memory allocation failed");
//             free(line);
//             return NULL;
//         }
//         memcpy(heredocInput + heredocInputSize, line, bytesRead);
//         heredocInputSize += bytesRead;

//         free(line);
//     }

//     if (heredocInputSize > 0) {
//         heredocInput[heredocInputSize] = '\0';
//     } else {
//         perror("No input provided");
//         free(heredocInput);
//         return NULL;
//     }

//     return heredocInput;
// }

// // Function to process the heredoc-like input
// void processHeredoc(const char *input) {
//     printf("Received Heredoc:\n%s\n", input);
//     // You can process the input here as needed
// }

// int main(int argc, char **argv) {
//     if (argc != 2) {
//         perror("Usage: ./a.out << END");
//         return 1;
//     }

//     if (strcmp(argv[1], "<< END") != 0) {
//         perror("Usage: ./a.out << END");
//         return 1;
//     }

//     char *heredocInput = readHeredoc();
//     if (heredocInput == NULL) {
//         return 1;
//     }

//     processHeredoc(heredocInput);
//     free(heredocInput);

//     return 0;
// }





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// Function to read lines of input until an "END" line is encountered
char *readHeredoc() {
    char *heredocInput = NULL;
    size_t heredocInputSize = 0;

    while (1) {
        char *line = readline(">"); // Use readline instead of getline

        if (line == NULL) {
            perror("Error reading input");
            free(heredocInput);
            return NULL;
        }

        // if (strcmp(line, "END") == 0) {
        //     free(line);
        //     break;
        // }
        add_history(line); // Add the line to history
        size_t lineLength = strlen(line);
        heredocInput = realloc(heredocInput, heredocInputSize + lineLength + 1);
        if (heredocInput == NULL) {
            perror("Memory allocation failed");
            free(line);
            return NULL;
        }
        memcpy(heredocInput + heredocInputSize, line, lineLength);
        heredocInputSize += lineLength;
        heredocInput[heredocInputSize] = '\n'; // Add newline character

        free(line);
    }

    if (heredocInputSize > 0) {
        heredocInput[heredocInputSize] = '\0';
    } else {
        perror("No input provided");
        free(heredocInput);
        return NULL;
    }

    return heredocInput;
}

// Function to process the heredoc-like input
void processHeredoc(const char *input) {
    printf("Received Heredoc:\n%s", input);
    // You can process the input here as needed
}

int main(int argc, char **argv)
{
    char *heredocInput = readHeredoc();
    if (heredocInput == NULL)
    {
        return 1;
    }
    processHeredoc(heredocInput);
    free(heredocInput);

    return 0;
}




// #include <stdio.h>
// #include <string.h>

// void here_doc(const char *delimiter) {
//     char line[256]; // Assuming a maximum line length of 255 characters
//     int is_delimiter = 0;

//     while (1) {
//         fgets(line, sizeof(line), stdin);

//         // Check if the current line matches the delimiter
//         if (strcmp(line, delimiter) == 0) {
//             is_delimiter = !is_delimiter;
//             if (!is_delimiter) {
//                 break; // Exit when the delimiter is encountered again
//             }
//         }

//         // Print the line if it's not the delimiter
//         if (!is_delimiter) {
//             printf("%s", line);
//         }
//     }
// }

// int main() {
//     printf("Enter lines of text followed by 'END' on a separate line:\n");
//     here_doc("END\n"); // Use "END\n" as the delimiter

//     return 0;
// }
