/*******************************************************************************
 * 文件名   : myreadcfg.c
 * 文件功能 : 配置文件相关函数
 * 编程者   : WCJ
 * 初作时间 : 2017/04/28
 * 版本     : 1.0
 * -----------------------------------------------------------------------------
 * 时间            修改者        注释
 * 2017/04/28      WCJ           初期作成
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mycomm.h"

/*******************************************************************************
 ** 函数功能： 从配置文件读取配置项的值
 ** 输    入： 配置文件句柄  一级配置名  子配置项名
 ** 输    出： 子配置项的值
 ** 返    回： SUCCESS
 *******************************************************************************/
int GetConfigValue(FILE *fpCfg, char *sess, char *paraNm, char *paraValue, int valueLen)
{
    char buf[MAX_CONF_LINE_LEN + 1], *pNm, *pValue, *pSess;

    rewind(fpCfg); /* return the beginning of the cfg file */
    if (valueLen < 1)
        return FAILURE;

    /* find session in the cfg file */
    while (fgets(buf, MAX_CONF_LINE_LEN, fpCfg) != NULL)
    {
        if ((pSess = (char *)strtok(buf, "\n\r\t ,]")) == NULL) /* skip delimiters */
            continue;
        if (*pSess == '#' || *pSess != '[') /* not session name */
            continue;
        if (*(++pSess) == '\0')
        {
            if ((pSess = (char *)strtok(NULL, "\n\r\t ]")) == NULL)
                continue;
        }
        if (strcmp(sess, pSess) == 0)
            break;
    }

    /* find para value depending on para name */
    while (fgets(buf, MAX_CONF_LINE_LEN, fpCfg) != NULL)
    {
        pNm = buf + strspn(buf, "\n\r\t "); /* find first non-blank char */
        if (*pNm == '#' || *pNm == '=' || *pNm == '\0')
            continue;
        if (*pNm == '[') /* another session begin */
            break;
        if ((pValue = (char *)strchr(pNm, '=')) == NULL) /* can't find '=' */
            continue;
        *pValue = '\0';
        pValue++;                                           /* point to parameter value */
        if ((pNm = (char *)strtok(pNm, "\n\r\t ")) == NULL) /* can't get parameter name */
            continue;
        if (strcmp(paraNm, pNm) != 0) /* parameter name mismatch */
            continue;
        pValue += strspn(pValue, "\n\r\t "); /* skip blank char */
        /* del right '\n' and '\r' */
        RTrim(pValue);
        if ((int)strlen(pValue) >= valueLen - 1)
        {
            strncpy(paraValue, pValue, valueLen - 1);
            paraValue[valueLen - 1] = '\0';
        }
        else
        {
            strcpy(paraValue, pValue);
        }
    }
    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 从配置文件读取配置项到数组
 ** 输    入： 配置文件句柄  一级配置名  子配置项名
 ** 输    出： 子配置项的值
 ** 返    回： SUCCESS
 *******************************************************************************/
/* get key1,key2,key3 from key file
   input: key_file --key_file_name, need to include file path
   output: **key --char point array, including three keys */
int GetKeyFrmFile(char **key, const char *key_file)
{
    int i;
    char tmpKey[8 + 1];
    FILE *fpCfg = NULL;

    char sessNm[100 + 1], *paraNm[] = {"key1", "key2", "key3"};
    /* Initial session name , para name and then get para value from cfg file */
    if ((fpCfg = fopen(key_file, "r")) == NULL)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "File[%s] fopen error:[%s]!", key_file, strerror(errno));
        return FAILURE;
    }
    strcpy(sessNm, "KEY");
    for (i = 0; i < MAX_KEY_NUM; i++)
    {
        memset(tmpKey, 0x00, sizeof(tmpKey));
        GetConfigValue(fpCfg, sessNm, paraNm[i], tmpKey, sizeof(tmpKey));
        strcpy(key[i], tmpKey);
    }
    if (fpCfg != NULL)
    {
        fclose(fpCfg);
        fpCfg = NULL;
    }
    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 通用读取cfg配置的方法(传进来多个子配置项，获取多个对应子配置项的值)
 ** 输    入： 配置文件名  一级配置名  子配置项名
 ** 输    出： 子配置项的值
 ** 返    回： SUCCESS
 *******************************************************************************/
int GetKeyValueFrmFile(char *CfgFileName, char *SessName, char **ParaName, int ParaCount, char **ParaValue)
{
    int i;
    char tmpKey[100 + 1];
    FILE *fpCfg = NULL;

    if ((fpCfg = fopen(CfgFileName, "r")) == NULL)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "File[%s] fopen error:[%s]!", CfgFileName, strerror(errno));
        return FAILURE;
    }

    for (i = 0; i < ParaCount; i++)
    {
        memset(tmpKey, 0x00, sizeof(tmpKey));
        GetConfigValue(fpCfg, SessName, ParaName[i], tmpKey, sizeof(tmpKey));
        strcpy(ParaValue[i], tmpKey);
    }
    if (fpCfg != NULL)
    {
        fclose(fpCfg);
        fpCfg = NULL;
    }

    return SUCCESS;
}

