/*******************************************************************************
 * 文件名   : mytime.c
 * 文件功能 : 时间和日期相关函数
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
//#include <sys/time.h>
#include <linux/time.h>
#include <time.h>

#include "mycomm.h"

/*******************************************************************************
 ** 函数功能： 获取系统时间
 ** 输    入： 需要返回的时间格式
 ** 输    出： 系统时间字符串
 ** 返    回： 无
 *******************************************************************************/
void GetSysTime(char *c_sDate, char *c_sFlag)
{
    //    time_t t;
    //    struct tm *tp;
    //    t=time(NULL);
    //    tp=localtime(&t);

    time_t now;
    now = time(NULL);

    if (strcmp(c_sFlag, "yyyymmdd") == 0)
    {
        //        sprintf(c_sDate,"%04d%02d%02d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);
        strftime(c_sDate, DATETIMELEN, "%Y%m%d", localtime(&now));
    }
    else if (strcmp(c_sFlag, "yyyy-mm-dd") == 0)
    {
        //        sprintf(c_sDate,"%04d-%02d-%02d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);
        strftime(c_sDate, DATETIMELEN, "%Y-%m-%d", localtime(&now));
    }
    else if (strcmp(c_sFlag, "yyyymm") == 0)
    {
        //        sprintf(c_sDate,"%04d%02d",tp->tm_year+1900,tp->tm_mon+1);
        strftime(c_sDate, DATETIMELEN, "%Y%m", localtime(&now));
    }
    else if (strcmp(c_sFlag, "hhmmss") == 0)
    {
        //        sprintf(c_sDate,"%02d%02d%02d",tp->tm_hour,tp->tm_min,tp->tm_sec);
        strftime(c_sDate, DATETIMELEN, "%H%M%S", localtime(&now));
    }
    else if (strcmp(c_sFlag, "hhmm") == 0)
    {
        //        sprintf(c_sDate,"%02d%02d",tp->tm_hour,tp->tm_min);
        strftime(c_sDate, DATETIMELEN, "%H%M", localtime(&now));
    }
    else if (strcmp(c_sFlag, "mmdd") == 0)
    {
        //        sprintf(c_sDate,"%02d%02d",tp->tm_mon+1,tp->tm_mday);
        strftime(c_sDate, DATETIMELEN, "%m%d", localtime(&now));
    }
    else if (strcmp(c_sFlag, "yyyymmddhhmmss") == 0)
    {
        /*        sprintf(c_sDate,"%04d%02d%02d%02d%02d%02d",\
                tp->tm_year+1900,\
                tp->tm_mon+1,\
                tp->tm_mday,\
                tp->tm_hour,\
                tp->tm_min,\
                tp->tm_sec); */
        strftime(c_sDate, DATETIMELEN, "%Y%m%d%H%M%S", localtime(&now));
    }
    else if (strcmp(c_sFlag, "julia") == 0)
    {
        //        sprintf(c_sDate,"%04d%03d",tp->tm_year+1900,tp->tm_yday);
        strftime(c_sDate, DATETIMELEN, "%Y%j", localtime(&now));
    }
    else if (strcmp(c_sFlag, "log") == 0)
    {
        /*        sprintf(c_sDate, "%04d%02d%02d-%02d:%02d:%02d",\
                (1900+tp->tm_year),\
                (1+tp->tm_mon),\
                tp->tm_mday,\
                tp->tm_hour,\
                tp->tm_min,\
                tp->tm_sec); */
        strftime(c_sDate, DATETIMELEN, "%Y%m%d-%H:%M:%S", localtime(&now));
    }
    else if (strcmp(c_sFlag, "log2") == 0)
    {
        /*        sprintf(c_sDate, "%04d%02d%02d %02d:%02d:%02d",\
                (1900+tp->tm_year),\
                (1+tp->tm_mon),\
                tp->tm_mday,\
                tp->tm_hour,\
                tp->tm_min,\
                tp->tm_sec); */
        strftime(c_sDate, DATETIMELEN, "%Y-%m-%d %H:%M:%S", localtime(&now));
    }
    else
    {
        sprintf(c_sDate, "参数错误!");
    }

    return;
}

/*******************************************************************************
 ** 函数功能： 取系统时间的 百万分之一秒（仅供调试使用）
 ** 输    入： 无
 ** 输    出： 返回的系统时间字符串, >=13位
 ** 返    回： 无
 *******************************************************************************/
void GetMicroTime(char *microtime)
{
    struct tm *ttm;
    struct timeval tvalue;
    struct timezone tz;
    time_t lt;
    time(&lt);
    ttm = localtime(&lt);

    gettimeofday(&tvalue, &tz);
    sprintf(microtime, "%02d%02d%02d %6ld", ttm->tm_hour, ttm->tm_min, ttm->tm_sec, tvalue.tv_usec);
    return;
}

int GetMicroTime2(int lineno)
{
    struct timeval tvalue;
    struct timezone tz;
    gettimeofday(&tvalue, &tz);

    printf("Line no:%d [%ld].[%ld]\n", lineno, tvalue.tv_sec, tvalue.tv_usec);
    return 0;
}

