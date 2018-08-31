/*******************************************************************************
 * 文件名   : mylog.c
 * 文件功能 : 日志打印相关函数
 * 编程者   : WCJ
 * 初作时间 : 2017/04/28
 * 版本     : 1.0
 * -----------------------------------------------------------------------------
 * 时间            修改者        注释
 * 2017/04/28      WCJ           初期作成
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#include <fcntl.h>    //for O_WRONLY
#include <stdarg.h>   //for va_list
#include <assert.h>   //for assert
#include <sys/stat.h> //for stat
#include <sys/types.h>
#include <errno.h> //for errno
//#include <unistd.h>    //for lseek
//#include <syslog.h>

#include "mycomm.h"
#include "shm_sharemem.h"

static char mcaFileName[PL_FILE_NAME_LEN];
static int miLineNo;
static char mcaFuncName[PL_FUN_NAME_LEN];

/*******************************************************************************
 ** 函数功能： 日志打印变量设置
 ** 输    入： __FILE__, __FUNCTION__, __LINE__
 ** 输    出： 无
 ** 返    回： 无
 *******************************************************************************/
void myLogFileLine(const char *c_sFileName, const char *c_sFunName, int iLineNo)
{
    strcpy(mcaFileName, c_sFileName);
    strcpy(mcaFuncName, c_sFunName);
    miLineNo = iLineNo;
}

/*******************************************************************************
 ** 函数功能： 日志打印功能实现
 ** 输    入： 日志级别, 要打印的内容
 ** 输    出： 日志文件内容
 ** 返    回： 无
 *******************************************************************************/
