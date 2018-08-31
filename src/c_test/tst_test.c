#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mycomm.h"

void foo(int *a)
{
    int i;
    for (i = 1; i < 4; i++)
    {
        printf("before i=%d, *a=%d\n", i, *a);
        *a = i++;
        printf("after  i=%d, *a=%d\n", i, *a);
    }
}

void reverse(char *str)
{
    int len = strlen(str);
    char *end = str + len - 1;
    char tmp;
    //printf("length is %d\n", len);
    MY_LOG(DEBUG, "length is %d", len);

    while (str <= end)
    {
        tmp = *str;
        *str = *end;
        *end = tmp;

        str++;
        end--;
    }
}

//测试 foo 函数
int testTest()
{
    //int  iRet=0;

    //strcpy(agLogModule, "TEST");

    int a = 1;
    foo(&a);
    printf("Result: a=%d\n", a);

    char b[] = "123";
    printf("%s\n", b);
    reverse(b);
    printf("%s\n", b);

    MY_LOG(DEBUG, "testTest !");

    return SUCCESS;
}
