#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
	FILE* pFile;
	char str3[50], str2[50];
	char line[80];
	char* past[100], *ptr= NULL;	// 이미 나온 단어의 포인터를 저장하는 변수
	char check = 0, miss = 0, score = 0, round = 0, wrong = 1;

	srand(time(NULL));
	pFile = fopen("dict_test.txt", "r");

	if (pFile == NULL) {
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}

	while (miss < 3) {
		printf("%d 라운드\n", round + 1);
		if (round == 0) {
			while (check < rand() % 1000) {		// 컴퓨터 단어 고르기
				fgets(line, 80, pFile);
				ptr = strtok(line, " :");
			}
			printf("컴퓨터: %s\n", ptr);
			strcpy(str2, ptr);
		}
		check = 0;
		wrong = 1;

		fseek(pFile, 0, SEEK_SET);
		printf("단어는? ");
		scanf("%s", str3);
		past[round] = malloc(strlen(str3) + 1);
		strcpy(past[round],str3);
		round++;

		if (str2[strlen(str2)-1] == str3[0]) check++;	// 끝말잇기인지 확인
		else printf("잘못된 끝말잇기입니다.\n");

		if (strlen(str3) > 2 && strlen(str3) < 11) {		// 단어 길이 확인
			check++;
		}
		else printf("단어의 길이가 잘못되었습니다.\n");

		if (round < 2) check++;
		for (char i = 0; i < round-1; i++) {		// 이미 입력한 단어인지 확인
			if (strcmp(past[i], str3) == 0) printf("이미 나온 단어입니다.\n");
			else check++;
		}

		while (fgets(line, 80, pFile) != NULL) {	// 실제 있는 단어인지
			char* ptr = strtok(line, " :");
			if (ptr != NULL) {
				if (strcmp(ptr, str3) == 0) {
					check ++;
					wrong = 0;
					break;
				}
				else continue;
			}
			else continue;
		}
		if (wrong == 1) printf("없는 단어입니다.\n");

		if (((round==1) && (check - round) == 3) || ((check - round) == 2)) score++;
		else miss++;

		printf("현재점수 %d 점\n\n", score);
		strcpy(str2, str3);
	}

	fclose(pFile);
	return 0;
}