/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_system.c                                                */
/* DESCRIPTIONS: Unix系统数据接口                                            */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#include <unistd.h>
#include "bas/bas_global.h"

/*****************************************************************************/
/* FUNC:   char *basGetUserId(void);                                         */
/* PARAMS: 无                                                                */
/* RETURN: 用户名                                                            */
/* DESC:   取得UNIX日期                                                      */
/*****************************************************************************/
BAS_EXPORT char *basGetUserId(void)
{
	if (getenv("LOGNAME") == NULL)
	{
		BAS_LOG(BAS_ERR300003_ERRORENV, 0, 0, "basGetUserId:环境变量LOGNAME");
		return "";
	}
	return getenv("LOGNAME");
}

/*****************************************************************************/
/* FUNC:   char *basGetUserId(void);                                         */
/* PARAMS: 无                                                                */
/* RETURN: 用户名                                                            */
/* DESC:   取得UNIX日期                                                      */
/*****************************************************************************/
BAS_EXPORT char *basGetHostName(void)
{
	static char caHostName[512];

	memset(caHostName, 0, sizeof(caHostName));
	if (gethostname(caHostName, sizeof(caHostName)))
	{
		BAS_LOG(BAS_ERR300029_ERRORHOSTNAME, 0, errno, "basGetHostName:gethostname调用错误");
	}

	return caHostName;
}
