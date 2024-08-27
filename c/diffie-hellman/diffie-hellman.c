#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


unsigned int generatePrime(unsigned int wMin, unsigned int wMax);
_Bool isPrime(unsigned int wNum); 
unsigned int ExpMod(unsigned int base, unsigned int index, unsigned int modulus);


int main() {
	srand(time(NULL));
	unsigned int g = generatePrime(100, 10000);	
	printf("g: %d\n", g);
	unsigned int p = generatePrime(100, 10000);
	printf("p: %d\n", p);
	unsigned int a = generatePrime(10, p);
	printf("a: %d\n", a);
	unsigned int b = generatePrime(10, p);
	printf("b: %d\n", b);
	unsigned int sa = ExpMod(g, a, p);	
	printf("sa: %d\n", sa);
	unsigned int sb = ExpMod(g, b, p);
	printf("sb: %d\n", sb);

	printf("key: %d = %d \n", ExpMod(sa, b, p), ExpMod(sb, a, p));
}

unsigned int generatePrime(unsigned int wMin, unsigned int wMax) {
	while(1) {
		unsigned int wRnd = rand();	
		if(wRnd <= wMin || wRnd >= wMax) {
			continue;
		}
		if(isPrime(wRnd)) {
			return wRnd;
		}
	}
}

_Bool isPrime(unsigned int wNum) {
	_Bool *map = (_Bool*)malloc(wNum);
	memset(map, 0, sizeof(_Bool) * wNum);
	
	for(unsigned int i = 2; i < wNum; i++) {
		if(map[i + 1] == 1) {
			continue;
		}

		if(wNum % i == 0) {
			return 0;
		} else {
			for(unsigned int j = i - 1; j < wNum; j += i) {
				map[j] = 1;
			}
		}
	}
	
	return 1;
}

unsigned int ExpMod(unsigned int base, unsigned int index, unsigned int modulus) {
	unsigned int result = base % modulus;
	for(int i = 0; i < index; i++) {
		result = (result * (base % modulus)) % modulus;
	}
	return result;
}