/*******************************************************************************
 ** 函数功能： 检查日期合法性
 ** 输    入： 8位日期
 ** 输    出： 无
 ** 返    回： 成功：SUCCESS  失败：FAILURE
 *******************************************************************************/
int CheckSingleDate(char *pDate)
{
    char year[4 + 1];
    char month[2 + 1];
    char day[2 + 1];
    int dayflag = 0;

    /* 判断日期长度是否是 8 位 */
    if (strlen(pDate) != 8)
    {
        return FAILURE;
    }

    memset(year, 0x00, sizeof(year));
    memset(month, 0x00, sizeof(month));
    memset(day, 0x00, sizeof(day));

    memcpy(year, pDate, 4);
    memcpy(month, pDate + 4, 2);
    memcpy(day, pDate + 6, 2);

    /* 判断年份是否正确 */
    if (atoi(year) > 3000 || atoi(year) < 1900)
    {
        return FAILURE;
    }
    /* 判断月份是否正确 */
    if (atoi(month) > 12 || atoi(month) < 1)
    {
        return FAILURE;
    }

    /* 判断日期是否正确 */
    if (atoi(day) > 31 || atoi(day) < 1)
        dayflag = -1;

    if (atoi(month) == 4 || atoi(month) == 6 || atoi(month) == 9 || atoi(month) == 11)
    {
        if (atoi(day) > 30 || atoi(day) < 1)
            dayflag = -2;
    }
    else if (atoi(month) == 2)
    {
        if (atoi(year) % 4 == 0 && atoi(year) % 100 != 0 || atoi(year) % 400 == 0)
        {
            if (atoi(day) > 29)
                dayflag = -3;
        }
        else
        {
            if (atoi(day) > 28)
                dayflag = -4;
        }
    }
    if (dayflag != 0)
    {
        return FAILURE;
    }
    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 计算两个日期之间相差的月数
 ** 输    入： 日期一  日期二
 ** 输    出： 相差月数
 ** 返    回： 成功：SUCCESS   失败：FAILURE
 *******************************************************************************/
int MonthDiff(char *pBgTime, char *pEndTime, int *iDiffMonth)
{
    char aBgYear[4 + 1], aEndYear[4 + 1];
    char aBgMonth[2 + 1], aEndMonth[2 + 1];
    if (strlen(pBgTime) < 4 || strlen(pEndTime) < 4)
    {
        //        DEBUGMSG("MonthDiff error,参数错误 pBgTime == [%s] pEndTime == [%s]",pBgTime,pEndTime);
        COMM_Trace(__FILE__, __LINE__, "MonthDiff error,参数错误 pBgTime == [%s] pEndTime == [%s]", pBgTime, pEndTime);
        return FAILURE;
    }
    memset(aBgYear, 0, sizeof(aBgYear));
    memset(aEndYear, 0, sizeof(aEndYear));
    memset(aBgMonth, 0, sizeof(aBgMonth));
    memset(aEndMonth, 0, sizeof(aEndMonth));

    memcpy(aBgYear, pBgTime, 4);
    memcpy(aEndYear, pEndTime, 4);
    memcpy(aBgMonth, pBgTime + 4, 2);
    memcpy(aEndMonth, pEndTime + 4, 2);
    (*iDiffMonth) = (atol(aBgYear) - atol(aEndYear)) * 12 + (atol(aBgMonth) - atol(aEndMonth));

    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 将14位的日期字符串转换成长整型
 ** 输    入： 要转换的日期
 ** 输    出： 无
 ** 返    回： 转换后的长整型秒数
 *******************************************************************************/
long DateToLong(char *aDate)
{
    long llTime;
    struct tm sTime;
    char alTmpyear[4 + 1];
    char alTmpmon[2 + 1];
    char alTmpday[2 + 1];
    char alTmphour[2 + 1];
    char alTmpmin[2 + 1];
    char alTmpsec[2 + 1];

    memset(alTmpyear, 0, sizeof(alTmpyear));
    memset(alTmpmon, 0, sizeof(alTmpmon));
    memset(alTmpday, 0, sizeof(alTmpday));
    memset(alTmphour, 0, sizeof(alTmphour));
    memset(alTmpmin, 0, sizeof(alTmpmin));
    memset(alTmpsec, 0, sizeof(alTmpsec));

    memcpy(alTmpyear, aDate, 4);
    memcpy(alTmpmon, aDate + 4, 2);
    memcpy(alTmpday, aDate + 6, 2);
    memcpy(alTmphour, aDate + 8, 2);
    memcpy(alTmpmin, aDate + 10, 2);
    memcpy(alTmpsec, aDate + 12, 2);

    sTime.tm_sec = atoi(alTmpsec);
    sTime.tm_min = atoi(alTmpmin);
    sTime.tm_hour = atoi(alTmphour);
    sTime.tm_mday = atoi(alTmpday);
    sTime.tm_mon = atoi(alTmpmon) - 1;
    sTime.tm_year = atoi(alTmpyear) - 1900;

    llTime = mktime(&sTime);
    return (llTime);
}

/*******************************************************************************
 ** 函数功能： 将长整型的时间转换为字符串型
 ** 输    入： iDateTime 长整型的时间  pcFormat 时间的格式
 ** 输    出： pcDateTime 字符串型的时间
 ** 返    回： 0 -- 成功  -1 --失败
 *******************************************************************************/
int LongToDate(long lDateTime, char *pcDateTime, char *pcFormat)
{
    struct tm *sttm;
    sttm = localtime(&lDateTime);
    //memset(pcDateTime, 0x00, sizeof(pcDateTime));
    if (strcmp(pcFormat, "YYMMDD") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%02d%02d%02d", (sttm->tm_year + 1900) % 100, sttm->tm_mon + 1, sttm->tm_mday);
        else
            strcpy(pcDateTime, "------");
    }
    else if (strcmp(pcFormat, "YYYYMMDD") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%04d%02d%02d", sttm->tm_year + 1900, sttm->tm_mon + 1, sttm->tm_mday);
        else
            strcpy(pcDateTime, "--------");
    }
    else if (strcmp(pcFormat, "YYYYMMDDHHMMSS") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%04d%02d%02d%02d%02d%02d", sttm->tm_year + 1900, sttm->tm_mon + 1,
                    sttm->tm_mday, sttm->tm_hour, sttm->tm_min, sttm->tm_sec);
        else
            strcpy(pcDateTime, "--------------");
    }
    else if (strcmp(pcFormat, "YYYY-MM-DD HH:MM:SS") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%04d-%02d-%02d %02d:%02d:%02d", sttm->tm_year + 1900,
                    sttm->tm_mon + 1, sttm->tm_mday, sttm->tm_hour, sttm->tm_min, sttm->tm_sec);
        else
            strcpy(pcDateTime, "----/--/-- --:--:--");
    }
    else if (strcmp(pcFormat, "HHMMSS") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%02d%02d%02d", sttm->tm_hour, sttm->tm_min, sttm->tm_sec);
        else
            strcpy(pcDateTime, "------");
    }
    else if (strcmp(pcFormat, "HH:MM:SS") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%02d:%02d:%02d", sttm->tm_hour, sttm->tm_min, sttm->tm_sec);
        else
            strcpy(pcDateTime, "--:--:--");
    }
    else if (strcmp(pcFormat, "MMDD") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%02d%02d", sttm->tm_mon + 1, sttm->tm_mday);
        else
            strcpy(pcDateTime, "----");
    }
    else if (strcmp(pcFormat, "MMDDHHMMSS") == 0)
    {
        if (lDateTime)
            sprintf(pcDateTime, "%02d%02d%02d%02d%02d", sttm->tm_mon + 1, sttm->tm_mday,
                    sttm->tm_hour, sttm->tm_min, sttm->tm_sec);
        else
            strcpy(pcDateTime, "----------");
    }
    else
    {
        if (lDateTime)
            sprintf(pcDateTime, "%04d-%02d-%02d %02d:%02d:%02d", sttm->tm_year + 1900,
                    sttm->tm_mon + 1, sttm->tm_mday, sttm->tm_hour, sttm->tm_min, sttm->tm_sec);
        else
            strcpy(pcDateTime, "----/--/-- --:--:--");
    }
    return (0);
}

