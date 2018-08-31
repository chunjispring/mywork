/*******************************************************************************
 * 文件名   : myenv.c
 * 文件功能 : 环境变量操作相关函数
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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "mycomm.h"

/*******************************************************************************
 ** 函数功能： 取出HOME环境变量配置的值
 ** 输    入： 无
 ** 输    出： HOME环境变量配置的值
 ** 返    回： 成功：SUCCESS  失败：ENV_HOME_ERR
 *******************************************************************************/
int GetHomePath(char *pHomePath)
{
    char *pEnv = NULL;

    pEnv = (char *)getenv("WCJHOME");
    if (pEnv == NULL)
    {
        //printf("环境变量WCJHOME为空\n");
        return ENV_LOG_ERR;
    }

    strcpy(pHomePath, pEnv);

    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 取出MYLOGDIR环境变量配置的值
 ** 输    入： 无
 ** 输    出： MYLOGDIR环境变量配置的值
 ** 返    回： 成功：SUCCESS  失败：ENV_LOG_ERR
 *******************************************************************************/
int GetLogPath(char *pLogPath)
{
    char *pEnv = NULL;

    pEnv = (char *)getenv("MYLOGDIR");
    if (pEnv == NULL)
    {
        //printf("环境变量MYLOGDIR为空\n");
        return ENV_LOG_ERR;
    }

    strcpy(pLogPath, pEnv);

    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 取出MYCFGPATH环境变量配置的值
 ** 输    入： 无
 ** 输    出： HOME环境变量配置的值
 ** 返    回： 成功：SUCCESS  失败：ENV_CFG_ERR
 *******************************************************************************/
int GetCfgPath(char *pCfgPath)
{
    char *pEnv = NULL;

    pEnv = (char *)getenv("MYCFGPATH");
    if (pEnv == NULL)
    {
        //printf("环境变量MYCFGPATH为空\n");
        return ENV_LOG_ERR;
    }

    strcpy(pCfgPath, pEnv);

    return SUCCESS;
}
