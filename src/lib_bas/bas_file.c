/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_file.c                                                  */
/* DESCRIPTIONS: 文件操作接口                                                */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "bas/bas_global.h"

#define BAS_MAX_DBLOG_BYTES 10000000L

/*****************************************************************************/
/* FUNC:   int basFileLock(FILE *fpFile)                                     */
/* PARAMS: fpFile - 文件句柄                                                 */
/* RETURN: 1 - 文件已经被锁                                                  */
/*         0 - 锁成功                                                        */
/*        -1 - 错误                                                          */
/* DESC:   文件加锁                                                          */
/*****************************************************************************/
BAS_EXPORT int basFileLock(FILE *fpFile)
{
    int fd;
    struct flock tLock;

    fd = fileno(fpFile);

    tLock.l_type = F_WRLCK;
    tLock.l_whence = 0;
    tLock.l_start = 0L;
    tLock.l_len = 0L;

    if (fcntl(fd, F_SETLK, &tLock) < 0)
    {
        if ((errno == EAGAIN) || (errno == EACCES))
        {
            return 1;
        }
        else
        {
            BAS_LOG(BAS_ERR300013_ERRORFCNTL, 0, errno, "basFileLock:锁文件失败");
            return -1;
        }
    }

    return 0;
}

/*****************************************************************************/
/* FUNC:   FILE *basOpenDBLogFile(int iForce)                                */
/* PARAMS: iForce - 是否强制输出日志                                         */
/* RETURN: 文件句柄                                                          */
/* DESC:   打开数据库日志文件                                                */
/*****************************************************************************/
BAS_EXPORT FILE *basOpenDBLogFile(int iForce)
{
    FILE *fp;
    int fd;
    struct stat tStat;
    char caLogFile[BAS_FILENAME_LEN];
    char caLogFileBack[BAS_FILENAME_LEN];
    char *pcaLogLevel;
    int iResult;
    char *pcaAppHome;

    if (iForce != BAS_TRUE)
    {
        if ((pcaLogLevel = getenv("LOGLEVEL")) != NULL)
        {
            if (atoi(pcaLogLevel) == 100)
            {
                return NULL;
            }
        }
    }

    if ((pcaAppHome = getenv("LOGHOME")) == NULL)
    {
        BAS_LOG(BAS_ERR300003_ERRORENV, 0, 0, "basOpenDBLogFile:缺少环境变量LOGHOME");
        return NULL;
    }

    sprintf(caLogFile, "%s%s/dbtrace.log", pcaAppHome, BAS_DBLOGPATH);
    sprintf(caLogFileBack, "%s%s/dbtrace.%s%s.log", pcaAppHome, BAS_DBLOGPATH, basGetSysDate(), basGetSysTime());

    if ((fp = fopen(caLogFile, "a+")) == NULL)
    {
        BAS_LOG(BAS_ERR300004_ERROROPENFILE, 0, errno, "basOpenDBLogFile:文件名[%s]", caLogFile);
        return NULL;
    }

    while ((iResult = basFileLock(fp)) != 0)
    {
        if (iResult == -1)
        {
            BAS_LOG(BAS_LOGINFO, 0, 0, "basOpenDBLogFile:锁文件[%s]失败", caLogFile);
            return NULL;
        }
        fclose(fp);
        usleep(10000L);                            /* 等待释放文件锁 */
        if ((fp = fopen(caLogFile, "a+")) == NULL) /* 重新打开文件 */
        {
            BAS_LOG(BAS_ERR300004_ERROROPENFILE, 0, errno, "basOpenDBLogFile:文件名[%s]", caLogFile);
            return NULL;
        }
    }

    fd = fileno(fp);
    if (fstat(fd, &tStat) != 0)
    {
        BAS_LOG(BAS_ERR300014_ERRORFSTAT, 0, errno, "basOpenDBLogFile:文件名[%s]", caLogFile);
        return NULL;
    }
    fchmod(fd, tStat.st_mode | S_IWGRP);

    if (tStat.st_size > BAS_MAX_DBLOG_BYTES)
    {
        if (rename(caLogFile, caLogFileBack) != 0)
        {
            fclose(fp);
            BAS_LOG(BAS_ERR300015_ERRORFRENAME, 0, errno,
                    "basOpenDBLogFile:原文件名[%s]:新文件名[%s]", caLogFile, caLogFileBack);
            return NULL;
        }
        fclose(fp);
        return basOpenDBLogFile(iForce);
    }

    return fp;
}
