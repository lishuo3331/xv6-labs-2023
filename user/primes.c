#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
int p[36][2];

int isPrime(int n)
{
    int i = 0;
    for(i = 2; i < n; i++)
    {
        if(0 == n % i)
        {
            return 0;
        }
    }
    return 1;
    exit(0);
}

void prime(int n, int fd)
{
    int ret = ERROR_SUCCESS;
    int temp = 0;
    if(n >  35)
    {
        exit(0);
    }
    if(1 == isPrime(n))
    {
        ret = pipe(p[fd]);
        if(ERROR_SUCCESS != ret)
        {
            printf("primes: pipe error");
            exit(-1);
        }
        ret = fork();
        if(0 > ret)
        {
            printf("primes: fork error\n");
            exit(-1);
        }
        if(0 == ret)
        {
            close(p[fd][0]);
            write(p[fd][1], &n, sizeof(n));
            close(p[fd][1]);
        }
        else
        {
            close(p[fd][1]);
            read(p[fd][0], &temp, sizeof(temp));
            printf("prime %d\n", temp);
            close(p[fd][0]);
            prime(n + 1, fd + 1);
        }
    }
    else
    {
        prime(n + 1, fd);
    }

}
int main(int argc, char *argv[])
{
    if(1 != argc)
    {
        printf("primes: argc error\n");
        exit(-1);
    }
    prime(2, 0);
    exit(0);
}