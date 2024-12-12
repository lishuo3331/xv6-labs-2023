# Initial process that execs /init.
# This code runs in user space.
# 用于启动第一个用户进程，设置初始环境，栈指针 程序计数器 执行exec系统调用 将程序和参数入栈 通过系统调用进入内核 替换进程内存和寄存器 设置寄存器--发起中断
# 内存管理和与内核交互
#include "syscall.h"

# exec(init, argv)
.globl start
start:
        la a0, init
        la a1, argv
        li a7, SYS_exec
        ecall

# for(;;) exit();
exit:
        li a7, SYS_exit
        ecall
        jal exit

# char init[] = "/init\0";
init:
  .string "/init\0"

# char *argv[] = { init, 0 };
.p2align 2
argv:
  .long init
  .long 0
