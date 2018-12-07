/*==============================================================================
* File      Name: checkAccount.c
*         Author: Wang Chunji
*       Compiler: gcc/g++
*    Description: 比较A、B两文件的内容，并输出A有B无的记录
*   Created Time: 2018年12月06日 星期四 14时19分32秒
================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "HashTable.h"

//#define TEST

#ifndef TEST
#define TimerBlock(_block, ...) do{ _block }while(0) ;
#else
#define TimerBlock(_block, ...) \
do{ \
    struct timeval start; \
    struct timeval end;   \
    struct tm     *ptTm;  \
    char strDest[20] = {0};  \
    time_t now = time(NULL); \
    unsigned long long diff; \
    gettimeofday(&start, NULL); \
    if ((ptTm = localtime(&(start.tv_sec))) == NULL) { ptTm = localtime(&now);} \
    strftime(strDest, 20, "%Y-%m-%d %H:%M:%S", ptTm); \
    printf("---[%s]: start time [%s.%06ld]\n", __VA_ARGS__, strDest, start.tv_usec); \
    _block \
    gettimeofday(&end, NULL); \
    if ((ptTm = localtime(&(end.tv_sec))) == NULL) { ptTm = localtime(&now);} \
    strftime(strDest, 20, "%Y-%m-%d %H:%M:%S", ptTm); \
    printf("---[%s]: end   time [%s.%06ld]\n", __VA_ARGS__, strDest, end.tv_usec); \
    diff = 1000000L * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec; \
    printf("---[%s]: spend time [%llu] usec\n", __VA_ARGS__, diff); \
}while(0) ;
#endif

extern void md5(const uint8_t *initial_msg, size_t initial_len, char *digest);

//冲突结构内存释放函数
static void free_value(void* val)
{
}

int main(int argc, const char *argv[])
{
    //int iRet = 0;
    char caMD5[32+1]= {0};
    char caFileNameA[80]= {0};
    char caFileNameB[80]= {0};
    char caTempBuff[100]= {0};
    FILE *fpA,*fpB,*fpResult;
    HashTable* ht = NULL;
    char *findkey = NULL;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if(argc != 3)
    {
        printf("Usage: %s FileNameA  FileNameB\n", argv[0]);
        exit(1);
    }

    strcpy(caFileNameA, argv[1]);
    strcpy(caFileNameB, argv[2]);

    /*新建一个HashTable实例*/
    TimerBlock(ht = hash_table_new();,"hash_table_new()")
    if (NULL == ht)
    {
        return -1;
    }

    /*分别打开A、B两个文件读取其中的内容*/
    if((fpA = fopen(caFileNameA, "r")) == NULL)
    {
        printf("open file [%s] error \n", caFileNameA);
        exit(1);
    }

    if((fpB = fopen(caFileNameB, "r")) == NULL)
    {
        printf("open file [%s] error \n", caFileNameB);
        exit(1);
    }

    if((fpResult = fopen ("result.txt", "w+")) == NULL)
    {
        printf("open file result.txt error \n");
        exit(1);
    }

    /*读取A文件中的每一行，生成hash值，放入到生成的HashTable中*/
    while( fgets(caTempBuff, 100, fpA)!=NULL )
    {
        /*使用md5算法计算每行内容的hash值*/
        TimerBlock(md5((uint8_t*)caTempBuff, strlen(caTempBuff), caMD5);,"md5()")
        //printf("MD5 = %s", caMD5);
        /*向哈希表中加入A文件的每行md5值*/
        TimerBlock(hash_table_put2(ht, caMD5, "0", free_value);,"hash_table_put2()")
    }

    /*读取B文件中的每一行，生成hash值，判断是否在HashTable中，如果在其中则继续下一条判断，否则写入到结果文件中*/
    while( fgets(caTempBuff, 100, fpB)!=NULL )
    {
        /*使用md5算法计算每行内容的hash值*/
        TimerBlock(md5((uint8_t*)caTempBuff, strlen(caTempBuff), caMD5);,"md5()")
        //printf("MD5 = %s", caMD5);
        TimerBlock(findkey = (char *)hash_table_get(ht, caMD5);,"hash_table_get()")
        //printf("found! value=[%s]\n", findkey);
        if(findkey == NULL)
        {
            //printf("[%s] not found!\n", caTempBuff);
            /*将不一致的数据写入到结果文件*/
            fprintf(fpResult, "%s", caTempBuff);
        }
    }

    //销毁哈希表实例
    TimerBlock(hash_table_delete(ht);,"hash_table_delete()")
    fclose(fpA);
    fclose(fpB);
    fclose(fpResult);
    return 0;
}

