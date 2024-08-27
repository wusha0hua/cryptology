#include<stdlib.h>
#include<string.h>
#include<stdio.h>

const unsigned char base64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char* getBase64(const unsigned char* data) {
	unsigned long len = strlen(data);
	unsigned char *base64;	
	int base64Len;
	unsigned char *paddedData;
	switch(len % 3) {
		case 0: 
			base64 = (unsigned char*)malloc(len / 3 * 4);
			for(int i = 0; i < len; i += 3) {
				base64[(i / 3) * 4] = base64Map[data[i] >> 2];
				base64[(i / 3) * 4 + 1] = base64Map[(((data[i] << 4) & 0b00110000) | ((data[i + 1] >> 4) & 0b00001111))];
				base64[(i / 3) * 4 + 2] = base64Map[((data[i + 1] << 2) & 0b00111100) | ((data[i + 2] >> 6) & 0b00000011)];
				base64[(i / 3) * 4 + 3] = base64Map[data[i + 2] & 0b00111111];
			}
			break;
		case 1:
			base64Len = (len + 2) / 3 * 4;
			base64 = (unsigned char*)malloc((len + 2) / 3 * 4);
			paddedData = calloc(1, len + 2);
			memcpy(paddedData, data, len);
			for(int i = 0; i < len + 1; i += 3) {
				base64[(i / 3) * 4] = base64Map[paddedData[i] >> 2];
				base64[(i / 3) * 4 + 1] = base64Map[(((paddedData[i] << 4) & 0b00110000) | ((paddedData[i + 1] >> 4) & 0b00001111))];
				base64[(i / 3) * 4 + 2] = base64Map[((paddedData[i + 1] << 2) & 0b00111100) | ((paddedData[i + 2] >> 6) & 0b00000011)];
				base64[(i / 3) * 4 + 3] = base64Map[paddedData[i + 2] & 0b00111111];
			}
			base64[base64Len - 2] = '=';
			base64[base64Len - 1] = '=';
			break;
		case 2:
			base64Len = (len + 1) / 3 * 4;
			base64 = (unsigned char*)malloc((len + 1) / 3 * 4);
			paddedData = calloc(1, len + 1);
			memcpy(paddedData, data, len);
			for(int i = 0; i < len; i += 3) {
				base64[(i / 3) * 4] = base64Map[paddedData[i] >> 2];
				base64[(i / 3) * 4 + 1] = base64Map[(((paddedData[i] << 4) & 0b00110000) | ((paddedData[i + 1] >> 4) & 0b00001111))];
				base64[(i / 3) * 4 + 2] = base64Map[((paddedData[i + 1] << 2) & 0b00111100) | ((paddedData[i + 2] >> 6) & 0b00000011)];
				base64[(i / 3) * 4 + 3] = base64Map[paddedData[i + 2] & 0b00111111];
			}
			base64[base64Len - 1] = '=';		
			break;
	}
	return base64;
}

