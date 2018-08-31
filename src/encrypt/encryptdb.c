#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mycomm.h"
#include "encryptdb.h"

/** 定义标准全局变量  【模块名  程序名】*/
char gcaSysLogModule[COMM_LEN + 1] = "mywork";     /* 日志文件名中的模块 */
char gcaSysLogProg[COMM_LEN + 1] = "encryptdb";    /* 日志文件名中的程序名 */


//加密测试函数
void myEncryptDB()
{
    int iret = 0;
    char aUsername[128], aPassword[128], aDatasource[128];

    printf("请输入用户名:\n");
    scanf("%s", aUsername);

    printf("请输入密码:\n");
    scanf("%s", aPassword);

    printf("请输入连接库:\n");
    scanf("%s", aDatasource);

    iret = myencrypt(aUsername, aPassword, aDatasource);
    if (iret != 0)
    {
        printf("加密错误!iret = [%d]\n",iret);
        exit(-1);
    }

    //return;
}

int main(int argc, char *argv[])
{
    myEncryptDB();

    return 0;
}
