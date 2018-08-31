/*  Copyright 2006, Robert Peng(robertpeng1116@gmail.com).  All right reserved.
 *
 *  THIS IS UNPUBLISHED  PROPRIETARY  SOURCE  CODE  OF Robert Peng.
 *  THE CONTENTS OF THIS FILE MAY  NOT  BE  DISCLOSED TO THIRD
 *  PARTIES, COPIED OR DUPLICATED IN ANY FORM, IN WHOLE OR IN PART,
 *  WITHOUT THE PRIOR WRITTEN PERMISSION OF Robert Peng.
 *
 *
 *  Edit History:
 *    2006/04/28 created by  Robert Peng(robertpeng1116@gmail.com)
 *
 */
#ifndef HDR_USRLOG_H
#define HDR_USRLOG_H

//中文测试

#include <stdarg.h>

#define N_MAX_LOG_SIZE  1000000000

#define usrlog( ... ) \
    _vWriteLogAsc(\
        __FILE__, \
        __func__, \
        __LINE__, \
        "DUXLOG", \
        ##__VA_ARGS__)

#define usrlognm( vspLogName, ... ) \
    _vWriteLogAsc(\
        __FILE__, \
        __func__, \
        __LINE__, \
        vspLogName, \
        ##__VA_ARGS__)

#define usrlognm0( FILE_NM, FUNC_NM, LINE_NO, vspLogName, ... ) \
    _vWriteLogAsc(\
        FILE_NM, \
        FUNC_NM, \
        LINE_NO, \
        vspLogName, \
        ##__VA_ARGS__)

#define vusrlognm0( FILE_NM, FUNC_NM, LINE_NO, vspLogName, vspFmt, vstrValist ) \
    _vVWriteLogAsc(\
        FILE_NM, \
        FUNC_NM, \
        LINE_NO, \
        vspLogName, \
        vspFmt, \
        vstrValist)

#define usrhex(vvpRawBuf, vtLen) \
    _vWriteLogHex( \
        __FILE__, \
        __func__, \
        __LINE__, \
        "DUXLOG", \
        vvpRawBuf, \
        vtLen)

#define usrhexnm( vspLogName, vvpRawBuf, vtLen) \
    _vWriteLogHex( \
        __FILE__, \
        __func__, \
        __LINE__, \
        vspLogName, \
        vvpRawBuf, \
        vtLen)

#define usrhexnm0( FILE_NM, FUNC_NM, LINE_NO, vspLogName, vvpRawBuf, vtLen) \
    _vWriteLogHex( \
        FILE_NM, \
        FUNC_NM, \
        LINE_NO, \
        vspLogName, \
        vvpRawBuf, \
        vtLen)

#ifdef _DEBUG

#define TRACE( ... ) \
    _vWriteLogAsc(\
        __FILE__, \
        __func__, \
        __LINE__, \
        "TRCLOG", \
        ##__VA_ARGS__)

#define TRACEHEX(vvpRawBuf, vtLen) \
    _vWriteLogHex( \
        __FILE__, \
        __func__, \
        __LINE__, \
        "TRCLOG", \
        vvpRawBuf, \
        vtLen)


#define DEBUG_ONLY(f)   (f)
#define VERIFY(f)       ASSERT(f)

#else   //_DEBUG

#define TRACE( ... )
#define TRACEHEX(vvpRawBuf, vtLen)
#define DEBUG_ONLY(f)      ((void)0)
#define VERIFY(f)          ((void)(f))

#endif  //!_DEBUG

#define ASSERT(f)       \
    DEBUG_ONLY((void) ((f) || \
    _tAssertFailedLine(__FILE__, __func__, __LINE__) || (_vDebugBreak(), 0)))

extern int _tAssertFailedLine(char const *, char const *,int);
extern void _vDebugBreak(void);
extern void _vWriteLogAsc(char const *, char const *, int, char *, char *, ... );
extern void _vWriteLogHex(char const *, char const *,int,  char *, void *, int);
extern void _vVWriteLogAsc(char const *, char const *, int, char *, char *, va_list);

#endif /* end of HDR_USRLOG_H */
