#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#include "mycomm.h"

int GetFileNameList(char fileList[][22 + 1], int *pNum)
{
    DIR *pDirPath;
    struct dirent *pDirent;
    int i = 0;

    pDirPath = opendir("/home/haps/tmp/wangcj/mycode/c_test");
    if (pDirPath == NULL)
    {
        MY_LOG(DEBUG, "open dir path error! ErrNo[%s]", strerror(errno));
        return FAILURE;
    }

    while ((pDirent = readdir(pDirPath)) != NULL)
    {
        strcpy(fileList[i], pDirent->d_name);
        i++;
        //printf("d_name=[%s],  d_type=[%d],  d_off=[%d],  d_reclen=[%d]\n", pDirent->d_name, pDirent->d_type, pDirent->d_off, pDirent->d_reclen);
    }

    closedir(pDirPath);
    *pNum = i;

    return SUCCESS;
}

//测试opendir函数
int testOpenDir()
{
    int iRet = 0;
    int i;
    int iToalFileNum = 0;

    char aFileNameList[15][22 + 1];

    //strcpy(agLogModule, "OPENDIR");

    MY_LOG(DEBUG, "testOpenDir  begin...");

    for (i = 0; i < 15; i++)
    {
        aFileNameList[i][0] = '\0';
    }

    iRet = GetFileNameList(aFileNameList, &iToalFileNum);
    if (iRet >= 0)
    {
        MY_LOG(DEBUG, "call GetFileNameList() Success!");
    }
    else
    {
        MY_LOG(DEBUG, "call GetFileNameList() Failure!");
        return FAILURE;
    }

    MY_LOG(DEBUG, "Total File Num is:%d\n", iToalFileNum);

    MY_LOG(DEBUG, "File List:\n");
    for (i = 0; i < 15; i++)
    {
        MY_LOG(DEBUG, __FILE__, __LINE__, "%s  ", aFileNameList[i]);
    }
    //printf("\n");
    MY_LOG(DEBUG, "test OpenDir success!");

    return SUCCESS;
}
