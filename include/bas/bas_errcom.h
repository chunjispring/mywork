/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_errcom.h                                                */
/* DESCRIPTIONS: 公共模块错误代码                                            */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#ifndef __BAS_ERRCOM_H
#define __BAS_ERRCOM_H

#define BAS_ERRCOM_BASE              0000

#define BAS_LOGFATAL                 100001
#define BAS_LOGERROR                 200001
#define BAS_LOGWARNING               300001
#define BAS_LOGINFO                  400001
#define BAS_LOGDEBUG                 500001

#define BAS_ERR300002_ERRORTIME      300002  /* 时间计算错误           */
#define BAS_ERR300003_ERRORENV       300003  /* 缺少环境变量           */
#define BAS_ERR300004_ERROROPENFILE  300004  /* 打开文件错             */
#define BAS_ERR300005_ERRORWRITEFILE 300005  /* 写文件错               */
#define BAS_ERR300006_ERRORREADFILE  300006  /* 读文件错               */
#define BAS_ERR300007_ERRORDB        300007  /* 数据库错误             */
#define BAS_ERR300008_ERRORFUN       300008  /* 功能错误               */
#define BAS_ERR300009_ERROROVERLIMIT 300009  /* 超出系统限制           */
#define BAS_ERR300010_ERRORNOTFOUND  300010  /* 没有找到指定记录       */
#define BAS_ERR300011_ERRORARG       300011  /* 参数错误               */
#define BAS_ERR300012_ERRORMEMOUT    300012  /* 分配内存失败           */
#define BAS_ERR300013_ERRORFCNTL     300013  /* 文件控制fcntl错误      */
#define BAS_ERR300014_ERRORFSTAT     300014  /* 文件状态fstat错误      */
#define BAS_ERR300015_ERRORFRENAME   300015  /* 文件改名错误           */
#define BAS_ERR300029_ERRORHOSTNAME  300029  /* 取主机名错误           */
#define BAS_ERR300101_ERRORSYSPRM    300101  /* 系统参数表错误         */
#define BAS_ERR300102_ERRORNEXTSEQ   300102  /* 读取数据库下一序号失败 */
#define BAS_ERR300103_ERRORBATCHNO   300103  /* 无效的批次号           */
#define BAS_ERR300104_ERRORCATINFO   300104  /* 查找分类信息失败       */
#define BAS_ERR300105_ERRORDATAFILE  300105  /* 数据文件格式错误       */

#define BAS_ERR300500_CARDNOTEXT     300500  /* 卡信息不存在 */
#define BAS_ERR300501_CUSTNOTEXT     300501  /* 客户信息不存在 */
#define BAS_ERR300502_CARDSTAT       300502  /* 卡状态错误 */
#define BAS_ERR300503_BSCCUSTNOTEXT  300503  /* 主卡客户信息不存在 */
#define BAS_ERR300504_ACTIONTYPE     300504  /* 错误的操作代码 */
#define BAS_ERR300505_BSCARDNOTEXT   300505  /* 主卡不存在 */
#define BAS_ERR300506_PRDGRPNOTEXT   300506  /* 产品组不存在 */
#define BAS_ERR300507_INDACCR        300507  /* 个人帐户表信息不存在 */
#define BAS_ERR300508_FINTBLR        300508  /* 财务账号表信息不存在 */
#define BAS_ERR300509_COPMSTR        300509  /* 公司合作表信息不存在 */
#define BAS_ERR300510_PRODUCTNOTEXT  300510  /* 产品信息不存在 */
#define BAS_ERR300511_POSCNTRYERR    300511  /* 受理地区错误 */
#define BAS_ERR300512_COCARDFORBID   300512  /* 公司母卡不允许交易 */
#define BAS_ERR300513_PRDFRQR        300513  /* 授权频率表读错 */
#define BAS_ERR300514_PRDFRQW        300514  /* 授权频率表写错 */
#define BAS_ERR300515_CURRATE        300515  /* 汇率错误 */
#define BAS_ERR300516_PRDUSGR        300516  /* 产品授权参数表读取错误 */
#define BAS_ERR300517_PRDCTRR        300517  /* 国家代码监控表读取错误 */
#define BAS_ERR300518_PRDCRDR        300518  /* 产品状态指示表读取错误 */
#define BAS_ERR300519_PINERROR       300519  /* 密码错误 */
#define BAS_ERR300520_MERCHANT       300520  /* 无此商户信息 */
#define BAS_ERR300521_MERCHSTU       300521  /* 商户状态错误 */
#define BAS_ERR300522_MERCHCAU       300522  /* 商户警告错误 */
#define BAS_ERR300523_RETCHQFREQ     300523  /* 允许的累计退票笔数超限 */

#endif

