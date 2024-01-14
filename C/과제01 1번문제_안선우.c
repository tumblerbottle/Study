#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ladderresult(char ladder[20][4],char result[5]) {		// 결과 확인 함수
	char i, j, saveres;
	for (i = 19; i > -1 ; i--) {
		for (j = 0; j < 4; j++) {		// -이 있는 열에 해당하는 변수와 열+1의 위치에 해당하는 변수 스위치
			if(ladder[i][j] == 45) {
				saveres = result[j];
				result[j] = result[j + 1];
				result[j + 1] = saveres;
			}
		}
	}
}

int main() {
	srand(time(NULL));

	char ladder[20][4];
	char result[5] = { 65,66,67,68,69 };	// 결과 배열

	char i, j, r, linecount = 0;
	char minline = 15;		// 최소 15개 생성

	while (linecount < minline) {		// 사다리 생성
		i = rand() % 20;		// rand 함수 사용 최소화를 위함
		j = rand() % 4;

		if (ladder[i][j]!=45) {		// 해당 위치에 가로선이 없으며
			if ((j == 0 && ladder[i][j + 1] != 45) 
				|| (j == 3 && ladder[i][j - 1] != 45)
				|| (ladder[i][j - 1] != 45 && ladder[i][j + 1] != 45)) {	// 앙옆이 가로선이 아니면서

				if ((i < 2) || 
					!(ladder[i - 1][j] == 45 && ladder[i - 2][j] != 45)) {	// 가로줄이 위아래로 두줄 이상 나오지 않게 함.

					ladder[i][j] = 45;
					linecount++;
				}
			}
		}
	}	
	
	ladderresult(ladder,result);	// 결과 확인 함수

	printf("1  2  3  4  5\n");		// 사다리 출력
	for (i=0;i<20;i++){
		for (j = 0; j < 4; j++) {
			printf("|");

			if (ladder[i][j] != 45) {	// 배열 빈칸 채우기
				ladder[i][j] = 32;
			}

			for (r = 0; r < 2; r++) {		// 가로줄을 두줄로 표현함
				printf("%c", ladder[i][j]);
			}
		}
		printf("|\n");
	}
	printf("A  B  C  D  E\n");

	for (i = 0; i < 5; i++) {		// 각자 결과 표시
		printf("%d -> %c\n", i + 1, result[i]);
	}

	printf("\n20224382 안선우\n");
}