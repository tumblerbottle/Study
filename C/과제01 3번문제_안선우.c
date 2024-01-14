#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ladderresult(char ladder[40][4], char result[5]) {		// 결과 확인 함수
	char i, j, saveres;
	for (i = 19; i > -1; i--) {
		for (j = 0; j < 4; j++) {		// -이 있는 열에 해당하는 변수와 열+1의 위치에 해당하는 변수 스위치
			if (ladder[i][j] == 45) {
				saveres = result[j];
				result[j] = result[j + 1];
				result[j + 1] = saveres;
			}
		}
	}
}

void laddermaker(char result[5], char minline) {
	char ladder[40][4];
	char linecount = 0, i, j;

	while (linecount < minline) {		// 사다리 생성
		i = rand() % 20;		// rand 함수 사용 최소화를 위함
		j = rand() % 4;

		if (ladder[i][j] != 45) {		// 해당 위치에 가로선이 없으며
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

	ladderresult(ladder, result);	// 결과 확인 함수
}

int main() {
	srand(time(NULL));

	short speresult[5][5] = { 0, };	// 개별 결과 모음  
	// speresult[해당 result 배열의 index][저장된 숫자의 순번]
	char i, j, r;
	char minline = 33;		// 최소 33개 생성 - 가로선이 많을수록 균등한 결과가 나오는 듯 하다
	short try = 0;	// 사다리 게임 횟수

	while (try < 1000) {
		char result[5] = { 65,66,67,68,69 };	// 결과 배열
		laddermaker(result, minline);

		for (i = 0; i < 5; i++) {		// speresult에 개별 결과 저장
			speresult[i][result[i] - 65]++;
		}

		try++;
	}

	for (i = 0; i < 5; i++) {		// 전체 결과 출력
		printf("%d : ", i + 1);
		for (j = 0; j < 5; j++) {
			printf("%c(%d) ", j + 65, speresult[i][j]);
		}
		printf(" : 1000\n");
	}

	printf("\n20224382 안선우\n");
}