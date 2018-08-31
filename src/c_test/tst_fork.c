#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#include "mycomm.h"

//全局变量
char agInfo[128];

int DoSomeThing(int pid)
{
    MY_LOG(DEBUG, "%d Do SomeThing...", pid);
    sleep(1);

    MY_LOG(DEBUG, "%d Do SomeThing Else...", pid);
    sleep(1);

    MY_LOG(DEBUG, "%d Done!", pid);
    return SUCCESS;
}

int printFORK()
{
    int iRet;
    pid_t childPid;
    int i;
    pid_t pidBack;
    int pidStatus = -1;

    VERSION_PT;
    MY_LOG(DEBUG, "Fork doing!");

    for (i = 0; i < 3; i++)
    {
        childPid = fork();
        if (childPid < 0)
        {
            MY_LOG(DEBUG, "When fork load child [%d] ERROR occured!", i + 1);
            return childPid;
        }
        else if (childPid == 0)
        {
            //strcpy(agLogfile, "child");

            MY_LOG(DEBUG, "this is child ,pid = %d , ppid = %d", getpid(), getppid());
            iRet = DoSomeThing(getpid());
            if (iRet != SUCCESS)
            {
                MY_LOG(DEBUG, "Call DoSomeThing() ERROR!");
                exit(-1);
            }

            strcpy(agInfo, "Child");
            //退出子进程很重要
            exit(0);
        }
        else
        {
            MY_LOG(DEBUG, "this is parent ,pid = %d", getpid());

            strcpy(agInfo, "Parent");
        }

        MY_LOG(DEBUG, "fork child process [%d] success!", childPid);
    }

    for (i = 0; i < 3; i++)
    {
        //父进程执行到此，马上阻塞自己，知道有子进程结束
        //当发现有子进程结束时，就会回收它的资源
        pidBack = wait(&pidStatus);
        if (WIFEXITED(pidStatus)) /* child process exit normally */
        {
            MY_LOG(DEBUG, "Child process %d exit normally.WIFEXITED return code=[%d].WEXITSTATUS return code=[%d]", pidBack, WIFEXITED(pidStatus), WEXITSTATUS(pidStatus));
        }
        else /* child process exit abnormally, eg. receive a kill signal */
        {
            MY_LOG(DEBUG, "Child process %d exit abnormally ERROR!WIFEXITED return code=[%d]. pidStatus=[%d]", pidBack, WIFEXITED(pidStatus), pidStatus);
        }
    }
    //printf("child exit status is %d\n", WEXITSTATUS(pidStatus));
    //pidStatus　是按位存储的状态信息，需要调用相应的宏来还原一下

    //printf("end of program from pid = %d\n",getpid() );

    return childPid;
}

int testFork()
{
    int iRet = 0;

    //strcpy(agLogModule, "FORK");

    iRet = printFORK();
    if (iRet >= 0)
    {
        MY_LOG(DEBUG, "call printFORK() Success!");
    }
    else
    {
        MY_LOG(DEBUG, "call printFORK() Failure!");
    }
    MY_LOG(DEBUG, "%s Working!", agInfo);

    return SUCCESS;
}

int testFork2()
{
    //int  iRet=0;
    pid_t Pid;
    int i;

    //strcpy(agLogModule, "FORK");

    for (i = 0; i < 2; i++)
    {
        Pid = fork();
        if (Pid < 0)
        {
            MY_LOG(DEBUG, "fork ERROR occured!");
            return FAILURE;
        }
        else if (Pid == 0)
        {
            printf("I am child[%d], my parent is[%d]\n", getpid(), getppid());
            //printf("Do something...\n");

            //sleep(1);
            exit(0);
        }
        else
        {
            printf("I am parent[%d]\n", getpid());
        }
    }

    printf("[%d] hello world!\n", getpid());

    return SUCCESS;
}
