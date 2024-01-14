#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	char space[50], used = 0, count = 0;

	while ((50 - used)>=0) {
		printf("= %d 바이트 남음\n> ", 50 - used);
		scanf("%hhd", &space[used]);
		used++;

		switch (space[used-1]) {
			case(1):
				if (50 - used >= 1) {
					scanf("%hhd", (char*)&space[used]);
					count++;
				}
				used += 1;
				break;
			case(2):
				if (50 - used >= 2) {
					scanf("%hd", (short*)&space[used]);
					count++;
				}
				used += 2;
				break;
			case(3):
				if (50 - used >= 4) {
					scanf("%d", (int*)&space[used]);
					count++;
				}
				used += 4;
				break;
			case(4):
				if (50 - used >= 8) {
					scanf("%lld", (long long*)&space[used]);
					count++;
				}
				used += 8;
				break;
		}
	} // end of while


	printf("= 저장공간이 가득 찼습니다.\n");
	printf("%d\n", count);
	used = 0;
	for (char i = 0; i < count; i++) {
		switch (space[used]) {
			case(1):
				printf("%dC ", *((char*)&space[used + 1]));
				used += 2;
				break;
			case(2):
				printf("%dS ", *((short*)&space[used + 1]));
				used += 3;
				break;
			case(3):
				printf("%dI ", *((int*)&space[used + 1]));
				used += 5;
				break;
			case(4):
				printf("%dLL ", *((long long*)&space[used + 1]));
				used += 9;
				break;
		}
	}

	printf("\n\n\n20224382 안선우\n");
}