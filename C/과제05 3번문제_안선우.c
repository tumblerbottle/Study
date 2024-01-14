#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct INFO {
	char length;
	char moeum;
	char *word;
};

int compare(const void* m, const void* n) {		// 단어 길이 함수
	struct INFO* first = (struct INFO*)m;
	struct INFO* second = (struct INFO*)n;

	if (first->length < second->length) return 1;
	else if (first->length > second->length) return -1;
	else return 0;

	// return first->length - second->length;
}

int compare2(const void* m, const void* n) {		// 모음 개수 함수
	struct INFO* first = (struct INFO*)m;
	struct INFO* second = (struct INFO*)n;

	if (first->moeum < second->moeum) return 1;
	else if (first->moeum > second->moeum) return -1;
	else return 0;
}

int main() {
	FILE* pFile;
	struct INFO info[52000];
	char str3[50];
	char* token;
	int i = 0;

	pFile = fopen("dict_test.txt", "r");
	if (pFile == NULL) {
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}

	while (i < 52000 && fgets(str3, sizeof(str3), pFile) != NULL) {
		token = strtok(str3, ":");
		info[i].word = malloc(strlen(token)+1);
		strcpy(info[i].word, token);

		info[i].length = strlen(token);
		info[i].moeum = 0;
		for (char j = 0; j < info[i].length; j++) {
			if (token[j] == 'a' || token[j] == 'e' || token[j] == 'i'
				|| token[j] == 'o' || token[j] == 'u') info[i].moeum++;
		}

		i++;
	}


	qsort(info, i, sizeof(info[0]), compare);
	printf("단어길이 긴 순서대로 10개 출력\n");
	for (char j = 0; j < 10; j++) {
		printf("%2d) %s\n", j+1, info[j].word);
	}
	printf("\n");


	qsort(info, i, sizeof(info[0]), compare2);
	printf("모음이 많은 순서대로 10개 출력\n");
	for (char j = 0; j < 10; j++) {
		printf("%2d) %s\n", j+1,info[j].word);
	}
	printf("\n");

	fclose(pFile);
}