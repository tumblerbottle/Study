#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ladderresult(char ladder[40][4], char result[5]) {		// ��� Ȯ�� �Լ�
	char i, j, saveres;
	for (i = 19; i > -1; i--) {
		for (j = 0; j < 4; j++) {		// -�� �ִ� ���� �ش��ϴ� ������ ��+1�� ��ġ�� �ش��ϴ� ���� ����ġ
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

	while (linecount < minline) {		// ��ٸ� ����
		i = rand() % 20;		// rand �Լ� ��� �ּ�ȭ�� ����
		j = rand() % 4;

		if (ladder[i][j] != 45) {		// �ش� ��ġ�� ���μ��� ������
			if ((j == 0 && ladder[i][j + 1] != 45)
				|| (j == 3 && ladder[i][j - 1] != 45)
				|| (ladder[i][j - 1] != 45 && ladder[i][j + 1] != 45)) {	// �ӿ��� ���μ��� �ƴϸ鼭

				if ((i < 2) ||
					!(ladder[i - 1][j] == 45 && ladder[i - 2][j] != 45)) {	// �������� ���Ʒ��� ���� �̻� ������ �ʰ� ��.

					ladder[i][j] = 45;
					linecount++;
				}
			}
		}
	}

	ladderresult(ladder, result);	// ��� Ȯ�� �Լ�
}

int main() {
	srand(time(NULL));

	short speresult[5][5] = { 0, };	// ���� ��� ����  
	// speresult[�ش� result �迭�� index][����� ������ ����]
	char i, j, r;
	char minline = 33;		// �ּ� 33�� ���� - ���μ��� �������� �յ��� ����� ������ �� �ϴ�
	short try = 0;	// ��ٸ� ���� Ƚ��

	while (try < 1000) {
		char result[5] = { 65,66,67,68,69 };	// ��� �迭
		laddermaker(result, minline);

		for (i = 0; i < 5; i++) {		// speresult�� ���� ��� ����
			speresult[i][result[i] - 65]++;
		}

		try++;
	}

	for (i = 0; i < 5; i++) {		// ��ü ��� ���
		printf("%d : ", i + 1);
		for (j = 0; j < 5; j++) {
			printf("%c(%d) ", j + 65, speresult[i][j]);
		}
		printf(" : 1000\n");
	}

	printf("\n20224382 �ȼ���\n");
}