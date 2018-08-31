//****************************************************************************/
// PROGRAM NAME: opripc.c                                                     /
// DESCRIPTIONS: 共享内存操作程序                                                /
// AUTHOR      :                                                              /
// CREATE DATE :                                                              /
//****************************************************************************/

/** @file                                               
 *  共享内存操作程序
 *  提供共享内存的创建、加载、查看、删除主要四个功能
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "mycomm.h"
#include "shm_sharemem.h"

/** 定义标准全局变量  【模块名  程序名】*/
char gcaSysLogModule[COMM_LEN + 1] = "mywork";     /* 日志文件名中的模块 */
char gcaSysLogProg[COMM_LEN + 1] = "opripc";    /* 日志文件名中的程序名 */


#define N_SHM_HELP          (1<<0)
#define N_SHM_CREATE        (1<<1)
#define N_SHM_LOAD          (1<<2)
#define N_SHM_VIEW          (1<<3)
#define N_SHM_REMOVE        (1<<4)
//#define SEM_KEY 0x99999       //信号量key值

//static long sem_key;
static int LoadAllMemory(void);
//static int LoadMemory(void);
static int ViewMemory(void);
static int ViewStaticMemory(char cInd);
static void usage(void);
//static int GetConfig(void);
//static struct sembuf SemBuf = {0,0,SEM_UNDO};

/** 
 *  @brief     共享内存操作main函数
 *  @param[in] argc 参数个数
 *  @param[in] argv 参数指针
 *  @return 函数处理结果
 *  @retval   0: 成功
 *  @retval  -1: 失败
 */
int main(int argc,char* argv[])
{
    int             ch;
    int             iInputFlag=0;
//    int             semId = 0;
/*    union semun
    {
       int val;
       struct semid_ds *buf;
       unsigned short *array;	
    }sem_union;
    sem_union.val=1;
*/
    /// 获取操作指示代码
    if (argc < 2)
    {
        usage();
        return FAILURE;
    }

    while ((ch = getopt(argc, argv, "?CRLV")) != -1) 
    {
        switch (ch) 
        {
            case '?':
                iInputFlag |= N_SHM_HELP;
                break;
            case 'C':
                iInputFlag |= N_SHM_CREATE;
                break;
            case 'R':
                iInputFlag |= N_SHM_REMOVE;
                break;
            case 'L':
                iInputFlag |= N_SHM_LOAD;
                break;    
            case 'V':
                iInputFlag |= N_SHM_VIEW;
                break;
            default:
                usage();
                return FAILURE;
        }
    }
 
    /// 查看帮助
    if (N_SHM_HELP&iInputFlag) 
    {
        usage();
    }
    /**这里需要获取信号量，才能继续操作**/
/*    if(GetConfig()<0)
    {
        printf("GetConfig error\n");
        return -1;
    }
    if((semId=semget(sem_key,1,0))<0)
    {    	  
        semId=semget(sem_key,1,IPC_CREAT|0666);
    	  if(semId==-1)
        {
            printf("semget fail[%d][%s][%d]\n",errno,strerror(errno),__LINE__);
            return -1;
        }
        if(semctl(semId,0,SETVAL,sem_union)!=0)
        {
            printf("semctl fail[%d][%s][%d]\n",errno,strerror(errno),__LINE__);
            return -1;
        }
        //printf("create new sem[semId=%d][%d][%d]\n",semId,semctl(semId,0,GETVAL,sem_union),__LINE__);
    }
*/    /**信号量P操作*/
 /*   SemBuf.sem_op=-1;
    if(semop(semId,&SemBuf,1)!=0)
    {
        printf("semop fail[%d][%d][%s][%d]\n",semId,errno,strerror(errno),__LINE__);
        return -1;
    }
 */   //printf("get sem[semId=%d][%d][%d]\n",semId,semctl(semId,0,GETVAL,sem_union),__LINE__);
    /// 创建共享内存
    if (N_SHM_CREATE&iInputFlag)
    { 
		printf("N_SHM_CREATE\n");
        if (CumShmInit() != SUCCESS) 
        {
            printf("Initial Share Memory failure!\n");
            CumShmRemove();
            return FAILURE;
        }
        
        if (LoadAllMemory() != SUCCESS) 
        {
            printf("Load Share Memory failure!\n");
            CumShmRemove();
            return FAILURE;
        }
        
        if (CumShmDetach() != SUCCESS) 
        {
            printf("Detach Share Memory failure!\n");
            CumShmRemove();
            return FAILURE;
        }
    }
    
    /// 加载共享内存
    if (N_SHM_LOAD&iInputFlag) 
    {
        printf("N_SHM_LOAD\n");
        if (CumShmAttach() != SUCCESS) 
        {
            printf("Attach Share Memory failure!\n");
            return FAILURE;
        }
        
        if (LoadAllMemory() != SUCCESS) 
        {
            printf("Load Share Memory failure!\n");
            return FAILURE;
        }

        if (CumShmDetach() != SUCCESS) 
        {
            printf("Detach Share Memory failure!\n");
            return FAILURE;
        }
    }
    
    /// 查看共享内存
    if (N_SHM_VIEW&iInputFlag) 
    {
		printf("N_SHM_VIEW\n");
        if (CumShmAttach() != SUCCESS) 
        {
            printf("Attach Share Memory failure!\n");
            return FAILURE;
        }
        
        if (ViewMemory() != SUCCESS) 
        {
            printf("View Share Memory failure!\n");
            return FAILURE;
        }

        if (CumShmDetach() != SUCCESS) 
        {
            printf("Detach Share Memory failure!\n");
            return FAILURE;
        }
    }

    /// 删除共享内存
    if (N_SHM_REMOVE&iInputFlag) 
    {
		printf("N_SHM_REMOVE\n");
        printf("Are you sure to remove cum share memory?(Y/N)\n");
        ch=getchar();
        if(ch != 'Y' && ch != 'y')
        {
            printf("You choose [%c],return!\n", ch);
            return FAILURE;
        }    
        
        if (CumShmAttach() != SUCCESS) 
        {
            printf("Attach Share Memory failure!\n");
            return FAILURE;
        }

        if (CumShmRemove() != SUCCESS) 
        {
            printf("Remove share memory failure!\n");
            return FAILURE;
        }
        printf("Share Memory Removed!\n");
    }
    /**信号量V操作*/
/*    SemBuf.sem_op = 1;
    if(semop(semId,&SemBuf,1)!=0)
    {
        printf("semop fail[%d][%d][%s][%d]\n",semId,errno,strerror(errno),__LINE__);
        return -1;
    }
*/    //else
    //    printf("OP V success\n");
    //printf("get sem[semId=%d][%d][%d]\n",semId,semctl(semId,0,GETVAL,sem_union),__LINE__);
    return SUCCESS;
}


