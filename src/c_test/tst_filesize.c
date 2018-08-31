#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "mycomm.h"

//测试 stat 函数
int testFileSize()
{
    int iRet = 0;
    int filesize;
    char aFilePath[50 + 1];
    char aFileName[50 + 1];
    char aSysDate[8 + 1];

    //strcpy(agLogModule, "FSIZE");

    memset(aSysDate, 0x00, sizeof(aSysDate));
    memset(aFilePath, 0x00, sizeof(aFilePath));
    memset(aFileName, 0x00, sizeof(aFileName));
    
    GetSysTime(aSysDate, "yyyymmdd");
    iRet = GetLogPath(aFilePath);

    if (iRet != 0)
    {
        return iRet;
    }
    sprintf(aFileName, "%s/log_HAPS_mytest.%s", aFilePath, aSysDate);

    iRet = GetFileSize(aFileName, &filesize);
    if (iRet != 0)
    {
        MY_LOG(DEBUG, "Get FileSize of %s ERROR[%s]", aFileName, aczErrMsg);
        return FAILURE;
    }

    MY_LOG(DEBUG, "FileSize of %s is %.2lf M", aFileName, filesize * 1.0 / 1024 / 1024);

    return SUCCESS;
}
