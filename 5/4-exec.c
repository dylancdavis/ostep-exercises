#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int id = fork();
    if (id == 0) {
        execl("/usr/bin/ls", "ls", (char*) NULL);
    }

    id = fork();
    if (id == 0) {
        execlp("ls", "ls", (char*) NULL);
    }

    id = fork();
    if (id == 0) {
        char* args[2];
        args[0] = "ls";
        args[1] = (char*) NULL;
        execv("/usr/bin/ls", args);
    }

    id = fork();
    if (id == 0) {
        char* args[2];
        args[0] = "ls";
        args[1] = (char*) NULL;
        execvp("ls", args);
    }

}