/** 
 *  @brief 加载共享内存所有数据
 *  @param[in]  无
 *  @param[out] 无
 *  @return 函数处理结果
 *  @retval   0: 成功
 *  @retval  -1: 失败
 */
static int LoadAllMemory(void)
{
    short       nCurrSecId;
    short       nBackSecId;

    assert(gtpShmBuf != NULL);
    nCurrSecId = gtpShmBuf->nSecId;
    nBackSecId = (gtpShmBuf->nSecId+1)%N_MAX_SEC;

    /// 共享内存备块导入配置文件静态参数部分
    //memset(&gtpShmBuf->taStatic[nBackSecId], 0, sizeof(T_StaticMemBlock));
    if (LoadStaticMem(nBackSecId) != SUCCESS) 
    {
        printf("LoadStaticMem failure!");
        return FAILURE;
    }
    
    /// 将备块内容复制到主块
    memcpy(&gtpShmBuf->taStatic[nCurrSecId],
           &gtpShmBuf->taStatic[nBackSecId],
           sizeof(T_StaticMemBlock));

    return SUCCESS;
}


/** 
 *  @brief 有选择的加载共享内存块数据
 *  @details 暂未启用
 *  @param[in]  无
 *  @param[out] 无
 *  @return 函数处理结果
 *  @retval   0: 成功
 *  @retval  -1: 失败
 */
/*
static int LoadMemory(void)
{
    char ch = '\0';
    
    printf("Choose Memory Block To Load: \n");
    printf("S--[S]tatic memory block\n");
    printf("D--[D]ynamic memory block\n");
    printf("A--[A]ccount memory block\n");
    printf("T--[T]xnattr memory block\n");
    printf("F--[F]ldattr memory block\n");
    printf("K--[K]eyinf memory block\n");
    printf("else to quit!\n");

    do
    {
        ch = getchar();
        if(ch == 'S' || ch == 's')
        {
            //LoadStaticMemory();
        }
        else if(ch == 'D' || ch == 'd')
        {
            //LoadDynamicMemory();
        }   
        else if(ch == 'A' || ch == 'a')
        {
            //LoadAccountMemory();
        }
        else if(ch == 'T' || ch == 't')
        {
            //LoadTxnAttrMemory();
        }
        else if(ch == 'F' || ch == 'f')
        {
            //LoadFldAttrMemory();
        }
        else if(ch == 'K' || ch == 'k')
        {
            //LoadKeyInfMemory();
        }
        else
        {
            printf("Quit:[%c]!\n", ch);
            break;
        }    
    }while(ch == '\0' || ch == '\n' || ch == '\t');
    
    return SUCCESS;
}
*/

