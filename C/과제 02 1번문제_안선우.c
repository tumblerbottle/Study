#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>

int main() {
	char i;

	for (i = 0; i < 5; i++) {
		short year = 1970;		// ��ǻ�ʹ� 1970.1.1. ���� �����
		char month, date, hour, min, sec;
		char monthlist[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int spentsec;

		spentsec = time(NULL);
		sec = spentsec % 60;
		spentsec /= 60;		// �� ������ ����

		min = spentsec % 60;
		spentsec = spentsec / 60 + 9;		// UTC+9:00 �ð��� �ð� ������ ����, 

		hour = spentsec % 24;
		spentsec = spentsec / 24 + 1;	// ��¥ ������ ����

		while (spentsec > 365) {
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {		// ���� ����ؼ� ����-��-��¥ ������ ���
				spentsec -= 366;
				year++;
			}
			else {
				spentsec -= 365;
				year++;
			}
		}

		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {		// ���� - 2���� 29�ϱ��� ����
			monthlist[1] = 29;
		}

		for (month = 1; month < 13; month++) {
			if (spentsec > monthlist[month - 1]) {
				spentsec -= monthlist[month - 1];
			}
			else {
				date = spentsec;
				break;
			}
		}

		printf("����ð��� %d�� %d�� %d�� %d�� %d�� %d�� �Դϴ�\n", year, month, date, hour, min, sec);
		Sleep(1000);	// �ð� ����
	}

	printf("\n20224382 �ȼ���\n");
}