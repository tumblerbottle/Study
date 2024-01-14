#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {	//qsort ��
	return strcmp((char*)a,(char*)b);
}

int diffwordcounter(char input[],char norepeatword[200][50]) {	// �ߺ� �ܾ� ���� �Լ�
	int nosameword = 0;	// �ߺ� ���� �ܾ� ��
	char* token;
	char finder = 0;	// �ߺ��� �ܾ �ִ���

	token = strtok(input, " \n");

	while (token != 0) {
		finder = 0;
		for (char i = 0; i < nosameword; i++) {		// �ߺ� �ܾ ���� �ܾ��� �迭�� nosameword�� token �� ����
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
	char input2[10000] = { 0, };	// input ���� ������
	char norepeatword[200][50] = {" "};	// �ߺ����� �ʴ� �ܾ� ����� �迭 -> qsort�� ���
	int word = 0, line = 0, used = 0, norepeat = 0;		// �Էµ� �ܾ� ��/�Էµ� ���� ��/�������� ����/�ߺ��ܾ� ���� �ܾ� ��

	printf("���ϴ� ������ �Է��ϼ���. \n");
	printf("end�� �Է��ϸ� �Է��� ����˴ϴ�.\n");

	while (1) {
		fgets(input, sizeof(input), stdin);
		if (strcmp(input, "end\n") == 0) {	// �ܵ����� end �Է� �� �Է� �ߴ�
			break;
		}
		used += strlen(input);

		strncpy(input2+used-strlen(input), input,strlen(input));	// ������ �����ϱ� ����. 

		if (strchr(input, '\n') != NULL) {	// �ٹٲ��� \n���� Ȯ��
			line++;
		}

		char* token = strtok(input, " \n");		// �ܾ� �� ����
		while (token != NULL) {
			word++;
			token = strtok(NULL, " \n");
		}
	}

	norepeat = diffwordcounter(input2,norepeatword);	// �ߺ��ܾ� ���� �Լ�

	printf("\n�Էµ� ������ ��: %d\n",line);
	printf("�Էµ� �ܾ��� ��: %d\n",word);
	printf("�ߺ��� ���ŵ� �ܾ��� ��: %d\n\n",norepeat);

	qsort(norepeatword, norepeat, sizeof(norepeatword[0]), compare);

	for (char i = 0; i < norepeat; i++) {
		printf("%s\n", norepeatword[i]);
	}

	printf("\n20224382 �ȼ���\n");
}