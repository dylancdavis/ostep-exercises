#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    FILE* f = fopen("foo", "w");

    if (f == NULL) {
        puts("Failed to open file.");
        return 1;
    }

    int id = fork();

    if (id == 0) {
        fputs("childbar", f);
        fputs("childbaz", f);
        fclose(f);
    } else {
        fputs("parentbar", f);
        fputs("parentbaz", f);
        fclose(f);
    }
}