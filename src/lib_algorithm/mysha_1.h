#include <stdlib.h>
#include <string.h>

//中文测试

#ifdef undef

#ifndef SHA_1
#define SHA_0
#endif
#endif

#define ULONG  unsigned long
#define UCHAR  unsigned char
#define UINT   unsigned int

#ifdef NOCONST
#define const
#endif

#undef c2nl
#define c2nl(c, l) (l = (((unsigned long)(*((c)++))) << 24),  \
					l |= (((unsigned long)(*((c)++))) << 16), \
					l |= (((unsigned long)(*((c)++))) << 8),  \
					l |= (((unsigned long)(*((c)++)))))

#undef p_c2nl
#define p_c2nl(c, l, n)                             \
	{                                               \
		switch (n)                                  \
		{                                           \
		case 0:                                     \
			l = ((unsigned long)(*((c)++))) << 24;  \
		case 1:                                     \
			l |= ((unsigned long)(*((c)++))) << 16; \
		case 2:                                     \
			l |= ((unsigned long)(*((c)++))) << 8;  \
		case 3:                                     \
			l |= ((unsigned long)(*((c)++)));       \
		}                                           \
	}

#undef c2nl_p

#define c2nl_p(c, l, n)                             \
	{                                               \
		l = 0;                                      \
		(c) += n;                                   \
		switch (n)                                  \
		{                                           \
		case 3:                                     \
			l = ((unsigned long)(*(--(c)))) << 8;   \
		case 2:                                     \
			l |= ((unsigned long)(*(--(c)))) << 16; \
		case 1:                                     \
			l |= ((unsigned long)(*(--(c)))) << 24; \
		}                                           \
	}

#undef p_c2nl_p
#define p_c2nl_p(c, l, sc, len)                     \
	{                                               \
		switch (sc)                                 \
		{                                           \
		case 0:                                     \
			l = ((unsigned long)(*((c)++))) << 24;  \
			if (--len == 0)                         \
				break;                              \
		case 1:                                     \
			l |= ((unsigned long)(*((c)++))) << 16; \
			if (--len == 0)                         \
				break;                              \
		case 2:                                     \
			l |= ((unsigned long)(*((c)++))) << 8;  \
		}                                           \
	}

#undef nl2c
#define nl2c(l, c) (*((c)++) = (unsigned char)(((l) >> 24) & 0xff), \
					*((c)++) = (unsigned char)(((l) >> 16) & 0xff), \
					*((c)++) = (unsigned char)(((l) >> 8) & 0xff),  \
					*((c)++) = (unsigned char)(((l)) & 0xff))

#undef c2l
#define c2l(c, l) (l = (((unsigned long)(*((c)++)))),        \
				   l |= (((unsigned long)(*((c)++))) << 8),  \
				   l |= (((unsigned long)(*((c)++))) << 16), \
				   l |= (((unsigned long)(*((c)++))) << 24))

#undef p_c2l
#define p_c2l(c, l, n)                              \
	{                                               \
		switch (n)                                  \
		{                                           \
		case 0:                                     \
			l = ((unsigned long)(*((c)++)));        \
		case 1:                                     \
			l |= ((unsigned long)(*((c)++))) << 8;  \
		case 2:                                     \
			l |= ((unsigned long)(*((c)++))) << 16; \
		case 3:                                     \
			l |= ((unsigned long)(*((c)++))) << 24; \
		}                                           \
	}

#undef c2l_p

#define c2l_p(c, l, n)                             \
	{                                              \
		l = 0;                                     \
		(c) += n;                                  \
		switch (n)                                 \
		{                                          \
		case 3:                                    \
			l = ((unsigned long)(*(--(c)))) << 16; \
		case 2:                                    \
			l |= ((unsigned long)(*(--(c)))) << 8; \
		case 1:                                    \
			l |= ((unsigned long)(*(--(c))));      \
		}                                          \
	}

#undef p_c2l_p
#define p_c2l_p(c, l, sc, len)                      \
	{                                               \
		switch (sc)                                 \
		{                                           \
		case 0:                                     \
			l = ((unsigned long)(*((c)++)));        \
			if (--len == 0)                         \
				break;                              \
		case 1:                                     \
			l |= ((unsigned long)(*((c)++))) << 8;  \
			if (--len == 0)                         \
				break;                              \
		case 2:                                     \
			l |= ((unsigned long)(*((c)++))) << 16; \
		}                                           \
	}

#undef l2c
#define l2c(l, c) (*((c)++) = (unsigned char)(((l)) & 0xff),       \
				   *((c)++) = (unsigned char)(((l) >> 8) & 0xff),  \
				   *((c)++) = (unsigned char)(((l) >> 16) & 0xff), \
				   *((c)++) = (unsigned char)(((l) >> 24) & 0xff))

#undef ROTATE
#if defined(WIN32)
#define ROTATE(a, n) _lrotl(a, n)
#else
#define ROTATE(a, n) (((a) << (n)) | (((a)&0xffffffff) >> (32 - (n))))
#endif

#if defined(WIN32)

#define Endian_Reverse32(a)                                                 \
	{                                                                       \
		unsigned long l = (a);                                              \
		(a) = ((ROTATE(l, 8) & 0x00FF00FF) | (ROTATE(l, 24) & 0xFF00FF00)); \
	}
#else

