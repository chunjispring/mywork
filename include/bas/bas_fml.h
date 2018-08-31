#ifndef __BAS_FML_H__
#define __BAS_FML_H__

//#include "gfsFmlPool.h"

#define MAX_FML_LEN   8192

#define FN_PRI_ACCT_NO  "priAcctNo"              /*  真实卡号             */
#define FN_CARD_BIN     "cardBin"                /*  卡BIN                */
#define FN_MCHNT_CD     "mchntCd"                /*  商户号               */
#define FN_TERM_ID      "termId"                 /*  终端号               */
#define FN_MCHNT_TERM   "mchntTerm"              /* 商户号终端号          */
#define FN_SE_ID        "seId"      // 设备号，暂时不用
#define  FN_DATETIME       "dateTime"            /* 时间(YYYYMMDDhhmiss)  */
#define  FN_FWDINS         "fwdIns"              /* 发送机构代码          */
#define  FN_REQTRANAT      "reqTransAt"          /* 交易金额              */
#define  FN_ACQINS         "acqIns"              /* 收单机构代码          */
#define  FN_CARDMEDIA      "cardMedia"           /* 卡介质                */
#define  FN_ACQRGNCD       "acqRgnCd"            /* 受理地区              */
/*
#define  FN_INSISS         "InsIss"               发卡行地区代码        

*/
#define  FN_LCTM           "lcTm"                /* 当前交易时间          */
#define  FN_TRANCURRCD     "tranCurrCd"          /* 交易货币代码       tranCurrCd    */
#define  FN_CHNL           "channel"                /* 交易渠道           channel       */
#define  FN_MCHNTTERM      "mchntTerm"           /* 商户地区代码       mchntArea     */
#define  FN_MCHNTBSCC      "mchntBsCC"           /* 商户业务控制类别   mchntbscc */
#define  FN_CUPSTRANSID    "cupsTransId"         /* CUPS交易代码          */
#define  FN_ADMDIVCD       "admDivCd"            /* 行政区划代码          */
#define  FN_REGIONCD       "regionCd"            /* 清算地区代码       regionCd      */
#define  FN_MONTOEXPI      "monToExpi"           /* 卡有效期过期还剩的月数*/
#define  FN_CARDLVL        "cardLvl"             /* 卡等级                */
#define  FN_AUTHDIFDAY     "authDifDay"          /* 酒店住几晚            */
#define  FN_VASVCTP        "vASvcTp"             /* 增值服务类型       vaSvcTp       */
#define  FN_ICPRODTYPE     "iCProdType"          /* 智能卡产品类型     icProdType    */
#define  FN_CARRISSUE      "carrIssue"           /* 载体发行方         carrIssue     */
#define  FN_MPRODTYPE      "mProdType"           /* 移动支付产品类型   mProdType */
#define  FN_INSISSPF       "insIssPF"            /* 发卡方前缀            */
#define  FN_TRID           "trId"                /* CUPA内部交易类型      */
#define  FN_MASEQNUM       "mASeqNum"            /* 移动应用序列号     maSeqNum      */
#define  FN_PRIACCTNO      "priAcctNo"           /* 真实卡号              */
#define  FN_SINGLEPRODID   "singleProdId"        /* 商品编号              */
#define  FN_MCC            "mcc"                 /* 商户类型           mcc           */
#define  FN_CARDATTR       "cardAttr"            /* 卡性质                */
#define  FN_CARDBRAND      "cardBrand"           /* 卡品牌                */
#define  FN_INSISS         "insIss"              /* 发卡方机构标识码      */

/*add by yutk 0320*/
#define FDN_PRI_NO_CONV          "PriAcctCv"       /**< char(LEN_PRI_NO)      截卡后主账号         C2 */
#define FDN_MOBI_IC_PROD_TP      "MProdType"       /*移动支付产品类型*/
#define FDN_TSP_PRI_NO           "TSPPriACv"       /*真实截卡后主账号*/
#define FDN_DSCT_TOP_APP_ID      "topAppId"        /* 过滤活动ID 用于折扣额度通知TOP */
#define FDN_DSCT_APP_GRP_ID      "appGrpId"        /* 过滤活动的共享组ID */
#define FDN_DSCT_APP_DT_TM       "appDtTm"         /* 活动日期时间 */
#define FDN_DSCT_ALL_NUM         "allNum"          /* 活动全部限制笔数 */
#define FDN_DSCT_ALL_USE_NUM     "allUseNum"       /* 活动全部已用笔数 */
#define FDN_DSCT_ALL_SUM         "allSum"          /* 活动全部限制金额 */
#define FDN_DSCT_ALL_USE_SUM     "allUseSum"       /* 活动全部已用金额 */
#define FDN_DSCT_DAY_NUM         "dayNum"          /* 活动当日限制笔数 */
#define FDN_DSCT_DAY_USE_NUM     "dayUseNum"       /* 活动当日已用笔数 */
#define FDN_DSCT_DAY_SUM         "daySum"          /* 活动当日限制金额 */
#define FDN_DSCT_DAY_USE_SUM     "dayUseSum"       /* 活动当日已用金额 */
#define FDN_DSCT_MONTH_NUM       "monNum"          /* 活动每月限制笔数 */
#define FDN_DSCT_MONTH_USE_NUM   "monUseNum"       /* 活动每月已用笔数 */
#define FDN_DSCT_MONTH_SUM       "monSum"          /* 活动每月限制金额 */
#define FDN_DSCT_MONTH_USE_SUM   "monUseSum"       /* 活动每月已用金额 */
#define FDN_DSCT_YEAR_NUM        "yearNum"         /* 活动每年限制笔数 */
#define FDN_DSCT_YEAR_USE_NUM    "yearUseNum"      /* 活动每年已用笔数 */
#define FDN_DSCT_YEAR_SUM        "yearSum"         /* 活动每年限制金额 */
#define FDN_DSCT_YEAR_USE_SUM    "yearUseSum"      /* 活动每年已用金额 */