void myLog(int ilLogLevel, char *c_sMsg, ...)
{
    FILE *fp;
    int  ilTraceLevel = 0; /* 默认当前日志级别 */
    char *plEnv = NULL;
    char aczLogPath[PL_FILE_NAME_LEN];
    char alLogDate[PL_DATE_AND_TIME_LEN];
    char aczLogHour[PL_DATE_AND_TIME_LEN];
    char aczTime[PL_DATE_AND_TIME_LEN];
    char aczFname[PL_FILE_NAME_LEN];
    char aczFnameBak[PL_FILE_NAME_LEN];

    char aczFunInfo[PL_LINE_LENGTH];
    char aczMsg[PL_COMMON_MSG_LEN];

    char aczBuf[PL_COMMON_MSG_LEN];
    char aczBuf1[PL_COMMON_MSG_LEN];

    off_t lFileSize = 0;
    va_list vlist;

    memset(aczLogPath, 0x00, sizeof(aczLogPath));
    memset(alLogDate, 0x00, sizeof(alLogDate));
    memset(aczLogHour, 0x00, sizeof(aczLogHour));
    memset(aczTime, 0x00, sizeof(aczTime));
    memset(aczMsg, 0x00, sizeof(aczMsg));
    memset(aczFname, 0x00, sizeof(aczFname));
    memset(aczFnameBak, 0x00, sizeof(aczFnameBak));
    memset(aczBuf, 0x00, sizeof(aczBuf));
    memset(aczBuf1, 0x00, sizeof(aczBuf1));
    memset(aczFunInfo, 0x00, sizeof(aczFunInfo));

    //连接共享内存
    if (CumShmAttach() != SUCCESS)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "共享内存连接错误！");
        return;
    }

    /* 获取当前日志级别 */
    if ((plEnv = (char *)getenv("TRACE_LEVEL")) != NULL)
    {
        ilTraceLevel = atoi(plEnv);
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "取环境变量中的日志级别：%d\n", ilTraceLevel);
    }
    else
    {
        ilTraceLevel = gtpShmBuf->taStatic[gnSecId].iLogLevel;
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "取共享内存中的日志级别：%d\n", ilTraceLevel);
    }

    /** 如果日值级别 ilLogLevel > TRACE_LEVEL定义的当前日志数据级别的话,不记录日志信息 */
    if (ilLogLevel > ilTraceLevel)
    {
        return;
    }

    /* 获取当前日志目录 */
    if (SUCCESS != GetLogPath(aczLogPath))
    {
        //snprintf(aczLogPath, PL_FILE_NAME_LEN, "~/log");
        //没有配置MYLOGDIR环境变量，则取共享内存中的
        strncpy(aczLogPath, gtpShmBuf->taStatic[gnSecId].acLogPath, sizeof(aczLogPath));
    }

    /* 设置默认文件名 */
    if (strlen(gcaSysLogProg) == 0)
    {
        strcpy(gcaSysLogProg, "default");
    }

    /* 组成当前日志文件名 */
    GetSysTime(alLogDate, "yyyymmdd");
    snprintf(aczFname, PL_FILE_NAME_LEN, "%s/log_%s_%s.%s", aczLogPath, gcaSysLogModule, gcaSysLogProg, alLogDate);

    /** 向日志文件写入日志信息 **/
    if ((fp = fopen(aczFname, "a+")) == NULL)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "PL_FILE_OPEN_ERROR");
        return;
    }

    /* 计算日志文件的长度，如超过PL_FILE_SIZE，则生成一个备份文件 */
    fseek(fp, 0, SEEK_END);
    if ((lFileSize = ftell(fp)) == -1)
    {
        fclose(fp);
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "PL_FILE_SEEK_ERROR");
        return;
    }

    if (lFileSize >= PL_FILE_SIZE)
    {
        GetSysTime(aczLogHour, "hhmmss");
        snprintf(aczFnameBak, PL_FILE_NAME_LEN, "%s.%s", aczFname, aczLogHour);

        if ((rename(aczFname, aczFnameBak)) < 0)
        {
            fclose(fp);
            COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "PL_RENAME_ERROR");
            return;
        }
    }

    if (*c_sMsg)
    {
        va_start(vlist, c_sMsg);
        vsprintf(aczMsg, c_sMsg, vlist);
        va_end(vlist);
    }

    GetSysTime(aczTime, "log");
    switch (ilLogLevel)
    {
    case PRINT:
        snprintf(aczBuf1, PL_COMMON_MSG_LEN, "%s|%5d|%s|", aczTime + 2, (int)getpid(), "P");
        break;
    case ERROR:
        snprintf(aczBuf1, PL_COMMON_MSG_LEN, "%s|%5d|%s|", aczTime + 2, (int)getpid(), "E");
        break;
    case DEBUG:
        snprintf(aczBuf1, PL_COMMON_MSG_LEN, "%s|%5d|%s|", aczTime + 2, (int)getpid(), "D");
        break;
    case INFO:
        snprintf(aczBuf1, PL_COMMON_MSG_LEN, "%s|%5d|%s|", aczTime + 2, (int)getpid(), "I");
        break;
    case TRACE:
        snprintf(aczBuf1, PL_COMMON_MSG_LEN, "%s|%5d|%s|", aczTime + 2, (int)getpid(), "T");
        break;
    default:
        snprintf(aczBuf1, PL_COMMON_MSG_LEN, "%s|%5d|%s|", aczTime + 2, (int)getpid(), "U");
        break;
    }

    snprintf(aczFunInfo, sizeof(aczFunInfo), "%4d|%s:%s", miLineNo, mcaFileName, mcaFuncName);
    if (aczFunInfo[PL_FUN_NAME_LEN] != '\0')
    {
        aczFunInfo[PL_FUN_NAME_LEN - 1] = '*';
        aczFunInfo[PL_FUN_NAME_LEN] = '\0';
    }
    snprintf(aczBuf, sizeof(aczBuf), "%s %-*s > %s", aczBuf1, PL_FUN_NAME_LEN, aczFunInfo, aczMsg);

    fprintf(fp, "%s\n", aczBuf);

    fclose(fp);

    //断开共享内存
    CumShmDetach();

    return;
}

