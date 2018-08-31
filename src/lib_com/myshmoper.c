//****************************************************************************/
// PROGRAM NAME: shm_operate.c                                                /
// DESCRIPTIONS: 共享内存操作函数库                                              /
// AUTHOR      :                                                              /
// CREATE DATE :                                                              /
//****************************************************************************/

/** @file                                               
 *  共享内存操作相关函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "mycomm.h"
#include "shm_sharemem.h"

short gnSecId;          /**< 共享内存当前块指示变量 */
T_ShmBufDef *gtpShmBuf; /**< 共享内存结构体指针 */

#define CUM_SHM_PERM 0660

/** 
 *  @brief   共享内存的创建
 *  @details 根据配置文件app.ini中的IPCKEY创建共享内存
 *  @return  函数处理结果
 *  @retval   0: 成功
 *  @retval  -1：失败
 */
int CumShmInit(void)
{
    int tShmId;
    key_t tShmKey;
    int tTmp;

    gnSecId = 0;
    gtpShmBuf = NULL;
    if (tPflInit() != SUCCESS)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflInit failure!");
        return FAILURE;
    }

    if (tPflGetInt("SYSTEM", "IPCKEY", gsaConfigFileName, &tTmp) != SUCCESS)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflGetInt IPCKEY  failure!");
        return FAILURE;
    }

    tShmKey = tTmp;
    if ((tShmId = shmget(tShmKey, sizeof(*gtpShmBuf), CUM_SHM_PERM | IPC_EXCL | IPC_CREAT)) == -1)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "shmget gtpShmBuf failure!");
        return FAILURE;
    }

    gtpShmBuf = (T_ShmBufDef *)shmat(tShmId, 0, 0);
    if (((long)gtpShmBuf) == -1L)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "shmat gtpShmBuf failure!");
        return FAILURE;
    }

    gtpShmBuf->nSecId = 0;

    return SUCCESS;
}

/** 
 *  @brief   共享内存的连接
 *  @details 根据配置文件app.ini中的IPCKEY连接共享内存块
 *  @return  函数处理结果
 *  @retval   0: 成功
 *  @retval  -1：失败
 */
int CumShmAttach(void)
{
    int tShmId;
    key_t tShmKey;
    int tTmp;

    if (tPflInit() != SUCCESS)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflInit failure!");
        return FAILURE;
    }

    if (tPflGetInt("SYSTEM", "IPCKEY", gsaConfigFileName, &tTmp) != SUCCESS)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflGetInt IPCKEY failure!");
        return FAILURE;
    }
    tShmKey = tTmp;

    if ((tShmId = shmget(tShmKey, sizeof(*gtpShmBuf), CUM_SHM_PERM)) == -1)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "shmget gtpShmBuf failure!");
        return FAILURE;
    }

    gtpShmBuf = (T_ShmBufDef *)shmat(tShmId, 0, 0);
    if (((long)gtpShmBuf) == -1L)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "shmat gtpShmBuf failure!");
        return FAILURE;
    }

    gnSecId = gtpShmBuf->nSecId;

    return SUCCESS;
}

/** 
 *  @brief   共享内存的断开
 *  @details 断开共享内存块
 *  @return  函数处理结果
 *  @retval   0: 成功
 *  @retval  -1：失败
 */
int CumShmDetach(void)
{
    shmdt((void *)gtpShmBuf);
    gtpShmBuf = NULL;
    return SUCCESS;
}

/** 
 *  @brief   共享内存的删除
 *  @details 根据配置文件app.ini中的IPCKEY删除共享内存块
 *  @return  函数处理结果
 *  @retval   0: 成功
 *  @retval  -1：失败
 */
int CumShmRemove(void)
{
    int tShmId;
    key_t tShmKey;
    int tTmp;

    if (tPflInit() != SUCCESS)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflInit failure!");
        return FAILURE;
    }

    if (tPflGetInt("SYSTEM", "IPCKEY", gsaConfigFileName, &tTmp) != SUCCESS)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "tPflGetString SHARED_MEM->SHM_BUF  failure!");
        return FAILURE;
    }

    tShmKey = tTmp;
    if ((tShmId = shmget(tShmKey, sizeof(*gtpShmBuf), CUM_SHM_PERM | IPC_CREAT)) == -1)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "shmget gtpShmBuf failure!");
        return FAILURE;
    }

    if (shmctl(tShmId, IPC_RMID, 0) < 0)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "shmctl gtpShmBuf failure!");
        return FAILURE;
    }
    return SUCCESS;
}

/** 
 *  @brief   共享内存切换
 *  @details 切换当前共享内存的主备块
 *  @return 无
 */
void CumShmSwitch(void)
{
    gnSecId = (gtpShmBuf->nSecId + 1) % N_MAX_SEC;
    gtpShmBuf->nSecId = gnSecId;
}

/** 
 *  @brief   共享内存当前指示变量的设置
 *  @details 设置全局变量当前可用快指示变量值
 *  @return 无
 */
void CumShmSetSecId(void)
{
    gnSecId = gtpShmBuf->nSecId;
}

