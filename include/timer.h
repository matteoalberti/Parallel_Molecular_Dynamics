#ifndef __timer__
#define __timer__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

double timer_seconds()
{
    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}

#endif /* __timers__ */

