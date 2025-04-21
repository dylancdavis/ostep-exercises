#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int id = fork();

    if (id == 0) {
        puts("running child process");
    } else {
        printf("ID returned from fork: %d\n", id);
        int wstatus;
        pid_t pid = waitpid(id, &wstatus, 0);
        printf("parent wait returned waitpid: %d\n", pid);
    }
}