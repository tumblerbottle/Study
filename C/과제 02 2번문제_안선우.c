#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char smartcomp4(char board[25][3]) {		// �ȶ��� ��ǻ�� ���� 4. �� �ٿ� 3�� �̻��� �ִٸ� ������ �� �� �ϳ��� �θ��� �Լ�
	char i, j, count = 0, empty = 0;

	for (i = 0; i < 5; i ++) {		// ���� ����
		for (j = 0 + i; j < 21 + i; j += 5) {
			if (board[j][0] == 40) count++;
			else empty = j;	
		}
		if (count > 2 && count < 5) return empty;	// 3~4 ���� ä���� ���, ä������ ���� �� �� ���� �Ʒ��ʿ� �ִ� �� ��ȯ
		else count = 0;
	}

	for (i = 0; i < 21; i += 5) {		// ���� ����
		for (j = 0 + i; j < 5 + i; j++) {
			if (board[j][0] == 40) count++;
			else empty = j;
		}
		if (count > 2 && count < 5) return empty;	// 3~4 ���� ä���� ���, ä������ ���� �� �� ���� �����ʿ� �ִ� �� ��ȯ
		else count = 0;
	}

	for (i = 0; i < 25; i += 6) {		// �밢�� ���� ����->�����Ʒ�
		if (board[i][0] == 40) count++;
		else empty = i;
	}
	if (count > 2 && count < 5) return empty;	// 3~4 ���� ä���� ���, ä������ ���� �� �� ���� �����Ʒ��� �ִ� �� ��ȯ
	else count = 0;

	for (i = 4; i < 21; i += 4) {		// �밢�� ���� ������->�޾Ʒ�
		if (board[i][0] == 40) count++;
		else empty = i;	
	}
	if (count > 2 && count < 5) return empty;	// 3~4 ���� ä���� ���, ä������ ���� �� �� ���� �޾Ʒ��� �ִ� �� ��ȯ
	else return 0;		// 4�� ���� ������ �Ұ������� �ǹ�.
}	// end of smartcomp4(�ȶ��� ��ǻ�� ���� 4 �Լ�)


char bingocounter(char board[25][3]) {		// ���� Ȯ�� �Լ�
	char i, j, count = 0, bingo = 0;
	for (i = 0; i < 5; i ++) {		// ���� ����
		for (j = 0 + i; j < 21 + i; j += 5) {
			if (board[j][0] == 40) count++;
		}
		if (count == 5) bingo ++ ;
		count = 0;
	}

	for (i = 0; i < 21; i += 5) {		// ���� ����
		for (j = 0 + i; j < 5 + i; j++) {
			if (board[j][0] == 40) count++;
		}
		if (count == 5) bingo++;
		count = 0;
	}

	for (i = 0; i < 25; i += 6) {		// �밢�� ���� ����->�����Ʒ�
		if (board[i][0] == 40) count++;
	}
	if (count == 5) bingo++;
	count = 0;

	for (i = 4; i < 21; i += 4) {		// �밢�� ���� ������->�޾Ʒ�
		if (board[i][0] == 40) count++;
	}
	if (count == 5) bingo++;
	count = 0;

	return bingo;
}	// end of char bingochecker(���� Ȯ�� �Լ�)

void eliminate(char board[25][3], char num) {		// ���õ� ���� ��ȣ ����� �Լ�
	char i;
	for (i = 0; i < 25; i++) {
		if (board[i][1] == num) {
			board[i][0] = 40;		// ASCII (
			board[i][2] = 41;		// ASCII )
		}
	}
}

char inputchecker(char board[25][3], char num) {	// �ߺ� ���� ���� �Լ�
	char i;
	for (i = 0; i < 25; i++) {
		if (board[i][1] == num) {
			if (board[i][0] == 40) return 0;	// �̹� ���õ� ���� �ٽ� �θ� ���
		}
		else continue;
	}
	return 1;
}

void printboard(char board[25][3]) {		// ������ ��� �Լ�
	char i, j;
	for (i = 0; i < 21; i+= 5 ) {
		for (j = 0 + i; j < 5 + i; j++) {
			if (board[j][0] != 40) printf("   %c%c%2d%c%c   ", board[j][0], board[j][0], board[j][1], board[j][2], board[j][2]);
			else if (board[0][0]==40 && j==0)printf("   %c%2d%c   ", board[j][0], board[j][1], board[j][2]);
			else printf("  %c%2d%c  ", board[j][0], board[j][1], board[j][2]);		// ���� ���� ����ϱ� ����. 
		}
		printf("\n  ");
	}
}

