#include <stdio.h>
#include <string.h>
#include <memory.h>
#undef SHA_0
#define SHA_1

#include "mysha_1.h"

//中文测试

//static char sccsid[] = "@(#)sha_1.c 1.1 99/06/16 13:37:36@(#)";

#define INIT_DATA_h0 (unsigned long)0x67452301L
#define INIT_DATA_h1 (unsigned long)0xefcdab89L
#define INIT_DATA_h2 (unsigned long)0x98badcfeL
#define INIT_DATA_h3 (unsigned long)0x10325476L
#define INIT_DATA_h4 (unsigned long)0xc3d2e1f0L

#define K_00_19 0x5a827999L
#define K_20_39 0x6ed9eba1L
#define K_40_59 0x8f1bbcdcL
#define K_60_79 0xca62c1d6L

#ifndef NOPROTO
#ifdef SHA1_ASM
void sha1_block_x86(SHA_CTX *c, register unsigned long *p, int num);
#define sha1_block sha1_block_x86
#else
void sha1_block(SHA_CTX *c, register unsigned long *p, int num);
#endif
#else
#ifdef SHA1_ASM
void sha1_block_x86();
#define sha1_block sha1_block_x86
#else
void sha1_block();
#endif
#endif

#if defined(L_ENDIAN) && defined(SHA1_ASM)
#define M_c2nl c2l
#define M_p_c2nl p_c2l
#define M_c2nl_p c2l_p
#define M_p_c2nl_p p_c2l_p
#define M_nl2c l2c
#else
#define M_c2nl c2nl
#define M_p_c2nl p_c2nl
#define M_c2nl_p c2nl_p
#define M_p_c2nl_p p_c2nl_p
#define M_nl2c nl2c
#endif

void SHA1_Init(c)
	SHA_CTX *c;
{
	c->h0 = INIT_DATA_h0;
	c->h1 = INIT_DATA_h1;
	c->h2 = INIT_DATA_h2;
	c->h3 = INIT_DATA_h3;
	c->h4 = INIT_DATA_h4;
	c->Nl = 0;
	c->Nh = 0;
	c->num = 0;
}

void SHA1_Update(c, data, len)
	SHA_CTX *c;
register unsigned char *data;
unsigned long len;
{
	register ULONG *p;
	int ew, ec, sw, sc;
	ULONG l;

	if (len == 0)
		return;

	l = (c->Nl + (len << 3)) & 0xffffffffL;
	if (l < c->Nl) /* overflow */
		c->Nh++;
	c->Nh += (len >> 29);
	c->Nl = l;

	if (c->num != 0)
	{
		p = c->data;
		sw = c->num >> 2;
		sc = c->num & 0x03;

		if ((c->num + len) >= SHA_CBLOCK)
		{
			l = p[sw];
			M_p_c2nl(data, l, sc);
			p[sw++] = l;
			for (; sw < SHA_LBLOCK; sw++)
			{
				M_c2nl(data, l);
				p[sw] = l;
			}
			len -= (SHA_CBLOCK - c->num);

			sha1_block(c, p, 64);
			c->num = 0;
			/* drop through and do the rest */
		}
		else
		{
			c->num += (int)len;
			if ((sc + len) < 4) /* ugly, add char's to a word */
			{
				l = p[sw];
				M_p_c2nl_p(data, l, sc, len);
				p[sw] = l;
			}
			else
			{
				ew = (c->num >> 2);
				ec = (c->num & 0x03);
				l = p[sw];
				M_p_c2nl(data, l, sc);
				p[sw++] = l;
				for (; sw < ew; sw++)
				{
					M_c2nl(data, l);
					p[sw] = l;
				}
				if (ec)
				{
					M_c2nl_p(data, l, ec);
					p[sw] = l;
				}
			}
			return;
		}
	}

#if 1
#if defined(B_ENDIAN) || defined(SHA1_ASM)
	if ((((unsigned int)data) % sizeof(ULONG)) == 0)
	{
		sw = len / SHA_CBLOCK;
		if (sw)
		{
			sw *= SHA_CBLOCK;
			sha1_block(c, (ULONG *)data, sw);
			data += sw;
			len -= sw;
		}
	}
#endif
#endif

	p = c->data;
	while (len >= SHA_CBLOCK)
	{
#if defined(B_ENDIAN) || defined(L_ENDIAN)
		if (p != (unsigned long *)data)
			memcpy(p, data, SHA_CBLOCK);
		data += SHA_CBLOCK;
#ifdef L_ENDIAN
#ifndef SHA1_ASM /* Will not happen */
		for (sw = (SHA_LBLOCK / 4); sw; sw--)
		{
			Endian_Reverse32(p[0]);
			Endian_Reverse32(p[1]);
			Endian_Reverse32(p[2]);
			Endian_Reverse32(p[3]);
			p += 4;
		}
		p = c->data;
#endif
#endif
#else
		for (sw = (SHA_BLOCK / 4); sw; sw--)
		{
			M_c2nl(data, l);
			*(p++) = l;
			M_c2nl(data, l);
			*(p++) = l;
			M_c2nl(data, l);
			*(p++) = l;
			M_c2nl(data, l);
			*(p++) = l;
		}
		p = c->data;
#endif
		sha1_block(c, p, 64);
		len -= SHA_CBLOCK;
	}
	ec = (int)len;
	c->num = ec;
	ew = (ec >> 2);
	ec &= 0x03;

	for (sw = 0; sw < ew; sw++)
	{
		M_c2nl(data, l);
		p[sw] = l;
	}
	M_c2nl_p(data, l, ec);
	p[sw] = l;
}

