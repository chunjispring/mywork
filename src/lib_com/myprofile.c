#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "mycomm.h"

static int _tIsThisEntry(const char *vspLine, const char *vspEntry);
static void _vClearBlank(char *vspLine);
static void _vCutContent(char *vspLine, char *vspDest);

char gsaConfigFileName[ _POSIX_PATH_MAX + 1];

/*默认从 etc/app.ini 配置文件读取内容*/
int tPflInit(void)
{
    char        *spTmp;

    memset(gsaConfigFileName, 0, sizeof(gsaConfigFileName));
    if ((spTmp = getenv("WKPATH")) == NULL) {
        //usrlog("getenv WKPATH failure!\n");
        return FAILURE;
    }
    if (strlen(spTmp) > _POSIX_PATH_MAX-13) {
        //usrlog("file name[%s] is too long, the lenght can't excced[%d]!\n",spTmp,_POSIX_PATH_MAX+13);
        return FAILURE;
    }
    strcpy(gsaConfigFileName, spTmp);
    strcat(gsaConfigFileName, "/etc/app.ini");

    return SUCCESS;
}


/*
 *      To remove all comment and blank char from one line
 */
static void _vClearBlank(char *vspLine)
{
    unsigned int i = 0;
    int   j, k;
    char  buf[_POSIX_MAX_INPUT];

    while (vspLine[i] != 0) {
        if (vspLine[i] == PFL_MEMO_CHARACTER || vspLine[i] == '\n') {
            vspLine[i] = 0;
            if (i == 0) break;
            j = i - 1;
            do {
                if (j < 0) break;
                if ((vspLine[j] != ' ') && (vspLine[j] != '\t')) break;
                vspLine[j--] = 0;
            } while(1);
            break;
        }
        i++;
    }

    i = 0;
    memset(buf, 0, _POSIX_MAX_INPUT);

    while ((vspLine[i] != '=') && (i < strlen(vspLine)))
        i++;
    if (i == strlen(vspLine)) return;

    for (j = i - 1; (vspLine[j] == ' ') || (vspLine[j] == '\t'); j--);
    for (k = i + 1; (vspLine[k] == ' ') || (vspLine[k] == '\t'); k++);

    memcpy(buf, vspLine, j + 1);
    buf[j + 1] = '=';
    strcat(buf + j + 2, vspLine + k);

    strcpy(vspLine, buf);
    return;
}

/*
 *      To confirm if a line is a section line
 */

int _tIsSection(char * vspLine)
{
    return (vspLine[0] == '[');
}


/*
 *      To confirm if this line is a spec section
 */

int _tIsThisSection(const char *vspLine, const char *vspSection)
{
    return (!memcmp(vspLine + 1, vspSection, strlen(vspSection)) &&
        vspLine[strlen(vspSection)+1] == ']');
}


/*
 *      To confire if this line is a spec entry
 */

static int _tIsThisEntry(const char *vspLine, const char *vspEntry)
{
    return (!memcmp(vspLine, vspEntry, strlen(vspEntry)) &&
            vspLine[strlen(vspEntry)] == '=') ;
}


/*
 *      To get the value from a line
 */

static void _vCutContent(char *vspLine, char *vspDest)
{
    int     i = 0;

    while (vspLine[i++] != '=');

    strcpy(vspDest, vspLine + i);
    return;
}


/*
 *      To get a string value from profile
 */

int tPflGetString(const char *vspSection,
                    const char *vspEntry,
                    const char *vspFilename,
                    char *vspValue)
{
    int     cbNum = FALSE;
    int     tInSection = FALSE;
    FILE    *fp;
    char    saLine[_POSIX_MAX_INPUT+1];

    if ((fp = fopen(vspFilename, "r")) == NULL) {
        return FAILURE;
    }

    while (NULL != fgets(saLine, _POSIX_MAX_INPUT, fp)) {
        _vClearBlank(saLine);

        if (_tIsSection(saLine)) {
            tInSection = _tIsThisSection(saLine, vspSection);
            continue;
        }

        if (tInSection == FALSE) continue;

        if (_tIsThisEntry(saLine, vspEntry)) {
            _vCutContent(saLine, vspValue);
            cbNum = TRUE;
            break;
        }
    }

    fclose(fp);

    if (cbNum == FALSE) {
        return FAILURE;
    }

    return SUCCESS;
}