char boardchecker(char board[25][3], char index, char innum) {		// ���� ���� �� �ߺ��� ���� �Լ�
	char i;	
	for (i = 0; i < index; i ++) {
		if (board[i][1] == innum) return 0;
		else continue;
	}
	return 1;
}

void boardmaker(char board[25][3]) {		// ���� ä��� �Լ�
	char i, num;
	for (i = 0; i < 25; i++) {
		do {
			num = rand() % 25 + 1;
		} while (boardchecker(board, i, num) == 0);
		board[i][1] = num;		// �迭�� 2��° ĭ�� ���ڸ� ����.
	}
}


int main() {
	char userboard[25][3] = { 32, }, compboard[25][3] = { 32, };
	char userturn = 0, compturn = 0, userbingo, compbingo, trial = 1, i, j;

	srand(time(NULL));
	boardmaker(userboard);
	boardmaker(compboard);

	printf("������ �������Դϴ�. \n");
	printboard(userboard);

	do {
		printf("\n%d���� ��\n", trial);
		if (trial % 2 == 1) {		// ������ ���� ����
			do {
				printf("���� �����Դϴ�. ���ϴ� ��ȣ�� �Է��ϼ���. ");
				scanf("%hhd", &userturn);
				if (inputchecker(userboard, userturn) == 0) printf("������ ���� ���Դϴ�. �ٽ� �Է��ϼ���. \n");	// 0�� ������ �ǹ���. 
			} while (inputchecker(userboard, userturn) == 0);
			eliminate(userboard, userturn);
			eliminate(compboard, userturn);			// ����� ���Ǹ� ���� ¦�� ȸ��(��ǻ�� ����) ���� �� ���� ������ ��� 
		}	// end of if(���� ����) 

		else {		// ��ǻ�Ͱ� ���� ����
			do {
				if ((trial == 2) && (compboard[12][0] != 40)) {		// �ȶ��� ��ǻ�� ���� 1 : ���� ���� ���߾ӿ� ��ġ�� ���� �θ���.
					compturn = compboard[12][1];
				}
				else if (smartcomp4(compboard) != 0) {		// �ȶ��� ��ǻ�� ���� 4. �� �ٿ� 3�� �̻��� �ִٸ� ������ �� �� �ϳ��� �θ���.
					compturn = compboard[smartcomp4(compboard)][1];
				}
				else if (compboard[0][0] != 40 || compboard[4][0] != 40 ||
					compboard[20][0] != 40 || compboard[24][0] != 40) {		// �ȶ��� ��ǻ�� ���� 2. �𼭸��� �ִ� ���� �θ���.
					for(i = 0; i < 21; i += 20) {
						for (j = 0 + i; j < 5 + i; j += 4) {
							if (compboard[j][0] != 40) compturn = compboard[j][1];
						}
					}
				}
				else if (compboard[7][0] != 40 || compboard[11][0] != 40 ||
					compboard[13][0] != 40 || compboard[17][0] != 40){		// �ȶ��� ��ǻ�� ���� 3. ���߾� ������ ��(+)�� ��ġ�� ���� �θ��� (7.11.13.17)
					for (i = 1; i < 6; i += 4) {
						for (j = -1; j < 2; j += 2 ) {
							if (compboard[12 + i * (j)][0] != 40) compturn = compboard[12 + i * (j)][1];
						}
					}
				}
				else compturn = rand() % 25 + 1;	// end of if(�ȶ��� ��ǻ�� ����)
			} while (inputchecker(compboard, compturn) == 0);	// end of do-while(��ǻ�� �ߺ����� Ȯ��)

			printf("��ǻ�ʹ� %d�� ������ϴ�. \n");		
			eliminate(userboard, compturn);
			eliminate(compboard, compturn);
			printboard(userboard);		// ���� �������� ȥ���� ���̱� ���� ¦�� ȸ�� ���� �Ŀ��� ���
			printf("������ ��: %d\n", bingocounter(userboard));
		} // end of else(��ǻ�� ����)

		userbingo = bingocounter(userboard);	// ���� ���� Ȯ��
		compbingo = bingocounter(compboard);
		trial ++ ;
	} while (userbingo < 5 && compbingo < 5);	// end of do-while(�������)

	if (compbingo >= 5 && userbingo >= 5) printf("\n �����ϴ�.\n");
	else if(compbingo < 5 && userbingo >= 5) printf("\n ���� �¸�!\n");
	else printf("\n ��ǻ�� �¸�!\n");

	printf("��ǻ���� �������� �̷����ϴ�.\n");
	printboard(compboard);
	printf("������ ��: %d", compbingo);
	printf("\n");
	printf("������ �������� �̷����ϴ�.\n");
	printboard(userboard);
	printf("������ ��: %d", userbingo);
	printf("\n");

	printf("\n20224382 �ȼ���\n");
}