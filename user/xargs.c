#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
#if 1
    int ret = ERROR_SUCCESS;
    if (2 > argc)
    {
        printf("argument of xargs is short");
        exit(-1);
    }
    ret = fork();
    if (0 > ret)
    {
        printf("fork error\n");
        exit(-1);
    }
#endif
#if 1
    // 子进程 从标准输入依次读出参数并exec
    if (0 == ret)
    {
        char buf[512] = {0};
        char *args[32] = {0};
        // 依次拷贝参数
        for (int i = 1; i < argc;)
        {
            args[i - 1] = argv[i];
            ++i;
        }
        int arg_cot = argc - 1;
        int index = 0, cot = 0;
        while ((cot = read(0, buf + index, sizeof(buf))) > 0)
        {
            index += cot;
        }
        int len = strlen(buf);
        args[arg_cot++] = buf;
        //可以修改为字符查找strchr while(strchr)
        for (int i = 0; i < len; i++)
        {
            if (buf[i] == '\n')
            {
                buf[i] = '\0';
                if ((i + 1 < len) && buf[i + 1] != '\0')
                {
                    args[arg_cot++] = buf + i + 1;
                }
            }
        }
        exec(args[0], args);
        exit(0);
    }
    else
    {
        ret = wait(0);
        if (0 > ret)
        {
            exit(-1);
        }
        exit(0);
    }
#endif
    exit(0);
}