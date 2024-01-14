#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>

int main() {
	char i;

	for (i = 0; i < 5; i++) {
		short year = 1970;		// 컴퓨터는 1970.1.1. 부터 계산함
		char month, date, hour, min, sec;
		char monthlist[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int spentsec;

		spentsec = time(NULL);
		sec = spentsec % 60;
		spentsec /= 60;		// 분 단위로 수정

		min = spentsec % 60;
		spentsec = spentsec / 60 + 9;		// UTC+9:00 시간대 시간 단위로 수정, 

		hour = spentsec % 24;
		spentsec = spentsec / 24 + 1;	// 날짜 단위로 수정

		while (spentsec > 365) {
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {		// 윤년 고려해서 연도-월-날짜 순으로 계산
				spentsec -= 366;
				year++;
			}
			else {
				spentsec -= 365;
				year++;
			}
		}

		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {		// 윤년 - 2월은 29일까지 있음
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

		printf("현재시각은 %d년 %d월 %d일 %d시 %d분 %d초 입니다\n", year, month, date, hour, min, sec);
		Sleep(1000);	// 시간 지연
	}

	printf("\n20224382 안선우\n");
}