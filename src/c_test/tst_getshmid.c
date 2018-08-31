/*==============================================================================
* File      Name: tst_getshmid.c
*         Author: Wang Chunji, (chunjispring88@163.com)
*       Compiler: gcc/g++
*    Description:
*   Created Time: 2018年03月29日 星期四 09时19分11秒
================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>

#include "mycomm.h"

//测试 foo 函数
int testGetShmKey()
{
    key_t semkey;
    if((semkey = ftok("/home/ss/mywork/etc/mm.cfg", 4))<0)
    {
        MY_LOG(ERROR, "ftok failed !");
        printf("ftok failed!\n");
        exit(FAILURE);
    }

    MY_LOG(DEBUG, "ftok ok,semkey=%d ", semkey);
    printf("ftok ok ,semkey = %d\n", semkey);

    return SUCCESS;
}

