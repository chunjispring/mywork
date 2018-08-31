/*  Copyright 2006, Robert Peng(robertpeng1116@gmail.com).  All right reserved.
 *
 *  THIS IS UNPUBLISHED  PROPRIETARY  SOURCE  CODE  OF Robert Peng.
 *  THE CONTENTS OF THIS FILE MAY  NOT  BE  DISCLOSED TO THIRD
 *  PARTIES, COPIED OR DUPLICATED IN ANY FORM, IN WHOLE OR IN PART,
 *  WITHOUT THE PRIOR WRITTEN PERMISSION OF Robert Peng.
 *
 *
 *  Edit History:
 *    2006/04/28 created by  Robert Peng(robertpeng1116@gmail.com)
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>

#include "bas/bas_global.h"
#include "bas/bas_usrlog.h"

#define N_MAX_PATH_LEN 256
#define N_MAX_NAME_LEN 256

//中文测试

BAS_EXPORT void _vVWriteLogAsc(char const *vspFileName, char const *vspFuncName, int vtLine,
                               char *vspLogName, char *vspFmt, va_list vstrValist)
{
    FILE *pFile;
    time_t strTime;
    struct tm *strpTm;
    char saTraceLogFileName[N_MAX_PATH_LEN + N_MAX_NAME_LEN + 1];
    char saFileName[N_MAX_NAME_LEN + 1];
    struct stat strFstat;
    char *psAppHome;

    time(&strTime);
    strpTm = localtime(&strTime);

    memset(saTraceLogFileName, 0, sizeof(saTraceLogFileName));

    sprintf(saFileName, "%s.%04d%02d%02d",
            vspLogName,
            strpTm->tm_year + 1900,
            strpTm->tm_mon + 1,
            strpTm->tm_mday);

    psAppHome = getenv("LOGHOME");

    if (psAppHome == NULL)
    {
        sprintf(saTraceLogFileName, "%s", saFileName);
    }
    else
    {
        sprintf(saTraceLogFileName, "%s/log/%s/%s", psAppHome, gcaModuleName, saFileName);
    }

    if (stat(saTraceLogFileName, &strFstat) < 0)
    {
        if ((pFile = fopen(saTraceLogFileName, "w+")) == NULL)
            return;
    }
    else
    {
        if (strFstat.st_size > N_MAX_LOG_SIZE)
        {
            if ((pFile = fopen(saTraceLogFileName, "w+")) == NULL)
                return;
        }
        else
        {
            if ((pFile = fopen(saTraceLogFileName, "a+")) == NULL)
                return;
        }
    }

    fprintf(pFile, "[%02d:%02d:%02d]",
            strpTm->tm_hour,
            strpTm->tm_min,
            strpTm->tm_sec);

    fprintf(pFile, "[%s][%s][%d]",
            vspFileName,
            vspFuncName,
            vtLine);
    fprintf(pFile, "[%-d]",
            getpid());

    vfprintf(pFile, vspFmt, vstrValist);

    fclose(pFile);
}

BAS_EXPORT void _vWriteLogAsc(char const *vspFileName, char const *vspFuncName, int vtLine,
                              char *vspLogName, char *vspFmt, ...)
{
    va_list strArgPtr;
    FILE *pFile;
    time_t strTime;
    struct tm *strpTm;
    char saTraceLogFileName[N_MAX_PATH_LEN + N_MAX_NAME_LEN + 1];
    char saFileName[N_MAX_NAME_LEN + 1];
    struct stat strFstat;
    char *psAppHome;

    time(&strTime);
    strpTm = localtime(&strTime);

    memset(saTraceLogFileName, 0, sizeof(saTraceLogFileName));

    sprintf(saFileName, "%s.%04d%02d%02d",
            vspLogName,
            strpTm->tm_year + 1900,
            strpTm->tm_mon + 1,
            strpTm->tm_mday);
    psAppHome = getenv("LOGHOME");
    if (psAppHome == NULL)
    {
        sprintf(saTraceLogFileName, "%s", saFileName);
    }
    else
    {
        sprintf(saTraceLogFileName, "%s/log/%s/%s", psAppHome, gcaModuleName, saFileName);
    }

    if (stat(saTraceLogFileName, &strFstat) < 0)
    {
        if ((pFile = fopen(saTraceLogFileName, "w+")) == NULL)
            return;
    }
    else
    {
        if (strFstat.st_size > N_MAX_LOG_SIZE)
        {
            if ((pFile = fopen(saTraceLogFileName, "w+")) == NULL)
                return;
        }
        else
        {
            if ((pFile = fopen(saTraceLogFileName, "a+")) == NULL)
                return;
        }
    }

    va_start(strArgPtr, vspFmt);

    fprintf(pFile, "[%02d:%02d:%02d]",
            strpTm->tm_hour,
            strpTm->tm_min,
            strpTm->tm_sec);

    fprintf(pFile, "[%s][%s][%d]",
            vspFileName,
            vspFuncName,
            vtLine);
    fprintf(pFile, "[%-d]",
            getpid());

    vfprintf(pFile, vspFmt, strArgPtr);
    va_end(strArgPtr);
    fclose(pFile);
}

BAS_EXPORT void _vWriteLogHex(char const *vspFileName, char const *vspFuncName, int vtLine,
                              char *vspLogName, void *vvpRawBuf, int vtLen)
{
    FILE *pFile;
    time_t strTime;
    struct tm *strpTm;
    char saTraceLogFileName[N_MAX_PATH_LEN + N_MAX_NAME_LEN + 1];
    char saFileName[N_MAX_NAME_LEN + 1];
    register unsigned int i, j, k;
    unsigned char *spRawBuf;
    //   char                    saTmpBuf[17];
    struct stat strFstat;
    char *psAppHome;

    spRawBuf = vvpRawBuf;
    time(&strTime);
    strpTm = localtime(&strTime);

    sprintf(saFileName, "%s.%04d%02d%02d",
            vspLogName,
            strpTm->tm_year + 1900,
            strpTm->tm_mon + 1,
            strpTm->tm_mday);

    psAppHome = getenv("LOGHOME");
    if (psAppHome == NULL)
    {
        sprintf(saTraceLogFileName, "%s", saFileName);
    }
    else
    {
        sprintf(saTraceLogFileName, "%s/log/%s/%s", psAppHome, gcaModuleName, saFileName);
    }

    if (stat(saTraceLogFileName, &strFstat) < 0)
    {
        if ((pFile = fopen(saTraceLogFileName, "w+")) == NULL)
            return;
    }
    else
    {
        if (strFstat.st_size > N_MAX_LOG_SIZE)
        {
            if ((pFile = fopen(saTraceLogFileName, "w+")) == NULL)
                return;
        }
        else
        {
            if ((pFile = fopen(saTraceLogFileName, "a+")) == NULL)
                return;
        }
    }

    fprintf(pFile, "[%02d:%02d:%02d]",
            strpTm->tm_hour,
            strpTm->tm_min,
            strpTm->tm_sec);

    fprintf(pFile, "[%s][%s][%d]",
            vspFileName,
            vspFuncName,
            vtLine);
    fprintf(pFile, "[%-d]length[%d]\n",
            getpid(),
            vtLen);
    j = vtLen / 16;
    for (i = 0; i < j; i++)
    {
        fprintf(pFile, "%06x: ", i * 16);
        for (k = 0; k < 16; k++)
        {
            fprintf(pFile, "%02X ", spRawBuf[i * 16 + k]);
            if (k == 7)
                fprintf(pFile, " ");
        }

        fprintf(pFile, "; ");

        for (k = 0; k < 16; k++)
        {
            if (isprint(spRawBuf[i * 16 + k]))
                fprintf(pFile, "%c", spRawBuf[i * 16 + k]);
            else
                fprintf(pFile, ".");
            if (k == 7)
                fprintf(pFile, " ");
        }
        fprintf(pFile, " :%06x\n", i * 16 + 15);
    }
    if (vtLen % 16)
    {
        fprintf(pFile, "%06x: ", j * 16);
        for (i = 0; i < 16; i++)
        {
            if (i + j * 16 < (unsigned int)vtLen)
                fprintf(pFile, "%02X ", spRawBuf[i + j * 16]);
            else
                fprintf(pFile, "   ");
            if (i == 7)
                fprintf(pFile, " ");
        }
        fprintf(pFile, "; ");
        for (i = 0; i < 16; i++)
        {
            if (i + j * 16 < (unsigned int)vtLen)
            {
                if (isprint(spRawBuf[i + j * 16]))
                    fprintf(pFile, "%c", spRawBuf[i + j * 16]);
                else
                    fprintf(pFile, ".");
            }
            else
                fprintf(pFile, " ");
            if (i % 16 == 7)
                fprintf(pFile, " ");
        }
        fprintf(pFile, " :%06x\n", j + 16 + 15);
    }
    fprintf(pFile, "\n\n");
    fclose(pFile);
}

BAS_EXPORT int _tAssertFailedLine(char const *vspFileName, char const *vspFuncName, int vtLine)
{
    _vWriteLogAsc(vspFileName, vspFuncName, vtLine, "TRCLOG", "ASSERT Failure!\n");

    return 0;
}

BAS_EXPORT void _vDebugBreak(void)
{
    usrlog("DEBUG Break!\n");
    exit(-1);
}