/** 
 *  @brief 有选择的查看共享内存块数据
 *  @param[in]  无
 *  @param[out] 无
 *  @return 函数处理结果
 *  @retval   0: 成功
 *  @retval  -1: 失败
 */
static int ViewMemory(void)
{
    char ch = '\0';
    char ind = '\0';
        
    printf("Choose Memory Block To View: \n");
    printf("S--[S]tatic memory block\n");
    printf("else to quit!\n");   

    do
    {
        ch = getchar();
        if(ch == 'S' || ch == 's')
        {
            printf("Choose [A]ctive Or [S]tandby: \n");
            do
            {
                ind = getchar();
            }while(ind == '\0' || ind == '\n' || ind == '\t');
            ViewStaticMemory(ind);
        }
        else
        {
            printf("Quit:[%c]!\n", ch);
            break;
        }    
    }while(ch == '\0' || ch == '\n' || ch == '\t');
    
    return SUCCESS;
}


/** 
 *  @brief 查看静态块内容
 *  @param[in]  cInd - 主备块指示变量
 *  @param[out] 无
 *  @return 函数处理结果
 *  @retval   0: 成功
 *  @retval  -1: 失败
 */
static int ViewStaticMemory(char cInd)
{
    short       nCurrSecId;
    short       nBackSecId;

    nCurrSecId = gtpShmBuf->nSecId;
    nBackSecId = (gtpShmBuf->nSecId+1)%N_MAX_SEC;
    
    printf("sizeofshm:[%d], nCurrSecId=[%d], nBackSecId=[%d]\n", (int)sizeof(*gtpShmBuf), nCurrSecId, nBackSecId);
    
    if (cInd == 'A' || cInd == 'a')
    {
        printf("[Static] [Active] Memory Block:\n");
        printf("iLogLevel=[%d]\n", gtpShmBuf->taStatic[nCurrSecId].iLogLevel);
        printf("acLogPath=[%s]\n", gtpShmBuf->taStatic[nCurrSecId].acLogPath);
        printf("acCfgPath=[%s]\n", gtpShmBuf->taStatic[nCurrSecId].acCfgPath);
    }
    else if (cInd == 'S' || cInd == 's')
    {
        printf("[Static] [Standby] Memory Block:\n");
        printf("iLogLevel=[%d]\n", gtpShmBuf->taStatic[nBackSecId].iLogLevel);
        printf("acLogPath=[%s]\n", gtpShmBuf->taStatic[nBackSecId].acLogPath);
        printf("acCfgPath=[%s]\n", gtpShmBuf->taStatic[nBackSecId].acCfgPath);
    } 
    else
    {
        printf("Unrecognized Choice:[%c]\n", cInd);
        return FAILURE;
    }
    
    return SUCCESS;
}


/** 
 *  @brief 用法帮助
 *  @param[in]  无
 *  @param[out] 无
 *  @return 无
 */
static void usage(void)
{
    printf("usage: opripc [-? -C -R -L -V]");
    printf("\n"
"             -? help\n"
"             -C Create Share Memory\n"
"             -L Load Share Memory\n"
"             -R Remove Share Memory\n"
"             -V View Share Memory\n");
}


/** 
 *  @brief 获取配置参数信息
 *  @details 解析配置文件app.ini获取OPRIPCKEY相关信息
 *  @return  函数处理结果
 *  @retval   0: 参数获取成功
 *  @retval  -1：参数获取失败
 */
/*
static int GetConfig(void)
{
    int     iTmp = 0;

    if (tPflInit() != SUCCESS) 
    {
        printf("set gsaConfigFileName -1!\n");
        return -1;
    }
    //printf("gsaConfigFileName[%s]",gsaConfigFileName);
    
    if (tPflGetInt("SYSTEM", "OPRIPCKEY", gsaConfigFileName, &iTmp) != SUCCESS) 
    {
        printf("tPflGetInt OPRIPCKEY failed!\n");
        return -1;
    }
    sem_key = iTmp;
    //printf("OPRIPCKEY=%ld\n",sem_key);
    return 0;
}
*/
