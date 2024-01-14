#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct BOOK {
	char title[50];
	char author[30];
	char publisher[20];
	char current;	// 0: ���� ����, 1: ���� ��
};

struct USER {
	char name[30];
	char phone[15];
};

struct BORROW {
	struct BOOK* book;
	struct USER* borrower;
	char borrowdate[10];
	char returnornot[10];
};

int main() {
	struct BOOK books[100] = {
		{"(Ŭ��콺 ������) ��4�� �������","Schwab, Klaus","���ο�����",0},
		{"�ɸ��� �����","Swift, Jonathan","�������ǻ�",0},
		{"���ΰ� �ٴ�","Hemingway, Ernest","���е���",0},
		{"����","�ϸ����","�������ǻ�",0},
		{"�Ƿλ�ȸ","�Ѻ�ö","���а�������",0},
	};
	struct USER users[100] = {
		{"������","010-1111-2222"},
		{"������","010-2222-3333"},
		{"�ٴٴ�","010-3333-4444"},
		{"����","010-4444-5555"},
		{"������","010-5555-6666"},
	};
	struct BORROW history[100];

	char work, bookcount = 5, usercount = 5, flag = 0, temp[50], historycount = 0;
	struct BOOK* ptr1 = NULL;
	struct USER* ptr2 = NULL;
	struct BORROW* ptr3 = NULL;

	while (flag == 0) {
		printf("���ϴ� ������ ������. \n1: ���� �߰� / 2: ȸ�� �߰� / 3: ���� ���� / 4: ���� �ݳ� / \n5: ���� ���� ��Ȳ / 6: ���� ��Ȳ / 7: ���α׷� ����\n");
		scanf("%hhd", &work);
		getchar();

		switch (work) {
		case(1):	// ���� �߰�
			printf("1�� '���� �߰�'�� �����̽��ϴ�.\n");
			if (bookcount >= 100) {
				printf("���� ������ ���� �� �ѵ��� �ʰ��߽��ϴ�.\n\n");
				break;
			}
			printf("- �߰��� ������ ������ �Է��ϼ���.\n");
			fgets(&books[bookcount].title, 50, stdin);
			books[bookcount].title[strcspn(books[bookcount].title, "\n")] = '\0';	// ���๮�� ����

			printf("- �߰��� ������ ���ڸ��� �Է��ϼ���.\n");
			fgets(&books[bookcount].author, 30, stdin);
			books[bookcount].author[strcspn(books[bookcount].author, "\n")] = '\0';

			printf("- �߰��� ������ ���ǻ���� �Է��ϼ���.\n");
			fgets(&books[bookcount].publisher, 20, stdin);
			books[bookcount].publisher[strcspn(books[bookcount].publisher, "\n")] = '\0';

			books[bookcount].current = 0;
			bookcount++;
			printf("���� �߰��� �Ϸ�Ǿ����ϴ�.\n\n");
			break;


		case(2):	// ȸ�� �߰�
			printf("2�� 'ȸ�� �߰�'�� �����̽��ϴ�.\n");
			if (usercount > 100) {
				printf("���� ������ ȸ�� �� �ѵ��� �ʰ��߽��ϴ�.\n\n");
				break;
			}
			printf("- �߰��� ȸ���� �̸��� �Է��ϼ���.\n");
			fgets(&users[usercount].name, 30, stdin);
			users[usercount].name[strcspn(users[usercount].name, "\n")] = '\0';

			printf("- �߰��� ȸ���� ��ȭ��ȣ�� �Է��ϼ���.\n");
			fgets(&users[usercount].phone, 15, stdin);
			users[usercount].phone[strcspn(users[usercount].phone, "\n")] = '\0';

			usercount++;
			printf("ȸ�� �߰��� �Ϸ�Ǿ����ϴ�.\n\n");
			break;


		case(3):	// ���� ����
			printf("3�� '���� ����'�� �����̽��ϴ�.\n");
			ptr1 = NULL;
			ptr2 = NULL;
			printf("- ���� �� å ������ �Է��ϼ���.\n");
			fgets(temp, 50, stdin);
			temp[strcspn(temp, "\n")] = '\0';

			for (char i = 0; i < bookcount; i++) {		// ���� DB�� �ش� å�� �ִ��� ã��
				if (strcmp(temp, books[i].title) == 0) {
					ptr1 = &books[i];
					break;
				}
			}
			if (ptr1 == NULL) {			// å�� DB�� �������� ����
				printf("** �߸��� å �����Դϴ�. \n\n");
				break;
			}
			if (ptr1->current == 1) {
				printf("** ���� ���� å�Դϴ�.\n\n");	// �̹� �������� å�� ��
				break;
			}


			printf("- ���� ȸ�� �̸��� �Է��ϼ���.\n");
			fgets(temp, 30, stdin);
			temp[strcspn(temp, "\n")] = '\0';
			for (char i = 0; i < usercount; i++) {		// ȸ�� DB�� ȸ������ �����ϴ��� Ȯ��
				if (strcmp(temp, users[i].name) == 0) {
					ptr2 = &users[i];
					break;
				}
			}
			if (ptr2 == NULL) {
				printf("** �߸��� ȸ�����Դϴ�. \n\n");
				break;
			}

			printf("- ���� ��¥�� �Է��ϼ���. ��)20231202 \n");
			fgets(&history[historycount].borrowdate, 10, stdin);
			history[historycount].borrowdate[strcspn(history[historycount].borrowdate, "\n")] = '\0';
			strcpy(history[historycount].returnornot, "������");

			ptr1->current = 1;
			history[historycount].book = ptr1;
			history[historycount].borrower = ptr2;
			historycount++;
			printf("������ �Ϸ�Ǿ����ϴ�. \n\n");
			break;
		


		case(4):	// ���� �ݳ�
			printf("4�� '���� �ݳ�'�� �����̽��ϴ�.\n");
			ptr1 = NULL;
			ptr3 = NULL;
			printf("- �ݳ� �� å ������ �Է��ϼ���.\n");
			fgets(temp, 50, stdin);
			temp[strcspn(temp, "\n")] = '\0';

			for (char i = 0; i < bookcount; i++) {		// ���� DB�� �ش� å�� �ִ��� ã��
				if (strcmp(temp, books[i].title) == 0) {
					ptr1 = &books[i];
					break;
				}
			}
			if (ptr1 == NULL) {			// å�� DB�� �������� ����
				printf("** �߸��� å �����Դϴ�. \n\n");
				break;
			}

			if (ptr1->current != 1) {
				printf("** �������� ���� å�Դϴ�.\n\n");
				break;
			}

			for (char i = 0; i < historycount; i++) {		// ���� DB�� �ش� å�� �ִ��� ã��
				if (strcmp(temp, history[i].book) == 0) {
					ptr3 = &history[i];
					break;
				}
			}
			ptr1->current = 0;
			printf("- ���� ��¥�� �Է��ϼ���. ��)20231202 \n");
			fgets(ptr3->returnornot, 10, stdin);
			ptr3->returnornot[strcspn(ptr3->returnornot, "\n")] = '\0';
			printf("�ݳ��� �Ϸ�Ǿ����ϴ�. \n\n");
			break;


		case(5):	// ���� ���� ��Ȳ ���
			printf("5�� '���� ���� ��Ȳ'�� �����̽��ϴ�.\n");
			for (char i = 0; i < bookcount; i++) {
				printf("  %d) %s // %s // %s //", i+1, books[i].title, books[i].author, books[i].publisher);
				if (books[i].current == 1) printf(" (������)\n");
				else printf(" (������)\n");
			}
			printf("\n");
			break;

		case(6):	// ���� ��Ȳ ���
			printf("6�� '���� ��Ȳ'�� �����̽��ϴ�.\n");
			for (char i = 0; i < historycount; i++) {
				printf("  %d) %s // %s(%s) // %s // %s\n", i+1 ,history[i].book->title, history[i].borrower->name, history[i].borrower->phone, history[i].borrowdate, history[i].returnornot);
			}
			printf("\n");
			break;
		

		case(7):
			printf("7�� '���α׷� ����'�� �����̽��ϴ�.\n");
			printf("- ����� �ּż� �����մϴ�.\n");
			flag = 1;
			break;
		}
	}

	printf("\n\n20224382 �ȼ���\n");
}