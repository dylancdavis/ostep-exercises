#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main(void)
{
    struct timeval start_time = {
        tv_sec : 0,
        tv_usec : 0
    };

    struct timeval end_time = {
        tv_sec : 0,
        tv_usec : 0
    };

    int num_evaluations = 2;

    // Create pipes
    int pipefd1[2];
    int pipefd2[2];

    int ret = pipe(pipefd2);
    if (ret == -1)
    {
        puts("Error creating pipe");
        return 1;
    }

    ret = pipe(pipefd2);
    if (ret == -1)
    {
        puts("Error creating pipe");
        return 1;
    }

    // Get starting time
    int tret = gettimeofday(&start_time, NULL);
    if (tret != 0)
    {
        printf("Error in gettimeofday");
        return 1;
    };

    int child_pid = fork();

    // Case: Parent process
    if (child_pid != 0)
    {
        close(pipefd1[0]); // close first pipe read end
        close(pipefd2[1]); // and second pipe write end

        FILE *f1 = fdopen(pipefd1[1], "w");
        FILE *f2 = fdopen(pipefd2[0], "r");

        for (int i = 0; i < num_evaluations; i++)
        {
            // Write to the first pipe and read from the second
            fputc('a', f1);
            char c = fgetc(f2);
            printf("Parent received from pipe #2: %c\n", c);
        }
        fclose(f1);
    }
    else
    // Case: Child process
    {
        close(pipefd1[1]); // close first pipe write end
        close(pipefd2[0]); // and second pipe read end

        FILE *f1 = fdopen(pipefd1[0], "r");
        FILE *f2 = fdopen(pipefd2[1], "w");

        char c = getc(f1);
        while (c != EOF)
        {
            printf("Child received from pipe #1: %c\n", c);
            fputc('b', f2);
            c = getc(f1);
        }
    }

    tret = gettimeofday(&end_time, NULL);
    if (tret != 0)
    {
        printf("Error in gettimeofday");
        return 1;
    };

    long s_diff = end_time.tv_sec - start_time.tv_sec;
    long us_diff = end_time.tv_usec - start_time.tv_usec;

    printf("Executed context switch %d times.\n", num_evaluations);
    printf("- Total exectution times: %lds, %ldus\n", s_diff, us_diff);

    float us_diff_total = (s_diff * 1000000 + us_diff);
    printf("- Average execution time: %fns\n", (us_diff_total * 1000) / num_evaluations);
}