#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int id = fork();

    if (id == 0) {
        puts("hello");
    } else {
        int wstatus;
        waitpid(id, &wstatus, 0);
        puts("goodbye");
    }
}