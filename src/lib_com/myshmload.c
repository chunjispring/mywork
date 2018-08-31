//****************************************************************************/
// PROGRAM NAME: shm_load.c                                                   /
// DESCRIPTIONS: 共享内存参数加载函数库                                           /
// AUTHOR      :                                                              /
// CREATE DATE :                                                              /
//****************************************************************************/

/** @file                                               
 *  共享内存参数加载相关函数
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "mycomm.h"
#include "shm_sharemem.h"

/** 
 *  @brief   加载静态参数变量
 *  @details 取自配置文件app.ini中
 *  @return  函数处理结果
 *  @retval   0: 成功
 *  @retval  -1：失败
 */
int LoadStaticMem(int nBackSecId)
{
    int             iTmp;
    char            caBuf[255];
    
    memset(&gtpShmBuf->taStatic[nBackSecId], 0x00, sizeof(T_StaticMemBlock));

    iTmp=0;
    if (tPflGetInt("STATIC", "LOGLEVEL", gsaConfigFileName, &iTmp) != SUCCESS) 
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflGetInt SHARED_MEM->LOGLEVEL  failure!");
        //printf("tPflGetInt SHARED_MEM->LOGLEVEL  failure!\n");
        return FAILURE;
    }
    gtpShmBuf->taStatic[nBackSecId].iLogLevel=iTmp;	

    memset(caBuf, 0x00, sizeof(caBuf));
    if (tPflGetString("STATIC", "LOGPATH", gsaConfigFileName, caBuf) != SUCCESS) 
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflGetString SHARED_MEM->LOGPATH  failure!");
        //printf("tPflGetString SHARED_MEM->LOGPATH  failure!\n");
        return FAILURE;
    }
    strcpy(gtpShmBuf->taStatic[nBackSecId].acLogPath, caBuf);

    memset(caBuf, 0x00, sizeof(caBuf));
    if (tPflGetString("STATIC", "CFGPATH", gsaConfigFileName, caBuf) != SUCCESS) 
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflGetString SHARED_MEM->CFGPATH  failure!");
        //printf("tPflGetString SHARED_MEM->CFGPATH  failure!\n");
        return FAILURE;
    }
    strcpy(gtpShmBuf->taStatic[nBackSecId].acCfgPath, caBuf);

    return SUCCESS;
}

