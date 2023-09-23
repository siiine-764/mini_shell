
// // // int main(int ac, char **av)
// // // {
// // //     //  int fd = open("file.txt", O_WRONLY | O_CREAT, 0644);
// // //     // if (fd == -1) {
// // //     //     perror("open");
// // //     //     exit(1);
// // //     // }

// // //     // // Using dup
// // //     // int newfd = dup(fd);
// // //     // if (newfd == -1) {
// // //     //     perror("dup");
// // //     //     exit(1);
// // //     // }

// // //     // printf("Original file descriptor: %d\n", fd);
// // //     // printf("Duplicated file descriptor: %d\n", newfd);

// // //     // // Using dup2
// // //     // int targetfd = open("newfile.txt", O_WRONLY | O_CREAT, 0644);
// // //     // if (targetfd == -1) {
// // //     //     perror("open");
// // //     //     exit(1);
// // //     // }

// // //     // int result = dup2(fd, targetfd);
// // //     // if (result == -1) {
// // //     //     perror("dup2");
// // //     //     exit(1);
// // //     // }

// // //     // printf("Original file descriptor: %d\n", fd);
// // //     // printf("Target file descriptor: %d\n", targetfd);

// // //     // close(fd);
// // //     // close(newfd);
// // //     // close(targetfd);

// // //     // printf( "%s\n", readline( "test> " ) );
// // //     // return 0;
// // // // int c = 0; 
// // // // int cr;
// // // //   while (c != EOF) 
// // // //     { 
// // // //       printf("\n Enter input: "); 
// // // //       c = getchar(); 
// // // //       cr = getchar();  /* Read and discard the carriage return */
// // // //       putchar(c); 
// // // //     }

// // // echo(av[1]);
// // // }



// #include "./../minishell.h"

// void exect(void)
// {
// 	int	fd[2];
// 	int pid;
// 	// // static int cnt;

// 	pid = 0;

// 	if (pipe(fd) < 0)
// 		return;
//     dup2(pid, 1);
// 	// printf("ddddd");

// 	// if (ptr->type == CMD)
// 	// {	
// 	// }
// }

// int main(int ac, char **av, char **env) {

//     (void)ac;
//     (void)av;

//     struct Node* head = malloc(sizeof(head));

//     // printf("dddd");

//     // int i = 0;
//     // t_env   *e = malloc(sizeof(t_env));

//     create_env(env, head);
    
//     // cd(env, head);
// 	// char *arr[] = {"echo", "fff", "fffffff", "fff", NULL};
//     // echo(arr);
    
// 	int i = 0;
// 	while(env[i])
//     {
//         insertNode(&head, get_value(env[i]), get_key(env[i]));
//         i++;
//     }
// 	// ft_ex_port(head, "test", "test");
//     displayList(head);

//     // exect();

//     // struct Node* head = NULL;

//     // // Insert nodes into the linked list
//     // char    *key;
//     // int     j;
//     // int     k;

//     // k = 0;
//     // j = 0;
//     // int i = 0;
//     // while(env[i])
//     // {
//     //     // printf("---%s---\n", get_key(env[i]));
//     //     insertNode(&head, get_value(env[i]), get_key(env[i]));
//     //     i++;
//     // }
//     // // Display the linked list
//     // displayList(head);


//     printf("cdddd");
//     return 0;
// }




#include <stdio.h>
#include <stdlib.h>

struct MyCommand {
    char ***cmd;
};

int main() {
    char *command[][3] = {
        {"cat", "xxxx", "sssss"},
        {"ls", "xxxx", "ssss"},
    };
    
    printf("Dddd\n");
    
    // Allocate memory for my_cmd and cmd array
    struct MyCommand *my_cmd = (struct MyCommand *)malloc(sizeof(struct MyCommand));
    if (my_cmd == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    my_cmd->cmd = (char ***)malloc(2 * sizeof(char **));
    if (my_cmd->cmd == NULL) {
        perror("Memory allocation failed");
        free(my_cmd);
        return 1;
    }
    for (int i = 0; i < 2; i++) {
        my_cmd->cmd[i] = (char **)malloc(3 * sizeof(char *));
        if (my_cmd->cmd[i] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }

        for (int j = 0; j < 3; j++) {
            my_cmd->cmd[i][j] = command[i][j];
            printf("-> %s\n", my_cmd->cmd[i][j]);
        }
    }

    // Your code logic here

    // Free the allocated memory
    // for (int i = 0; i < 2; i++) {
        // for (int j = 0; j < 3; j++) {
        //     free(my_cmd->cmd[i][j]);
        // }
        // free(my_cmd->cmd[i]);
    // }
    // free(my_cmd->cmd);
    // free(my_cmd);

    return 0;
}


