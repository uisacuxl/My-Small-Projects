#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]) {
	printf("(Hex) %X", argv[1][0]);
	for (int i = 1, l = strlen(argv[1]); i < l; i++)
		printf(" %X", (unsigned char) argv[1][i]);
	printf("\n(Oct) %o", argv[1][0]);
	for (int i = 1, l = strlen(argv[1]); i < l; i++)
		printf(" %o", (unsigned char) argv[1][i]);
	printf("\n(Dec) %u", argv[1][0]);
	for (int i = 1, l = strlen(argv[1]); i < l; i++)
		printf(" %u", (unsigned char) argv[1][i]);
	putchar('\n');
}
