#include <stdio.h> // for printf
#include <sys/times.h> // for times
#include <unistd.h> // for sysconf
#include <stdlib.h>


int main()
{
    double avg = 0;
    int j = 0;
    for(; j < 3; j++){
        struct tms start, end;
        long clocks_per_sec = sysconf(_SC_CLK_TCK);
        long clocks;

        times(&start);
        // ===================================
            long int n = 4000000000;
            float pi = 0;
            for (long int i = 0; i <= n; i++)
            {
                    if (i % 2 == 0) pi += 4.0 / (2*i + 1);
                    else pi += ( -4.0) / (2*i + 1);
            }

        // ===================================
        times(&end);
        clocks = end.tms_utime - start.tms_utime;
        printf("\n=====Iteration %d===== \nTime taken: %lf sec.\n", j + 1,
        (double)clocks / clocks_per_sec);
        avg += (double)clocks / clocks_per_sec;
    }

    printf("=====TOTAL===== \nAverage time taken: %lf sec.\nRelative fault: %lf",
        avg/j, 0.01/avg/j);

    return 0;
}