#define FDN_DSCT_PRE_APP_ID      "preAppId"        /* 上一活动ID */
#define FDN_DSCT_ACALL_TOP_FLAG  "AcTopFlg"        /* 实时通知TOP的标志位 */
#define FDN_DSCT_TOP_CYCLE_TP    "cycleTP"         /* 活动限制周期类型 */

#define FML_SET_OR_ERR(ret, loc, name, value, fmlPool)         \
{                                                               \
    ret = swSubFmlAddandUpdate(loc, name, strlen(value), value, fmlPool);\
    if(ret == 0) {                                           \
            ISVR_SYS_LOG(DOG_DEBUG, "成功赋值一个FML域, name:%s, val:%s.\n", name, value); \
    }                               \
    else {                          \
        ISVR_SYS_LOG(DOG_ERROR,"设置FML域%s失败", name);     \
    }                                                       \
}

#define FML_GET_OR_RET(fmlPool, name, max_len, value)          \
{                                                                   \
    int in_ret, in_len;                                                \
    in_len = max_len;                                                    \
    in_ret = swFmlget(fmlPool, name, &in_len, value);                \
    if (in_ret<0 || in_len == 0)                                         \
    {                                                               \
        ISVR_BUS_LOG(DOG_ERROR, "FML域获取失败, ret:%d, name:%s, len:%d.", \
                in_ret, name, in_len);                       \
        return -__LINE__;                                                  \
    }                                                               \
    value[in_len] = '\0';                                  \
}   


#define FML_GET(ret, fmlPool, name, max_len, value)          \
{                                                                   \
    int  in_len;                                                \
    in_len = max_len;                                                    \
    ret = swFmlget(fmlPool, name, &in_len, value);                \
    if (ret < 0 || in_len == 0)                                         \
    {                                                               \
        ISVR_BUS_LOG(DOG_INFO, "FML域未能获取, ret:%d, name:%s, len:%d.", \
                ret, name, in_len);                       \
    }          \
    else {    \
        value[in_len] = '\0';                                   \
        ISVR_BUS_LOG(DOG_INFO, "FML域成功获取,  name:%s, value:%s.", name, value);     \
    } \
}   


#define FML_SET(fmlPool, name, value )       \
{                                                    \
    ret=swSubFmlAddandUpdate(fmlPool, name, strlen(value) + 1, value, fmlPool);\
    if(ret == 0)                                        \
    {                                                   \
        ISVR_SYS_LOG(MTQ_DEBUG, "成功赋值一个FML域, name:%s, val:%s.", name, value); \
    }                                                   \
    else  \
    { \
        ISVR_SYS_LOG(MTQ_ERROR, "赋值一个FML域失败, name:%s, val:%s.", name, value); \
    }\
}


/* 检查是否成功
   不成功则赋值 ErrNo */
#define CHKERROR_BUSS(rt, fmlPool, ERRNO, ...)  \
{       \
    char  in_value[12];                    \
    int   in_len, in_ret;                       \
    ISVR_SYS_LOG(DOG_DEBUG, "CHKERROR rt:[%d]",  rt); \
    if (rt != 0) {                     \
        ISVR_BUS_LOG(MTQ_ERROR, __VA_ARGS__);  \
        in_len = sizeof(in_value);              \
        in_ret = swFmlget(fmlPool, "ErrNo", &in_len, in_value);                \
        if (in_ret != 0 || in_len == 0)                                 \
            swSubFmlAddandUpdate(fmlPool, "ErrNo", strlen(ERRNO) + 1, ERRNO, fmlPool);\
        return -__LINE__;                      \
    }  \
}

#define CHKERROR_SYS(ret, fmlPool, ERRNO, ...)  \
{       \
    char  in_value[12];                    \
    int   in_len, in_ret;                       \
    if (ret != 0) {                     \
        ISVR_SYS_LOG(DOG_ERROR, __VA_ARGS__);  \
        in_len = sizeof(in_value);              \
        in_ret = swFmlget(fmlPool, "ErrNo", &in_len, in_value);                \
        if (ret != 0 || in_len == 0)                                 \
            swSubFmlAddandUpdate(fmlPool, "ErrNo", strlen(ERRNO) + 1, ERRNO, fmlPool);\
        return -__LINE__;                      \
    }  \
}


#define FML_GET_OR_ERRNO(fmlPool, name, max_len, value, ErrNo)          \
{   \
    int     in_ret;                     \
    FML_GET(in_ret, fmlPool, name, max_len, value);                 \
    if (in_ret != 0) {      \
        swSubFmlAddandUpdate(fmlPool, "ErrNo", strlen(ErrNo) + 1, ErrNo, fmlPool);\
        return -__LINE__;          \
    }   \
}

#define FML_GET_LONG_OR_ERRNO(fmlPool, name, value, ErrNo)          \
{                                                          \
    int     in_ret;                     \
    char    in_str[32];            \
    FML_GET(in_ret, fmlPool, name, sizeof(in_str), in_str);                 \
    if (in_ret != 0) {      \
        swSubFmlAddandUpdate(fmlPool, "ErrNo", strlen(ErrNo) + 1, ErrNo, fmlPool);\
        return -__LINE__;          \
    }   \
    value = atol(in_str);                  \
}


#endif
