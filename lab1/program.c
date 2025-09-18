#include <stdio.h> // for printf
#include <sys/times.h> // for times
#include <unistd.h> // for sysconf
#include <stdlib.h>
#include <limits.h>

int main()
{
    double min = __DBL_MAX__;
    int j = 0;
    for(; j < 3; j++){
        struct tms start, end;
        long clocks_per_sec = sysconf(_SC_CLK_TCK);
        long clocks;
        times(&start);
            long int n = 2000000000;
            float pi = 0;
            for (long int i = 0; i <= n; i++)
            {
                    if (i % 2 == 0) pi += 4.0 / (2*i + 1);
                    else pi += ( -4.0) / (2*i + 1);
            }

        times(&end);
        clocks = end.tms_utime - start.tms_utime;
        printf("\n=====Iteration %d===== \nTime taken: %lf sec.\n", j + 1,
        (double)clocks / clocks_per_sec);

        if (min > (double)clocks / clocks_per_sec)
        {
            min = (double)clocks / clocks_per_sec;
        }
    }

    printf("=====TOTAL===== \nMin time taken: %lf sec.\nRelative fault: %lf",
        min, 0.01/min);

    return 0;
}
