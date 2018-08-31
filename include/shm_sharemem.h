#ifndef __SHM_SHAREMEM_H__
#define __SHM_SHAREMEM_H__

#define N_MAX_SEC       2       /*the max section of share memery*/
#define MAX_PATH_LEN    80

/*静态参数结构体*/
typedef struct {
    int  iLogLevel;
    char acLogPath[MAX_PATH_LEN];
    char acCfgPath[MAX_PATH_LEN];
}T_StaticMemBlock;


/*共享内存结构*/
typedef struct {
    short nSecId;
    T_StaticMemBlock  taStatic[N_MAX_SEC];
} T_ShmBufDef;

extern short gnSecId; /*Need to be reassigned at top of each transaction*/
extern T_ShmBufDef *gtpShmBuf;


extern int CumShmInit(void);
extern int CumShmAttach(void);
extern int CumShmDetach(void);
extern int CumShmRemove(void);
extern void CumShmSwitch(void);
extern void CumShmSetSecId(void);

extern int LoadStaticMem(int nBackSecId);

#endif /*__SHM_SHAREMEM_H__*/
