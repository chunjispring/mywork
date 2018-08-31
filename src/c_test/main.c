#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mycomm.h"

/** 定义标准全局变量  【模块名  程序名】*/
char gcaSysLogModule[COMM_LEN + 1] = "mywork";     /* 日志文件名中的模块 */
char gcaSysLogProg[COMM_LEN + 1] = "ctest";        /* 日志文件名中的程序名 */

//中文测试
int main(int argc, char *argv[])
{
    //int  iRet=0;
    
    VERSION_PT;
    MY_LOG(DEBUG, "****************** begin ******************");

    //testFork();
    //testFork2();
    //testFileSize();
    //testCfg3();
    //testSignal();
    //testPopen();
    //testOpenDir();
    //testSystem();
    //testFgets();
    //testFuncPointer();
    //testTest();
    testGetShmKey();


    MY_LOG(DEBUG, "******************  end  ******************");
    return SUCCESS;
}

