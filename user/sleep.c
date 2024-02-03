// Lab1 睡眠函数
#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if(2 != argc)
    {
        printf("sleep needs one argument\n");
        // return -1;
        exit(-1);
    }
    int ticks = atoi(argv[1]);
    sleep(ticks);
    printf("sleep %d ticks\n", ticks);
    // return 0;
    exit(0);
}