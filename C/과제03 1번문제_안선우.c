#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {	//qsort 용
	return strcmp((char*)a,(char*)b);
}

int diffwordcounter(char input[],char norepeatword[200][50]) {	// 중복 단어 제거 함수
	int nosameword = 0;	// 중복 없는 단어 수
	char* token;
	char finder = 0;	// 중복된 단어가 있는지

	token = strtok(input, " \n");

	while (token != 0) {
		finder = 0;
		for (char i = 0; i < nosameword; i++) {		// 중복 단어가 없는 단어의 배열인 nosameword를 token 과 비교함
			if (strcmp(norepeatword[i], token) == 0) {
				finder=1;
				break;
			}
		}
		if (finder == 0) {
			strcpy(norepeatword[nosameword], token);
			nosameword++;
		}
		token = strtok(NULL, " \n");
	}
	return nosameword;
}


int main() {
	char input[10000] = { 0, };
	char input2[10000] = { 0, };	// input 원본 유지용
	char norepeatword[200][50] = {" "};	// 중복되지 않는 단어 저장용 배열 -> qsort에 사용
	int word = 0, line = 0, used = 0, norepeat = 0;		// 입력된 단어 수/입력된 문장 수/원본길이 저장/중복단어 제거 단어 수

	printf("원하는 문장을 입력하세요. \n");
	printf("end를 입력하면 입력이 종료됩니다.\n");

	while (1) {
		fgets(input, sizeof(input), stdin);
		if (strcmp(input, "end\n") == 0) {	// 단독으로 end 입력 시 입력 중단
			break;
		}
		used += strlen(input);

		strncpy(input2+used-strlen(input), input,strlen(input));	// 원본은 유지하기 위함. 

		if (strchr(input, '\n') != NULL) {	// 줄바꿈은 \n으로 확인
			line++;
		}

		char* token = strtok(input, " \n");		// 단어 수 세기
		while (token != NULL) {
			word++;
			token = strtok(NULL, " \n");
		}
	}

	norepeat = diffwordcounter(input2,norepeatword);	// 중복단어 제거 함수

	printf("\n입력된 문장의 수: %d\n",line);
	printf("입력된 단어의 수: %d\n",word);
	printf("중복이 제거된 단어의 수: %d\n\n",norepeat);

	qsort(norepeatword, norepeat, sizeof(norepeatword[0]), compare);

	for (char i = 0; i < norepeat; i++) {
		printf("%s\n", norepeatword[i]);
	}

	printf("\n20224382 안선우\n");
}