#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "utils.h"
 
#define INNER_LOOP 1000
int num_iterations = 10;
struct timespec sleep_time = { 0, 50 * 1000};
 
int main(int argc, char** argv) {
              int i = 0;
              int j;
              struct timeval start, end;
              struct timespec nano_time[INNER_LOOP + 1], end_no_time[INNER_LOOP + 1];
              unsigned long diff[num_iterations];
              double min_ary[num_iterations], max_ary[num_iterations], max, min;
              double ndiff, nlimit, diffn[num_iterations];
 
              if (geteuid() == 0) {
                            /* super user -- switch to real-time mode and lock memory pages */
                            struct sched_param sp;
                            memset(&sp, 0, sizeof(sp));
                            sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
                            Try(sched_setscheduler(0, SCHED_FIFO, &sp));
                            Try(mlockall(MCL_CURRENT | MCL_FUTURE));
              } else {
                            fprintf(stderr, " Not running with realtime priority ") ;
              }
              if (argc > 1) {
                            num_iterations = atoi(argv[1]);
              }
              if (argc > 2) {
                            sleep_time.tv_nsec = atoi(argv[2]) * 1000;
              }
 
              clock_getres(CLOCK_REALTIME, &nano_time[0]);
              printf("clock resolution = %ld secs and %ld nsecs ",
                            nano_time[0].tv_sec, nano_time[0].tv_nsec);
              printf("Doing %d iterations of sleeping for %ld"
                     " micro seconds %d times "
                     "Total time for each iteration should be %f seconds. ",
                     num_iterations, sleep_time.tv_nsec / 1000, INNER_LOOP,
                    ((double)INNER_LOOP * (double)sleep_time.tv_nsec)/1000000000.0 );
              nlimit = sleep_time.tv_nsec * 100;
              nlimit /= NSEC_PER_SEC;
 
              clock_getres(CLOCK_REALTIME, &nano_time[0]);
        printf("clock resolution = %ld secs and %ld nsecs ",
                            nano_time[0].tv_sec, nano_time[0].tv_nsec);
             
              for (i= -1;  i < num_iterations; i++) {
 
                            Try(gettimeofday(&start, NULL));
                            for(j=0;j < INNER_LOOP; j++)
                            {
                                          Try(clock_gettime(CLOCK_REALTIME, &nano_time[j]));
                                          Try0(clock_nanosleep(CLOCK_REALTIME, 0,
                                                                          &sleep_time, NULL));
                                          Try(clock_gettime(CLOCK_REALTIME, &end_no_time[j]));
                                          if (j == 0 || i < 0)
                                                        continue;
 
                                          ndiff =  timerdiff(&end_no_time[j], &nano_time[j]);
                                          if (ndiff > nlimit) {
                                                        struct timespec dum;
                                                        printf("Found %f at (%d,%d) ", ndiff, i,j);
                                                        Try(clock_gettime(CLOCK_MONOTONIC, &dum));
                                          }
                            }
                            Try(clock_gettime(CLOCK_REALTIME, &nano_time[INNER_LOOP]));
                            Try(gettimeofday(&end, NULL));
 
                            /* skip the first iteration through the loop */
                            if (i >= 0)  {
                                    diff[i] = (end.tv_sec - start.tv_sec) * 1000 * 1000 +
                                                        (end.tv_usec - start.tv_usec);
                                          diffn[i] = timerdiff(&nano_time[INNER_LOOP],
                                                                            &nano_time[0]);
                            }
                            min = 10.0;
                            max = -10.0;
                            for(j=0; j < INNER_LOOP; j++) {
                                          ndiff = timerdiff(&nano_time[j + 1], &nano_time[j]);
                                          min = min > ndiff ? ndiff : min;
                                          max = max < ndiff ? ndiff : max;
                            }
                            min_ary[i] = min;
                            max_ary[i] = max;
              }
 
              printf("Iteration iter time (secs)           min sleep max sleep ");
              for (i= 0;  i < num_iterations; i++) {
                printf("  %d        %f  %f %f    %f ", i, (double)diff[i] / 1000000.0,
                            diffn[i],  min_ary[i], max_ary[i]) ;
              }
 
              return 0;
}
 
