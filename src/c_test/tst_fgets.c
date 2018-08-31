#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#include "mycomm.h"

//全局变量
char agInfo[128];

int DoSomeThingss()
{
    char aczBuff[16];
    FILE *input;

    input = fopen("./bb", "r");

    while (1)
    {
        if (fgets(aczBuff, sizeof(aczBuff) - 1, input) == NULL)
        {
            if (feof(input))
            {
                fclose(input);
                return 0;
            }
            else
            {
                fclose(input);
                return -1;
            }
        }
        //printf("BUFF:%s\n", aczBuff);
        MY_LOG(DEBUG, "BUFF:%s", aczBuff);
    }

    fclose(input);
    return SUCCESS;
}

int testFgets()
{
    int iRet = 0;

    //strcpy(agLogModule, "FGETS");

    iRet = DoSomeThingss();
    if (iRet >= 0)
    {
        MY_LOG(DEBUG, "call DoSomeThing() Success!");
    }
    else
    {
        MY_LOG(DEBUG, "call DoSomeThing() Failure!");
    }

    return SUCCESS;
}