void SHA1_Transform(c, b)
	SHA_CTX *c;
unsigned char *b;
{
	ULONG p[16];
#ifndef B_ENDIAN
	ULONG *q;
	int i;
#endif

#if defined(B_ENDIAN) || defined(L_ENDIAN)
	memcpy(p, b, 64);
#ifdef L_ENDIAN
	q = p;
	for (i = (SHA_LBLOCK / 4); i; i--)
	{
		Endian_Reverse32(q[0]);
		Endian_Reverse32(q[1]);
		Endian_Reverse32(q[2]);
		Endian_Reverse32(q[3]);
		q += 4;
	}
#endif
#else
	q = p;
	for (i = (SHA_LBLOCK / 4); i; i--)
	{
		ULONG l;
		c2nl(b, l);
		*(q++) = l;
		c2nl(b, l);
		*(q++) = l;
		c2nl(b, l);
		*(q++) = l;
		c2nl(b, l);
		*(q++) = l;
	}
#endif
	sha1_block(c, p, 64);
}

#ifndef SHA1_ASM

void sha1_block(c, W, num)
	SHA_CTX *c;
register unsigned long *W;
int num;
{
	register ULONG A, B, C, D, E, T;
	ULONG X[16];

	A = c->h0;
	B = c->h1;
	C = c->h2;
	D = c->h3;
	E = c->h4;

	for (;;)
	{
		BODY_00_15(0, A, B, C, D, E, T, W);
		BODY_00_15(1, T, A, B, C, D, E, W);
		BODY_00_15(2, E, T, A, B, C, D, W);
		BODY_00_15(3, D, E, T, A, B, C, W);
		BODY_00_15(4, C, D, E, T, A, B, W);
		BODY_00_15(5, B, C, D, E, T, A, W);
		BODY_00_15(6, A, B, C, D, E, T, W);
		BODY_00_15(7, T, A, B, C, D, E, W);
		BODY_00_15(8, E, T, A, B, C, D, W);
		BODY_00_15(9, D, E, T, A, B, C, W);
		BODY_00_15(10, C, D, E, T, A, B, W);
		BODY_00_15(11, B, C, D, E, T, A, W);
		BODY_00_15(12, A, B, C, D, E, T, W);
		BODY_00_15(13, T, A, B, C, D, E, W);
		BODY_00_15(14, E, T, A, B, C, D, W);
		BODY_00_15(15, D, E, T, A, B, C, W);
		BODY_16_19(16, C, D, E, T, A, B, W, W, W, W);
		BODY_16_19(17, B, C, D, E, T, A, W, W, W, W);
		BODY_16_19(18, A, B, C, D, E, T, W, W, W, W);
		BODY_16_19(19, T, A, B, C, D, E, W, W, W, X);

		BODY_20_31(20, E, T, A, B, C, D, W, W, W, X);
		BODY_20_31(21, D, E, T, A, B, C, W, W, W, X);
		BODY_20_31(22, C, D, E, T, A, B, W, W, W, X);
		BODY_20_31(23, B, C, D, E, T, A, W, W, W, X);
		BODY_20_31(24, A, B, C, D, E, T, W, W, X, X);
		BODY_20_31(25, T, A, B, C, D, E, W, W, X, X);
		BODY_20_31(26, E, T, A, B, C, D, W, W, X, X);
		BODY_20_31(27, D, E, T, A, B, C, W, W, X, X);
		BODY_20_31(28, C, D, E, T, A, B, W, W, X, X);
		BODY_20_31(29, B, C, D, E, T, A, W, W, X, X);
		BODY_20_31(30, A, B, C, D, E, T, W, X, X, X);
		BODY_20_31(31, T, A, B, C, D, E, W, X, X, X);
		BODY_32_39(32, E, T, A, B, C, D, X);
		BODY_32_39(33, D, E, T, A, B, C, X);
		BODY_32_39(34, C, D, E, T, A, B, X);
		BODY_32_39(35, B, C, D, E, T, A, X);
		BODY_32_39(36, A, B, C, D, E, T, X);
		BODY_32_39(37, T, A, B, C, D, E, X);
		BODY_32_39(38, E, T, A, B, C, D, X);
		BODY_32_39(39, D, E, T, A, B, C, X);

		BODY_40_59(40, C, D, E, T, A, B, X);
		BODY_40_59(41, B, C, D, E, T, A, X);
		BODY_40_59(42, A, B, C, D, E, T, X);
		BODY_40_59(43, T, A, B, C, D, E, X);
		BODY_40_59(44, E, T, A, B, C, D, X);
		BODY_40_59(45, D, E, T, A, B, C, X);
		BODY_40_59(46, C, D, E, T, A, B, X);
		BODY_40_59(47, B, C, D, E, T, A, X);
		BODY_40_59(48, A, B, C, D, E, T, X);
		BODY_40_59(49, T, A, B, C, D, E, X);
		BODY_40_59(50, E, T, A, B, C, D, X);
		BODY_40_59(51, D, E, T, A, B, C, X);
		BODY_40_59(52, C, D, E, T, A, B, X);
		BODY_40_59(53, B, C, D, E, T, A, X);
		BODY_40_59(54, A, B, C, D, E, T, X);
		BODY_40_59(55, T, A, B, C, D, E, X);
		BODY_40_59(56, E, T, A, B, C, D, X);
		BODY_40_59(57, D, E, T, A, B, C, X);
		BODY_40_59(58, C, D, E, T, A, B, X);
		BODY_40_59(59, B, C, D, E, T, A, X);

		BODY_60_79(60, A, B, C, D, E, T, X);
		BODY_60_79(61, T, A, B, C, D, E, X);
		BODY_60_79(62, E, T, A, B, C, D, X);
		BODY_60_79(63, D, E, T, A, B, C, X);
		BODY_60_79(64, C, D, E, T, A, B, X);
		BODY_60_79(65, B, C, D, E, T, A, X);
		BODY_60_79(66, A, B, C, D, E, T, X);
		BODY_60_79(67, T, A, B, C, D, E, X);
		BODY_60_79(68, E, T, A, B, C, D, X);
		BODY_60_79(69, D, E, T, A, B, C, X);
		BODY_60_79(70, C, D, E, T, A, B, X);
		BODY_60_79(71, B, C, D, E, T, A, X);
		BODY_60_79(72, A, B, C, D, E, T, X);
		BODY_60_79(73, T, A, B, C, D, E, X);
		BODY_60_79(74, E, T, A, B, C, D, X);
		BODY_60_79(75, D, E, T, A, B, C, X);
		BODY_60_79(76, C, D, E, T, A, B, X);
		BODY_60_79(77, B, C, D, E, T, A, X);
		BODY_60_79(78, A, B, C, D, E, T, X);
		BODY_60_79(79, T, A, B, C, D, E, X);

		c->h0 = (c->h0 + E) & 0xffffffffL;
		c->h1 = (c->h1 + T) & 0xffffffffL;
		c->h2 = (c->h2 + A) & 0xffffffffL;
		c->h3 = (c->h3 + B) & 0xffffffffL;
		c->h4 = (c->h4 + C) & 0xffffffffL;

		num -= 64;
		if (num <= 0)
			break;

		A = c->h0;
		B = c->h1;
		C = c->h2;
		D = c->h3;
		E = c->h4;

		W += 16;
	}
}
#endif

