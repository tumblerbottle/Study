#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
	FILE* pFile;
	char str3[50], str2[50];
	char line[80];
	char* past[100], *ptr= NULL;	// �̹� ���� �ܾ��� �����͸� �����ϴ� ����
	char check = 0, miss = 0, score = 0, round = 0, wrong = 1;

	srand(time(NULL));
	pFile = fopen("dict_test.txt", "r");

	if (pFile == NULL) {
		printf("������ �� �� �����ϴ�.\n");
		exit(1);
	}

	while (miss < 3) {
		printf("%d ����\n", round + 1);
		if (round == 0) {
			while (check < rand() % 1000) {		// ��ǻ�� �ܾ� ����
				fgets(line, 80, pFile);
				ptr = strtok(line, " :");
			}
			printf("��ǻ��: %s\n", ptr);
			strcpy(str2, ptr);
		}
		check = 0;
		wrong = 1;

		fseek(pFile, 0, SEEK_SET);
		printf("�ܾ��? ");
		scanf("%s", str3);
		past[round] = malloc(strlen(str3) + 1);
		strcpy(past[round],str3);
		round++;

		if (str2[strlen(str2)-1] == str3[0]) check++;	// �����ձ����� Ȯ��
		else printf("�߸��� �����ձ��Դϴ�.\n");

		if (strlen(str3) > 2 && strlen(str3) < 11) {		// �ܾ� ���� Ȯ��
			check++;
		}
		else printf("�ܾ��� ���̰� �߸��Ǿ����ϴ�.\n");

		if (round < 2) check++;
		for (char i = 0; i < round-1; i++) {		// �̹� �Է��� �ܾ����� Ȯ��
			if (strcmp(past[i], str3) == 0) printf("�̹� ���� �ܾ��Դϴ�.\n");
			else check++;
		}

		while (fgets(line, 80, pFile) != NULL) {	// ���� �ִ� �ܾ�����
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
		if (wrong == 1) printf("���� �ܾ��Դϴ�.\n");

		if (((round==1) && (check - round) == 3) || ((check - round) == 2)) score++;
		else miss++;

		printf("�������� %d ��\n\n", score);
		strcpy(str2, str3);
	}

	fclose(pFile);
	return 0;
}