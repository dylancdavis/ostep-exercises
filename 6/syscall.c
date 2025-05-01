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

	for (int i = 0; i < num_evaluations; i++)
	{
		int buf[1];
		int ret = read(1, buf, 0);
	}

	tret = gettimeofday(&end_time, NULL);
	if (tret != 0)
	{
		printf("Error in gettimeofday");
		return 1;
	};

	long s_diff = end_time.tv_sec - start_time.tv_sec;
	long us_diff = end_time.tv_usec - start_time.tv_usec;

	printf("Executed zero-byte read() %d times.\n", num_evaluations);
	printf("- Total exectution times: %lds, %ldus\n", s_diff, us_diff);

	float us_diff_total = (s_diff * 1000000 + us_diff);
	printf("- Average execution time: %fns\n", (us_diff_total * 1000) / num_evaluations);
}