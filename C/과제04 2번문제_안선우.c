#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct CITY {
	char name[10];
	char owner;
};
struct PLAYER {
	int money;
	char place;	// 마지막에 머무른 장소
};

char turn(struct PLAYER *player, struct CITY *cities, char dice, char info) {
	if ((*player).place + dice > 9) (*player).place = (*player).place + dice - 10;
	else (*player).place += dice;

	printf("\n%s ", cities[(*player).place].name);
	if (cities[(*player).place].owner == 3) {				// 시작 포인트로 돌아옴
		printf("(시작포인트)\n");
		printf("player %d의 잔고 %d\n\n", info, (*player).money);
	}
	else if (cities[(*player).place].owner == (3-info)) {	// 타인 소유 도시에 들어감 -> 통행세 납부
		printf("(%d)\n",3-info);
		if ((*player).money >= 600) {
			printf("통행세 600원을 납부합니다. \n");
			(*player).money -= 600;
			printf("player %d의 잔고 %d\n\n", info, (*player).money);
			return 4;										// return 4 -> 타인에게 돈 주기
		}
		else {		// 통행세 납부 불가능
			printf("통행세를 납부할 수 없습니다. (원인: 잔고부족) \n");
			printf("player %d의 잔고 %d\n\n", info, (*player).money);
			return 5;										// return 5 -> 잔고부족 상황
		}
	}
	else if (cities[(*player).place].owner == 0) {			// 빈 도시에 들어감 -> 구입가능 여부
		printf("(주인없음)\n");
		if ((*player).money >= 300) {		// 구입가능
			printf("player %d가 %s를 구입합니다. \n",info, cities[(*player).place].name);
			(*player).money -= 300;
			cities[(*player).place].owner = info;
			printf("player %d의 잔고 %d\n\n", info, (*player).money);
		}
		else {			// 구입 불가능
			printf("%s을 구매할 수 없습니다. (원인: 잔고부족) \n", cities[(*player).place].name);
			printf("player %d의 잔고 %d\n\n", info, (*player).money);		// 빈도시 구매 불가라도 계속 진행
		}
	}
	else {			// 자신 소유의 도시에 들어감.
		printf("(%d)\n",info);
		printf("player %d의 잔고 %d\n\n", info, (*player).money);
	}
	return 1; // default return 값 -> 아무 의미 없음.
}


int main() {
	struct PLAYER p1 = { 5000,0 }, p2 = { 5000,0 };
	struct CITY cities[] = {
		{"Start",3},{"Seoul",0},{"Tokyo",0},{"Sydney",0},{"LA",0},{"Paris",0},{"Hanoi",0},{"New Delhi",0},{"Phuket",0},{"Cairo",0}
	};
	char round = 1, dice = 0, flag = 0;

	srand(time(NULL));

	while (round < 31) {
		printf("%d번째 라운드\n", round);
		dice = rand() % 6 + 1;
		printf("player 1의 주사위: %d", dice);
		flag = turn(&p1, &cities, dice, 1);
		if (flag == 5) {
			printf("player 2가 승리했습니다.");
			break;
		}
		if (flag==4) p2.money += 600;	// return = 4 인 경우.


		dice = rand() % 6 + 1;
		printf("player 2의 주사위: %d", dice);
		flag = turn(&p2, &cities, dice, 2);
		if (flag == 5) {
			printf("player 1이 승리했습니다.");
			break;
		}
		if (flag==4) p1.money += 600;
		round++;
	}

	if (round == 31) {		// 중도 탈락하지 않고 30회를 모두 진행한 경우, 남은 자산이 가장 많은 플레이어 승리
		if (p1.money > p2.money) printf("player 1의 잔고가 더 많습니다. player 1이 승리했습니다.");
		else if (p1.money < p2.money) printf("player 2의 잔고가 더 많습니다. player 2가 승리했습니다.");
		else printf("player 1과 2의 잔고가 동일합니다. 무승부입니다.");
	}

	printf("\n\n20224382 안선우\n\n");
	
}