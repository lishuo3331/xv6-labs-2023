#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    #if 1
    int ret = ERROR_SUCCESS;
    ret = fork();
    if(0 > ret)
    {
        printf("fork error\n");
        exit(-1);
    }
    #endif
    #if 1
    //子进程
    if(0 == ret)
    {
        char *args[16] = {0};
        for(int i = 1; i < argc;)
        {
            args[i-1] = argv[i];
            ++i;
        }
        int x = argc - 1;
        char buf[512] = {0};
        int n = 0;
        int index = 0;
        while(1)
        {
            n = read(0, buf + index, 1);
            if(n < 0)
            {
                printf("read error\n");
                exit(-1);
            }
            if(0 == n)
            {
                int begin = 0;
                for(int i = begin; i < index; ++i)
                {
                    if(buf[i] == '\n')
                    {
                        buf[i] = '\0';
                        args[x++] = buf + begin;
                        begin = i + 1;
                    }
                    if(buf[begin] == 0)
                    {
                        exec(args[0], args);
                        break;
                    }
                }
                exit(0);
            }
            ++index;
        }
        exit(0);
    }
    else
    {
        int status = 0;
        ret = wait(&status);
        if(0 > ret)
        {
            exit(-1);
        }
        exit(0);
    }
    #endif
    exit(0);
}