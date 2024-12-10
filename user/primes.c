#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
int p[1][2];
void prime(int fd, int *num, int cot)
{
    int ret = ERROR_SUCCESS;
    if(fd >  35)
    {
        exit(0);
    }
    ret = pipe(p[fd]);
    if(ERROR_SUCCESS != ret)
    {
        printf("primes: apply pipe error\n");
        exit(-1);
    }
    ret = fork();
    //子进程从pipe fd读数据 关闭写端
    if(0 == ret)
    {
        close(p[fd][1]);
        int n = 0;
        if(read(p[fd][0], &n, sizeof(n)) > 0)
        {
            int index = 0;
            int m = 0;
            printf("prime %d\n", n);
            while(read(p[fd][0], &m, sizeof(m)) > 0)
            {
                if(m % n != 0)
                {
                    num[index++] = m;
                }
            }
            close(p[fd][0]);
            prime(fd,num,index);
        }
        else
        {
            close(p[fd][0]);
        }
        exit(0);
    }
    //父进程向pipe fd 发数据 关闭读端
    else
    {
        close(p[fd][0]);
        for(int i = 0; i < cot; ++i)
        {
            write(p[fd][1], &num[i], sizeof(num[i]));
        }
        close(p[fd][1]);
        wait(0);
    }
}
int main(int argc, char *argv[])
{
    if(1 != argc)
    {
        printf("primes: argc error\n");
        exit(-1);
    }
    int num[36] = {0};
    for(int i = 2; i <= 35; ++i)
    {
        num[i-2] = i;
    }
    // 传递左侧pipe 下标
    prime(0, num, 34);
    exit(0);
}