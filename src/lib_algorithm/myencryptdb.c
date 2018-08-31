#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mycomm.h"
#include "myalgorithm.h"

int put2file(char *uname, char *passwd, int passwd_cycle, char *dbsrc);
int readdbinfo(char *uname, char *passwd, long *passwd_len, char *dbsrc);
int getenkey(char *enkey);
int check_word(char *username, char *password, char *dbsource);
extern int des(unsigned char *source, unsigned char *dest, unsigned char *inkey, int flg);

/*加密主函数*/
int myencrypt(char *username, char *password, char *dbsource)
{
    char passwd_dest[256], passwd_final[256];
    char enkey1[8 + 1], enkey2[8 + 1];

    char aTmppasswd[256];
    char aFirpasswd[256], aFirdest[256];
    char aSeconpasswd[256], aSecondest[256];
    int iModzero; /*判断密码长度是否正好是8的倍数*/
    int passwd_len;
    int iPasslen_cycle;

    int i, iret;
    int rest = 0;

    iret = check_word(username, password, dbsource);
    if (iret != SUCCESS)
    {
        return iret;
    }
    passwd_len = strlen(password);

    memset(passwd_dest, 0x00, sizeof(passwd_dest));
    memset(passwd_final, 0x00, sizeof(passwd_final));
    memset(enkey1, 0x00, sizeof(enkey1));
    memset(enkey2, 0x00, sizeof(enkey2));

    memset(aTmppasswd, 0x00, sizeof(aTmppasswd));
    memset(aFirpasswd, 0x00, sizeof(aFirpasswd));
    memset(aFirdest, 0x00, sizeof(aFirdest));

    /*读取密钥文件中的密钥*/
    iret = getenkey(enkey1);
    if (iret != SUCCESS)
    {
        return iret;
    }

    /*第一遍加密*/
    /*加密密码*/

    for (i = 0; i < passwd_len / 8; i++)
    {
        memset(aTmppasswd, 0x00, sizeof(aTmppasswd));
        memset(aFirpasswd, 0x00, sizeof(aFirpasswd));
        memset(aFirdest, 0x00, sizeof(aFirdest));

        memcpy(aTmppasswd, password + i * 8, 8);
        des((unsigned char *)aTmppasswd, (unsigned char *)aFirdest, (unsigned char *)enkey1, ENCRYPT);
        memcpy(passwd_dest + i * 8, aFirdest, 8);
    }
    rest = passwd_len % 8;
    if (rest != 0)
    {
        memset(aTmppasswd, 0x00, sizeof(aTmppasswd));
        memset(aFirdest, 0x00, sizeof(aFirdest));
        memcpy(aTmppasswd, password + i * 8, rest);
        des((unsigned char *)aTmppasswd, (unsigned char *)aFirdest, (unsigned char *)enkey1, ENCRYPT);
        memcpy(passwd_dest + i * 8, aFirdest, 8);
    }

    /*第二遍加密*/
    strcpy(enkey2, ENCRYPTKEY); /*固定密钥*/

    memset(aTmppasswd, 0x00, sizeof(aTmppasswd));
    memset(aSeconpasswd, 0x00, sizeof(aSeconpasswd));
    iModzero = passwd_len % 8;
    if (iModzero == 0)
    {
        iPasslen_cycle = passwd_len / 8;
    }
    else
    {
        iPasslen_cycle = passwd_len / 8 + 1;
    }
    for (i = 0; i < iPasslen_cycle; i++)
    {

        memset(aTmppasswd, 0x00, sizeof(aTmppasswd));
        memset(aSeconpasswd, 0x00, sizeof(aSeconpasswd));
        memset(aSecondest, 0x00, sizeof(aSecondest));

        memcpy(aTmppasswd, passwd_dest + i * 8, 8);
        memcpy(aSeconpasswd, aTmppasswd, 8);
        des((unsigned char *)aSeconpasswd, (unsigned char *)aSecondest, (unsigned char *)enkey2, ENCRYPT);
        memcpy(passwd_final + i * 8, aSecondest, 8);
    }

    /*将加密信息写入文件*/
    iret = put2file(username, passwd_final, iPasslen_cycle, dbsource);
    if (iret != SUCCESS)
    {
        return ERRPUTFILE;
    }

    return SUCCESS;
}