/*******************************************************************************
 ** 函数功能： 通用读取cfg配置的方法(传进来一个子配置项，获取一个对应子配置项的值)
 ** 输    入： 配置文件名  一级配置名  子配置项名
 ** 输    出： 子配置项的值
 ** 返    回： SUCCESS
 *******************************************************************************/
int GetKeyValueFrmFileOne(char *CfgFileName, char *SessName, char *ParaName, char *ParaValue)
{
    //int i;
    char tmpKey[100 + 1];
    FILE *fpCfg = NULL;

    if ((fpCfg = fopen(CfgFileName, "r")) == NULL)
    {
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "File[%s] fopen error:[%s]!", CfgFileName, strerror(errno));
        return FAILURE;
    }

    memset(tmpKey, 0x00, sizeof(tmpKey));
    GetConfigValue(fpCfg, SessName, ParaName, tmpKey, sizeof(tmpKey));
    strcpy(ParaValue, tmpKey);

    if (fpCfg != NULL)
    {
        fclose(fpCfg);
        fpCfg = NULL;
    }

    return SUCCESS;
}

void getValue(char *keyAndValue, char *key, char *value)
{
    char *p = keyAndValue;

    p = strstr(keyAndValue, key);
    if (p == NULL)
    {
        //printf("没有key\n");
        return;
    }

    p += strlen(key);
    trim(p, value);

    p = strstr(value, "=");
    if (p == NULL)
    {
        printf("没有=\n");
        return;
    }
    p += strlen("=");
    trim(p, value);

    p = strstr(value, "=");
    if (p != NULL)
    {
        printf("多余的=\n");
        return;
    }
    p = value;
    trim(p, value);
}

int writeCFG(const char *filename /*in*/, const char *key /*in*/, const char *value /*in*/)
{
    FILE *pf = NULL;
    char ftemp[PL_FILE_NAME_LEN] = {0}, fline[1024] = {0}, *fp; //文件缓存数组
    long fsize = 0;
    int reg = 0;
    int exit = 0;
    //int i = 0;

    pf = fopen(filename, "r+");
    if (pf == NULL)
    {
        pf = fopen(filename, "w+");
    }
    //获得文件大小
    fseek(pf, 0, SEEK_END); // 将文件指针指向末尾
    fsize = ftell(pf);
    if (fsize > PL_FILE_NAME_LEN)
    {
        printf("文件不能超过8k\n");
        reg = -1;
        goto end;
    }
    fseek(pf, 0, SEEK_SET); //将文件指针指向开头

    //一行一行的读，如果存在key则修改value存到缓存数组中
    while (!feof(pf))
    {
        fgets(fline, 1024, pf);
        if (strstr(fline, key) != NULL && exit == 1)
            strcpy(fline, "");
        if (strstr(fline, key) != NULL && exit == 0) //判断key是否存在
        {
            exit = 1;
            sprintf(fline, "%s = %s\n", key, value);
        }

        printf("fline = %s\n", fline);
        strcat(ftemp, fline);
    }
    if (exit != 1) //如果不存在则把key value写入到最后一行
    {
        sprintf(fline, "%s = %s\n", key, value);
        strcat(ftemp, fline);
    }
    if (pf != NULL)
    {
        fclose(pf);
        pf = fopen(filename, "w+");
        fp = (char *)malloc(sizeof(char) * strlen(ftemp) + 1);
        strcpy(fp, ftemp);
        fp[strlen(fp) - 1] = EOF;
        //fputs(ftemp, pf);
        fputs(fp, pf);
        if (fp != NULL)
        {
            free(fp);
            fp = NULL;
        }
        fclose(pf);
    }

    return reg;
end:
    if (pf != NULL)
        fclose(pf);
    //重新创建一个以filename命名的文件
    return reg;
}

void readCFG(char *filename /*in*/, char *key /*in*/, char **value /*out*/)
{
    FILE *pf = NULL;
    char line[1024] = {0}, vtemp[1024] = {0};

    pf = fopen(filename, "r"); //以只读方式打开

    while (!feof(pf))
    {
        fgets(line, 1024, pf);
        getValue(line, (char *)key, vtemp);
        if (strlen(vtemp) != 0)
            break;
    }
    if (strlen(vtemp) != 0)
    {
        *value = (char *)malloc(sizeof(char) * strlen(vtemp) + 1);
        strcpy((char *)*value, vtemp);
    }
    else
        *value = NULL;
    if (pf != NULL)
        fclose(pf);
}
