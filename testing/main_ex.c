#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Main Method
int main() {
    char *a = getenv("PWD");
    char *b = getenv("OLDPWD");
    printf("%s\n", a);
    printf("%s\n", b);
    chdir(a);
    chdir(b);
prtinf
return 0;
}
