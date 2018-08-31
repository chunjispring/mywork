#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "mycomm.h"
FILE *popen(const char *, const char *);

int SearchFile(char *aPath, char *aFileName)
{
    char aCommand[COMMAND_LEN + 1];
    char aBuff[COMMAND_LEN + 1];
    FILE *fp = NULL;

    memset(aCommand, 0x00, sizeof(aCommand));
    sprintf(aCommand, "find %s -name %s", aPath, aFileName);

    fp = popen(aCommand, "r");
    if (fp == NULL)
    {
        return (SYSTEM_ERR);
    }

    memset(aBuff, 0, sizeof(aBuff));
    fgets(aBuff, COMMAND_LEN, fp);
    RTrim(aBuff);
    MY_LOG(DEBUG, "Result : %s\n", aBuff);
    if (strlen(aBuff) < 1)
    {
        pclose(fp);
        return (FAILURE);
    }
    pclose(fp);
    return (SUCCESS);
}

//测试 popen 函数
int testPopen()
{
    int iRet = 0;

    //strcpy(agLogModule, "POPEN");

    iRet = SearchFile("~/dist", "Z11");
    if (iRet >= 0)
    {
        MY_LOG(DEBUG, "call SearchFile() Success!");
    }
    else
    {
        MY_LOG(DEBUG, "call SearchFile() Failure!");
        return FAILURE;
    }
    MY_LOG(DEBUG, "testPopen !");

    return SUCCESS;
}
