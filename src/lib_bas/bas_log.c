/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_log.c                                                   */
/* DESCRIPTIONS: 系统日志接口                                                */
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
#include <ctype.h>

//#include "dbs/dbs_basopr.h"
#include "bas/bas_global.h"

static char mcaSourceFile[BAS_FILENAME_LEN];
static int mcaSourceLine;

BAS_EXPORT void basLogFileLine(const char *pcaFile, int iLine)
{
    strcpy(mcaSourceFile, pcaFile);
    mcaSourceLine = iLine;
}

/*****************************************************************************/
/* FUNC:   void basLog(int iErrCode, int iSqlCode, int iErrno,               */
/*                     const char *pcaFmt, ...)                              */
/* PARAMS: iErrCode - 应用的错误代码                                         */
/*         iSqlCode - 数据库SQLCODE, 如果是0则忽略 (I)                       */
/*         iErrno   - 操作系统的errno, 如果是0则忽略 (I)                     */
/*         pcaFmt   - 错误信息的格式串 (I)                                   */
/*         ...      - 错误信息的变参部分 (I)                                 */
/* RETURN: 无                                                                */
/* DESC:   系统日志接口                                                      */
/*****************************************************************************/
BAS_EXPORT void basLog(int iErrCode, int iSqlCode, int iErrno, const char *pcaFmt, ...)
{
    FILE *fp;
    int fd;
    struct stat tStat;
    va_list vlVar;
    char *pcaAppHome;
    char *pcaLogLevel;
    char caLogFile[BAS_FILENAME_LEN];
    time_t tTime;
    struct tm *ptmNow;
    char caTimeString[80];
    int iLevel = iErrCode / 100000;

    if ((pcaLogLevel = getenv("LOGLEVEL")) != NULL)
    {
        if (atoi(pcaLogLevel) < iLevel)
        {
            return;
        }
    }

    if ((pcaAppHome = getenv("LOGHOME")) == NULL)
    {
        return;
    }
    if ((tTime = time(NULL)) == -1)
    {
        return;
    }
    if ((ptmNow = localtime(&tTime)) == NULL)
    {
        return;
    }
    sprintf(caLogFile, "%s%s/%s/trace.%s.%04d%02d%02d.log", pcaAppHome, BAS_LOGPATH, gcaModuleName, gcaProgramName,
            ptmNow->tm_year + 1900, ptmNow->tm_mon + 1, ptmNow->tm_mday);

    if ((fp = fopen(caLogFile, "a+")) == NULL)
    {
        return;
    }

    fd = fileno(fp);
    if (fstat(fd, &tStat) != 0)
    {
        return;
    }
    fchmod(fd, tStat.st_mode | S_IWGRP);

    fprintf(fp, "------------------------------------------------------------------------------\n");

    switch (iLevel)
    {
    case 1:
        fprintf(fp, "FATAL:");
        break;
    case 2:
        fprintf(fp, "ERROR:");
        break;
    case 3:
        fprintf(fp, "WARN :");
        break;
    case 4:
        fprintf(fp, "INFO :");
        break;
    case 5:
        fprintf(fp, "DEBUG:");
        break;
    default:
        fprintf(fp, "-----:");
        break;
    }

    tTime = time(NULL);
    ptmNow = localtime(&tTime);
    strftime(caTimeString, sizeof(caTimeString), "%c", ptmNow);

    va_start(vlVar, pcaFmt);
    fprintf(fp, "%s:%s[%d]:%s,%d:\n%s[%d]:",
            caTimeString,
            gcaProgramName,
            getpid(),
            mcaSourceFile,
            mcaSourceLine,
            basGetErrDesc(iErrCode),
            iErrCode);
    if (iErrno != 0)
    {
        fprintf(fp, "OS[%d,%s]:", iErrno, strerror(iErrno));
    }
    if (iSqlCode != 0)
    {
        /* Dongbin 20100205 临时封，记住放开
        fprintf(fp, "DB[%d,%s]:", iSqlCode, dbsGetErrMsg());
		*/
        fprintf(fp, "DB[%d,%s]:", iSqlCode, "数据库操作错！！");
    }
    vfprintf(fp, pcaFmt, vlVar);
    fprintf(fp, "\n");
    va_end(vlVar);

    fclose(fp);
}

