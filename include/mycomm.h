/*******************************************************************************
 * 文件名   : mycomm.h
 * 文件功能 : 定义所有常用的宏及全局变量
 * 编程者   : WCJ
 * 初作时间 : 2017/04/28
 * 版本     : 1.0
 * -----------------------------------------------------------------------------
 * 时间        修改者    注释
 * 2017/04/28  WCJ       初期作成
********************************************************************************/
#ifndef __MYCOMM_H__
#define __MYCOMM_H__

#include "cJSON.h"
/*
**  调试宏定义
*/
//#ifdef __DEBUG__
//    #define DEBUGMSG(format,...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
//#else
//    #define DEBUGMSG(format,...)
//#endif

#define _IS_STRING_BORDER(x)     (x == PFL_STRING_BORDER_CHAR)
#define _IS_COMMENT(x)           (x == PFL_MEMO_CHARACTER)
#define _IS_SECTION_BEGIN(x)     (x == '[')
#define _IS_YES(x)               (x == 'Y' || x == 'y')
#define MY_MAX(X, Y)             ((X) > (Y) ? (X) : (Y))
#define MY_MIN(X, Y)             ((X) > (Y) ? (Y) : (X))


#ifdef _POSIX_MAX_INPUT
#undef _POSIX_MAX_INPUT
#endif
#define _POSIX_MAX_INPUT   4096

#ifndef _POSIX_PATH_MAX
#define _POSIX_PATH_MAX    256
#endif

#define SUCCESS            0  /* 成功 */
#define FAILURE           -1  /* 失败 */
#ifndef TRUE
#define TRUE               1
#endif

#ifndef FALSE
#define FALSE              0
#endif


#define PFL_MEMO_CHARACTER      '#'
#define PFL_STRING_BORDER_CHAR  '"'

/*
**  环境变量相关常量定义
*/
#define GET_ENV_ERR            2000  /* 取环境变量出错       */
#define ENV_HOME_ERR           2001  /* 环境变量 WCJHOME 出错   */
#define ENV_LOG_ERR            2002  /* 环境变量 MYLOGDIR 出错   */
#define ENV_CFG_ERR            2003  /* 环境变量 MYCFGPATH 出错   */

/*
**  日志模块常量定义
*/
#define PL_OK                  0
#define PL_ERR                -999

#define PL_DATE_AND_TIME_LEN   50
#define PL_COMMON_MSG_LEN      2048
#define PL_MAX_MSG_LEN         4096
#define PL_LINE_LENGTH         80
#define PL_FILE_NAME_LEN       80
#define PL_MAX_PATH_LEN        80
#define PL_FUN_NAME_LEN        25
#define PL_FILE_SIZE           10000000

#define COMM_LEN               20
#define COMMAND_LEN            512 /* 系统命令长度*/

/* 5个日志级别 */
#define PRINT                  0   /* 不管什么级别都打印 */
#define ERROR                  1
#define DEBUG                  2
#define INFO                   3
#define TRACE                  4

#define MY_LOG_LOCAL           myLogFileLine(__FILE__, __FUNCTION__, __LINE__);myLog
#define MY_LOG(ErrLvl, ...)    MY_LOG_LOCAL(ErrLvl, ##__VA_ARGS__)
#define VERSION_PT             MY_LOG(PRINT, "================== 文件编译时间：%s %s ==================", __DATE__, __TIME__)

#define PL_FILE_OPEN_ERROR    -2001 /* 调试文件打开错    */
#define PL_FILE_SEEK_ERROR    -2002 /* 调试文件定位错误  */
#define PL_RENAME_ERROR       -2003 /* 调试文件更名错误  */

/*
**  时间模块常量定义
*/
#define DATETIMELEN            99

/*
**  字符串模块常量定义
*/
#define DATE_LEN_8             8      /* 8位日期的长度 */
#define DATE_LEN_10            10     /* 10位日期的长度 */
#define FILE_NAME_LEN          255    /* 文件名长度 */

/*
**  文件模块常量定义
*/
#define MAX_LINE_LEN           1024   /* 一行最大长度 */

/*
**  数据库模块常量定义
*/
#define Cursor_Open            0
#define Cursor_Fetch           1
#define Cursor_Close           2

#define DB_CONNECT_ERR         1001   /* 数据库连接失败 */
#define DB_ENV_ERR             1003   /* 数据库配置路径的环境变量出错 CONFIGPATH */
#define DBFILE_NOT_EXSIT       1004   /* 数据库配置配置文件不存在 */
#define GET_DB_CFG_ERR         1005   /* 取数据库配置信息失败 */

#define SYSTEM_ERR             9999   /* 系统错误 */

#define SQLNOTFOUND            1403   /* 数据库无记录 */
#define SQLSUCCESS             0      /* 数据库操作成功 */
#define SQLNULLVALUE          -1405   /* 取出数据中含NULL值 */
#define SQLTOOMANYROWS         2112
#define SQLNOTUNIQUE          -1      /* 违反唯一性约束 */

#define MAXINPUTLEN            30     /*用户名、密码、连接库名的最大长度*/