/*将用户名、加密密码及数据库连接串输入文件*/
int put2file(char *uname, char *passwd, int passwd_cycle, char *dbsrc)
{
    FILE *fpconfig;
    int iRet = 0;
    char aCfgPath[128];
    char aConfFileName[128];
    int i;

    memset(aCfgPath, 0x00, sizeof(aCfgPath));
    iRet = GetCfgPath(aCfgPath);
    if (iRet != 0)
    {
        return iRet;
    }

    memset(aConfFileName, 0, sizeof(aConfFileName));
    strcat(aConfFileName, aCfgPath);
    strcat(aConfFileName, "/");
    strcat(aConfFileName, "mydb.txt");
    fpconfig = NULL;
    if ((fpconfig = fopen(aConfFileName, "w+")) == NULL)
    {
        return ERROPENFILE;
    }
    fputs(uname, fpconfig);
    fputs("\n", fpconfig);
    for (i = 0; i < passwd_cycle * 8; i++)
    {
        fprintf(fpconfig, "%02X", (unsigned char)passwd[i]);
    }
    fputs("\n", fpconfig);
    fputs(dbsrc, fpconfig);

    fclose(fpconfig);
    return SUCCESS;
}

/*解密主函数*/
int mydecrypt(char *username, char *password, char *dbsource)
{
    char uname_dest[256], passwd_dest[256], dbsrc_dest[256];
    char enkey1[8 + 1], enkey2[8 + 1];
    char aTmppasswd[128], aFirdest[128];
    char aFstpasswd[128];
    char aSecondest[128], aFinalpasswd[128];
    long lPasswdLen;

    int i, iret;

    memset(uname_dest, 0x00, sizeof(uname_dest));
    memset(passwd_dest, 0x00, sizeof(passwd_dest));
    memset(dbsrc_dest, 0x00, sizeof(dbsrc_dest));
    memset(enkey1, 0x00, sizeof(enkey1));
    memset(enkey2, 0x00, sizeof(enkey2));

    /*读取密钥文件中的密钥*/
    iret = getenkey(enkey2);
    if (iret != SUCCESS)
    {
        return iret;
    }
    lPasswdLen = 0;
    /*从配置文件中读取用户名、密码、连接串，并判断长度*/
    iret = readdbinfo(uname_dest, passwd_dest, &lPasswdLen, dbsrc_dest);
    if (iret != SUCCESS)
    {
        return iret;
    }

    iret = check_word(uname_dest, passwd_dest, dbsrc_dest);
    if (iret != SUCCESS)
    {
        return iret;
    }

    /*第一遍解密*/
    strcpy(enkey1, ENCRYPTKEY); /*固定密钥*/

    memset(aFstpasswd, 0x00, sizeof(aFstpasswd));
    for (i = 0; i < lPasswdLen / 8; i++)
    {
        memset(aTmppasswd, 0x00, sizeof(aTmppasswd));
        memset(aFirdest, 0x00, sizeof(aFirdest));
        memcpy(aTmppasswd, passwd_dest + i * 8, 8);
        des((unsigned char *)aTmppasswd, (unsigned char *)aFirdest, (unsigned char *)enkey1, DENCRYPT);
        memcpy(aFstpasswd + i * 8, aFirdest, 8);
    }

    /*第二遍解密*/
    memset(aFinalpasswd, 0x00, sizeof(aFinalpasswd));
    for (i = 0; i < lPasswdLen / 8; i++)
    {
        memset(aTmppasswd, 0x00, sizeof(aTmppasswd));
        memset(aSecondest, 0x00, sizeof(aSecondest));

        memcpy(aTmppasswd, aFstpasswd + i * 8, 8);
        des((unsigned char *)aTmppasswd, (unsigned char *)aSecondest, (unsigned char *)enkey2, DENCRYPT);
        memcpy(aFinalpasswd + i * 8, aSecondest, 8);
    }
    strcpy(username, uname_dest);
    strcpy(password, aFinalpasswd);
    strcpy(dbsource, dbsrc_dest);
    return SUCCESS;
}

