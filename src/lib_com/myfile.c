/*******************************************************************************
 * 文件名   : myfile.c
 * 文件功能 : 文件操作相关函数
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
 ** 函数功能： 根据传入的文件获取文件大小
 ** 输    入： 全路径的文件名
 ** 输    出： 文件大小
 ** 返    回： 成功：SUCCESS  失败：相应的错误码errno
 *******************************************************************************/
int GetFileSize(char *pFileName, int *FileSize)
{
    int iRet = 0;
    struct stat tStat;

    memset(&tStat, 0x00, sizeof(struct stat));

    iRet = stat(pFileName, &tStat);
    if (iRet != 0)
    {
        switch (errno)
        {
        case ENOENT:
            //            DEBUG("参数file_name指定的文件不存在");
            sprintf(aczErrMsg, "参数file_name指定的文件不存在");
            break;
        case ENOTDIR:
            //            DEBUG("路径中的目录存在但却非真正的目录");
            sprintf(aczErrMsg, "路径中的目录存在但却非真正的目录");
            break;
        case ELOOP:
            //            DEBUG("欲打开的文件有过多符号连接问题，上限为16符号连接");
            sprintf(aczErrMsg, "欲打开的文件有过多符号连接问题，上限为16符号连接");
            break;
        case EFAULT:
            //            DEBUG("参数buf为无效指针，指向无法存在的内存空间");
            sprintf(aczErrMsg, "参数buf为无效指针，指向无法存在的内存空间");
            break;
            //        case EACCESS:
            //            DEBUG("存取文件时被拒绝");
            //            sprintf(aczErrMsg, "存取文件时被拒绝");
            //            break;
        case ENOMEM:
            //            DEBUG("核心内存不足");
            sprintf(aczErrMsg, "核心内存不足");
            break;
        case ENAMETOOLONG:
            //            DEBUG("参数file_name的路径名称太长");
            sprintf(aczErrMsg, "参数file_name的路径名称太长");
            break;
        default:
            //            DEBUG("未知错误");
            sprintf(aczErrMsg, "未知错误");
            break;
        }
        return iRet;
    }

    *FileSize = tStat.st_size;
    COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "[%s] FileSize: %d Bytes", pFileName, tStat.st_size);

    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 判断某文件在一个间隔时间前后长度有否发生变化
 ** 输    入： 全路径的文件名  间隔时间(秒数)
 ** 输    出： 无
 ** 返    回： 未改变：SUCCESS  发生改变：FAILURE
 *******************************************************************************/
int IsFileSizeChanged(char *aFileName, int iSecondTimes)
{
    //int ilRc;
    long long llSize1, llSize2;
    struct stat buf;

    if (access(aFileName, R_OK) == -1)
    {
        return 1;
    }

    memset(&buf, 0x00, sizeof(buf));
    if (stat(aFileName, &buf) != 0)
    {
        /*perror("stat-l:");*/
        return 2;
    }
    llSize1 = buf.st_size;

    sleep(iSecondTimes);
    memset(&buf, 0x00, sizeof(buf));
    if (stat(aFileName, &buf) != 0)
    {
        /*perror("stat-2:");*/
        return 3;
    }
    llSize2 = buf.st_size;

    if (llSize1 != llSize2)
    {
        return FAILURE;
    }

    return SUCCESS;
}