/*
**  加解密模块常量定义
*/
#define ERRINPUT               1001   /*用户名、密码、连接库名错误*/
#define ERRPUTFILE             1002   /*写密码文件错误*/
#define ERRGETENV              1003   /*取环境变量错误*/
#define ERROPENFILE            1004   /*打开文件错误*/
#define ERRKEYLEN              1005   /*密钥长度错误*/

#define ENCRYPTKEY             "pingan**"  /*加密密钥*/

#define ENCRYPT                0       /*加密*/
#define DENCRYPT               1       /*解密*/
#define KEYLEN                 8       /*秘钥长度*/
#define COMMAND_LEN            512     /*系统命令长度*/

#define PATH_LEN               1024    /*文件目录*/
#define MAX_CONF_LINE_LEN      1000
#define MAX_CONF_VAL_LEN       200     /* max para value */
#define MAX_KEY_LEN            8       /* DES or 3DES arithmetic request key 8 bit */
#define MAX_KEY_NUM            3       /* key1, key2, key3 */

#define MSG_MAC_LEN            8       /*message mac len*/
#define MAX_GETCONF_LEN        1000
#define MAX_MSG_LEN            4096    /*response message max filed len*/

/*
**  配置读取模块常量定义
*/
#define MAX_CFG_NUM 8 /*最大子配置项数量*/

typedef struct __SCFG
{
    char aczKeyName[8 + 1];
    char aczKeyValue[56 + 1];
} sCfg;

typedef struct
{
    char aczSessName[20];
    struct __SCFG cfg[MAX_CFG_NUM];
} sCfgStruct;


/* myenv.c */
extern int GetHomePath(char *pHomePath);
extern int GetLogPath(char *pLogPath);
extern int GetCfgPath(char *pCfgPath);

/* myfile.c */
extern int GetFileSize(char *pFileName, int *FileSize);
extern int IsFileSizeChanged(char *aFileName, int iSecondTimes);

/* mylog.c */
extern void COMM_Trace(const char *c_sFileName, int iLineNo, const char *c_sFunName, char *c_sMsg, ...);
extern void myLog(int ilLogLevel, char *c_sMsg, ...);
extern void myLogFileLine(const char *c_sFileName, const char *c_sFunName, int iLineNo);

/* mystring.c */
extern char *LTrim(char *string);
extern char *RTrim(char *string);
extern char *AllTrim(char *string);
void trim(char *strIn, char *strOut);
extern int IsIntNumber(char *num);
extern int Data_Align(char *string, char align, int fmtlen);

/* mytime.c */
extern void GetSysTime(char *c_sDate, char *c_sFlag);
extern void printTime();
extern void GetMicroTime(char *microtime);
extern int CheckSingleDate(char *pDate);
extern int MonthDiff(char *pBgTime, char *pEndTime, int *iDiffMonth);
extern int LongToDate(long lDateTime, char *pcDateTime, char *pcFormat);
extern long DateToLong(char *aDate);
extern int DateOpertion(char *aCurrDate, int iDayNum, char *aNewDate);

/* myprofile.c */
extern int tLTrim(char *vspString);
extern int tRTrim(char *vspString);
extern int tAllTrim(char*vspString);
extern int tPflInit(void);
extern int tPflGetString(const char *vspSection, const char *vspEntry, const char *vspFilename, char *vspValue);
extern int tPflGetInt(const char *vspSection, const char *vspEntry, const char *vspFilename, int *vtpValue);
extern int tPflGetShort(const char *vspSection, const char *vspEntry, const char *vspFilename, short *vnpValue);
extern int tPflGetLong(const char *vspSection, const char *vspEntry, const char *vspFilename, long *vlpValue);

/* myreadcfg.c */
extern int GetConfigValue(FILE *fpCfg, char *sess, char *paraNm, char *paraValue, int valueLen);
extern int GetKeyFrmFile(char **key, const char *key_file);
//extern int GetKeyValueFrmFile(char *CfgFileName, char *SessName, char **ParaName, char **ParaValue);
extern int GetKeyValueFrmFile(char *CfgFileName, char *SessName, char **ParaName, int ParaCount, char **ParaValue);
extern int GetKeyValueFrmFileOne(char *CfgFileName, char *SessName, char *ParaName, char *ParaValue);
extern void getValue(char *keyAndValue, char *key, char *value);
extern int writeCFG(const char *filename /*in*/, const char *key /*in*/, const char *value /*in*/);
extern void readCFG(char *filename /*in*/, char *key /*in*/, char **value /*out*/);

/* encryptdb.h */
extern int mydecrypt(char *username, char *password, char *dbsource);
extern int myencrypt(char *username, char *password, char *dbsource);


/* 全局变量声明 */
extern char gcaSysLogDir[COMM_LEN + 1];     /* 日志目录 暂不使用*/
extern char gcaSysLogModule[COMM_LEN + 1];  /* 日志文件名中的模块 */
extern char gcaSysLogProg[COMM_LEN + 1];    /* 日志文件名中的程序名 */

char aczErrMsg[128]; /* 全局使用的报错信息 */

extern char gsaConfigFileName[ _POSIX_PATH_MAX + 1];

#endif
