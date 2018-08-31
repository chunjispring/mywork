#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "mycomm.h"

void del_sigint(int signum);
void del_sigkill(int signum);
void del_sigalrm(int signum);
typedef void (*sigalrm_handler)(int);

int testSignal()
{
    //int  iRet=0;

    //strcpy(agLogModule, "SIGNAL");

    //signal(SIGINT, (void *)del_sigint);
    //signal(SIGKILL, (void *)del_sigkill);
    sigalrm_handler p_siglarm = del_sigalrm;
    signal(SIGALRM, p_siglarm);
    //for(;;)
    //{
    //    MY_LOG(DEBUG,"call testSignal() Success!");
    //}

    alarm(0);

    alarm(5);
    sleep(10);

    return SUCCESS;
}

void del_sigint(int signum)
{
    printf("del_sigint called! sig_num:%d\n", signum);
}

void del_sigalrm(int signum)
{
    printf("del_sigalrm called! sig_num:%d\n", signum);
}

//测试 -9 函数
void del_sigkill(int signum)
{
    printf("del_sigkill called! do nothing! sig_num:%d\n", signum);
}
