#include<stdio.h>
int main() {
	for (int j = 32; j < 51; j++) {
		int v = j;
		for (int i = 0; i < 3; i++, v += 19)
			printf("%d: '%c'   ", v, v);
		printf("%d:%s'%c'   ", v, j < 43 ? "  " : " ", v);
		v += 19;
		printf("%d: '%c'", v, v);
		putchar('\n');
	}
}
