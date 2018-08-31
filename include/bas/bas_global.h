/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_global.h                                                */
/* DESCRIPTIONS: 全局全局头文件                                              */
/* AUTHOR      : Robert Peng                                                  */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#ifndef __BAS_GLOBAL_H
#define __BAS_GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/errno.h>


#include "bas/bas_const.h"
#include "bas/bas_datlen.h"
#include "bas/bas_ext.h"
#include "bas/bas_usrlog.h"

/* 错误代码 */
#include "bas/bas_errcom.h"
#include "bas/bas_errbat.h"

/* 全局变量声明 */
extern char gcaModuleName[BAS_MODULENAME_LEN + 1];
extern char gcaProgramName[BAS_PROGRAMNAME_LEN + 1];

#endif

