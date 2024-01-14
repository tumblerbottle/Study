#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char smartcomp4(char board[25][3]) {		// 똑똑한 컴퓨터 선택 4. 한 줄에 3개 이상이 있다면 나머지 값 중 하나를 부른다 함수
	char i, j, count = 0, empty = 0;

	for (i = 0; i < 5; i ++) {		// 세로 빙고
		for (j = 0 + i; j < 21 + i; j += 5) {
			if (board[j][0] == 40) count++;
			else empty = j;	
		}
		if (count > 2 && count < 5) return empty;	// 3~4 개가 채워진 경우, 채워지지 않은 수 중 가장 아래쪽에 있는 수 반환
		else count = 0;
	}

	for (i = 0; i < 21; i += 5) {		// 가로 빙고
		for (j = 0 + i; j < 5 + i; j++) {
			if (board[j][0] == 40) count++;
			else empty = j;
		}
		if (count > 2 && count < 5) return empty;	// 3~4 개가 채워진 경우, 채워지지 않은 수 중 가장 오른쪽에 있는 수 반환
		else count = 0;
	}

	for (i = 0; i < 25; i += 6) {		// 대각선 빙고 왼위->오른아래
		if (board[i][0] == 40) count++;
		else empty = i;
	}
	if (count > 2 && count < 5) return empty;	// 3~4 개가 채워진 경우, 채워지지 않은 수 중 가장 오른아래에 있는 수 반환
	else count = 0;

	for (i = 4; i < 21; i += 4) {		// 대각선 빙고 오른위->왼아래
		if (board[i][0] == 40) count++;
		else empty = i;	
	}
	if (count > 2 && count < 5) return empty;	// 3~4 개가 채워진 경우, 채워지지 않은 수 중 가장 왼아래에 있는 수 반환
	else return 0;		// 4번 조건 성립이 불가능함을 의미.
}	// end of smartcomp4(똑똑한 컴퓨터 선택 4 함수)


char bingocounter(char board[25][3]) {		// 빙고 확인 함수
	char i, j, count = 0, bingo = 0;
	for (i = 0; i < 5; i ++) {		// 세로 빙고
		for (j = 0 + i; j < 21 + i; j += 5) {
			if (board[j][0] == 40) count++;
		}
		if (count == 5) bingo ++ ;
		count = 0;
	}

	for (i = 0; i < 21; i += 5) {		// 가로 빙고
		for (j = 0 + i; j < 5 + i; j++) {
			if (board[j][0] == 40) count++;
		}
		if (count == 5) bingo++;
		count = 0;
	}

	for (i = 0; i < 25; i += 6) {		// 대각선 빙고 왼위->오른아래
		if (board[i][0] == 40) count++;
	}
	if (count == 5) bingo++;
	count = 0;

	for (i = 4; i < 21; i += 4) {		// 대각선 빙고 오른위->왼아래
		if (board[i][0] == 40) count++;
	}
	if (count == 5) bingo++;
	count = 0;

	return bingo;
}	// end of char bingochecker(빙고 확인 함수)

void eliminate(char board[25][3], char num) {		// 선택된 숫자 괄호 씌우는 함수
	char i;
	for (i = 0; i < 25; i++) {
		if (board[i][1] == num) {
			board[i][0] = 40;		// ASCII (
			board[i][2] = 41;		// ASCII )
		}
	}
}

char inputchecker(char board[25][3], char num) {	// 중복 선택 방지 함수
	char i;
	for (i = 0; i < 25; i++) {
		if (board[i][1] == num) {
			if (board[i][0] == 40) return 0;	// 이미 선택된 값을 다시 부른 경우
		}
		else continue;
	}
	return 1;
}

void printboard(char board[25][3]) {		// 빙고판 출력 함수
	char i, j;
	for (i = 0; i < 21; i+= 5 ) {
		for (j = 0 + i; j < 5 + i; j++) {
			if (board[j][0] != 40) printf("   %c%c%2d%c%c   ", board[j][0], board[j][0], board[j][1], board[j][2], board[j][2]);
			else if (board[0][0]==40 && j==0)printf("   %c%2d%c   ", board[j][0], board[j][1], board[j][2]);
			else printf("  %c%2d%c  ", board[j][0], board[j][1], board[j][2]);		// 간격 맞춰 출력하기 위함. 
		}
		printf("\n  ");
	}
}

char boardchecker(char board[25][3], char index, char innum) {		// 보드 생성 시 중복값 방지 함수
	char i;	
	for (i = 0; i < index; i ++) {
		if (board[i][1] == innum) return 0;
		else continue;
	}
	return 1;
}