#define Endian_Reverse32(a)                                        \
	{                                                              \
		unsigned long l = (a);                                     \
		l = (((l & 0xFF00FF00) >> 8L) | ((l & 0x00FF00FF) << 8L)); \
		(a) = ROTATE(l, 16L);                                      \
	}
#endif

#define F_00_19(b, c, d) ((((c) ^ (d)) & (b)) ^ (d))
#define F_20_39(b, c, d) ((b) ^ (c) ^ (d))
#define F_40_59(b, c, d) (((b) & (c)) | (((b) | (c)) & (d)))
#define F_60_79(b, c, d) F_20_39(b, c, d)

#ifdef SHA_0
#undef Xupdate
#define Xupdate(a, i, ia, ib, ic, id) X[(i)&0x0f] = (a) = \
										  (ia[(i)&0x0f] ^ ib[((i) + 2) & 0x0f] ^ ic[((i) + 8) & 0x0f] ^ id[((i) + 13) & 0x0f]);
#endif
#ifdef SHA_1
#undef Xupdate
#define Xupdate(a, i, ia, ib, ic, id)                                                         \
	(a) =                                                                                     \
		(ia[(i)&0x0f] ^ ib[((i) + 2) & 0x0f] ^ ic[((i) + 8) & 0x0f] ^ id[((i) + 13) & 0x0f]); \
	X[(i)&0x0f] = (a) = ROTATE((a), 1);
#endif

#define BODY_00_15(i, a, b, c, d, e, f, xa)                                \
	(f) = xa[i] + (e) + K_00_19 + ROTATE((a), 5) + F_00_19((b), (c), (d)); \
	(b) = ROTATE((b), 30);

#define BODY_16_19(i, a, b, c, d, e, f, xa, xb, xc, xd)             \
	Xupdate(f, i, xa, xb, xc, xd);                                  \
	(f) += (e) + K_00_19 + ROTATE((a), 5) + F_00_19((b), (c), (d)); \
	(b) = ROTATE((b), 30);

#define BODY_20_31(i, a, b, c, d, e, f, xa, xb, xc, xd)             \
	Xupdate(f, i, xa, xb, xc, xd);                                  \
	(f) += (e) + K_20_39 + ROTATE((a), 5) + F_20_39((b), (c), (d)); \
	(b) = ROTATE((b), 30);

#define BODY_32_39(i, a, b, c, d, e, f, xa)                         \
	Xupdate(f, i, xa, xa, xa, xa);                                  \
	(f) += (e) + K_20_39 + ROTATE((a), 5) + F_20_39((b), (c), (d)); \
	(b) = ROTATE((b), 30);

#define BODY_40_59(i, a, b, c, d, e, f, xa)                         \
	Xupdate(f, i, xa, xa, xa, xa);                                  \
	(f) += (e) + K_40_59 + ROTATE((a), 5) + F_40_59((b), (c), (d)); \
	(b) = ROTATE((b), 30);

#define BODY_60_79(i, a, b, c, d, e, f, xa)                                      \
	Xupdate(f, i, xa, xa, xa, xa);                                               \
	(f) = X[(i)&0x0f] + (e) + K_60_79 + ROTATE((a), 5) + F_60_79((b), (c), (d)); \
	(b) = ROTATE((b), 30);

#ifndef HEADER_SHA_H
#define HEADER_SHA_H

#ifdef __cplusplus
extern "C" {
#endif

#define SHA_CBLOCK 64
#define SHA_LBLOCK 16
#define SHA_BLOCK 16
#define SHA_LAST_BLOCK 56
#define SHA_LENGTH_BLOCK 8
#define SHA_DIGEST_LENGTH 20

typedef struct SHAstate_st
{
	unsigned long h0, h1, h2, h3, h4;
	unsigned long Nl, Nh;
	unsigned long data[SHA_LBLOCK];
	int num;
} SHA_CTX;

#ifndef NOPROTO
void SHA_Init(SHA_CTX *c);
void SHA_Update(SHA_CTX *c, unsigned char *data, unsigned long len);
void SHA_Final(unsigned char *md, SHA_CTX *c);
unsigned char *SHA(unsigned char *d, unsigned long n, unsigned char *md);
void SHA_Transform(SHA_CTX *c, unsigned char *data);
void SHA1_Init(SHA_CTX *c);
void SHA1_Update(SHA_CTX *c, unsigned char *data, unsigned long len);
void SHA1_Final(unsigned char *md, SHA_CTX *c);
unsigned char *SHA1(unsigned char *d, unsigned long n, unsigned char *md);
void SHA1_Transform(SHA_CTX *c, unsigned char *data);
void SHA_Hash(unsigned char *plaintexts, unsigned char *hash, unsigned long block_number);
void SHA_Padding(unsigned char *plaintexts, unsigned char *plaintexts_padding,
				 unsigned long byte_number, unsigned long *block_number);
#else
void SHA_Init();
void SHA_Update();
void SHA_Final();
unsigned char *SHA();
void SHA_Transform();
void SHA1_Init();
void SHA1_Update();
void SHA1_Final();
unsigned char *SHA1();
void SHA1_Transform();
void SHA_Hash(unsigned char *plaintexts, unsigned char *hash, unsigned long block_number);
void SHA_Padding(unsigned char *plaintexts, unsigned char *plaintexts_padding,
				 unsigned long byte_number, unsigned long *block_number);
#endif

#ifdef __cplusplus
}
#endif

#endif
