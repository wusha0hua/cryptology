#include"sha1.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	unsigned char *sh1Val = getSha1_1("hello");
	for(int i = 0; i < 20; i++) {
		printf("%02x",sh1Val[i]);
	}
	puts("");
	memset(sh1Val, 0, 20);
	sh1Val = getSha1_2("hello");
	for(int i = 0; i < 20; i++) {
		printf("%02x", sh1Val[i]);
	}
	puts("");
}
