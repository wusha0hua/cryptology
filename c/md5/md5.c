#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int A = 0x01234567;
int B = 0x89ABCDEF;
int C = 0xFEDCBA98;
int D = 0x76543210;

#define F(X, Y, Z) (X & Y) | ((~X) & Z)
#define G(X, Y, Z) (X & Z) | (Y & (~Z))
#define H(X, Y, Z) X ^ Y ^ Z
#define I(X, Y, Z) Y ^ (X | (~Z))

#define ROL(X, N) (int)((X) << N) | ((X) >> (32 - N)) 

#define FF(a, b, c, d, Mj, s, ti) b + ROL(a + F(b, c, d) + Mj + ti, s)
#define GG(a, b, c, d, Mj, s, ti) b + ROL(a + G(b, c, d) + Mj + ti, s)
#define HH(a, b, c, d, Mj, s, ti) b + ROL(a + H(b, c, d) + Mj + ti, s)
#define II(a, b, c, d, Mj, s, ti) b + ROL(a + I(b, c, d) + Mj + ti, s)

char* md5(char* data) {
	int data_len = strlen(data);
	int padding_len = (56 - (data_len % 64) + 64) % 64;
	char data_len_str[8];		

	char *data_padded = calloc(1, data_len + padding_len + 8);
	memcpy(data_padded, data, data_len);
	if(padding_len != 0) {
		data_padded[data_len] = 0b10000000;
	}
	*(unsigned long*)(data_padded + data_len + padding_len) = data_len;
	
	/*
	int a = ((unsigned int)data_padded[0] << 24) | ((unsigned int)data_padded[1] << 16) | ((unsigned int)data_padded[2] << 8) | ((unsigned int)data_padded[3]);
	int b = ((unsigned int)data_padded[4] << 24) | ((unsigned int)data_padded[5] << 16) | ((unsigned int)data_padded[6] << 8) | ((unsigned int)data_padded[7]);
	int c = ((unsigned int)data_padded[8] << 24) | ((unsigned int)data_padded[9] << 16) | ((unsigned int)data_padded[10] << 8) | ((unsigned int)data_padded[11]);
	int d = ((unsigned int)data_padded[12] << 24) | ((unsigned int)data_padded[13] << 16) | ((unsigned int)data_padded[14] << 8) | ((unsigned int)data_padded[15]);
	*/

	int a = A;
	int b = B;
	int c = C;
	int d = D;
	for(int i = 0; i < (data_len + padding_len + 8) / 64; i++) {
		int *M = (int*)malloc(sizeof(int) * 16);		
		for(int j = 0; j < 16; j++) {
			M[j] = ((unsigned int)data_padded[64 * i + j * 4] << 24) | ((unsigned int)data_padded[64 * i + j * 4 + 1] << 16) | ((unsigned int)data_padded[64 * i + j * 4 + 2] << 8) | ((unsigned int)data_padded[64 * i + j * 4 + 3]);
		}
		
		a = FF(a, b, c, d, M[0], 7, 0xd76aa478);
		d = FF(d, a, b, c, M[1], 12, 0xe8c7b756);
		c = FF(c, d, a, b, M[2], 17, 0x242070db);
		b = FF(b, c, d, a, M[3], 22, 0xc1bdceee);
		a = FF(a, b, c, d, M[4], 7, 0xf57c0faf);
		d = FF(d, a, b, c, M[5], 12, 0x4787c62a);
		c = FF(c, d, a, b, M[6], 17, 0xa8304613);
		b = FF(b, c, d, a, M[7], 22, 0xfd469501);
		a = FF(a, b, c, d, M[8], 7, 0x698098d8);
		d = FF(d, a, b, c, M[9], 12, 0x8b44f7af);
		c = FF(c, d, a, b, M[10], 17, 0xffff5bb1);
		b = FF(b, c, d, a, M[11], 22, 0x895cd7be);
		a = FF(a, b, c, d, M[12], 7, 0x6b901122);
		d = FF(d, a, b, c, M[13], 12, 0xfd987193);
		c = FF(c, d, a, b, M[14], 17, 0xa679438e);
		b = FF(b, c, d, a, M[15], 22, 0x49b40821);

		a = GG(a, b, c, d, M[1], 5, 0xf61e2562);
		d = GG(d, a, b, c, M[6], 9, 0xc040b340);
		c = GG(c, d, a, b, M[11], 14, 0x265e5a51);
		b = GG(b, c, d, a, M[0], 20, 0xe9b6c7aa);
		a = GG(a, b, c, d, M[5], 5, 0xd62f105d);
		d = GG(d, a, b, c, M[10], 9, 0x02441453);
		c = GG(c ,d ,a ,b ,M[15] ,14 ,0xd8a1e681);
		b = GG(b ,c ,d ,a ,M[4] ,20 ,0xe7d3fbc8);
		a = GG(a ,b ,c ,d ,M[9] ,5 ,0x21e1cde6);
		d = GG(d ,a ,b ,c ,M[14] ,9 ,0xc33707d6);
		c = GG(c ,d ,a ,b ,M[3] ,14 ,0xf4d50d87);
		b = GG(b ,c ,d ,a ,M[8] ,20 ,0x455a14ed);
		a = GG(a ,b ,c ,d ,M[13] ,5 ,0xa9e3e905);
		d = GG(d ,a ,b ,c ,M[2] ,9 ,0xfcefa3f8);
		c = GG(c ,d ,a ,b ,M[7] ,14 ,0x676f02d9);
		b = GG(b ,c ,d ,a ,M[12] ,20 ,0x8d2a4c8a);

		a = HH(a ,b ,c ,d ,M[5] ,4 ,0xfffa3942);
		d = HH(d ,a ,b ,c ,M[8] ,11 ,0x8771f681);
		c = HH(c ,d ,a ,b ,M[11] ,16 ,0x6d9d6122 );
		b = HH(b ,c ,d ,a ,M[14] ,23 ,0xfde5380c );
		a = HH(a ,b ,c ,d ,M[1] ,4 ,0xa4beea44 );
		d = HH(d ,a ,b ,c ,M[4] ,11 ,0x4bdecfa9 );
		c = HH(c ,d ,a ,b ,M[7] ,16 ,0xf6bb4b60 );
		b = HH(b ,c ,d ,a ,M[10] ,23 ,0xbebfbc70 );
		a = HH(a ,b ,c ,d ,M[13] ,4 ,0x289b7ec6 );
		d = HH(d ,a ,b ,c ,M[0] ,11 ,0xeaa127fa );
		c = HH(c ,d ,a ,b ,M[3] ,16 ,0xd4ef3085 );
		b = HH(b ,c ,d ,a ,M[6] ,23 ,0x04881d05 );
		a = HH(a ,b ,c ,d ,M[9] ,4 ,0xd9d4d039 );
		d = HH(d ,a ,b ,c ,M[12] ,11 ,0xe6db99e5 );
		c = HH(c ,d ,a ,b ,M[15] ,16 ,0x1fa27cf8 );
		b = HH(b ,c ,d ,a ,M[2] ,23 ,0xc4ac5665 );

		a = II(a ,b ,c ,d ,M[0] ,6 ,0xf4292244);
		d = II(d ,a ,b ,c ,M[7] ,10 ,0x432aff97);
		c = II(c ,d ,a ,b ,M[14] ,15 ,0xab9423a7);
		b = II(b ,c ,d ,a ,M[5] ,21 ,0xfc93a039);
		a = II(a ,b ,c ,d ,M[12] ,6 ,0x655b59c3);
		d = II(d ,a ,b ,c ,M[3] ,10 ,0x8f0ccc92);
		c = II(c ,d ,a ,b ,M[10] ,15 ,0xffeff47d);
		b = II(b ,c ,d ,a ,M[1] ,21 ,0x85845dd1);
		a = II(a ,b ,c ,d ,M[8] ,6 ,0x6fa87e4f);
		d = II(d ,a ,b ,c ,M[15] ,10 ,0xfe2ce6e0);
		c = II(c ,d ,a ,b ,M[6] ,15 ,0xa3014314);
		b = II(b ,c ,d ,a ,M[13] ,21 ,0x4e0811a1);
		a = II(a ,b ,c ,d ,M[4] ,6 ,0xf7537e82);
		d = II(d ,a ,b ,c ,M[11] ,10 ,0xbd3af235);
		c = II(c ,d ,a ,b ,M[2] ,15 ,0x2ad7d2bb);
		b = II(b ,c ,d ,a ,M[9] ,21 ,0xeb86d391);

		a = (a + A) & 0xffffffff;
		b = (b + B) & 0xffffffff;
		c = (c + C) & 0xffffffff;
		d = (d + D) & 0xffffffff;
	}

	char *md5 = calloc(1, sizeof(int) * 4);
	*(unsigned int*)md5 = a;
	*(unsigned int*)(md5 + 4) = b;
	*(unsigned int*)(md5 + 8) = c;
	*(unsigned int*)(md5 + 12) = d;
	return md5;
}
