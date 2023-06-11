#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <fcntl.h>

void  echo(char *com)
{
  int i = 0;

  printf("ddfds");
  while (com[i])
  {
    printf("%c", com[i]);
    i++;
  }
}

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100



int main() {
    char input[MAX_INPUT_LENGTH];

    printf("Echo program - Enter 'exit' to quit.\n");

    // while (1) {
        printf("echo ");
        fgets(input, sizeof(input), stdin);

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting the program.\n");
            // break;
        }

        printf("%s\n", input);
    // }

    return 0;
}

// \n :      new line
// #include <stdio.h>
// #include <string.h>

// int main() {
//     char input[100];

//     printf("Enter a message: ");
//     fgets(input, sizeof(input), stdin);

//     input[strcspn(input, "\n")] = '\0';  // remove the newline character

//     printf("You entered: %s\n", input);

//     return 0;
// }


// int main(int ac, char **av)
// {
//     //  int fd = open("file.txt", O_WRONLY | O_CREAT, 0644);
//     // if (fd == -1) {
//     //     perror("open");
//     //     exit(1);
//     // }

//     // // Using dup
//     // int newfd = dup(fd);
//     // if (newfd == -1) {
//     //     perror("dup");
//     //     exit(1);
//     // }

//     // printf("Original file descriptor: %d\n", fd);
//     // printf("Duplicated file descriptor: %d\n", newfd);

//     // // Using dup2
//     // int targetfd = open("newfile.txt", O_WRONLY | O_CREAT, 0644);
//     // if (targetfd == -1) {
//     //     perror("open");
//     //     exit(1);
//     // }

//     // int result = dup2(fd, targetfd);
//     // if (result == -1) {
//     //     perror("dup2");
//     //     exit(1);
//     // }

//     // printf("Original file descriptor: %d\n", fd);
//     // printf("Target file descriptor: %d\n", targetfd);

//     // close(fd);
//     // close(newfd);
//     // close(targetfd);

//     // printf( "%s\n", readline( "test> " ) );
//     // return 0;
// // int c = 0; 
// // int cr;
// //   while (c != EOF) 
// //     { 
// //       printf("\n Enter input: "); 
// //       c = getchar(); 
// //       cr = getchar();  /* Read and discard the carriage return */
// //       putchar(c); 
// //     }

// echo(av[1]);
// }
