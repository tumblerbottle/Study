#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char input[1000], input2[1000];
	char* temp;
	int result = 0;
	printf("수식을 입력하세요. 숫자는 10,000로 제한합니다.\n");
	fgets(input, sizeof(input), stdin);
	strcpy(input2, input);

	temp = strtok(input, "+-=");
	while (temp != NULL) {
		if (input2[temp - input - 1] == '-') result -= atoi(temp);
		else result += atoi(temp);
		temp = strtok(NULL, "+-=");
	}

	printf("= %d", result);

	printf("\n\n20224382 안선우\n");
}