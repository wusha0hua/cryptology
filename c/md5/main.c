#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"md5.h"

int main() {
	while(1) {
		char data[1000];
		memset(data, 0, 1000);
		scanf("%s", data);
		char *md = md5(data);
		for(int i = 0; i < 16; i++) {
			printf("%02x", (unsigned char)md[i]);
		}
		puts("");
	}
}
