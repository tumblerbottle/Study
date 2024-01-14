#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct BOOK {
	char title[50];
	char author[30];
	char publisher[20];
	char current;	// 0: 대출 가능, 1: 대출 중
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

	char work, bookcount = 5, usercount = 5, flag = 0, temp[50], historycount = 0;
	struct BOOK* ptr1 = NULL;
	struct USER* ptr2 = NULL;
	struct BORROW* ptr3 = NULL;

	while (flag == 0) {
		printf("원하는 업무를 고르세요. \n1: 도서 추가 / 2: 회원 추가 / 3: 도서 대출 / 4: 도서 반납 / \n5: 도서 보유 현황 / 6: 대출 현황 / 7: 프로그램 종료\n");
		scanf("%hhd", &work);
		getchar();

		switch (work) {
		case(1):	// 도서 추가
			printf("1번 '도서 추가'를 누르셨습니다.\n");
			if (bookcount >= 100) {
				printf("저장 가능한 도서 수 한도를 초과했습니다.\n\n");
				break;
			}
			printf("- 추가할 도서의 제목을 입력하세요.\n");
			fgets(&books[bookcount].title, 50, stdin);
			books[bookcount].title[strcspn(books[bookcount].title, "\n")] = '\0';	// 개행문자 제거

			printf("- 추가할 도서의 저자명을 입력하세요.\n");
			fgets(&books[bookcount].author, 30, stdin);
			books[bookcount].author[strcspn(books[bookcount].author, "\n")] = '\0';

			printf("- 추가할 도서의 출판사명을 입력하세요.\n");
			fgets(&books[bookcount].publisher, 20, stdin);
			books[bookcount].publisher[strcspn(books[bookcount].publisher, "\n")] = '\0';

			books[bookcount].current = 0;
			bookcount++;
			printf("도서 추가가 완료되었습니다.\n\n");
			break;


		case(2):	// 회원 추가
			printf("2번 '회원 추가'를 누르셨습니다.\n");
			if (usercount > 100) {
				printf("저장 가능한 회원 수 한도를 초과했습니다.\n\n");
				break;
			}
			printf("- 추가할 회원의 이름을 입력하세요.\n");
			fgets(&users[usercount].name, 30, stdin);
			users[usercount].name[strcspn(users[usercount].name, "\n")] = '\0';

			printf("- 추가할 회원의 전화번호를 입력하세요.\n");
			fgets(&users[usercount].phone, 15, stdin);
			users[usercount].phone[strcspn(users[usercount].phone, "\n")] = '\0';

			usercount++;
			printf("회원 추가가 완료되었습니다.\n\n");
			break;


		case(3):	// 도서 대출
			printf("3번 '도서 대출'을 누르셨습니다.\n");
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
		


		case(4):	// 도서 반납
			printf("4번 '도서 반납'을 누르셨습니다.\n");
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


		case(5):	// 도서 보유 현황 출력
			printf("5번 '도서 보유 현황'을 누르셨습니다.\n");
			for (char i = 0; i < bookcount; i++) {
				printf("  %d) %s // %s // %s //", i+1, books[i].title, books[i].author, books[i].publisher);
				if (books[i].current == 1) printf(" (대출중)\n");
				else printf(" (보유중)\n");
			}
			printf("\n");
			break;

		case(6):	// 대출 현황 출력
			printf("6번 '대출 현황'을 누르셨습니다.\n");
			for (char i = 0; i < historycount; i++) {
				printf("  %d) %s // %s(%s) // %s // %s\n", i+1 ,history[i].book->title, history[i].borrower->name, history[i].borrower->phone, history[i].borrowdate, history[i].returnornot);
			}
			printf("\n");
			break;
		

		case(7):
			printf("7번 '프로그램 종료'를 누르셨습니다.\n");
			printf("- 사용해 주셔서 감사합니다.\n");
			flag = 1;
			break;
		}
	}

	printf("\n\n20224382 안선우\n");
}