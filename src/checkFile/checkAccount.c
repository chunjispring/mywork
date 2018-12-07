/*==============================================================================
* File      Name: checkAccount.c
*         Author: Wang Chunji
*       Compiler: gcc/g++
*    Description: �Ƚ�A��B���ļ������ݣ������A��B�޵ļ�¼
*   Created Time: 2018��12��06�� ������ 14ʱ19��32��
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

//��ͻ�ṹ�ڴ��ͷź���
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

    /*�½�һ��HashTableʵ��*/
    TimerBlock(ht = hash_table_new();,"hash_table_new()")
    if (NULL == ht)
    {
        return -1;
    }

    /*�ֱ��A��B�����ļ���ȡ���е�����*/
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

    /*��ȡA�ļ��е�ÿһ�У�����hashֵ�����뵽���ɵ�HashTable��*/
    while( fgets(caTempBuff, 100, fpA)!=NULL )
    {
        /*ʹ��md5�㷨����ÿ�����ݵ�hashֵ*/
        TimerBlock(md5((uint8_t*)caTempBuff, strlen(caTempBuff), caMD5);,"md5()")
        //printf("MD5 = %s", caMD5);
        /*���ϣ���м���A�ļ���ÿ��md5ֵ*/
        TimerBlock(hash_table_put2(ht, caMD5, "0", free_value);,"hash_table_put2()")
    }

    /*��ȡB�ļ��е�ÿһ�У�����hashֵ���ж��Ƿ���HashTable�У�����������������һ���жϣ�����д�뵽����ļ���*/
    while( fgets(caTempBuff, 100, fpB)!=NULL )
    {
        /*ʹ��md5�㷨����ÿ�����ݵ�hashֵ*/
        TimerBlock(md5((uint8_t*)caTempBuff, strlen(caTempBuff), caMD5);,"md5()")
        //printf("MD5 = %s", caMD5);
        TimerBlock(findkey = (char *)hash_table_get(ht, caMD5);,"hash_table_get()")
        //printf("found! value=[%s]\n", findkey);
        if(findkey == NULL)
        {
            //printf("[%s] not found!\n", caTempBuff);
            /*����һ�µ�����д�뵽����ļ�*/
            fprintf(fpResult, "%s", caTempBuff);
        }
    }

    //���ٹ�ϣ��ʵ��
    TimerBlock(hash_table_delete(ht);,"hash_table_delete()")
    fclose(fpA);
    fclose(fpB);
    fclose(fpResult);
    return 0;
}

