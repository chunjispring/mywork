#ifndef HDR_PROFILE_H
#define HDR_PROFILE_H
#include <limits.h>

//中文测试

#define PFL_MEMO_CHARACTER      '#'
#define PFL_STRING_BORDER_CHAR  '"'
#define _IS_STRING_BORDER(x)     (x == PFL_STRING_BORDER_CHAR)
#define _IS_COMMENT(x)           (x == PFL_MEMO_CHARACTER)
#define _IS_SECTION_BEGIN(x)     (x == '[')
#define _IS_YES(x)               (x == 'Y' || x == 'y')

#define     MTQ_AGENT_BLK    "MTQAGENT"
#define     _POSIX_PATH_MAX  256

extern char gsaConfigFileName[ _POSIX_PATH_MAX + 1];

extern int tPflGetShort(const char *vspSection,
                const char *vspEntry,
                const char *vspFilename,
                short *vnpValue);
extern int tPflGetInt(const char *vspSection,
                const char *vspEntry,
                const char *vspFilename,
                int *vtpValue);
extern int tPflGetLong(const char *vspSection,
                const char *vspEntry,
                const char *vspFilename,
                long *vlpValue);
extern int tPflGetString(const char *vspSection,
                    const char *vspEntry,
                    const char *vspFilename,
                    char *vspValue);
extern int tLTrim(char *vspString);
extern int tRTrim(char *vspString);
extern int tAllTrim(char*vspString);
extern int _tTrimComment(char *vspString);
extern int _tTrimExtraSpace(char *vspString);
extern int _tIsSection(char * vspLine);
extern int _tIsThisSection(const char *vspLine, const char *vspSection);
extern int tPflInit(void);

#endif /* end of HDR_PROFILE_H */
