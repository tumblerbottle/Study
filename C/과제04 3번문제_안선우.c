#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct BOOK {	// 책 정보 저장
	char title[50];
	char author[30];
	char publisher[20];
	char current;	// 0: 대출 가능, 1: 대출 중
};

struct USER {	// 회원 정보 저장
	char name[30];
	char phone[15];
};

struct BORROW {		// 대출.반납 기록 저장
	struct BOOK* book;
	struct USER* borrower;
	char borrowdate[10];
	char returnornot[10];
};

int main() {
	struct BOOK books[100] = {
		{"(클라우스 슈밥의) 제4차 산업혁명","Schwab, Klaus","새로운현재",0},
		{"걸리버 여행기","Swift, Jonathan","문예출판사",0},
		{"노인과 바다","Hemingway, Ernest","문학동네",0},
		{"마음","하목수석","문예출판사",0},
		{"피로사회","한병철","문학과지성사",0},
	};
	struct USER users[100] = {
		{"가가가","010-1111-2222"},
		{"나나나","010-2222-3333"},
		{"다다다","010-3333-4444"},
		{"라라라","010-4444-5555"},
		{"마마마","010-5555-6666"},
	};
	struct BORROW history[100];

	char work, bookcount = 5, usercount = 5, temp[50], historycount = 0;
	struct BOOK* ptr1 = NULL;
	struct USER* ptr2 = NULL;
	struct BORROW* ptr3 = NULL;

	while (1) {
		printf("원하는 업무를 고르세요. \n1: 도서 대출 / 2: 도서 반납 / 3: 도서 보유 현황 / 4: 대출 현황\n");
		scanf("%hhd", &work);
		getchar();

		switch (work) {
		case(1):	// 도서 대출
			printf("1번 '도서 대출'을 누르셨습니다.\n");
			ptr1 = NULL;
			ptr2 = NULL;
			printf("- 대출 할 책 제목을 입력하세요.\n");
			fgets(temp, 50, stdin);
			temp[strcspn(temp, "\n")] = '\0';

			for (char i = 0; i < bookcount; i++) {		// 도서 DB에 해당 책이 있는지 찾기
				if (strcmp(temp, books[i].title) == 0) {
					ptr1 = &books[i];
					break;
				}
			}
			if (ptr1 == NULL) {			// 책이 DB에 존재하지 않음
				printf("** 잘못된 책 제목입니다. \n\n");
				break;
			}
			if (ptr1->current == 1) {
				printf("** 대출 중인 책입니다.\n\n");	// 이미 대출중인 책일 때
				break;
			}


			printf("- 빌릴 회원 이름을 입력하세요.\n");
			fgets(temp, 30, stdin);
			temp[strcspn(temp, "\n")] = '\0';
			for (char i = 0; i < usercount; i++) {		// 회원 DB에 회원명이 존재하는지 확인
				if (strcmp(temp, users[i].name) == 0) {
					ptr2 = &users[i];
					break;
				}
			}
			if (ptr2 == NULL) {
				printf("** 잘못된 회원명입니다. \n\n");
				break;
			}

			printf("- 오늘 날짜를 입력하세요. 예)20231202 \n");
			fgets(&history[historycount].borrowdate, 10, stdin);
			history[historycount].borrowdate[strcspn(history[historycount].borrowdate, "\n")] = '\0';
			strcpy(history[historycount].returnornot, "대출중");

			ptr1->current = 1;
			history[historycount].book = ptr1;
			history[historycount].borrower = ptr2;
			historycount++;
			printf("대출이 완료되었습니다. \n\n");
			break;



		case(2):	// 도서 반납
			printf("2번 '도서 반납'을 누르셨습니다.\n");
			ptr1 = NULL;
			ptr3 = NULL;
			printf("- 반납 할 책 제목을 입력하세요.\n");
			fgets(temp, 50, stdin);
			temp[strcspn(temp, "\n")] = '\0';

			for (char i = 0; i < bookcount; i++) {		// 도서 DB에 해당 책이 있는지 찾기
				if (strcmp(temp, books[i].title) == 0) {
					ptr1 = &books[i];
					break;
				}
			}
			if (ptr1 == NULL) {			// 책이 DB에 존재하지 않음
				printf("** 잘못된 책 제목입니다. \n\n");
				break;
			}

			if (ptr1->current != 1) {
				printf("** 대출하지 않은 책입니다.\n\n");
				break;
			}

			for (char i = 0; i < historycount; i++) {		// 대출 DB에 해당 책이 있는지 찾기
				if (strcmp(temp, history[i].book) == 0) {
					ptr3 = &history[i];
					break;
				}
			}
			ptr1->current = 0;
			printf("- 오늘 날짜를 입력하세요. 예)20231202 \n");
			fgets(ptr3->returnornot, 10, stdin);
			ptr3->returnornot[strcspn(ptr3->returnornot, "\n")] = '\0';
			printf("반납이 완료되었습니다. \n\n");
			break;


		case(3):	// 도서 보유 현황 출력
			printf("3번 '도서 보유 현황'을 누르셨습니다.\n");
			for (char i = 0; i < bookcount; i++) {
				printf("  %d) %s // %s // %s //", i + 1, books[i].title, books[i].author, books[i].publisher);
				if (books[i].current == 1) printf(" (대출중)\n");
				else printf(" (보유중)\n");
			}
			printf("\n");
			break;


		case(4):	// 대출 현황 출력
			printf("4번 '대출 현황'을 누르셨습니다.\n");
			for (char i = 0; i < historycount; i++) {
				printf("  %d) %s // %s(%s) // %s // %s\n", i + 1, history[i].book->title, history[i].borrower->name, history[i].borrower->phone, history[i].borrowdate, history[i].returnornot);
			}
			printf("\n");
			break;
		}
	}

	printf("\n\n20224382 안선우\n");
}