void SHA1_Final(md, c) unsigned char *md;
SHA_CTX *c;
{
	register int i, j;
	register ULONG l;
	register ULONG *p;
	static unsigned char end[4] = {0x80, 0x00, 0x00, 0x00};
	unsigned char *cp = end;

	p = c->data;
	j = c->num;
	i = j >> 2;
#ifdef PURIFY
	if ((j & 0x03) == 0)
		p[i] = 0;
#endif
	l = p[i];
	M_p_c2nl(cp, l, j & 0x03);
	p[i] = l;
	i++;

	if (c->num >= SHA_LAST_BLOCK)
	{
		for (; i < SHA_LBLOCK; i++)
			p[i] = 0;
		sha1_block(c, p, 64);
		i = 0;
	}
	for (; i < (SHA_LBLOCK - 2); i++)
		p[i] = 0;
	p[SHA_LBLOCK - 2] = c->Nh;
	p[SHA_LBLOCK - 1] = c->Nl;
#if defined(L_ENDIAN) && defined(SHA1_ASM)
	Endian_Reverse32(p[SHA_LBLOCK - 2]);
	Endian_Reverse32(p[SHA_LBLOCK - 1]);
#endif
	sha1_block(c, p, 64);
	cp = md;
	l = c->h0;
	nl2c(l, cp);
	l = c->h1;
	nl2c(l, cp);
	l = c->h2;
	nl2c(l, cp);
	l = c->h3;
	nl2c(l, cp);
	l = c->h4;
	nl2c(l, cp);

	c->num = 0;
}

void SHA_Padding(unsigned char *plaintexts, unsigned char *plaintexts_padding,
				 unsigned long byte_number, unsigned long *block_number)
{
	memcpy(plaintexts_padding, plaintexts, byte_number);
	*block_number = byte_number;
}

void SHA_Hash(unsigned char *plaintexts, unsigned char *hash, unsigned long block_number)
{
	SHA_CTX c;

	SHA1_Init(&c);
	SHA1_Update(&c, plaintexts, (unsigned long)block_number);
	SHA1_Final(hash, &c);
}
