#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decryptdb.h"
#include "mycomm.h"

/** 定义标准全局变量  【模块名  程序名】*/
char gcaSysLogModule[COMM_LEN + 1] = "mywork";     /* 日志文件名中的模块 */
char gcaSysLogProg[COMM_LEN + 1] = "decryptdb";    /* 日志文件名中的程序名 */

//解密测试函数
void myDecryptDB()
{
    int iret = 0;
    char aUsername[128], aPassword[128], aDatasource[128];

    memset(aUsername, 0, sizeof(aUsername));
    memset(aPassword, 0, sizeof(aPassword));
    memset(aDatasource, 0, sizeof(aDatasource));

    iret = mydecrypt(aUsername, aPassword, aDatasource);
    if (iret != 0)
    {
        printf("解密错误!iret = [%d]\n", iret);
        //exit -1;
    }

    printf("解密后\n");
    printf("aUsername   == [%s]\n", aUsername);
    printf("aPassword   == [%s]\n", aPassword);
    printf("aDatasource == [%s]\n", aDatasource);

    return;
}

int main(int argc, char *argv[])
{
    myDecryptDB();

    return 0;
}
