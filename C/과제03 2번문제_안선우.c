#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
	char answer[5][52] = {0};	// 최대 50자 65-
	char user[5][52] = { 0 }, blankroutine = 0;
	char wordcount;
	int score = 0;
	clock_t start, end;
	double spentsec;

	srand(time(NULL));

	for (char i = 0; i < 5; i++) {
		printf("(%d/5) 다음을 입력하세요\n", i+1);
		blankroutine = rand() % 7 + 4; 	// 4-10개 단어 간격으로 빈칸 생성. 
		wordcount = 40 + rand() % 10;	// 40-50개 사이의 랜덤한 글자 설정
		for (char j = 0; j < wordcount-1; j++) {
			if (j!=0 && j % blankroutine == 0) {
				answer[i][j] = 32;
			}
			else answer[i][j] = rand() % 26 + 65;	// 대문자
		}
		printf("%s", answer[i]);
		printf("\n");
		start = clock();
		fgets(user[i], 51, stdin);
		end = clock();

		spentsec = ((double)(end - start) / CLOCKS_PER_SEC);
		if (strcmp(answer[i], user[i]) != 0) {	// 틀린부분 표시하기
			for (char j = 0; j < strlen(answer); j++) {
				if (strchr(user[i]+j, answer[i][j]) != user[i]+j) {
					if (user[i][strlen(user[i])] == 10) {	// fgets는 enter도 고려하기 때문
						printf(" ");
					}
					else {
						printf("V");
						wordcount--;
					}
				}
				else printf(" ");
			}
		}
		score += (int)((double)wordcount / spentsec * 60);
		printf("\n%d자/분\n", (int)((double)wordcount / spentsec * 60));
	}

	printf("당신의 점수는 %d점 입니다.", score);
	printf("\n\n20224382 안선우\n");
}