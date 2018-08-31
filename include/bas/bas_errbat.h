/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_errbat.h                                                */
/* DESCRIPTIONS: BAT错误代码                                                 */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#ifndef __BAS_ERRBAT_H
#define __BAS_ERRBAT_H

#define BAS_ERRBAT_BASE                 11000

#define BAS_ERR111001_INFOSAMPLE        111001  /* 错误代码示范 */
#define BAS_ERR211001_FATLESAMPLE       211001  /* 错误代码示范 */
#define BAS_ERR300007_ERRORDB           300007  /* 数据库操作错误 */
#define BAS_ERR311001_ERRORSAMPLE       311001  /* 错误代码示范 */
#define BAS_ERR411001_WARNSAMPLE        411001  /* 错误代码示范 */
#define BAS_ERR511001_DEBUG             511001  /* 错误代码示范 */

#define BAS_ERR311001_INITCHK           311001 /* 总控程序初始化错误 */
#define BAS_ERR311002_HOLIDY            311002 /* 总控程序假日表错误 */
#define BAS_ERR311003_BATCHNOR          311003 /* Batchno表读错误 */
#define BAS_ERR311004_PID               311004 /* 进程号错误*/
#define BAS_ERR311005_BATSTEPU          311005 /* 更新批量步骤错误*/
#define BAS_ERR311006_SYSTEM            311006 /* system调用错误*/
#define BAS_ERR311007_ARGC              311007 /* 参数格式错误*/
#define BAS_ERR311008_BATOK             311008 /* 批量已经完称*/
#define BAS_ERR311009_BATUNKNOW         311009 /* 批量已经完称*/
#define BAS_ERR311010_BATSTEPR          311010 /* 读取批量步骤错误*/

#define BAS_ERR311011_BATCHJOBR         311011 /* 表batchjob读错误 */
#define BAS_ERR311012_BATCHJOBW         311012 /* 表batchjob写错误 */
#define BAS_ERR311013_BATCHPSTR         311013 /* 表batchpst读错误 */
#define BAS_ERR311014_BATCHPSTW         311014 /* 表batchpst写错误 */
#define BAS_ERR311015_BATCHNOR          311015 /* 表batchno读错误 */
#define BAS_ERR311016_BATCHNOW          311016 /* 表batchno写错误 */
#define BAS_ERR311017_BATCHSYSR         311017 /* 表batchsys读错误 */
#define BAS_ERR311018_BATCHSYSW         311018 /* 表batchsys写错误 */
#define BAS_ERR311019_BATCHPROCR        311019 /* 表batchproc读错误 */
#define BAS_ERR311020_BATCHPROCW        311020 /* 表batchproc写错误 */
#define BAS_ERR311021_SYSPRMR           311021 /* 表sysprm读错误 */
#define BAS_ERR311022_SYSPRMW           311022 /* 表sysprm写错误 */

#define BAS_ERR311121_BATTYPE           311121 /* 批量类型错误 */
#define BAS_ERR311122_BATSTAT           311122 /* 批量类型错误 */
#define BAS_ERR311123_TLRNO             311123 /* 柜员错误 */

#define BAS_ERR311124_DBCNT             311124 /* 数据库连接错误 */
#define BAS_ERR311125_DBCMT             311125 /* 数据提交错误 */
#define BAS_ERR311125_DBRBK             311125 /* 数据回滚错误 */


#endif