void boardmaker(char board[25][3]) {		// 보드 채우기 함수
	char i, num;
	for (i = 0; i < 25; i++) {
		do {
			num = rand() % 25 + 1;
		} while (boardchecker(board, i, num) == 0);
		board[i][1] = num;		// 배열의 2번째 칸에 숫자를 넣음.
	}
}


int main() {
	char userboard[25][3] = { 32, }, compboard[25][3] = { 32, };
	char userturn = 0, compturn = 0, userbingo, compbingo, trial = 1, i, j;

	srand(time(NULL));
	boardmaker(userboard);
	boardmaker(compboard);

	printf("유저의 빙고판입니다. \n");
	printboard(userboard);

	do {
		printf("\n%d번쨰 판\n", trial);
		if (trial % 2 == 1) {		// 유저가 숫자 선택
			do {
				printf("유저 순서입니다. 원하는 번호를 입력하세요. ");
				scanf("%hhd", &userturn);
				if (inputchecker(userboard, userturn) == 0) printf("이전에 나온 값입니다. 다시 입력하세요. \n");	// 0은 거짓을 의미함. 
			} while (inputchecker(userboard, userturn) == 0);
			eliminate(userboard, userturn);
			eliminate(compboard, userturn);			// 사용자 편의를 위해 짝수 회차(컴퓨터 차례) 종료 후 유저 빙고판 출력 
		}	// end of if(유저 선택) 

		else {		// 컴퓨터가 숫자 선택
			do {
				if ((trial == 2) && (compboard[12][0] != 40)) {		// 똑똑한 컴퓨터 선택 1 : 제일 먼저 정중앙에 위치한 값을 부른다.
					compturn = compboard[12][1];
				}
				else if (smartcomp4(compboard) != 0) {		// 똑똑한 컴퓨터 선택 4. 한 줄에 3개 이상이 있다면 나머지 값 중 하나를 부른다.
					compturn = compboard[smartcomp4(compboard)][1];
				}
				else if (compboard[0][0] != 40 || compboard[4][0] != 40 ||
					compboard[20][0] != 40 || compboard[24][0] != 40) {		// 똑똑한 컴퓨터 선택 2. 모서리에 있는 값을 부른다.
					for(i = 0; i < 21; i += 20) {
						for (j = 0 + i; j < 5 + i; j += 4) {
							if (compboard[j][0] != 40) compturn = compboard[j][1];
						}
					}
				}
				else if (compboard[7][0] != 40 || compboard[11][0] != 40 ||
					compboard[13][0] != 40 || compboard[17][0] != 40){		// 똑똑한 컴퓨터 선택 3. 정중앙 수에서 십(+)자 위치의 값을 부른다 (7.11.13.17)
					for (i = 1; i < 6; i += 4) {
						for (j = -1; j < 2; j += 2 ) {
							if (compboard[12 + i * (j)][0] != 40) compturn = compboard[12 + i * (j)][1];
						}
					}
				}
				else compturn = rand() % 25 + 1;	// end of if(똑똑한 컴퓨터 선택)
			} while (inputchecker(compboard, compturn) == 0);	// end of do-while(컴퓨터 중복선택 확인)

			printf("컴퓨터는 %d를 골랐습니다. \n");		
			eliminate(userboard, compturn);
			eliminate(compboard, compturn);
			printboard(userboard);		// 유저 빙고판은 혼란을 줄이기 위해 짝수 회차 종료 후에만 출력
			printf("빙고의 수: %d\n", bingocounter(userboard));
		} // end of else(컴퓨터 차례)

		userbingo = bingocounter(userboard);	// 빙고 개수 확인
		compbingo = bingocounter(compboard);
		trial ++ ;
	} while (userbingo < 5 && compbingo < 5);	// end of do-while(빙고게임)

	if (compbingo >= 5 && userbingo >= 5) printf("\n 비겼습니다.\n");
	else if(compbingo < 5 && userbingo >= 5) printf("\n 유저 승리!\n");
	else printf("\n 컴퓨터 승리!\n");

	printf("컴퓨터의 빙고판은 이렇습니다.\n");
	printboard(compboard);
	printf("빙고의 수: %d", compbingo);
	printf("\n");
	printf("유저의 빙고판은 이렇습니다.\n");
	printboard(userboard);
	printf("빙고의 수: %d", userbingo);
	printf("\n");

	printf("\n20224382 안선우\n");
}