/*******************************************************************************
 ** 函数功能： 全量日志打印功能实现
 ** 输    入： __FILE__宏,__LINE__宏,__FUNCTION__宏,要打印的内容
 ** 输    出： 日志文件内容
 ** 返    回： 无
 *******************************************************************************/
void COMM_Trace(const char *c_sFileName, int iLineNo, const char *c_sFunName, char *c_sMsg, ...)
{
    FILE *fp;
    char *plEnv = NULL;
    char aczLogPath[PL_FILE_NAME_LEN];
    char alLogDate[PL_DATE_AND_TIME_LEN];
    char aczLogHour[PL_DATE_AND_TIME_LEN];
    char aczTime[PL_DATE_AND_TIME_LEN];
    char aczFname[PL_FILE_NAME_LEN];
    char aczFnameBak[PL_FILE_NAME_LEN];

    char aczFunInfo[PL_LINE_LENGTH];
    char aczMsg[PL_COMMON_MSG_LEN];

    char aczBuf[PL_COMMON_MSG_LEN];
    char aczBuf1[PL_COMMON_MSG_LEN];

    off_t lFileSize = 0;
    va_list vlist;

    memset(aczLogPath, 0x00, sizeof(aczLogPath));
    memset(alLogDate, 0x00, sizeof(alLogDate));
    memset(aczLogHour, 0x00, sizeof(aczLogHour));
    memset(aczTime, 0x00, sizeof(aczTime));
    memset(aczMsg, 0x00, sizeof(aczMsg));
    memset(aczFname, 0x00, sizeof(aczFname));
    memset(aczFnameBak, 0x00, sizeof(aczFnameBak));
    memset(aczBuf, 0x00, sizeof(aczBuf));
    memset(aczBuf1, 0x00, sizeof(aczBuf1));
    memset(aczFunInfo, 0x00, sizeof(aczFunInfo));

    /* 日志目录指定 */
    if ((plEnv = (char *)getenv("WKPATH")) != NULL)
    {
        /* 组成当前日志文件名 */
        GetSysTime(alLogDate, "yyyymmdd");
        snprintf(aczFname, PL_FILE_NAME_LEN, "%s/log/log_default.%s", plEnv, alLogDate);
    }
    else
    {
        printf("取环境变量WKPATH失败\n");
        exit(FAILURE);
    }

    /** 向日志文件写入日志信息 **/
    if ((fp = fopen(aczFname, "a+")) == NULL)
    {
        return;
    }

    /* 计算日志文件的长度，如超过PL_FILE_SIZE，则生成一个备份文件 */
    fseek(fp, 0, SEEK_END);
    if ((lFileSize = ftell(fp)) == -1)
    {
        fclose(fp);
        return;
    }

    if (lFileSize >= PL_FILE_SIZE)
    {
        GetSysTime(aczLogHour, "hhmmss");
        snprintf(aczFnameBak, PL_FILE_NAME_LEN, "%s.%s", aczFname, aczLogHour);

        if ((rename(aczFname, aczFnameBak)) < 0)
        {
            fclose(fp);
            return;
        }
    }

    if (*c_sMsg)
    {
        va_start(vlist, c_sMsg);
        vsprintf(aczMsg, c_sMsg, vlist);
        va_end(vlist);
    }

    GetSysTime(aczTime, "log");
    snprintf(aczFunInfo, sizeof(aczFunInfo), "%4d|%s:%s", iLineNo, c_sFileName, c_sFunName);
    if (aczFunInfo[PL_FUN_NAME_LEN] != '\0')
    {
        aczFunInfo[PL_FUN_NAME_LEN - 1] = '*';
        aczFunInfo[PL_FUN_NAME_LEN] = '\0';
    }
    snprintf(aczBuf, sizeof(aczBuf), "[%s] [%5d] %s %-*s > %s", aczTime + 2, (int)getpid(), "[P]", PL_FUN_NAME_LEN, aczFunInfo, aczMsg);

    fprintf(fp, "%s\n", aczBuf);

    fclose(fp);

    return;
}
