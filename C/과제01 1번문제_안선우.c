#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ladderresult(char ladder[20][4],char result[5]) {		// ��� Ȯ�� �Լ�
	char i, j, saveres;
	for (i = 19; i > -1 ; i--) {
		for (j = 0; j < 4; j++) {		// -�� �ִ� ���� �ش��ϴ� ������ ��+1�� ��ġ�� �ش��ϴ� ���� ����ġ
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
	char result[5] = { 65,66,67,68,69 };	// ��� �迭

	char i, j, r, linecount = 0;
	char minline = 15;		// �ּ� 15�� ����

	while (linecount < minline) {		// ��ٸ� ����
		i = rand() % 20;		// rand �Լ� ��� �ּ�ȭ�� ����
		j = rand() % 4;

		if (ladder[i][j]!=45) {		// �ش� ��ġ�� ���μ��� ������
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
	
	ladderresult(ladder,result);	// ��� Ȯ�� �Լ�

	printf("1  2  3  4  5\n");		// ��ٸ� ���
	for (i=0;i<20;i++){
		for (j = 0; j < 4; j++) {
			printf("|");

			if (ladder[i][j] != 45) {	// �迭 ��ĭ ä���
				ladder[i][j] = 32;
			}

			for (r = 0; r < 2; r++) {		// �������� ���ٷ� ǥ����
				printf("%c", ladder[i][j]);
			}
		}
		printf("|\n");
	}
	printf("A  B  C  D  E\n");

	for (i = 0; i < 5; i++) {		// ���� ��� ǥ��
		printf("%d -> %c\n", i + 1, result[i]);
	}

	printf("\n20224382 �ȼ���\n");
}