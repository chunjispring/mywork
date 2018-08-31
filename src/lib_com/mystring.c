/*******************************************************************************
 * 文件名   : mystring.c
 * 文件功能 : 字符处理相关函数
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

#include "mycomm.h"

/*******************************************************************************
 ** 函数功能： 封装strlen函数，解决其参数为NULL时core掉的问题
 ** 输    入： 要计算长度的字符串
 ** 输    出： 无
 ** 返    回： 字符串的长度
 *******************************************************************************/
int mystrlen(const char *str)
{
    if (str != NULL)
        return strlen(str);
    else
        //参数传NULL时默认长度为0
        return 0;
}

/*******************************************************************************
 ** 函数功能： 去除字符串左侧空格/回车/换行
 ** 输    入： 需要去除空格的字符串
 ** 输    出： 去除左侧空格后的字符串
 ** 返    回： 去除左侧空格后的字符串（为实现链式表达式）
 *******************************************************************************/
char *LTrim(char *string)
{
    int i = 0;
    char strtmp[1024 * 2];
    memset(strtmp, 0x00, sizeof(strtmp));
    if (mystrlen(string) > 0)
    {
        while (string[i] == ' ')
            i++;
        memcpy(strtmp, string + i, mystrlen(string) - i);
        memset(string, 0x00, mystrlen(string));
        strcpy(string, strtmp);
    }

    return string;
}

/*******************************************************************************
 ** 函数功能： 去除字符串右侧空格/回车/换行
 ** 输    入： 需要去除空格的字符串
 ** 输    出： 去除右侧空格后的字符串
 ** 返    回： 去除右侧空格后的字符串（为实现链式表达式）
 *******************************************************************************/
char *RTrim(char *string)
{
    int i;
    i = mystrlen(string) - 1;
    if (string[i] != ' ' && string[i] != '\n')
    {
        return string;
    }
    while (string[i] == ' ' || string[i] == '\n' || string[i] == '\r')
    {
        if (i == 0)
        {
            string[i] = '\0';
            return string;
        }
        i--;
    }
    string[i + 1] = '\0';
    return string;
}

/*******************************************************************************
 ** 函数功能： 去除字符串中所有的空格
 ** 输    入： 需要去除空格的字符串
 ** 输    出： 去除空格后的字符串
 ** 返    回： 去除空格后的字符串（为实现链式表达式）
 *******************************************************************************/
char *AllTrim(char *string)
{
    char strtmp[1024];
    int i, j;
    j = mystrlen(string);
    memset(strtmp, 0, sizeof(strtmp));
    for (i = 0; i < j; i++)
    {
        if (string[i] == ' ')
            continue;
        else
            strncat(strtmp, string + i, 1);
    }
    strcpy(string, strtmp);

    return string;
}

void trim(char *strIn, char *strOut)
{

    char *start, *end, *temp; //定义去除空格后字符串的头尾指针和遍历指针

    temp = strIn;

    while (*temp == ' ')
    {
        ++temp;
    }

    start = temp; //求得头指针

    temp = strIn + mystrlen(strIn) - 1; //得到原字符串最后一个字符的指针(不是'\0')

    while (*temp == ' ')
    {
        --temp;
    }

    end = temp; //求得尾指针

    for (strIn = start; strIn <= end;)
    {
        *strOut++ = *strIn++;
    }

    *strOut = '\0';
}

/*******************************************************************************
 ** 函数功能： 检查输入的参数是否为整型数字
 ** 输    入： num--需要检查的字符串
 ** 输    出： 无
 ** 返    回： 0 -- 成功  -1 --失败
 *******************************************************************************/
int IsIntNumber(char *num)
{
    char str[11 + 1];
    int i = 0;
    char *p;
    strcpy(str, "0123456789");
    for (i = 0; i < mystrlen(num); i++)
    {
        p = strchr(str, num[i]);
        if (p == NULL)
            return -1;
    }
    return 0;
}

/*******************************************************************************
 ** 函数功能： 数据对齐函数
 ** 输    入： string -- 对齐数据(I/O)
 **            align  -- 对齐方式(I)
 **            fmtlen -- 数据总长度(I)
 ** 输    出： string -- 对齐数据(I/O)
 ** 返    回： FAILURE 错误发生，SUCCESS 成功结束
 *******************************************************************************/
int Data_Align(char *string, char align, int fmtlen)
{
    int iBack;
    int iStrLen, iTemp;
    char buff[MAX_LINE_LEN];

    iBack = SUCCESS;
    iTemp = 0;
    iStrLen = mystrlen(string);
    if (iStrLen > fmtlen)
    {
        iStrLen = fmtlen;
    }
    memset(buff, ' ', sizeof(buff));

    switch (align)
    {
    case 'L':
        memcpy(buff, string, iStrLen);
        break;

    case 'M':
        iTemp = (fmtlen - iStrLen) / 2;
        memcpy(&buff[iTemp], string, iStrLen);
        break;

    case 'R':
        iTemp = fmtlen - iStrLen;
        memcpy(&buff[iTemp], string, iStrLen);
        break;

    default:
        COMM_Trace(__FILE__, __LINE__, __FUNCTION__, "unsuport data align [%c]!", align);
        iBack = FAILURE;
    }

    memcpy(string, buff, fmtlen);
    string[fmtlen] = 0;

    return iBack;
}
