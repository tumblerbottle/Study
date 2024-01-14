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
	char place;	// �������� �ӹ��� ���
};

char turn(struct PLAYER *player, struct CITY *cities, char dice, char info) {
	if ((*player).place + dice > 9) (*player).place = (*player).place + dice - 10;
	else (*player).place += dice;

	printf("\n%s ", cities[(*player).place].name);
	if (cities[(*player).place].owner == 3) {				// ���� ����Ʈ�� ���ƿ�
		printf("(��������Ʈ)\n");
		printf("player %d�� �ܰ� %d\n\n", info, (*player).money);
	}
	else if (cities[(*player).place].owner == (3-info)) {	// Ÿ�� ���� ���ÿ� �� -> ���༼ ����
		printf("(%d)\n",3-info);
		if ((*player).money >= 600) {
			printf("���༼ 600���� �����մϴ�. \n");
			(*player).money -= 600;
			printf("player %d�� �ܰ� %d\n\n", info, (*player).money);
			return 4;										// return 4 -> Ÿ�ο��� �� �ֱ�
		}
		else {		// ���༼ ���� �Ұ���
			printf("���༼�� ������ �� �����ϴ�. (����: �ܰ����) \n");
			printf("player %d�� �ܰ� %d\n\n", info, (*player).money);
			return 5;										// return 5 -> �ܰ���� ��Ȳ
		}
	}
	else if (cities[(*player).place].owner == 0) {			// �� ���ÿ� �� -> ���԰��� ����
		printf("(���ξ���)\n");
		if ((*player).money >= 300) {		// ���԰���
			printf("player %d�� %s�� �����մϴ�. \n",info, cities[(*player).place].name);
			(*player).money -= 300;
			cities[(*player).place].owner = info;
			printf("player %d�� �ܰ� %d\n\n", info, (*player).money);
		}
		else {			// ���� �Ұ���
			printf("%s�� ������ �� �����ϴ�. (����: �ܰ����) \n", cities[(*player).place].name);
			printf("player %d�� �ܰ� %d\n\n", info, (*player).money);		// �󵵽� ���� �Ұ��� ��� ����
		}
	}
	else {			// �ڽ� ������ ���ÿ� ��.
		printf("(%d)\n",info);
		printf("player %d�� �ܰ� %d\n\n", info, (*player).money);
	}
	return 1; // default return �� -> �ƹ� �ǹ� ����.
}


int main() {
	struct PLAYER p1 = { 5000,0 }, p2 = { 5000,0 };
	struct CITY cities[] = {
		{"Start",3},{"Seoul",0},{"Tokyo",0},{"Sydney",0},{"LA",0},{"Paris",0},{"Hanoi",0},{"New Delhi",0},{"Phuket",0},{"Cairo",0}
	};
	char round = 1, dice = 0, flag = 0;

	srand(time(NULL));

	while (round < 31) {
		printf("%d��° ����\n", round);
		dice = rand() % 6 + 1;
		printf("player 1�� �ֻ���: %d", dice);
		flag = turn(&p1, &cities, dice, 1);
		if (flag == 5) {
			printf("player 2�� �¸��߽��ϴ�.");
			break;
		}
		if (flag==4) p2.money += 600;	// return = 4 �� ���.


		dice = rand() % 6 + 1;
		printf("player 2�� �ֻ���: %d", dice);
		flag = turn(&p2, &cities, dice, 2);
		if (flag == 5) {
			printf("player 1�� �¸��߽��ϴ�.");
			break;
		}
		if (flag==4) p1.money += 600;
		round++;
	}

	if (round == 31) {		// �ߵ� Ż������ �ʰ� 30ȸ�� ��� ������ ���, ���� �ڻ��� ���� ���� �÷��̾� �¸�
		if (p1.money > p2.money) printf("player 1�� �ܰ� �� �����ϴ�. player 1�� �¸��߽��ϴ�.");
		else if (p1.money < p2.money) printf("player 2�� �ܰ� �� �����ϴ�. player 2�� �¸��߽��ϴ�.");
		else printf("player 1�� 2�� �ܰ� �����մϴ�. ���º��Դϴ�.");
	}

	printf("\n\n20224382 �ȼ���\n\n");
	
}