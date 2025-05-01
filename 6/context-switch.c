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

    int num_evaluations = 1000000;

    int tret = gettimeofday(&start_time, NULL);
    if (tret != 0)
    {
        printf("Error in gettimeofday");
        return 1;
    };

    // TODO: fork two processes and wait for them both to return
    // In each process, write to the pipe, then wait for a read.
    // Do this a total of num_evaluation times
    // And then return

    for (int i = 0; i < num_evaluations; i++)
    {
        // Main iterative loop here to be placed inside processes
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