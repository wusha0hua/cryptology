#include<openssl/sha.h>
#include<stdlib.h>
#include<string.h>

unsigned char* getSha1_1(const char *data) {
	unsigned char *sha1Ouput = (unsigned char*)malloc(20);
	memset(sha1Ouput, 0, 20);	
	SHA1((const unsigned char*)data, sizeof(data), sha1Ouput);
	return sha1Ouput;
}

unsigned char* getSha1_2(const char *data) {
	unsigned char *sha1Ouput = (unsigned char*)malloc(20);
	memset(sha1Ouput, 0, 20);
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	SHA1_Update(&ctx, (const void*)data, sizeof(data));
	SHA1_Final(sha1Ouput, &ctx);
	return sha1Ouput;
}
