#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mycomm.h"

typedef int (*FuncPointer)(int, int);

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

//测试　min max 函数
int testFuncPointer()
{
    //int  iRet=0;
    FuncPointer f = NULL;

    //strcpy(agLogModule, "FUNCPOINTER");

    f = min;
    printf("The min is %d\n", f(1, 2));

    f = max;
    printf("The max is %d\n", f(3, 4));

    MY_LOG(DEBUG, "testFuncPointer !");

    return SUCCESS;
}