/*****************************************************************************/
/* FUNC:   void basBatLog(const char *pcaFmt, ...)                           */
/* PARAMS:                                                                   */
/*                                                                           */
/*         pcaFmt   - 错误信息的格式串 (I)                                   */
/*         ...      - 错误信息的变参部分 (I)                                 */
/* RETURN: 无                                                                */
/* DESC:   批量专用日志接口                                                  */
/*****************************************************************************/
BAS_EXPORT void basBatLog(const char *pcaFmt, ...)
{
    FILE *fp;
    va_list vlVar;
    char *pcaAppHome;
    char caLogFile[BAS_FILENAME_LEN];
    time_t tTime;
    struct tm *ptmNow;
    //char       caTimeString[80];

    if ((pcaAppHome = getenv("LOGHOME")) == NULL)
    {
        return;
    }
    if ((tTime = time(NULL)) == -1)
    {
        return;
    }
    if ((ptmNow = localtime(&tTime)) == NULL)
    {
        return;
    }
    sprintf(caLogFile, "%s%s/%s/trace.%s.%04d%02d%02d.log", pcaAppHome, BAS_LOGPATH, gcaModuleName, gcaProgramName,
            ptmNow->tm_year + 1900, ptmNow->tm_mon + 1, ptmNow->tm_mday);

    if ((fp = fopen(caLogFile, "a+")) == NULL)
    {
        return;
    }

    va_start(vlVar, pcaFmt);
    vfprintf(fp, pcaFmt, vlVar);
    va_end(vlVar);

    fclose(fp);
}

/*****************************************************************************/
/* FUNC:   void basDebugString(char *psLogName, char *psBuf, int iLength)   */
/* PARAMS: psLogName - 记录log的名称                                         */
/*         psBuf     - 需要记录的字符串                                      */
/*         iLength   - 字符串的长度                                          */
/* RETURN: 无                                                                */
/* DESC:   联机报文的16进制打印                                              */
/*****************************************************************************/
BAS_EXPORT void basDebugString(char *psLogName, char *psBuf, int iLength)
{
    char filename[BAS_FILENAME_LEN + 1];
    register int i, j = 0;
    char s[100], temp[5+1];
    time_t systime;
    char st[128];
    char caLogFile[BAS_FILENAME_LEN];
    FILE *fp = NULL;
    struct tm *ptmNow;
    char *pcaAppHome;

    if ((pcaAppHome = getenv("LOGHOME")) == NULL)
    {
        return;
    }

    systime = time(NULL);
    ptmNow = localtime(&systime);
    sprintf(caLogFile, "%s%s/%s/trace.%s.%04d%02d%02d.log", pcaAppHome, BAS_LOGPATH, gcaModuleName, psLogName,
            ptmNow->tm_year + 1900, ptmNow->tm_mon + 1, ptmNow->tm_mday);

    /********************************************************************/
    /*          get     current     system  time    to  register        */
    /********************************************************************/
    memset(st, 0, sizeof(st));
    strftime(st, sizeof(st), "%Y-%m-%d %H:%M:%S|%a %b %d %H:%M:%S %Y", ptmNow);

    /********************************************************************/
    /*          set     logical     file    name                        */
    /********************************************************************/
    memset(filename, 0, sizeof(filename)); /* Log File Name */
    if (strlen(caLogFile) == 0)            /* filename is "" */
    {
        strcpy(filename, "./ht.log");
    }
    else /* filename is normal string */
    {
        strcpy(filename, caLogFile);
    }

    if (fp != stderr)
    {
        if ((fp = fopen(filename, "a+")) == NULL)
            fp = stderr;
        /*
        else
        {

            memset(&statbuf, 0, sizeof(statbuf));
            nRet = stat(filename, &statbuf);
            if ( nRet == 0 && statbuf.st_size >= 1024 * 1024 * 5 )
            {
                fclose(fp);
                memset(bakfilename, 0, sizeof(bakfilename));
                sprintf(bakfilename, "%s.old", filename);
                rename(filename, bakfilename);
                if ( ( fp = fopen(filename, "a+") ) == NULL )
                    fp = stderr;
            }
        }
*/
    }

    fprintf(fp, "------------------------------------------------------------------------------\n");

    fprintf(fp, "Date:[%s] Lenth:[%04d]\n", st, iLength);

    for (i = 0; i < iLength; i++)
    {
        if (j == 0)
        {
            memset(s, ' ', sizeof(s));
            sprintf(temp, "%04d:", i);
            memcpy(s, temp, 5);
            sprintf(temp, ":%04d", i + 15);
            memcpy(&s[72], temp, 5);
        }
        sprintf(temp, "%02X ", (unsigned char)psBuf[i]);
        memcpy(&s[j * 3 + 5 + (j > 7)], temp, 3);
        if (isprint(psBuf[i]))
        {
            s[j + 55 + (j > 7)] = psBuf[i];
        }
        else
        {
            s[j + 55 + (j > 7)] = '.';
        }
        j++;
        if (j == 16)
        {
            s[77] = 0;
            fprintf(fp, "%s\n", s);
            j = 0;
        }
    }

    if (j)
    {
        s[77] = 0;
        fprintf(fp, "%s\n\n", s);
    }

    fflush(fp);

    if (fp != stderr)
        fclose(fp);

    return;
}
