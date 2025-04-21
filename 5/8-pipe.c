#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int pipefd[2];

    int ret = pipe(pipefd);
    if (ret == -1) {
        puts("Error creating pipe");
        return 1;
    }

    int id1 = fork();
    
    if (id1 != 0) {
        
        int id2 = fork();
        
        if (id2 != 0) {
            return 0;
        } else {
            close(pipefd[1]);

            FILE* f = fdopen(pipefd[0], "r");
            
            // read in pipe input and print to stdout
            char c = getc(f);
            while (c != EOF) {
                putchar(c);
                fflush(stdout);
                c = getc(f);
            }
            putchar('\n');
            fflush(stdout);
            fclose(f);
            close(pipefd[0]);
        }
        
    } else {
        close(pipefd[0]);
        FILE* f = fdopen(pipefd[1], "w");
        fputs("foobar", f); // write foobar to pipe
        fclose(f);
    }
}