int readdbinfo(char *uname, char *passwd, long *passwd_len, char *dbsrc)
{
    FILE *fpconfig;
    int iRet = 0;
    char aCfgPath[128];
    char aConfFileName[128];
    char aTmpuname[128], aTmppassword[128], aTmpdbsrc[128];
    char aFinalchar[128];
    char aTmpchar[128];
    long lTmpint;
    int i;

    memset(aCfgPath, 0x00, sizeof(aCfgPath));
    iRet = GetCfgPath(aCfgPath);
    if (iRet != 0)
    {
        return iRet;
    }

    memset(aConfFileName, 0, sizeof(aConfFileName));
    strcat(aConfFileName, aCfgPath);
    strcat(aConfFileName, "/");
    strcat(aConfFileName, "mydb.txt");
    fpconfig = NULL;
    if ((fpconfig = fopen(aConfFileName, "r")) == NULL)
    {
        return ERROPENFILE;
    }

    memset(aTmpuname, 0, sizeof(aTmpuname));
    memset(aTmppassword, 0, sizeof(aTmppassword));
    memset(aTmpdbsrc, 0, sizeof(aTmpdbsrc));
    fgets(aTmpuname, sizeof(aTmpuname), fpconfig);
    fgets(aTmppassword, sizeof(aTmppassword), fpconfig);
    fgets(aTmpdbsrc, sizeof(aTmpdbsrc), fpconfig);

    *passwd_len = (strlen(aTmppassword) - 1) / 2;
    memset(aFinalchar, 0x00, sizeof(aFinalchar));
    for (i = 0; (size_t)i < (strlen(aTmppassword) - 1) / 2; i++)
    {
        memset(aTmpchar, 0x00, sizeof(aTmpchar));
        memcpy(aTmpchar, aTmppassword + i * 2, 2);
        lTmpint = strtol(aTmpchar, 0, 16);
        aFinalchar[i] = lTmpint;
    }

    memcpy(passwd, aFinalchar, (strlen(aTmppassword) - 1) / 2);

    strncpy(uname, aTmpuname, strlen(aTmpuname) - 1);
    strcpy(dbsrc, aTmpdbsrc);

    fclose(fpconfig);
    return SUCCESS;
}

/*从密钥文件中读取密钥*/
int getenkey(char *enkey)
{
    FILE *fp;
    int iRet = 0;
    char aCfgPath[128];
    char aKeyFileName[128];
    char aOutKey[9];

    memset(aCfgPath, 0x00, sizeof(aCfgPath));
    iRet = GetCfgPath(aCfgPath);
    if (iRet != 0)
    {
        return iRet;
    }

    memset(aKeyFileName, 0, sizeof(aKeyFileName));
    strcat(aKeyFileName, aCfgPath);
    strcat(aKeyFileName, "/");
    strcat(aKeyFileName, "mykey.txt");

    if ((fp = fopen(aKeyFileName, "r")) == NULL)
    {
        return ERROPENFILE;
    }
    memset(aOutKey, 0, sizeof(aOutKey));
    fgets(aOutKey, sizeof(aOutKey), fp);
    if (strlen(aOutKey) != KEYLEN)
    {
        fclose(fp);
        return ERRKEYLEN;
    }
    strcpy(enkey, aOutKey);
    fclose(fp);
    return SUCCESS;
}

/*检查长度*/
int check_word(char *username, char *password, char *dbsource)
{
    if (strlen(username) > MAXINPUTLEN || strlen(password) > MAXINPUTLEN || strlen(dbsource) > MAXINPUTLEN)
    {
        return ERRINPUT;
    }
    if (strlen(username) == 0 || strlen(password) == 0 || strlen(dbsource) == 0)
    {
        return ERRINPUT;
    }
    return SUCCESS;
}
