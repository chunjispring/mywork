/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_log.c                                                   */
/* DESCRIPTIONS: 系统日志接口                                                */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "bas/bas_global.h"
#include "bas/bas_profile.h"

/*****************************************************************************/
/* FUNC:   char *basGetSysDate(void);                                        */
/* PARAMS: 无                                                                */
/* RETURN: 格式YYYYMMDD                                                      */
/* DESC:   取得UNIX日期                                                      */
/*****************************************************************************/
BAS_EXPORT char *basGetSysDate(void)
{
	static char caTimeBuf[8 + 1];

	struct tm *ptTimeStruct;
	time_t tTimeVal;

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	if ((tTimeVal = time(NULL)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysDate:time调用失败");
		return caTimeBuf;
	}
	if ((ptTimeStruct = localtime(&tTimeVal)) == NULL)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysDate:localtime调用失败");
		return caTimeBuf;
	}

	sprintf(caTimeBuf, "%04d%02d%02d",
			ptTimeStruct->tm_year + 1900,
			ptTimeStruct->tm_mon + 1,
			ptTimeStruct->tm_mday);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   char *basGetSysTime(void)                                         */
/* PARAMS: 无                                                                */
/* RETURN: 格式HHMMSS                                                        */
/* DESC:   取得UNIX时间                                                      */
/*****************************************************************************/
BAS_EXPORT char *basGetSysTime(void)
{
	static char caTimeBuf[6 + 1];

	struct tm *ptTimeStruct;
	time_t tTimeVal;

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	if ((tTimeVal = time(NULL)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysTime:time调用失败");
		return caTimeBuf;
	}
	if ((ptTimeStruct = localtime(&tTimeVal)) == NULL)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysTime:localtime调用失败");
		return caTimeBuf;
	}

	sprintf(caTimeBuf, "%02d%02d%02d",
			ptTimeStruct->tm_hour,
			ptTimeStruct->tm_min,
			ptTimeStruct->tm_sec);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   char *basGetSysTimestamp(void)                                    */
/* PARAMS: 无                                                                */
/* RETURN: 格式HHMMSSMS (6位MS)                                              */
/* DESC:   取得UNIX时间                                                      */
/*****************************************************************************/
BAS_EXPORT char *basGetSysTimestamp(void)
{
	static char caTimeBuf[12 + 1];

	struct tm *ptTimeStruct;
	struct timeval tTimeValue;
	//	time_t tTimeVal;

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	if (gettimeofday(&tTimeValue, NULL) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysTimestamp:gettimeofday调用失败");
		return caTimeBuf;
	}
	if ((ptTimeStruct = localtime(&(tTimeValue.tv_sec))) == NULL)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysTimestamp:localtime调用失败");
		return caTimeBuf;
	}

	sprintf(caTimeBuf, "%02d%02d%02d%06d",
			ptTimeStruct->tm_hour,
			ptTimeStruct->tm_min,
			ptTimeStruct->tm_sec,
			(int)tTimeValue.tv_usec);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   char *basGetGmDate(void);                                         */
/* PARAMS: 无                                                                */
/* RETURN: 格式YYYYMMDD                                                      */
/* DESC:   取得UNIX格林威治日期                                              */
/*****************************************************************************/
BAS_EXPORT char *basGetGmDate(void)
{
	static char caTimeBuf[8 + 1];

	struct tm *ptTimeStruct;
	time_t tTimeVal;

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	if ((tTimeVal = time(NULL)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetGmDate:time调用失败");
		return caTimeBuf;
	}
	if ((ptTimeStruct = gmtime(&tTimeVal)) == NULL)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetGmDate:localtime调用失败");
		return caTimeBuf;
	}

	sprintf(caTimeBuf, "%04d%02d%02d",
			ptTimeStruct->tm_year + 1900,
			ptTimeStruct->tm_mon + 1,
			ptTimeStruct->tm_mday);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   char *basGetGmTime(void)                                          */
/* PARAMS: 无                                                                */
/* RETURN: 格式HHMMSS                                                        */
/* DESC:   取得UNIX格林威治时间                                              */
/*****************************************************************************/
BAS_EXPORT char *basGetGmTime(void)
{
	static char caTimeBuf[6 + 1];

	struct tm *ptTimeStruct;
	time_t tTimeVal;

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	if ((tTimeVal = time(NULL)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetGmTime:time调用失败");
		return caTimeBuf;
	}
	if ((ptTimeStruct = gmtime(&tTimeVal)) == NULL)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetGmTime:localtime调用失败");
		return caTimeBuf;
	}

	sprintf(caTimeBuf, "%02d%02d%02d",
			ptTimeStruct->tm_hour,
			ptTimeStruct->tm_min,
			ptTimeStruct->tm_sec);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   int basCalDiffTwoDays(const char *pcaBeginDate,                   */
/*                               const char *pcaEndDate, int *piDays)        */
/* PARAMS: pcaBeginDate - 开始的日期(YYYYMMDD) (I)                           */
/*         pcaEndDate   - 结束的日期(YYYYMMDD) (I)                           */
/* RETURN: 天数                                                              */
/* DESC:   计算caBeginDate和caEndDate之间的天数                              */
/*****************************************************************************/
BAS_EXPORT int basCalDiffTwoDays(const char *pcaBeginDate, const char *pcaEndDate, int *piDays)
{
	char caYear[5], caMonth[3], caDay[3];
	struct tm tTime1, tTime2;
	//time_t		tTimeVal1, tTimeVal2, tTimeDummy;
	time_t tTimeVal1, tTimeVal2;

	memset(caYear, 0, sizeof(caYear));
	memset(caMonth, 0, sizeof(caMonth));
	memset(caDay, 0, sizeof(caDay));

	/* 构造date 1 */
	memcpy(caYear, pcaBeginDate, 4);
	memcpy(caMonth, pcaBeginDate + 4, 2);
	memcpy(caDay, pcaBeginDate + 6, 2);

	tTime1.tm_year = atoi(caYear) - 1900;
	tTime1.tm_mon = atoi(caMonth) - 1;
	tTime1.tm_mday = atoi(caDay);
	tTime1.tm_hour = 0;
	tTime1.tm_min = 0;
	tTime1.tm_sec = 1;
	tTime1.tm_isdst = -1;

	if ((tTimeVal1 = mktime(&tTime1)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basCalDiffTwoDays:mktime调用失败:[%s]:[%s]", pcaBeginDate, pcaEndDate);
		return -1;
	}

	/* 改造date 2 */
	memcpy(caYear, pcaEndDate, 4);
	memcpy(caMonth, pcaEndDate + 4, 2);
	memcpy(caDay, pcaEndDate + 6, 2);

	tTime2.tm_year = atoi(caYear) - 1900;
	tTime2.tm_mon = atoi(caMonth) - 1;
	tTime2.tm_mday = atoi(caDay);
	tTime2.tm_hour = 0;
	tTime2.tm_min = 0;
	tTime2.tm_sec = 1;
	tTime2.tm_isdst = -1;

	if ((tTimeVal2 = mktime(&tTime2)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basCalDiffTwoDays:mktime调用失败:[%s]:[%s]", pcaBeginDate, pcaEndDate);
		return -1;
	}

	/* 计算日期间隔 */
	if (tTimeVal2 > tTimeVal1)
	{
		*piDays = (int)(difftime(tTimeVal2, tTimeVal1) / 24 / 60 / 60 + 0.5);
	}
	else
	{
		*piDays = (int)(difftime(tTimeVal2, tTimeVal1) / 24 / 60 / 60 - 0.5);
	}
	/* +0.5 修正如果系统设置是夏令时，可能产生1小时误差 */

	return 0;
}

/*****************************************************************************/
/* FUNC:   int basCalDiffTwoMonths(const char *pcaBeginMonth,                */
/*                                 const char *pcaEndMonth, int *piMonths)   */
/* PARAMS: pcaBeginMonth - 开始的月(YYYYMM) (I)                              */
/*         pcaEndMonth   - 结束的月(YYYYMM) (I)                              */
/* RETURN: 天数                                                              */
/* DESC:   计算caBeginMonth和caEndMonth之间的天数                            */
/*****************************************************************************/
BAS_EXPORT int basCalDiffTwoMonths(const char *pcaBeginMonth, const char *pcaEndMonth, int *piMonths)
{
	char caBeginYear[5], caEndYear[5];
	char caBeginMonth[3], caEndMonth[3];

	memset(caBeginYear, 0, sizeof(caBeginYear));
	memset(caEndYear, 0, sizeof(caEndYear));
	memset(caBeginMonth, 0, sizeof(caBeginMonth));
	memset(caEndMonth, 0, sizeof(caEndMonth));

	memcpy(caBeginYear, pcaBeginMonth, 4);
	memcpy(caEndYear, pcaEndMonth, 4);
	memcpy(caBeginMonth, pcaBeginMonth + 4, 2);
	memcpy(caEndMonth, pcaEndMonth + 4, 2);

	*piMonths = (atoi(caEndYear) - atoi(caBeginYear)) * 12 + atoi(caEndMonth) - atoi(caBeginMonth);

	return 0;
}

/*****************************************************************************/
/* FUNC:   char *basAddDays(const char *pcaBeginDate, int iDays)             */
/* PARAMS: pcaBeginDate - 开始的日期(YYYYMMDD) (I)                           */
/*         iDays       - 天数                                                */
/* RETURN: 日前,格式YYYYMMDD                                                 */
/* DESC:   计算caBeginDay之后iDay天的日期                                    */
/*****************************************************************************/
BAS_EXPORT char *basAddDays(const char *pcaBeginDate, int iDays)
{
	static char caTimeBuf[9];
	struct tm tTime, *ptTime;
	time_t tTimeNow;
	char caYear[5], caMonth[3], caDay[3];

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	memset(caYear, 0, sizeof(caYear));
	memset(caMonth, 0, sizeof(caMonth));
	memset(caDay, 0, sizeof(caDay));

	memcpy(caYear, pcaBeginDate, 4);
	memcpy(caMonth, pcaBeginDate + 4, 2);
	memcpy(caDay, pcaBeginDate + 6, 2);

	tTime.tm_year = atoi(caYear) - 1900;
	tTime.tm_mon = atoi(caMonth) - 1;
	tTime.tm_mday = atoi(caDay);
	tTime.tm_hour = 3; /* 修正夏令时产生的误差 */
	tTime.tm_min = 0;
	tTime.tm_sec = 1;
	tTime.tm_isdst = -1;

	if ((tTimeNow = mktime(&tTime)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basAddDays:mktime调用失败:[%s]:[%d]", pcaBeginDate, iDays);
		return caTimeBuf;
	}
	tTimeNow += iDays * (24 * 60 * 60);

	ptTime = localtime(&tTimeNow);

	sprintf(caTimeBuf, "%04d%02d%02d",
			ptTime->tm_year + 1900,
			ptTime->tm_mon + 1,
			ptTime->tm_mday);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   char *basSubDays(const char *pcaBeginDate, int iDays)             */
/* PARAMS: pcaBeginDate - 开始的日期(YYYYMMDD) (I)                           */
/*         iDays        - 天数                                               */
/* RETURN: 日前,格式YYYYMMDD                                                 */
/* DESC:   计算caBeginDay之前iDay天的日期                                    */
/*****************************************************************************/
BAS_EXPORT char *basSubDays(const char *pcaBeginDate, int iDays)
{
	return basAddDays(pcaBeginDate, -iDays);
}

/*****************************************************************************/
/* FUNC:   char *basAddMonths(const char *pcaBeginMonth, int iMonths)        */
/* PARAMS: pcaBeginMonth - 开始的月(YYYYMM) (I)                              */
/*         iMonths       - 月数                                              */
/* RETURN: 日前,格式YYYYMM                                                   */
/* DESC:   计算caBeginMonth之后iMonths月的日期                               */
/*****************************************************************************/
BAS_EXPORT char *basAddMonths(const char *pcaBeginMonth, int iMonths)
{
	static char caBuf[8 + 1];
	char caYear[5], caMonth[3], caDay[3];
	struct tm tTime;
	time_t tTimeVal;
	long lValue;

	memset(caBuf, 0, sizeof(caBuf));
	memset(caYear, 0, sizeof(caYear));
	memset(caMonth, 0, sizeof(caMonth));
	memset(caDay, 0, sizeof(caDay));

	memcpy(caYear, pcaBeginMonth, 4);
	memcpy(caMonth, pcaBeginMonth + 4, 2);
	if (pcaBeginMonth[6] == 0)
	{
		strcpy(caDay, "01");
	}
	else
	{
		memcpy(caDay, pcaBeginMonth + 6, 2);
	}

	lValue = atol(caYear) * 12 + atol(caMonth) + iMonths - 1;

	sprintf(caYear, "%04d", (int)((lValue) / 12));
	sprintf(caMonth, "%02d", (int)((lValue) % 12 + 1));

	while (1)
	{
		struct tm *ptTimeStruct;
		char caBufTmp[8 + 1];

		tTime.tm_year = atoi(caYear) - 1900;
		tTime.tm_mon = atoi(caMonth) - 1;
		tTime.tm_mday = atoi(caDay);
		tTime.tm_hour = 0;
		tTime.tm_min = 0;
		tTime.tm_sec = 1;
		tTime.tm_isdst = -1;

		sprintf(caBuf, "%s%s%s", caYear, caMonth, caDay);

		if ((tTimeVal = mktime(&tTime)) == -1)
		{
			memset(caBuf, 0, sizeof(caBuf));
			return caBuf;
		}
		if ((ptTimeStruct = localtime(&tTimeVal)) == NULL)
		{
			memset(caBuf, 0, sizeof(caBuf));
			return caBuf;
		}
		sprintf(caBufTmp, "%04d%02d%02d", ptTimeStruct->tm_year + 1900, ptTimeStruct->tm_mon + 1, ptTimeStruct->tm_mday);
		if (memcmp(caBuf, caBufTmp, sizeof(caBuf) - 1) == 0)
		{
			break;
		}
		sprintf(caDay, "%02d", (int)(atol(caDay) - 1));
	}

	if (pcaBeginMonth[6] == 0)
	{
		caBuf[6] = 0;
	}

	return caBuf;
}

/*****************************************************************************/
/* FUNC:   int basIsLeapYear(const char *pcaYear)                            */
/* PARAMS: pcaYear - 年份 (I)                                                */
/* RETURN:  1:闰年                                                           */
/*          0:非闰年                                                         */
/* DESC:   计算caBeginDay之前iDay天的日期                                    */
/*****************************************************************************/
BAS_EXPORT int basIsLeapYear(const char *pcaYear)
{
	int iYear = atoi(pcaYear);

	if ((iYear % 4 == 0 && iYear % 100 != 0) || iYear % 400 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*****************************************************************************/
/* FUNC:   char *basDateToJulianDate(const char *pcaDate)                    */
/* PARAMS: pcaDate - 日期(YYYYMMDD) (I)                                      */
/* RETURN: 太阳日 (YYDDD)                                                    */
/* DESC:   把日期转换为太阳日格式                                            */
/*****************************************************************************/
BAS_EXPORT char *basDateToJulianDate(const char *pcaDate)
{
	static char caTimeBuf[5+1];
	char caYear[6], caMonth[3], caDay[3];
	struct tm tTime;
	struct tm *ptTimeStruct;
	time_t tTimeVal;

	memset(caYear, 0, sizeof(caYear));
	memset(caMonth, 0, sizeof(caMonth));
	memset(caDay, 0, sizeof(caDay));

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	/* 构造date */
	memcpy(caYear, pcaDate, 4);
	memcpy(caMonth, pcaDate + 4, 2);
	memcpy(caDay, pcaDate + 6, 2);

	tTime.tm_year = atoi(caYear) - 1900;
	tTime.tm_mon = atoi(caMonth) - 1;
	tTime.tm_mday = atoi(caDay);
	tTime.tm_hour = 0;
	tTime.tm_min = 0;
	tTime.tm_sec = 1;
	tTime.tm_isdst = -1;

	if ((tTimeVal = mktime(&tTime)) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basDateToJuliandate:mktime调用失败:[%s]", pcaDate);
		return caTimeBuf;
	}

	if ((ptTimeStruct = localtime(&tTimeVal)) == NULL)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basDateToJuliandate:localtime调用失败");
		return caTimeBuf;
	}

	sprintf(caTimeBuf, "%02d%03d",
			ptTimeStruct->tm_year % 100,
			ptTimeStruct->tm_yday + 1);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   char *basDatePattern(const char *pcaDate, const char *pcaPattern) */
/* PARAMS: pcaDate    - 转换串 (YYYYMMDD) (I)                                */
/*         pcaPattern - 格式串 (I)                                           */
/* RETURN: 返回串                                                            */
/* DESC:   按模式串转换                                                      */
/*****************************************************************************/
BAS_EXPORT char *basDatePattern(const char *pcaDate, const char *pcaPattern)
{
	static char caDate[21];
	int i;
	int j = 0;
	int k = 0;
	int m = 0;
	int n = 0;
	int iLen = 0;

	char caYear[5];
	char caMonth[3];
	char caDay[3];
	char caBuf[21];

	memset(caDate, ' ', sizeof(caDate));
	memset(caYear, 0, sizeof(caYear));
	memset(caMonth, 0, sizeof(caMonth));
	memset(caDay, 0, sizeof(caDay));
	memset(caBuf, 0, sizeof(caBuf));

	memcpy(caYear, pcaDate, 4);
	memcpy(caMonth, pcaDate + 4, 2);
	memcpy(caDay, pcaDate + 6, 2);

	iLen = strlen(pcaPattern);
	if (iLen > 20)
	{
		BAS_LOG(BAS_LOGERROR, 0, 0, "basDatePattern:日期格式错误");
		return caDate;
	}

	for (i = 0; i < iLen; i++)
	{
		if (pcaPattern[i] == '/' ||
			pcaPattern[i] == '-' ||
			pcaPattern[i] == ' ' ||
			pcaPattern[i] == 0xc4 ||
			pcaPattern[i] == 0xffffffc4 ||
			pcaPattern[i] == 0xea ||
			pcaPattern[i] == 0xffffffea ||
			pcaPattern[i] == 0xd4 ||
			pcaPattern[i] == 0xffffffd4 ||
			pcaPattern[i] == 0xc2 ||
			pcaPattern[i] == 0xffffffc2 ||
			pcaPattern[i] == 0xc8 ||
			pcaPattern[i] == 0xffffffc8 ||
			pcaPattern[i] == 0xd5 ||
			pcaPattern[i] == 0xffffffd5)
		{
			caBuf[j] = pcaPattern[i];
		}
		else if (pcaPattern[i] == 'Y' || pcaPattern[i] == 'y')
		{
			caBuf[j] = caYear[k];
			k++;
		}
		else if (pcaPattern[i] == 'M' || pcaPattern[i] == 'm')
		{
			caBuf[j] = caMonth[m];
			m++;
		}
		else if (pcaPattern[i] == 'D' || pcaPattern[i] == 'd')
		{
			caBuf[j] = caDay[n];
			n++;
		}
		else
		{
			BAS_LOG(BAS_LOGINFO, 0, 0, "basDatePattern:日期格式错误[%s][%x][%d]", pcaPattern, pcaPattern[i], i);
			return caDate;
		}
		j++;
	}

	if (k > 4 || m > 2 || n > 2)
	{
		BAS_LOG(BAS_LOGINFO, 0, 0, "basDatePattern:日期格式错误");
		return caDate;
	}

	caBuf[iLen] = 0;
	strcpy(caDate, caBuf);

	return caDate;
}

/*****************************************************************************/
/* FUNC:   int basGetLastDayOfMonth(char *pcaDate)                           */
/* PARAMS: pcaDate    - 日期串 (YYYYMMDD) (I/O)                              */
/* RETURN: 返回串                                                            */
/* DESC:   得到当月的最后一天                                                */
/*****************************************************************************/
BAS_EXPORT int basGetLastDayOfMonth(char *pcaDate)
{
	char caYear[5];
	char caMonth[3];

	memset(caYear, 0, sizeof(caYear));
	memset(caMonth, 0, sizeof(caMonth));

	memcpy(caYear, pcaDate, 4);
	memcpy(caMonth, pcaDate + 4, 2);

	switch (atoi(caMonth))
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		memcpy(pcaDate + 6, "31", 2);
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		memcpy(pcaDate + 6, "30", 2);
		break;
	case 2:
		if (basIsLeapYear(caYear))
		{
			memcpy(pcaDate + 6, "29", 2);
		}
		else
		{
			memcpy(pcaDate + 6, "28", 2);
		}
		break;
	default:
		BAS_LOG(BAS_LOGERROR, 0, 0, "basGetLastDayOfMonth:日期格式错误");
		return -1;
	}
	return 0;
}

/*****************************************************************************/
/* FUNC:   char *basGetMonthName(int iMonth)                                 */
/* PARAMS: iMonth - 月份                                                     */
/* RETURN: 三个大写英文字母                                                  */
/* DESC:   得到月份缩写                                                      */
/*****************************************************************************/
BAS_EXPORT char *basGetMonthName(int iMonth)
{
	switch (iMonth)
	{
	case 1:
		return "JAN";
	case 2:
		return "FEB";
	case 3:
		return "MAR";
	case 4:
		return "APR";
	case 5:
		return "MAY";
	case 6:
		return "JUN";
	case 7:
		return "JUL";
	case 8:
		return "AUG";
	case 9:
		return "SEP";
	case 10:
		return "OCT";
	case 11:
		return "NOV";
	case 12:
		return "DEC";
	default:
		return "   ";
	}
}

/*****************************************************************************/
/* FUNC:   int basIsValidDate(const char *pcaDate)                           */
/* PARAMS: pcaDate - 日期(YYYYMMDD) (I)                                      */
/* RETURN:  1:合法日期                                                       */
/*          0:非法日期                                                       */
/* DESC:   判断日期十分合法                                                  */
/*****************************************************************************/
BAS_EXPORT int basIsValidDate(const char *pcaDate)
{
	char caYear[5], caMonth[3], caDay[3];
	struct tm tTime;

	memset(caYear, 0, sizeof(caYear));
	memset(caMonth, 0, sizeof(caMonth));
	memset(caDay, 0, sizeof(caDay));

	/* 构造date */
	memcpy(caYear, pcaDate, 4);
	memcpy(caMonth, pcaDate + 4, 2);
	memcpy(caDay, pcaDate + 6, 2);

	tTime.tm_year = atoi(caYear) - 1900;
	tTime.tm_mon = atoi(caMonth) - 1;
	tTime.tm_mday = atoi(caDay);
	tTime.tm_hour = 0;
	tTime.tm_min = 0;
	tTime.tm_sec = 1;
	tTime.tm_isdst = -1;

	if (mktime(&tTime) == -1)
	{
		return 0;
	}

	return 1;
}

/*****************************************************************************/
/* FUNC:   char *basGetFormatTimestamp(void)                                 */
/* PARAMS: 无                                                                */
/* RETURN: 格式YYYY-MM-DD.HH.MM.SS.mmmmm                                     */
/* DESC:   取得指定格式的时间戳                                              */
/*****************************************************************************/
BAS_EXPORT char *basGetFormatTimestamp(void)
{
	static char caTimestamp[25 + 1];
	char caBuf[30];

	memset(caTimestamp, 0, sizeof(caTimestamp));
	memset(caBuf, 0, sizeof(caBuf));

	memcpy(caTimestamp, basDatePattern(basGetSysDate(), "YYYY-MM-DD"), 10);
	memcpy(caBuf, basStringPattern(basGetSysTimestamp(), "##.##.##.#####"), 14);
	sprintf(caTimestamp + 10, " %14.14s", caBuf);
	basRTrim(caTimestamp, sizeof(caTimestamp) - 1);

	return caTimestamp;
}

/*****************************************************************************/
/* FUNC:   char *basGetTimestamp(void)                                    */
/* PARAMS: 无                                                                */
/* RETURN: 格式HHMMSSMS (6位MS)                                              */
/* DESC:   取得UNIX时间                                                      */
/*****************************************************************************/
BAS_EXPORT char *basGetTimestamp(void)
{
	static char caTimeBuf[100 + 1];
	char caTimestamp[26 + 1];

	struct tm *ptTimeStruct;
	struct timeval tTimeValue;
	//time_t tTimeVal;

	memset(caTimeBuf, 0, sizeof(caTimeBuf));
	memset(caTimeBuf, ' ', sizeof(caTimeBuf) - 1);

	if (gettimeofday(&tTimeValue, NULL) == -1)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysTimestamp:gettimeofday调用失败");
		return caTimeBuf;
	}
	if ((ptTimeStruct = localtime(&(tTimeValue.tv_sec))) == NULL)
	{
		BAS_LOG(BAS_ERR300002_ERRORTIME, 0, errno, "basGetSysTimestamp:localtime调用失败");
		return caTimeBuf;
	}

	memset(caTimestamp, 0, sizeof(caTimestamp));
	memcpy(caTimestamp, basDatePattern(basGetSysDate(), "YYYY-MM-DD"), 10);
	sprintf(caTimeBuf, "%s-%02d.%02d.%02d.%06d",
			caTimestamp,
			ptTimeStruct->tm_hour,
			ptTimeStruct->tm_min,
			ptTimeStruct->tm_sec,
			(int)tTimeValue.tv_usec);

	return caTimeBuf;
}

/*****************************************************************************/
/* FUNC:   char *basDateToTm( char * )                                 */
/* PARAMS: YYYYMMDDxxxxxx or YYMMDD                                          */
/* RETURN: YYYY-MM-DD-HH.MM.SS.xxxxxx                                        */
/* DESC:   将时间戳格式的字符串，转换为日期格式的字符串                      */
/*****************************************************************************/
BAS_EXPORT char *basDatetoTm(char *tm_str1)
{
	//int  i;
	static char str_date[100];
	char str_tmp[100];
	char tm_str[100];

	strcpy(tm_str, tm_str1);

	tAllTrim(tm_str1);
	if (strlen(tm_str1) == 8)
		sprintf(tm_str, "%s000000", tm_str1);
	else if (strlen(tm_str1) != 14)
	{
		BAS_LOG(BAS_LOGINFO, 0, 0, "basDateToTm 格式错:[%s] 必须是8位或者14位 \n", tm_str);
		return "0000-00-00-00.00.00.000000";
	}

	memset(str_date, 0, sizeof(str_date));
	memset(str_tmp, 0, sizeof(str_tmp));

	memcpy(str_date, tm_str, 4);
	strcat(str_date, "-");

	memset(str_tmp, 0, sizeof(str_tmp));
	memcpy(str_tmp, &tm_str[4], 2);
	strcat(str_date, str_tmp);
	strcat(str_date, "-");

	memset(str_tmp, 0, sizeof(str_tmp));
	memcpy(str_tmp, &tm_str[6], 2);
	strcat(str_date, str_tmp);
	strcat(str_date, "-");

	memset(str_tmp, 0, sizeof(str_tmp));
	memcpy(str_tmp, &tm_str[8], 2);
	strcat(str_date, str_tmp);
	strcat(str_date, ".");

	memset(str_tmp, 0, sizeof(str_tmp));
	memcpy(str_tmp, &tm_str[10], 2);
	strcat(str_date, str_tmp);
	strcat(str_date, ".");

	memset(str_tmp, 0, sizeof(str_tmp));
	memcpy(str_tmp, &tm_str[12], 2);
	strcat(str_date, str_tmp);

	strcat(str_date, ".000000");

	return str_date;
}

/*********************************************************************************/
/*FUNC:    basJudgeWeekday(const char *caYourDate, int *piWeekday)               */
/*PARAMS:  caYourDate - 需要判断的日期的星期几(YYYYMMDD) (I)                     */
/*RETURN:  结果由piWeekday带回                                                   */
/*DESC:    判断caYourDate这天是星期几，0代表星期天，1~6代表星期一到星期六        */
/*********************************************************************************/
BAS_EXPORT int basJudgeWeekday(const char *caYourDate, int *piWeekday)
{
	time_t timep;
	struct tm *p;
	int ret;
	int iArbitrator;
	char caSysDate[9];
	char caBeginDate[9];
	char caEndDate[9];
	char caTmp[9];

	time(&timep);
	p = localtime(&timep);

	memset(caSysDate, 0, sizeof(caSysDate));
	memset(caBeginDate, 0, sizeof(caBeginDate));
	memset(caEndDate, 0, sizeof(caEndDate));

	strcpy(caSysDate, basGetSysDate());

	strcpy(caBeginDate, caYourDate);
	strcpy(caEndDate, caSysDate);

	if (atol(caBeginDate) - atol(caEndDate) > 0)
	{
		strcpy(caTmp, caBeginDate);
		strcpy(caBeginDate, caEndDate);
		strcpy(caEndDate, caTmp);
		iArbitrator = 7 - p->tm_wday;
		ret = basCalDiffTwoDays(caBeginDate, caEndDate, piWeekday);
		if (ret)
		{
			printf("Calculating wrong!\n");
			return -1;
		}
		*piWeekday %= 7;
		*piWeekday += p->tm_wday;
		*piWeekday %= 7;
	}
	else
	{
		iArbitrator = p->tm_wday;
		ret = basCalDiffTwoDays(caBeginDate, caEndDate, piWeekday);
		if (ret)
		{
			printf("Calculating wrong!\n");
			return -1;
		}
		*piWeekday %= 7;
		if ((iArbitrator - *piWeekday) > 0)
			*piWeekday = iArbitrator - *piWeekday;
		else if ((iArbitrator - *piWeekday) < 0)
		{
			*piWeekday = *piWeekday - iArbitrator;
			*piWeekday = 7 - *piWeekday;
		}
		else
			*piWeekday = 0;
	}

	return 0;
}

/*********************************************************************************/
/*FUNC:    basGetDiffNowSeconds(const char *caTimeStamp)                         */
/*PARAMS:  caTimeStamp -格式YYYYMMDDDHHmmSS                                      */
/*RETURN:  结果返回某个时间戳距今相差的秒数                                      */
/*********************************************************************************/
BAS_EXPORT long basGetDiffNowSeconds(const char *caTimeStamp)
{
	long lDiffSeconds = 0;
	struct tm tTime;
	time_t tNowTime;
	char caYear[4 + 1] = {0};
	char caMonth[2 + 1] = {0};
	char caDay[2 + 1] = {0};
	char cahour[2 + 1] = {0};
	char caMin[2 + 1] = {0};
	char caSec[2 + 1] = {0};

	memcpy(caYear, caTimeStamp, 4);
	memcpy(caMonth, caTimeStamp + 4, 2);
	memcpy(caDay, caTimeStamp + 4 + 2, 2);
	memcpy(cahour, caTimeStamp + 4 + 2 + 2, 2);
	memcpy(caMin, caTimeStamp + 4 + 2 + 2 + 2, 2);
	memcpy(caSec, caTimeStamp + 4 + 2 + 2 + 2 + 2, 2);

	tTime.tm_year = atoi(caYear) - 1900;
	tTime.tm_mon = atoi(caMonth) - 1;
	tTime.tm_mday = atoi(caDay);
	tTime.tm_hour = atoi(cahour);
	tTime.tm_min = atoi(caMin);
	tTime.tm_sec = atoi(caSec);
	tTime.tm_isdst = -1;

	time(&tNowTime);
	lDiffSeconds = tNowTime - mktime(&tTime);

	return lDiffSeconds;
}

/*********************************************************************************/
/*FUNC:   char * basGetCurrTimeStamp()                                                 */
/*RETURN:  返回目前的时间戳格式为:YYYYMMDDHHmmSS                                 */
/*********************************************************************************/
BAS_EXPORT char *basGetCurrTimeStamp()
{

	time_t tTime;
	//struct tm   *pTmCurrTime;
	static char StrCurrTime[14 + 1];

	time(&tTime);
	strftime(StrCurrTime, sizeof(StrCurrTime), "%Y%m%d%H%M%S", localtime(&tTime));

	return StrCurrTime;
}
