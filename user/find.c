#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

//文件名解析函数 用以匹配
char *fmtname(char *path) {
  static char buf[DIRSIZ + 1];
  char *p;
  memset(buf, 0, DIRSIZ + 1);
  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ) return p;
  memmove(buf, p, strlen(p));
  return buf;
}
//find函数逻辑 递归调用
void find(char *path, char *target)
{
    int fd;
    char buf[512];
    struct stat st;
    struct dirent de;
    char *p;
    if((fd = open(path,0)) < 0)
    {
        printf("find: cannot open %s\n",path);
        return;
    }
    if(fstat(fd,&st) < 0)
    {
        printf("find: cannot stat %s\n",path);
        close(fd);
        return;
    }
    switch(st.type)
    {
        case T_FILE:
        {
            close(fd);
            if(strcmp(target, fmtname(path)) == 0)
            {
                printf("%s\n",path);
                // exit(0);
            }
            break;
        }
        case T_DIR:
        {
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf))
            {
                close(fd);
                printf("find: path too long\n");
                break;
            }
            strcpy(buf,path);
            p = buf + strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de))
            {
                memset(p, 0, DIRSIZ);
                if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0 || strcmp(de.name,"") == 0)
                {
                    continue;
                }
                memcpy(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if(stat(buf, &st) <0)
                {
                    continue;
                }
                find(buf, target);
            }
            close(fd);
            break;
        }
    }
}
int main(int argc, char *argv[])
{
    //参数数量校验
    if(3 != argc)
    {
        printf("argc error\n");
        exit(-1);
    }
    find(argv[1],argv[2]);
    exit(0);
}