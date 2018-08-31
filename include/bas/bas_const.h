/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_const.h                                                 */
/* DESCRIPTIONS: 全局常数                                                    */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#ifndef __BAS_CONST_H
#define __BAS_CONST_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef BAS_SUCCESS
#define BAS_SUCCESS 0
#endif

#ifndef BAS_EXPORT
#define BAS_EXPORT
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

/* 数据库标识 */
#define UMTXN_DB_ID     0  /* 交易、批量数据库 */
#define UMSVC_DB_ID     1  /* 服务、管理数据库 */
#define ACCS01_DB_ID    2  /* 从库1*/
#define ACCS02_DB_ID    3  /* 从库2*/
#define ACCS03_DB_ID    4  /* 从库3*/

/* 数据库SQLCODE的宏定义 */
#define BAS_DBOK           0
#define BAS_DBNOTFOUND     100
#define BAS_DBNULLVAL     -305
#define BAS_DBDUPKEY      -803
#define BAS_DBIDXVIOLATE  -603

/* 数据库操作的功能代码宏定义 */
#define BAS_DBSELECT       1
#define BAS_DBLOCK         2
#define BAS_DBINSERT       3
#define BAS_DBUPDATE       4
#define BAS_DBDELETE       5
#define BAS_DBCUROPEN      6
#define BAS_DBCURFETCH     7
#define BAS_DBCURCLOSE     8
#define BAS_DBDELETEALL    9
#define BAS_DBEXPORTALL    0
#define BAS_DBCURINIT      10

// 文件的每行标记
#define BAS_FILE_RECORD_HEADER 'H'
#define BAS_FILE_RECORD_DETAIL 'D'
#define BAS_FILE_RECORD_TAIL   'T'

/* 交易成功失败标志 */
#define BAS_TXN_YES            'Y'
#define BAS_TXN_NO             'N'

/* 标志位标志 */
#define BAS_FLAG_YES           'Y'
#define BAS_FLAG_NO            'N'
#define BAS_FLAG_SPACE         ' '

/* 文件路径宏定义 */
#define BAS_LOGPATH            "/log"
#define BAS_DBLOGPATH          "/log/db"
#define BAS_REPORTPATH         "/report"
#define BAS_DATAPATH           "/dat"

/* 报表数据文件暂存表文件类型定义 */
#define BAS_FILE_TYPE_RPT      '1' /* 报表文件 */
#define BAS_FILE_TYPE_DAT      '2' /* 数据文件 */

/* 报表数据文件暂存表数据格式定义 */
#define BAS_DATA_TYPE_TEXT     '1' /* 文本 */
#define BAS_DATA_TYPE_EXT      '2' /* ASCII 展开 */

/* 换行方式 */
#define BAS_NONEWLINE          '0' /* 不自动换行          */
#define BAS_NEWLINE_UNIX       '1' /* Unix 换行 \n        */
#define BAS_NEWLINE_DOS        '2' /* Dos 换行  0x0d 0x0a */

/* Boolean标志 */
#define BAS_TRUE  1
#define BAS_FALSE 0

#define BAS_TRACK2_EXPIRY_POS    17   /* 有效期在2磁道信息上的偏移量 */
#define BAS_TRACK2_CRDTYPE_POS   21   /* 卡种类在2磁道信息上的偏移量 */
#define BAS_TRACK2_CVC_POS       29   /* CVC在2磁道信息上的偏移量 */
#define BAS_CVC2_POS             4    /* CVC2的偏移量 */

#define BAS_8583MSG_LEN          1892 /* 8583报文长度 */

#endif