/*******************************************************************************
 ** 函数功能： 日期转换，加减指定天数
 ** 输    入： aCurrDate--需要转换的日期(8位), iDayNum--天数
 ** 输    出： aNewDate   --处理后的新日期
 ** 返    回： 0 -- 成功  -1 --失败
 *******************************************************************************/
int DateOpertion(char *aCurrDate, int iDayNum, char *aNewDate)
{
    char date[14 + 1];
    long lOldTime = 0;
    long lNewTime = 0;

    if (strlen(aCurrDate) != 8)
        return (FAILURE);
    memset(date, 0x00, sizeof(date));
    strcpy(date, aCurrDate);
    strcat(date, "000001");
    lOldTime = DateToLong(date);
    lNewTime = lOldTime + 86400 * iDayNum;
    LongToDate(lNewTime, aNewDate, "YYYYMMDD");

    return (SUCCESS);
}

/*******************************************************************************
 ** 函数功能： 打印当前系统时间
 ** 输    入： 无
 ** 输    出： 无
 ** 返    回： 无
 *******************************************************************************/
void printTime()
{
    time_t t;
    struct tm *tp;
    char *week[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};

    t = time(NULL);
    tp = localtime(&t);

    printf("%d年%02d月%02d日 %02d:%02d:%02d ", (1900 + tp->tm_year),
           (1 + tp->tm_mon),
           tp->tm_mday,
           tp->tm_hour,
           tp->tm_min,
           tp->tm_sec);

    printf("%s\n", week[tp->tm_wday]);

    return;
}
