#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int id = fork();

    if (id == 0) {
        close(STDOUT_FILENO);
        printf("foobar %d\n", 1);
    }
}