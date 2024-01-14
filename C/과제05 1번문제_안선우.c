#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DICTIONARY {
	char *word;
	char *meaning;
};

int main() {
	struct DICTIONARY wordlist[52000];
	FILE* pFile;
	char* token;
	int i = 0;
	char str1[30], str3[120], check = 0;

	pFile = fopen("dict_test.txt", "r");
	char* ptr = (char*)calloc(3000000, sizeof(char));
	if (ptr == NULL) {
		printf("error");
		exit(1);
	}
	char* ptr2 = " ";

	if (pFile == NULL) {
		printf("잘못된 파일이름입니다.");
		exit(1);
	}

	while (i < 60000 && fgets(str3, sizeof(str3), pFile) != NULL) {
		token = strtok(str3, ":");
		wordlist[i].word = ptr;
		strcpy(wordlist[i].word, token);
		ptr += (strlen(token) + 1);

		token = strtok(NULL, ":");
		wordlist[i].meaning = ptr;
		if (token == NULL) {
			strcpy(wordlist[i].meaning, ptr2);
			ptr += (strlen(ptr2) + 1);
		}
		else {
			strcpy(wordlist[i].meaning, token);
			ptr += (strlen(token) + 1);
		}

		i++;
	}

	while (1) {
		check = 0;
		printf("단어는? ");
		fgets(str1, 49, stdin);
		str1[strcspn(str1, "\n")] = ' ';

		for (int j = 0; j < i; j++) {		// wordlist에 해당 단어가 있는지 찾기
			if (strcmp(str1, wordlist[j].word) == 0) {
				printf("%s %s", str1, wordlist[j].meaning);
				check = 1;
			}
		}
		if (check == 0) {			// 단어가 wordlist에 존재하지 않음
			printf("** 사전에 없는 단어입니다. \n");
		}
		check = 0;

		printf("계속하겠습니까? yes=1, no=0 ");
		scanf("%hhd", &check);
		fgets(str1, 49, stdin);
		printf("\n");
		if (check == 0) break;
	}
}