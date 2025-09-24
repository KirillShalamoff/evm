#include <stdio.h> // for printf
#include <sys/times.h> // for times
#include <unistd.h> // for sysconf
#include <stdlib.h>

int main()
{
    long int n = 8000000000;
        struct tms start, end;
        long clocks_per_sec = sysconf(_SC_CLK_TCK);
        long clocks;
        times(&start);
            float pi = 0;
            for (long int i = 0; i <= n; i++)
            {
                    if (i % 2 == 0) pi += 4.0 / (2*i + 1);
                    else pi += ( -4.0) / (2*i + 1);
            }

    times(&end);
    clocks = end.tms_utime - start.tms_utime;
    printf("\nTime taken: %lf sec.\n", (double)clocks / clocks_per_sec);

    return 0;
}
