#include"base64.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
	while(1) {
		unsigned char *data = calloc(1, 100); 
		scanf("%s", data);
		printf("%s\n", getBase64(data));
	}
}
