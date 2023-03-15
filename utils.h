#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>



#define ENABLE_LOGS 0

void
logs(char c[])
{
    if (ENABLE_LOGS)
    {
        puts(c);
        printf("\n");
    }
}

void
err(char c[])
{
    printf(" - Error: ");
    puts(c);
    printf("\n");
}