/*
 *      To get a int value from profile
 */

int tPflGetInt(const char *vspSection,
               const char *vspEntry,
               const char *vspFilename,
               int *vtpValue)
{
    char buf[_POSIX_MAX_INPUT];

    if (tPflGetString(vspSection, vspEntry, vspFilename, buf) != SUCCESS) {
        *vtpValue = 0;
        return FAILURE;
    }
    else {
        *vtpValue = atoi(buf);
    }
    return SUCCESS;
}

/*
 *      To get a int value from profile
 */

int tPflGetShort(const char *vspSection,
                const char *vspEntry,
                const char *vspFilename,
                short *vnpValue)
{
    char buf[_POSIX_MAX_INPUT];

    if (tPflGetString(vspSection, vspEntry, vspFilename, buf) != SUCCESS) {
        *vnpValue = 0;
        return FAILURE;
    }
    else {
        *vnpValue = atoi(buf);
    }
    return SUCCESS;
}

/*
 *      To get a long value from profile
 */
int tPflGetLong(const char *vspSection,
                const char *vspEntry,
                const char *vspFilename,
                long *vlpValue)
{
    char buf[_POSIX_MAX_INPUT];

    if (tPflGetString(vspSection, vspEntry, vspFilename, buf) != SUCCESS) {
        *vlpValue = 0L;
        return FAILURE;
    }
    else {
        *vlpValue = atol(buf);
    }
    return SUCCESS;
}

int tLTrim(char *vspString)
{
    register int    i, j, tLen;

    tLen = strlen(vspString);
    j = 0;
    if (vspString[j] != ' ' && vspString[j] != '\t')
        return tLen;

    while (j < tLen && (vspString[j] == ' ' || vspString[j] == '\t') )
        j++;
    for(i = 0; i < tLen - j; i++)
        vspString[i] = vspString[i+j];
    vspString[i] = 0;
    return (i);
}

int tRTrim(char *vspString)
{
    register int    i;

    i = strlen(vspString)-1;

    while(i >= 0 && (vspString[i] == ' '||vspString[i] == '\t'||vspString[i] == '\n')) {
        vspString[i] = 0;
        i--;
    }
    return (i+1);
}

int tAllTrim(char *vspString)
{
    tRTrim(vspString);
    return(tLTrim(vspString));
}

int _tTrimComment(char *vspString)
{
    register int i, tLen;

    tLen = strlen(vspString);
    i = 0;
    while (i < tLen) {
        if (_IS_COMMENT(vspString[i])) {
            vspString[i] = 0;
        }
        i++;
    }
    return (i);
}

int _tTrimExtraSpace(char *vspString)
{
    register int i, j, tLen;
    int      tInString, tInSpace;

    tLen = strlen(vspString);
    i = 0, j = 0;
    tInString = FALSE;
    tInSpace = TRUE;

    while (j < tLen) {
        if (_IS_STRING_BORDER(vspString[j])) {
            tInString = !tInString;
            vspString[i] = vspString[j];
            tInSpace = FALSE;
            i++;
        }
        else {
            if (!tInString) {
                if (vspString[j] == '=') {
                    if (tInSpace&&i>0)  //elimite the front space of  equalsign
                        i--;
                    vspString[i] = vspString[j];
                    tInSpace = TRUE;    //elimite the back space of  equalsign
                    i++;
                }
                else if (vspString[j] == ' ' || vspString[j] == '\t') {
                    if (!tInSpace) {
                        tInSpace = TRUE;
                        vspString[i] = vspString[j];
                        i++;
                    }
                }
                else {
                    vspString[i] = vspString[j];
                    tInSpace = FALSE;
                    i++;
                }
            }
            else {
                vspString[i] = vspString[j];
                i++;
            }
        }
        j++;
    }
    vspString[i] = 0;
    return (i);
}
