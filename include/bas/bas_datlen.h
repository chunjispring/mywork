/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_datlen.h                                                */
/* DESCRIPTIONS: 数据长度定义                                                */
/* AUTHOR      : Hong Derek                                                  */
/* CREATE DATE : 2005-04-21                                                  */
/*****************************************************************************/

#ifndef __BAS_DATLEN_H
#define __BAS_DATLEN_H

#define BAS_FLAG_LEN          1
#define BAS_MODULENAME_LEN    4
#define BAS_PROGRAMNAME_LEN   80
#define BAS_FILENAME_LEN      1024

#define BAS_ADESC_LEN         20      /* 短描述 */
#define BAS_DESC_LEN          60      /* 中描述 */
#define BAS_LDESC_LEN         255     /* 长描述 */
#define BAS_LLDESC_LEN        2048    /* 长长描述 */

#define BAS_LINE_BUF_LEN      200     /* 文本行最大长度 */
#define BAS_JULIAN_DATE_LEN   5       /* 太阳日 */
#define BAS_YYMM_LEN          6       /* 年月 YYYYMM */
#define BAS_MMYY_LEN          6       /* 月年 MMYYYY */
#define BAS_YYMMDD_LEN        6       /* 年月日 YYMMDD */
#define BAS_YYYYDDD_LEN       7       /* 年日 YYYYDDD */
#define BAS_DATE_LEN          8       /* 日期 */
#define BAS_YEAR_LEN          4       /* 年 */
#define BAS_MONTH_LEN         2       /* 月 */
#define BAS_DAY_LEN           2       /* 日 */
#define BAS_LEAP_YY_LEN       2       /* ? */
#define BAS_TIME_LEN          8       /* 时间 */
#define BAS_HHMM_LEN          4       /* 时分 HHMM */
#define BAS_HHMMSS_LEN        6       /* 时分秒 HHMMSS */
#define BAS_DATE10_LEN        10      /* YYYY/MM/DD */
#define BAS_YYMM4_LEN         4       /* YYMM */
#define BAS_YDDD_LEN          4       /* YDDD */
#define BAS_DAY_OF_MONTH      31      /* 每月天数 */
#define BAS_TIMESTAMP_LEN     30      /* 时间戳 */
#define	BAS_ACCTNO_LEN        20      /* 账号长度 */

/* bat 模块 */
#define BAS_TLRNO_LEN           6           /* 柜员代码长度 */
#define BAS_BRCODE_LEN          6           /* 机构代码(行号) */
#define BAS_PRGNM_LEN           80          /* 批量程序名称 */
#define BAS_PARAM_LEN           80          /* 批量程序参数 */
#define BAS_TYPE_LEN            1           /* 类型长度 */
#define BAS_PRGNM_LEN           80          /* 批量名字长度 */
#define BAS_PARAM_LEN           80          /* 批量参数长度 */
#define BAS_BATCHSUBNO_LEN      40          /* 批量子顺序号 */
#define BAS_TIME10_LEN          10          /* 10位时间长度 */
#define BAS_BRANCHID_LEN        12          /* 局所代码 */


#endif
