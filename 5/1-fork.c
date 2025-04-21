#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int id = fork();
    int x = 100;

    if (id == 0) {
        x = 1;
        printf("Child process. (ID: %d) Value of x: %d\n", id, x);
    } else {
        x = 2;
        printf("Parent process. (ID: %d) Value of x: %d\n", id, x);
    }
}