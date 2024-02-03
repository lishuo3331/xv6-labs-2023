#include "kernel/types.h"
#include "user.h"


int main(int argc, char *argv[])
{
    //参数数量校验
    //开启管道 
    int faToCh[2], chToFa[2];
    int ret = ERROR_SUCCESS; 
    ret = pipe(faToCh);
    if(ERROR_SUCCESS != ret)
    {
        printf("pipe error\n");
        exit(-1);
    }
    ret = pipe(chToFa);
    if(ERROR_SUCCESS != ret)
    {
        printf("pipe error\n");
        exit(-1);
    }
    ret = fork();
    if(0 > ret)
    {
        printf("fork error\n");
        exit(-1);
    }
    char *ping = "ping";
    char *pong = "pong";

    if(0 == ret)
    {
        //子进程关闭chtofa读管道 fatoch写管道
        close(chToFa[0]);
        close(faToCh[1]);
        char buf[128] = {0};
        read(faToCh[0], buf, (uint)sizeof(buf));
        printf("%d: received %s\n", getpid(), buf);
        //写管道
        write(chToFa[1], pong, strlen(pong));
        close(chToFa[1]);
        close(faToCh[0]);
    }
    else
    {
        close(chToFa[1]);
        close(faToCh[0]);
        char buf[128] = {0};
        write(faToCh[1], ping, strlen(ping));
        read(chToFa[0], buf, (uint)sizeof(buf));
        printf("%d: received %s\n", getpid(), buf);
        close(chToFa[0]);
        close(faToCh[1]);
    }
    exit(0);
}