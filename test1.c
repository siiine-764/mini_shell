#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("Number of command-line arguments: %d\n", argc);
    
    printf("Command-line arguments:\n");
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    
    printf("\nEnvironment variables:\n");
    int envIndex = 0;
    while (envp[envIndex] != NULL) {
        printf("%s\n", envp[envIndex]);
        envIndex++;
    }   
    return 0;
}
