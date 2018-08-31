/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_ext.h                                                   */
/* DESCRIPTIONS: 基础函数接口定义                                            */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#ifndef __BAS_EXT_H
#define __BAS_EXT_H

#include "bas_global.h"

typedef struct
{
    int iErrNo;
    char *pcaErrDesc;
} T_ErrDesc;

#define BAS_MAX(X, Y)   ((X) > (Y) ? (X) : (Y))
#define BAS_MIN(X, Y)   ((X) > (Y) ? (Y) : (X))

#define OFFSET_OF(type, member) ((int)&((type *)0)->member)

#define BAS_LOG_LOCAL   basLogFileLine(__FILE__, __LINE__); basLog

// Add By Tiger 2009-08-07
#define BAS_LOG(ErrLvl, SqlCode, Errno, ...) \
          BAS_LOG_LOCAL(ErrLvl, SqlCode, Errno, __VA_ARGS__); \

extern int  basLogInit(const char *pPrgName);
extern void basLogFileLine(const char *pcaFile, int iLine);
extern void basLog(int iLevel, int iSqlCode, int iErrno, const char *pcaFmt, ...);
extern void basBatLog(const char *pcaFmt, ...);
extern char *basGetErrDesc(int iErrCode);
extern FILE *basOpenDBLogFile(int iForce);

extern int basDoubleCmp(double dVal1, double dVal2);
extern int basMemcmp(const char *pcaBuf1, const char *pcaBuf2, int iLen);
extern void basSprintf(char *pcaBuf, int iLen, const char *pcaFmt, ...);
extern double basRound(double dVal, int iPoint);
extern double basFloor(double dVal);
extern double basFloor2(double dVal, int iPoint);
extern double basCeil(double dVal);
extern double basCeil2(double dVal, int iPoint);
extern double basAtof(const char *pcaBuf, int iLen);
extern long basAtol(const char *pcaBuf, int iLen);
extern int basIsNumeric(const char *pcaBuf);
extern int basIsAlphabet(const char *pcaBuf);
extern int basIsSpace(const char *pcaBuf, int iLen);
extern int basIsZero(const char *pcaBuf, int iLen);
extern int basIsNull(const char *pcaBuf, int iLen);
extern char *basRSpace(char *pcaString, int iLen);
extern char *basRTrim(char *pcaBuf, int iMaxLen);
extern char *basLTrim(char *pcaBuf, int iMaxLen);
extern char *basLFill(char *pcaBuf, int iLen, char cChar);
extern char *basRemoveSpace(char *pcaBuf, int iMaxLen);
extern char *basToUpper(char *pcaBuf, int iMaxLen);
extern char *basToLower(char *pcaBuf, int iMaxLen);
extern char *basDbl2Char(double dValue, int iFix, int iFloat, char *pcaBuf);
extern char *basStringPattern(char *pcaString, const char *pcaPattern);
extern char *basDatePattern(const char *pcaDate, const char *pcaPattern);
extern char *basFloatToSection(double dValue, int iPointLen);
extern char *basGetSysJulianDate(void);
extern char *basGetSysDate(void);
extern char *basGetSysTime(void);
extern char *basGetGmDate(void);
extern char *basGetGmTime(void);
extern char *basGetSysTimestamp(void);
extern int basGetLastDayOfMonth(char *pcaDate);
extern char *basGetMonthName(int iMonth);
extern char *basDateToJulianDate(const char *pcaDate);
extern char *basGetMonthName(int iMonth);
extern int basCalDiffTwoDays(const char *pcaBeginDate, const char *pcaEndDate, int *piDays);
extern int basCalDiffTwoMonths(const char *pcaBeginMonth, const char *pcaEndMonth, int *piMonth);
extern char *basAddDays(const char *pcaBeginDate, int iDays);
extern char *basSubDays(const char *pcaBeginDate, int iDays);
extern char *basAddMonths(const char *pcaBeginDate, int iDays);
extern char *basAddString(char *pcaBuf, int iLen, int iVal);
extern int basCountString(const char *pcaBuf, char cChar, int iLen);
extern int basIsLeapYear(const char *pcaYear);
extern char *basGetUserId(void);
extern char *basGetHostName(void);
extern int basIsSameIdno(const char *pcaIdno1, const char *pcaIdno2);
extern char *basIdno18To15(char *pcaIdno);
extern char *basIdno15To18(char *pcaIdno);
extern char basIdno18GenCheckVal(char *pcaIdno);
extern int basIdno18IsValid(const char *pcaIdno);
extern int basChkActBit(char *pcaAcctno, int iLen);
extern void basDebugString(char *paLogName, char *psBuf, int iLength);
extern int basChar2FloatOfAmt(char *pcaBuf, double *dAmt);
extern char *basLtoa(long lValue, char *pcaBuf, int iDec);
extern int basIsValidDate(const char *pcaDate);
extern char *basTransVertical(const char *pcaBuf, int iLen);
extern char *basGetFormatTimestamp(void);
extern char *basGetTimestamp(void);
extern char *basDatetoTm( char * );
//extern int dbsNeedLog(void);

extern int basJudgeWeekday( const char *caYourDate, int *piWeekday );
extern int basStrRealCutLen(const char *ptStr, int iCutLen);

#endif
