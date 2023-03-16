#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>



#define ENABLE_LOGS 1

void
logs(char c[])
{
    if (ENABLE_LOGS)
    {
        puts(c);
    }
}

void
err(char c[])
{
    printf(" - Error: ");
    puts(c);
}