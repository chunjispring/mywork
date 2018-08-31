#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mycomm.h"

int ExecCMD(char *aCmd)
{
    pid_t status;

    printf("CMD[%s]\n", aCmd);
    status = system(aCmd);
    if (-1 == status)
    {
        printf("system error!");
    }
    else
    {
        printf("exit status value = [0x%x]\n", status);

        if (WIFEXITED(status))
        {
            if (0 == WEXITSTATUS(status))
            {
                printf("run shell script successfully.\n");
            }
            else
            {
                printf("run shell script fail, script exit code: %d\n", WEXITSTATUS(status));
            }
        }
        else
        {
            printf("exit status = [%d]\n", WEXITSTATUS(status));
        }
    }

    return (SUCCESS);
}

//测试 system 函数
int testSystem()
{
    int iRet = 0;
    char abuf[100 + 1];

    //strcpy(agLogModule, "SYSTEM");
    sprintf(abuf, "grep M44 ~/log/current/log_HAPS_datacollect.20170724|grep TransferStatus=Success");

    iRet = ExecCMD(abuf);
    if (iRet >= 0)
    {
        MY_LOG(DEBUG, "call ExecCMD() Success!");
    }
    else
    {
        MY_LOG(DEBUG, "call ExecCMD() Failure!");
        return FAILURE;
    }
    MY_LOG(DEBUG, "testSystem !");

    return SUCCESS;
}
