#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int id = fork();

    if (id == 0) {
        int wstatus;
        pid_t pid = wait(&wstatus);
        printf("child wait returned pid: %d\n", pid);
    } else {
        printf("ID returned from fork: %d\n", id);
        int wstatus;
        pid_t pid = wait(&wstatus);
        printf("parent wait returned pid: %d\n", pid);
    }
}