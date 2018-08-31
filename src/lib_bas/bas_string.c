/*****************************************************************************/
/*                           TOPCARD                                         */
/*****************************************************************************/
/* PROGRAM NAME: bas_string.c                                                */
/* DESCRIPTIONS: 字符串操作公共函数                                          */
/* AUTHOR      : Robert Peng                                                 */
/* CREATE DATE : 2008-06-23                                                  */
/*****************************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>

#include "bas/bas_global.h"

#define BAS_CMP_DELTA 0.000001

/*****************************************************************************/
/* FUNC:   void basDbl2Char(double dValue, int iFix, int iFloat,             */
/*                          char *pcaBuf)                                    */
/* PARAMS: dValue - 传入的值 (I)                                             */
/*         iFix   - 小数点前整数的位数 (I)                                   */
/*         iFloat - 小数的位数 (I)                                           */
/*         pcaBuf - 转换结果的字符串 (O)                                     */
/* RETURN: 转换结果的字符串                                                  */
/* DESC:   数字转为字符串                                                    */
/*****************************************************************************/
BAS_EXPORT char *basDbl2Char(double dValue, int iFix, int iFloat, char *pcaBuf)
{
    sprintf(pcaBuf, "%0*.0f", iFix + iFloat, dValue * pow(10, iFloat));

    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   double basRound(double dAmount, int iPoint)                       */
/* PARAMS: dAmount - 数值 (I)                                                */
/*         iPoint  - 保留小数位数 (I)                                        */
/* RETURN: 结果数值                                                          */
/* DESC:   四舍五入                                                          */
/*****************************************************************************/
BAS_EXPORT double basRound(double dAmount, int iPoint)
{
    return floor(dAmount * pow(10, iPoint) + 0.5001) / pow(10, iPoint); /* 由于存在浮点误差，需要多加0.0001 */
}

/*****************************************************************************/
/* FUNC:   double basFloor(double dAmount)                                   */
/* PARAMS: dAmount - 数值 (I)                                                */
/* RETURN: 结果数值                                                          */
/* DESC:   取整                                                              */
/*****************************************************************************/
BAS_EXPORT double basFloor(double dAmount)
{
    if (dAmount < 0)
    {
        return -floor(-dAmount);
    }
    else
    {
        return floor(dAmount);
    }
}

/*****************************************************************************/
/* FUNC:   double basFloor2(double dAmount, int iPoint)                      */
/* PARAMS: dAmount - 数值 (I)                                                */
/*         iPoint  - 保留小数位数 (I)                                        */
/* RETURN: 结果数值                                                          */
/* DESC:   取整                                                              */
/*****************************************************************************/
BAS_EXPORT double basFloor2(double dAmount, int iPoint)
{
    if (dAmount < 0)
    {
        return -floor(-dAmount * pow(10, iPoint)) / pow(10, iPoint);
    }
    else
    {
        return floor(dAmount * pow(10, iPoint)) / pow(10, iPoint);
    }
}

/*****************************************************************************/
/* FUNC:   double basCeil(double dAmount)                                    */
/* PARAMS: dAmount - 数值 (I)                                                */
/* RETURN: 结果数值                                                          */
/* DESC:   取整                                                              */
/*****************************************************************************/
BAS_EXPORT double basCeil(double dAmount)
{
    if (dAmount < 0)
    {
        return -ceil(-dAmount);
    }
    else
    {
        return ceil(dAmount);
    }
}

/*****************************************************************************/
/* FUNC:   double basCeil2(double dAmount, int iPoint)                      */
/* PARAMS: dAmount - 数值 (I)                                                */
/*         iPoint  - 保留小数位数 (I)                                        */
/* RETURN: 结果数值                                                          */
/* DESC:   取整                                                              */
/*****************************************************************************/
BAS_EXPORT double basCeil2(double dAmount, int iPoint)
{
    if (dAmount < 0)
    {
        return -ceil(-dAmount * pow(10, iPoint)) / pow(10, iPoint);
    }
    else
    {
        return ceil(dAmount * pow(10, iPoint)) / pow(10, iPoint);
    }
}

/*****************************************************************************/
/* FUNC:   char *basRSpace(char *pcaString, int iLen)                        */
/* PARAMS: pcaString - 转换串 (I/O)                                          */
/*         iLen      - 长度 (I)                                              */
/* RETURN: 结果串                                                            */
/* DESC:   右补空格                                                          */
/*****************************************************************************/
BAS_EXPORT char *basRSpace(char *pcaString, int iLen)
{
    char caBuffer[1024];

    sprintf(caBuffer, "%-*s", iLen, pcaString);
    strncpy(pcaString, caBuffer, iLen);

    return pcaString;
}

/*****************************************************************************/
/* FUNC:   int basIsNumeric(const char *psBuf)                               */
/* PARAMS: psBuf - 输入串 (I)                                                */
/* RETURN: 0 - 不是                                                          */
/*         1 - 是                                                            */
/* DESC:   判断是否为全数字串                                                */
/*****************************************************************************/
BAS_EXPORT int basIsNumeric(const char *psBuf)
{
    size_t i;

    for (i = 0; i < strlen(psBuf); i++)
    {
        if ((psBuf[i] < '0') || (psBuf[i] > '9'))
        {
            return 0;
        }
    }
    return 1;
}

/*****************************************************************************/
/* FUNC:   int basIsAlphabet(const char *psBuf)                              */
/* PARAMS: psBuf - 输入串 (I)                                                */
/* RETURN: 0 - 不是                                                          */
/*         1 - 是                                                            */
/* DESC:   判断是否为全字母串                                                */
/*****************************************************************************/
BAS_EXPORT int basIsAlphabet(const char *psBuf)
{
    size_t i;

    for (i = 0; i < strlen(psBuf); i++)
    {
        if ((psBuf[i] < 'A') ||
            ((psBuf[i] > 'Z') && (psBuf[i] < 'a')) ||
            (psBuf[i] > 'z'))
        {
            return 0;
        }
    }
    return 1;
}

/*****************************************************************************/
/* FUNC:   int basIsSpace(const char *pcaBuf, int iLen)                      */
/* PARAMS: psBuf - 输入串 (I)                                                */
/*         iLen  - 长度                                                      */
/* RETURN: 0 - 不是                                                          */
/*         1 - 是                                                            */
/* DESC:   是否全空格                                                        */
/*****************************************************************************/
BAS_EXPORT int basIsSpace(const char *pcaBuf, int iLen)
{
    int i;

    for (i = 0; i < iLen; i++)
    {
        if (pcaBuf[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

/*****************************************************************************/
/* FUNC:   int basIsZero(const char *pcaBuf, int iLen)                       */
/* PARAMS: psBuf - 输入串 (I)                                                */
/*         iLen  - 长度                                                      */
/* RETURN: 0 - 不是                                                          */
/*         1 - 是                                                            */
/* DESC:   是否全零                                                          */
/*****************************************************************************/
BAS_EXPORT int basIsZero(const char *pcaBuf, int iLen)
{
    int i;

    for (i = 0; i < iLen; i++)
    {
        if (pcaBuf[i] != '0')
        {
            return 0;
        }
    }
    return 1;
}

/*****************************************************************************/
/* FUNC:   int basIsNull(const char *pcaBuf, int iLen)                       */
/* PARAMS: psBuf - 输入串 (I)                                                */
/*         iLen  - 长度                                                      */
/* RETURN: 0 - 不是                                                          */
/*         1 - 是                                                            */
/* DESC:   是否全零或全空格                                                  */
/*****************************************************************************/
BAS_EXPORT int basIsNull(const char *pcaBuf, int iLen)
{
    if ((basIsSpace(pcaBuf, iLen) == 1) || (basIsZero(pcaBuf, iLen) == 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************/
/* FUNC:   char *basRTrim(char *pcaBuf, int iMaxLen)                         */
/* PARAMS: pcaBuf  - 转换串 (I/O)                                            */
/*         iMaxLen - 最大长度 (I)                                            */
/* RETURN: 转换结果串                                                        */
/* DESC:   去除右边空格                                                      */
/*****************************************************************************/
BAS_EXPORT char *basRTrim(char *pcaBuf, int iMaxLen)
{
    int i;

    if ((strlen(pcaBuf) <= (size_t)iMaxLen) && (strlen(pcaBuf) > 0))
    {
        iMaxLen = strlen(pcaBuf);
    }

    for (i = iMaxLen - 1; i >= 0; i--)
    {
        if (pcaBuf[i] == ' ')
        {
            pcaBuf[i] = 0;
        }
        else
        {
            break;
        }
    }

    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   char *basLTrim(char *pcaBuf, int iMaxLen)                         */
/* PARAMS: pcaBuf  - 传入串 (I)                                              */
/*         iMaxLen - 最大长度 (I)                                            */
/* RETURN: 转换结果串                                                        */
/* DESC:   去除左边空格                                                      */
/*****************************************************************************/
BAS_EXPORT char *basLTrim(char *pcaBuf, int iMaxLen)
{
    int i = 0, j = 0;
    int iFlag = 0;

    if (pcaBuf[0] != ' ')
    {
        return pcaBuf;
    }

    while ((pcaBuf[j] != '\0') && j < iMaxLen)
    {
        if (iFlag)
        {
            pcaBuf[i] = 0;
        }
        if (pcaBuf[j] == ' ' && iFlag == 0)
        {
            j++;
        }
        else
        {
            iFlag = 1;
            pcaBuf[i] = pcaBuf[j];
            i++;
            j++;
        }
    }
    pcaBuf[i] = 0;
    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   char *basRemoveSpace(char *pcaBuf, int iMaxLen)                   */
/* PARAMS: pcaBuf  - 传入串 (I)                                              */
/*         iMaxLen - 最大长度 (I)                                            */
/* RETURN: 结果串                                                            */
/* DESC:   去除字符串中的空格                                                */
/*****************************************************************************/
BAS_EXPORT char *basRemoveSpace(char *pcaBuf, int iMaxLen)
{
    int i = 0, j = 0;

    if ((strlen(pcaBuf) <= (size_t)iMaxLen) && (strlen(pcaBuf) > 0))
    {
        iMaxLen = strlen(pcaBuf);
    }

    for (i = 0; i < iMaxLen; i++)
    {
        if (pcaBuf[i] == ' ')
        {
            continue;
        }
        pcaBuf[j++] = pcaBuf[i];
    }
    for (i = j; i < iMaxLen; i++)
    {
        pcaBuf[i] = 0;
    }

    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   char *basToUpper(char *pcaBuf, int iLen)                          */
/* PARAMS: psBuf - 转换串 (I/O)                                              */
/*         iLen  - 长度                                                      */
/* RETURN: 返回串                                                            */
/*         1 - 是                                                            */
/* DESC:   转换为全大写                                                      */
/*****************************************************************************/
BAS_EXPORT char *basToUpper(char *pcaBuf, int iLen)
{
    int i;

    for (i = 0; i < iLen; i++)
    {
        if (((unsigned char)pcaBuf[i] >= 0x81) && ((unsigned char)pcaBuf[i] <= 0xfe))
        {
            /* 如果是汉字的前半个字符，跳过整个汉字不做转换 */
            i++;
        }
        else
        {
            pcaBuf[i] = toupper(pcaBuf[i]);
        }
    }
    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   char *basToLower(char *pcaBuf, int iLen)                          */
/* PARAMS: psBuf - 转换串 (I/O)                                              */
/*         iLen  - 长度                                                      */
/* RETURN: 返回串                                                            */
/*         1 - 是                                                            */
/* DESC:   转换为全小写                                                      */
/*****************************************************************************/
BAS_EXPORT char *basToLower(char *pcaBuf, int iLen)
{
    int i;

    for (i = 0; i < iLen; i++)
    {
        if (((unsigned char)pcaBuf[i] >= 0x81) && ((unsigned char)pcaBuf[i] <= 0xfe))
        {
            /* 如果是汉字的前半个字符，跳过整个汉字不做转换 */
            i++;
        }
        else
        {
            pcaBuf[i] = tolower(pcaBuf[i]);
        }
    }
    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   int basDoubleCmp(double dVal1, double dVal2)                      */
/* PARAMS: dVal1 - 比较值1 (I)                                               */
/*         dVal2 - 比较值2 (I)                                               */
/* RETURN: 0  : dVal1 = dVal2                                                */
/*         <0 : dVal1 < dVal2                                                */
/*         >0 : dVal1 > dVal2                                                */
/* DESC:   去除左边空格                                                      */
/*****************************************************************************/
BAS_EXPORT int basDoubleCmp(double dVal1, double dVal2)
{
    if (fabs(dVal1 - dVal2) < BAS_CMP_DELTA)
    {
        return 0;
    }
    if (dVal1 > dVal2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/*****************************************************************************/
/* FUNC:   int basChkActBit(char *pcaActno, int iCardLen)                    */
/* PARAMS: pcaActno - 帐号 (I/O)                                             */
/*         iCardLen -  (I)                                                   */
/* RETURN: 1  : 校验位正确                                                   */
/*         0  : 校验位错误                                                   */
/* DESC:   计算/检查校验位                                                   */
/*****************************************************************************/
BAS_EXPORT int basChkActBit(char *pcaActno, int iCardLen)
{
    int i, t;
    int iSum = 0;
    char cBit, cOrgBit;

    for (i = 0; i < iCardLen; i++)
    {
        if ((pcaActno[i] == ' ') || (pcaActno[i] == 0))
        {
            iCardLen = i;
            break;
        }
    }

    for (i = iCardLen - 2; i >= 0; i -= 2)
    {
        t = (pcaActno[i] - '0') * 2;
        iSum += t / 10 + t % 10;
        if (i - 1 >= 0)
        {
            iSum += (pcaActno[i - 1] - '0');
        }
    }

    if (iSum % 10 == 0)
    {
        cBit = '0';
    }
    else
    {
        cBit = '0' + 10 - iSum % 10;
    }

    cOrgBit = pcaActno[iCardLen - 1];
    pcaActno[iCardLen - 1] = cBit;

    if (cOrgBit == cBit)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************/
/* FUNC:   char *basStringPattern(char *pcaString, const char *pcaPattern)   */
/* PARAMS: pcaString  - 转换串 (I/O)                                         */
/*         pcaPattern - 格式串 (I)                                           */
/* RETURN: 返回串                                                            */
/* DESC:   按模式串转换                                                      */
/*****************************************************************************/
BAS_EXPORT char *basStringPattern(char *pcaString, const char *pcaPattern)
{
    char caBuf[1024];
    int i, j;
    int iCFlag = 0; /* 使用 ZZZ,ZZZ模式的标志 */
    int iZFlag = 0;
    int iNFlag = 0; /* 负数标志 */

    j = 0;
    memset(caBuf, 0, sizeof(caBuf));

    for (i = 0; (size_t)i < strlen(pcaPattern); i++)
    {
        if (pcaString[j] == 0)
        {
            break;
        }
        switch (pcaPattern[i])
        {
        case 'U': /* 转大写 */
            caBuf[i] = toupper(pcaString[j]);
            j++;
            break;
        case 'L': /* 转小写 */
            caBuf[i] = tolower(pcaString[j]);
            j++;
            break;
        case '#':
            if ((pcaString[j] == ' ') && (iCFlag == 1))
            {
                caBuf[i] = '0';
            }
            else
            {
                caBuf[i] = pcaString[j];
            }
            j++;
            break;
        case 'Z':
            iCFlag = 1;
            if (iNFlag == 1)
            {
                if ((caBuf[i - 1] == '-') && (pcaString[j] == '0'))
                {
                    caBuf[i - 1] = ' ';
                    caBuf[i] = '-';
                    j++;
                    break;
                }
                iNFlag = 0;
            }
            if (pcaString[j] == '-')
            {
                iNFlag = 1;
            }
            if (iZFlag == 1)
            {
                caBuf[i] = pcaString[j];
            }
            else
            {
                if ((pcaString[j] != '0') && (pcaString[j] != ' '))
                {
                    iZFlag = 1;
                    caBuf[i] = pcaString[j];
                }
                else
                {
                    caBuf[i] = ' ';
                }
            }
            j++;
            break;
        case ',':
            if (iNFlag == 1)
            {
                caBuf[i - 1] = ' ';
                caBuf[i] = '-';
                break;
            }
            if (iZFlag == 1)
            {
                caBuf[i] = ',';
            }
            else
            {
                caBuf[i] = ' ';
            }
            break;
        default:
            caBuf[i] = pcaPattern[i];
        }
    }

    strcpy(pcaString, caBuf);

    return pcaString;
}

/*****************************************************************************/
/* FUNC:   char *basFloatToSection(double dValue, int iPointLen)             */
/* PARAMS: dValue    - 数值 (I)                                              */
/*         iPointLen - 格式串 (I)                                            */
/* RETURN: 返回串                                                            */
/* DESC:   返回分节符的格式                                                  */
/*****************************************************************************/
BAS_EXPORT char *basFloatToSection(double dValue, int iPointLen)
{
    static char caBuf[100];
    char caPattern[30];
    int i;

    strcpy(caPattern, "ZZ,ZZZ,ZZZ,ZZZ,ZZZ,ZZZ,ZZ#");
    if (iPointLen > 0)
    {
        strcat(caPattern, ".");
        for (i = 0; i < iPointLen; i++)
        {
            strcat(caPattern, "#");
        }
    }
    sprintf(caBuf, "%0*.f", 20 + iPointLen, dValue * pow(10, iPointLen));
    basStringPattern(caBuf, caPattern);

    return basLTrim(caBuf, sizeof(caBuf));
}

/*****************************************************************************/
/* FUNC:   char *basAddString(char *pcaBuf, int iLen, int iVal)              */
/* PARAMS: pcaBuf - 数字串 (I/O)                                             */
/*         iLen   - 数字串的长度 (I)                                         */
/*         iVal   - 加数，目前只支持1 (I)                                    */
/* RETURN: 返回串                                                            */
/* DESC:   数字串加法运算                                                    */
/*****************************************************************************/
BAS_EXPORT char *basAddString(char *pcaBuf, int iLen, int iVal)
{
    int i = 0;

    for (i = iLen - 1; i >= 0; i--)
    {
        if (pcaBuf[i] < '9')
        {
            pcaBuf[i]++;
            break;
        }
        pcaBuf[i] = '0';
    }
    if (i < 0)
    {
        memset(pcaBuf, '0', iLen);
    }
    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   int basMemcmp(const char *pcaBuf1, const char *pcaBuf2, int iLen) */
/* PARAMS: pcaBuf1 - 数据1 (I)                                               */
/*         pcaBuf2 - 数据2 (I)                                               */
/*         iLen    - 长度                                                    */
/* RETURN: 0  : pcaBuf1 = pcaBuf2                                            */
/*         -1 : pcaBuf1 < pcaBuf2                                            */
/*         1  : pcaBuf1 > pcaBuf2                                            */
/* DESC:   忽略右边空格的内存比较                                            */
/*****************************************************************************/
BAS_EXPORT int basMemcmp(const char *pcaBuf1, const char *pcaBuf2, int iLen)
{
    int i;
    int iFlag1 = 0, iFlag2 = 0;
    for (i = 0; i < iLen; i++)
    {
        if ((iFlag1 == 0) && (pcaBuf1[i] == 0))
        {
            iFlag1 = 1;
        }
        if ((iFlag2 == 0) && (pcaBuf2[i] == 0))
        {
            iFlag2 = 1;
        }
        if (iFlag1 == 1 && iFlag2 == 1)
        {
            break;
        }
        if (iFlag1 == 1)
        {
            if (pcaBuf2[i] != ' ')
            {
                return -1;
            }
            continue;
        }
        if (iFlag2 == 1)
        {
            if (pcaBuf1[i] != ' ')
            {
                return 1;
            }
            continue;
        }
        if (pcaBuf1[i] > pcaBuf2[i])
        {
            return 1;
        }
        if (pcaBuf1[i] < pcaBuf2[i])
        {
            return -1;
        }
    }
    return 0;
}

/*****************************************************************************/
/* FUNC:   int basCountString(const char *pcaBuf, char cChar, int iLen)      */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         pcaBuf2 - 字符 (I)                                                */
/*         iLen    - 长度                                                    */
/* RETURN: cChar的数量                                                       */
/* DESC:   计算字符串中指定的字符的数量                                      */
/*****************************************************************************/
BAS_EXPORT int basCountString(const char *pcaBuf, char cChar, int iLen)
{
    int i;
    int iCount = 0;
    for (i = 0; i < iLen; i++)
    {
        if (pcaBuf[i] == 0)
        {
            break;
        }
        if (pcaBuf[i] == cChar)
        {
            iCount++;
        }
    }

    return iCount;
}

/*****************************************************************************/
/* FUNC:   double basAtof(const char *pcaBuf, int iLen)                      */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         iLen    - 长度                                                    */
/* RETURN: 转换的数值                                                        */
/* DESC:   字符串转换为double数值                                            */
/*****************************************************************************/
BAS_EXPORT double basAtof(const char *pcaBuf, int iLen)
{
    char caTmp[256];

    memset(caTmp, 0, sizeof(caTmp));
    memcpy(caTmp, pcaBuf, iLen);
    return atof(caTmp);
}

/*****************************************************************************/
/* FUNC:   long basAtol(const char *pcaBuf, int iLen)                        */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         iLen    - 长度                                                    */
/* RETURN: 转换的数值                                                        */
/* DESC:   字符串转换为long数值                                              */
/*****************************************************************************/
BAS_EXPORT long basAtol(const char *pcaBuf, int iLen)
{
    char caTmp[256];

    memset(caTmp, 0, sizeof(caTmp));
    memcpy(caTmp, pcaBuf, iLen);
    return atol(caTmp);
}

/*****************************************************************************/
/* FUNC:   int basCountStr(const char *pcaBuf, const char *pStr)             */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         pStr    - 字符串 (I)                                              */
/* RETURN: pStr的数量                                                        */
/* DESC:   计算字符串中包含指定字符串的数量                                  */
/*****************************************************************************/
BAS_EXPORT int basCountStr(const char *pcaBuf, const char *pStr)
{
    int iLen1;
    int iLen2;
    int iCnt = 0;
    int i;

    iLen1 = strlen(pcaBuf);
    iLen2 = strlen(pStr);

    if (iLen2 > iLen1)
        return 0;

    for (i = 0; i < iLen1;)
    {
        if (memcmp(pcaBuf + i, pStr, iLen2) == 0)
        {
            iCnt++;
            i += iLen2;
        }
        else
        {
            i++;
        }
    }
    return iCnt;
}

/*****************************************************************************/
/* FUNC:   int basLocateStr(const char *pcaBuf, const char *pStr)            */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         pStr    - 字符串 (I)                                              */
/* RETURN: pStr的首次出现位置                                                */
/* DESC:   计算字符串中指定字符串的位置                                      */
/*****************************************************************************/
BAS_EXPORT int basLocateStr(const char *pcaBuf, const char *pStr)
{
    int iLen1;
    int iLen2;
    int i;

    iLen1 = strlen(pcaBuf);
    iLen2 = strlen(pStr);

    if (iLen2 > iLen1)
        return -1;

    for (i = 0; i < iLen1; i++)
    {
        if (memcmp(pcaBuf + i, pStr, iLen2) == 0)
        {
            break;
        }
    }

    if (i == iLen1)
    {
        return -1;
    }

    return i;
}

/*****************************************************************************/
/* FUNC:   int basLocateSpace(const char *pcaBuf)                            */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/* RETURN: 空格或者TAB的首次出现位置                                         */
/* DESC:   计算字符串中首个空格或者TAB的位置                                 */
/*****************************************************************************/
BAS_EXPORT int basLocateSpace(const char *pcaBuf)
{
    int iLen1;
    //int     iLen2;
    int i;

    iLen1 = strlen(pcaBuf);

    for (i = 0; i < iLen1; i++)
    {
        if (pcaBuf[i] == ' ' || pcaBuf[i] == '\t')
        {
            break;
        }
    }

    if (i == iLen1)
    {
        return -1;
    }

    return i;
}

/*****************************************************************************/
/* FUNC:   void basInitSpaces(char *pcaBuf, int iLen)                        */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         iLen    - 长度                                                    */
/* RETURN:                                                                   */
/* DESC:   将字符串初始化为空格                                              */
/*****************************************************************************/
BAS_EXPORT void basInitSpaces(char *pcaBuf, int iLen)
{
    int i;

    for (i = 0; i < iLen; i++)
    {
        pcaBuf[i] = ' ';
    }

    return;
}

/*****************************************************************************/
/* FUNC:   void basInitZeros(char *pcaBuf, int iLen)                         */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         iLen    - 长度                                                    */
/* RETURN:                                                                   */
/* DESC:   将字符串初始化为'0'                                               */
/*****************************************************************************/
BAS_EXPORT void basInitZeros(char *pcaBuf, int iLen)
{
    int i;

    for (i = 0; i < iLen; i++)
    {
        pcaBuf[i] = '0';
    }

    return;
}

/*****************************************************************************/
/* FUNC:   void basRTrimChar(char *pcaBuf, char cStr)                        */
/* PARAMS: pcaBuf  - 字符串 (I)                                              */
/*         cStr    - 字符                                                    */
/* RETURN:                                                                   */
/* DESC:   去掉字符串后面的第一个cStr字符                                    */
/*****************************************************************************/
BAS_EXPORT void basRTrimChar(char *pcaBuf, int cStr)
{
    int i;
    int iLen;

    iLen = strlen(pcaBuf);

    for (i = iLen; i >= 0; i--)
    {
        if (pcaBuf[i] == cStr)
        {
            pcaBuf[i] = 0;
            break;
        }
    }

    return;
}

/*****************************************************************************/
/* FUNC:   int basIsSameIdno(const char *pcaIdno1, const char *pcaIdno2)     */
/* PARAMS: pcaIdno1  - 身份证号1 (I)                                         */
/*         pcaIdno2  - 身份证号2 (I)                                         */
/* RETURN: 0 : 不同                                                          */
/*         1 : 相同                                                          */
/* DESC:   比较两个身份证号码（支持15位和18位的比较）                        */
/*****************************************************************************/
BAS_EXPORT int basIsSameIdno(const char *pcaIdno1, const char *pcaIdno2)
{
    char caTmp1[18 + 1], caTmp2[18 + 1];

    memset(caTmp1, 0, sizeof(caTmp1));
    memset(caTmp2, 0, sizeof(caTmp2));

    memcpy(caTmp1, pcaIdno1, sizeof(caTmp1) - 1);
    memcpy(caTmp2, pcaIdno2, sizeof(caTmp2) - 1);

    basRTrim(caTmp1, sizeof(caTmp1));
    basRTrim(caTmp2, sizeof(caTmp2));

    if (strlen(caTmp1) == 18)
    {
        basIdno18To15(caTmp1);
    }
    if (strlen(caTmp2) == 18)
    {
        basIdno18To15(caTmp2);
    }

    if (strcmp(caTmp1, caTmp2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************/
/* FUNC:   char *basIdno18To15(char *pcaIdno)                                */
/* PARAMS: pcaIdno  - 18位身份证号 (I/O)                                     */
/* RETURN: 15位身份证号                                                      */
/* DESC:   把18位身份证号转换为15位                                          */
/*****************************************************************************/
BAS_EXPORT char *basIdno18To15(char *pcaIdno)
{
    char caTmp[15 + 1];

    memset(caTmp, 0, sizeof(caTmp));
    memcpy(caTmp, pcaIdno, 6);
    memcpy(caTmp + 6, pcaIdno + 8, 6);
    memcpy(caTmp + 12, pcaIdno + 14, 3);

    strcpy(pcaIdno, caTmp);

    return pcaIdno;
}

/*****************************************************************************/
/* FUNC:   char *basIdno15To18(char *pcaIdno)                                */
/* PARAMS: pcaIdno  - 15位身份证号 (I/O)                                     */
/* RETURN: 18位身份证号                                                      */
/* DESC:   把15位身份证号转换为18位                                          */
/*****************************************************************************/
BAS_EXPORT char *basIdno15To18(char *pcaIdno)
{
    char caTmp[18 + 1];

    memset(caTmp, 0, sizeof(caTmp));
    memcpy(caTmp, pcaIdno, 6);
    caTmp[6] = '1';
    caTmp[7] = '9';
    memcpy(caTmp + 8, pcaIdno + 6, 9);

    basIdno18GenCheckVal(caTmp);
    strcpy(pcaIdno, caTmp);

    return pcaIdno;
}

/*****************************************************************************/
/* FUNC:   char basIdno18GenCheckVal(char *pcaIdno)                          */
/* PARAMS: pcaIdno  - 18位身份证号 (I/O)                                     */
/* RETURN: 18位身份证号校验位                                                */
/* DESC:   为18位身份证号码生成校验位                                        */
/*****************************************************************************/
BAS_EXPORT char basIdno18GenCheckVal(char *pcaIdno)
{
    static int miaWi[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1};
    static char mcaVer[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2', '\0'};
    int iSum = 0;
    int i;

    for (i = 0; i < 17; i++)
    {
        iSum += (pcaIdno[i] - '0') * miaWi[i];
    }

    pcaIdno[17] = mcaVer[iSum % 11];

    return pcaIdno[17];
}

/*****************************************************************************/
/* FUNC:   int basIdno18IsValid(const char *pcaIdno)                         */
/* PARAMS: pcaIdno  - 18位身份证号 (I)                                       */
/* RETURN: 1 - 校验通过 0 - 校验失败                                         */
/* DESC:   为18位身份证号码验证有效性                                        */
/*****************************************************************************/
BAS_EXPORT int basIdno18IsValid(const char *pcaIdno)
{
    char caTmp[18 + 1];

    strcpy(caTmp, pcaIdno);
    basIdno18GenCheckVal(caTmp);

    if (caTmp[17] == pcaIdno[17])
    {
        return BAS_TRUE;
    }
    else
    {
        return BAS_FALSE;
    }
}

/*****************************************************************************/
/* FUNC:   void basSprintf(char *pcaBuf, int iLen, const char *pcaFmt, ...)  */
/* PARAMS: pcaBuf   - 返回的串(不输出\0) (O)                                 */
/*         iLen     - 返回的长度 (I)                                         */
/*         pcaFmt   - 格式串格式同printf (I)                                 */
/*         ...      - 变参部分 (I)                                           */
/* RETURN: 无                                                                */
/* DESC:   格式串输出（指定最大串长度）                                      */
/*****************************************************************************/
BAS_EXPORT void basSprintf(char *pcaBuf, int iLen, const char *pcaFmt, ...)
{
    va_list vlVar;
    char caTmp[2560];

    va_start(vlVar, pcaFmt);
    vsprintf(caTmp, pcaFmt, vlVar);
    va_end(vlVar);

    strncpy(pcaBuf, caTmp, iLen);
}

/*****************************************************************************/
/* FUNC:   char *basLFill(char *pcaBuf, int iLen, char cChar)                */
/* PARAMS: pcaBuf   - 转换串 (I/O)                                           */
/*         iLen     - 总长度 (I)                                             */
/*         cChar    - 补的字符 (I)                                           */
/*         ...      - 变参部分 (I)                                           */
/* RETURN: 转换后的串                                                        */
/* DESC:   串左补字符                                                        */
/*****************************************************************************/
BAS_EXPORT char *basLFill(char *pcaBuf, int iLen, char cChar)
{
    char caBuf[512];

    int iOrgLen = strlen(pcaBuf);
    if (iOrgLen >= iLen)
    {
        return pcaBuf;
    }

    memset(caBuf, 0, sizeof(caBuf));
    memset(caBuf, cChar, iLen - iOrgLen);
    strcat(caBuf, pcaBuf);
    memcpy(pcaBuf, caBuf, iLen);

    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   int basChar2FloatOfAmt(char *pcaBuf, double *dAmt)                */
/* PARAMS: pcaBuf    - 转换串 (I)                                            */
/*         pcaOutBuf - 转出串 (O)                                            */
/* RETURN: 0 - 成功                                                          */
/*        -1 - 失败                                                          */
/* DESC:   字符串金额转换为金额                                              */
/*****************************************************************************/
BAS_EXPORT int basChar2FloatOfAmt(char *pcaBuf, double *dAmt)
{
    char *temp;
    int len, i, j;
    int iCnt;
    char caStr[2000];

    memset(caStr, 0, sizeof(caStr));
    iCnt = 0;

    temp = pcaBuf;
    while ((' ' == *temp) || (',' == *temp))
    {
        temp++;
    }

    len = strlen(temp);
    if (0 == len)
    {
        *dAmt = 0;
        return 0;
    }

    while (' ' == temp[len - 1] || ',' == temp[len - 1] || '\n' == temp[len - 1])
    {
        len--;
    }
    temp[len] = '\0';

    j = 0;
    for (i = 0; i <= len; i++)
    {
        if (temp[i] == ' ' || temp[i] == ',')
            continue;

        if (temp[i] == '.')
            iCnt++;

        if (iCnt > 1)
        {
            return -1;
        }

        if ((i != len) && (temp[i] != '.') && (temp[i] < '0' || temp[i] > '9'))
        {
            return -1;
        }

        caStr[j] = temp[i];
        j++;
    }

    *dAmt = atof(caStr);

    return 0;
}

/*****************************************************************************/
/* FUNC:   char *basLtoa(long lValue, char *pcaBuf, int iDec)                */
/* PARAMS: lValue    - 数值   (I)                                            */
/*         pcaBuf    - 返回串 (O)                                            */
/*         iDec      - 进制   (I) 只支持10                                   */
/* RETURN: 0 - 成功                                                          */
/*        -1 - 失败                                                          */
/* DESC:   长整型转为字符串                                                  */
/*****************************************************************************/
BAS_EXPORT char *basLtoa(long lValue, char *pcaBuf, int iDec)
{
    sprintf(pcaBuf, "%ld", lValue);
    return pcaBuf;
}

/*****************************************************************************/
/* FUNC:   char *basTransVertical(const char *pcaBuf)                        */
/* PARAMS: pcaBuf    - 输入串 (I)                                            */
/* RETURN: 转换串                                                            */
/* DESC:   转换串中的"|"为"\|"                                               */
/*****************************************************************************/
BAS_EXPORT char *basTransVertical(const char *pcaBuf, int iLen)
{
    static char caTmpBuf[1024 + 1];
    char caTmpBuf2[1024 + 1];
    int i = 0, j = 0;

    memset(caTmpBuf, 0, sizeof(caTmpBuf));
    memset(caTmpBuf2, 0, sizeof(caTmpBuf2));

    if ((size_t)iLen > sizeof(caTmpBuf2) - 1)
    {
        iLen = sizeof(caTmpBuf2) - 1;
    }
    sprintf(caTmpBuf2, "%-*.*s", iLen, iLen, pcaBuf);

    for (i = 0; (size_t)i < strlen(caTmpBuf2); i++)
    {
        if ((size_t)j > (sizeof(caTmpBuf) - 2))
        {
            break;
        }
        if (caTmpBuf2[i] == '|')
        {
            caTmpBuf[j] = '\\';
            j++;
            caTmpBuf[j] = '|';
            j++;
            continue;
        }
        if (caTmpBuf2[i] == '\\')
        {
            caTmpBuf[j] = '\\';
            j++;
            caTmpBuf[j] = '\\';
            j++;
            continue;
        }
        if (((unsigned char)caTmpBuf2[i] >= 0x81) && ((unsigned char)caTmpBuf2[i] <= 0xfe))
        {
            caTmpBuf[j] = caTmpBuf2[i];
            j++;
            i++;
            caTmpBuf[j] = caTmpBuf2[i];
            j++;
            continue;
        }
        caTmpBuf[j] = caTmpBuf2[i];
        j++;
    }

    return caTmpBuf;
}

/*****************************************************************************/
/* FUNC:   char *basTransVertical(const char *pcaBuf)                        */
/* PARAMS: ptStr 字符串   iCutLen 截取的最大长度                             */
/* RETURN: 返回字符串实际应该截取的长度                                      */
/* DESC:   字符串长度获取函数                                                */
/*****************************************************************************/
BAS_EXPORT int basStrRealCutLen(const char *ptStr, int iCutLen)
{
    int iStrLen = 0;
    int iCurr = 0;
    int iPrev = 0;

    iStrLen = strlen(ptStr);
    if (iStrLen <= iCutLen)
    {
        return iStrLen;
    }

    while (iCurr <= iCutLen)
    {
        char c = *(ptStr + iCurr);

        iPrev = iCurr;
        int cc = c & 0x000000FF;
        if (cc >= 129)
        {
            iCurr += 2;
        }
        else
        {
            iCurr += 1;
        }
    }

    return iPrev;
}
