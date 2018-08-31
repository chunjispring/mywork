/*******************************************************************************
 * 文件名   : myalgorithm.h
 * 文件功能 : libmyalgorithm的头文件
 * 编程者   : WCJ
 * 初作时间 : 2017/04/28
 * 版本     : 1.0
 * -----------------------------------------------------------------------------
 * 时间            修改者        注释
 * 2017/04/28      WCJ         初期作成
********************************************************************************/
#ifndef __MYALGORITHM_H__
#define __MYALGORITHM_H__

/*
**  外部函数说明
*/

//DES加解密算法
extern int des(unsigned char *source, unsigned char *dest, unsigned char *inkey, int flg);

//SHA-1加解密  （逐步放弃使用）
extern void SHA_Hash(unsigned char *plaintexts, unsigned char *hash, unsigned long block_number);
extern void SHA_Padding(unsigned char *plaintexts, unsigned char *plaintexts_padding,
                        unsigned long byte_number, unsigned long *block_number);

#endif
