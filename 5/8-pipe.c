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
            //
            return 0;
        } else {
            puts("Child process 2");
            close(pipefd[1]); // in second child close pipe write end
            
            // read in pipe input and print to stdout
            char buf;
            while (read(pipefd[0], &buf, 1) > 0) {
                putc(buf, stdout);
            }
            close(pipefd[0]); // close read after finish
        }
        
    } else {
        puts("Child process 1");
        close(pipefd[0]); // in first child close pipe read end

        FILE* f = fdopen(pipefd[1], "w");
        fputs("foobar", f); // write foobar to pipe
        close(pipefd[1]); // close pipe write end
    }
}