#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void reverse(char ori[]) {		// 문자열을 뒤집어 주는 함수.
	int len = strlen(ori);
	char temp;
	for (char i = 0; i < len / 2; i++) {
		temp = ori[i];
		ori[i] = ori[len - i - 1];
		ori[len - i - 1] = temp;
	}
}
 
void adder(char x[], char y[], char add[]) {	// X+Y 함수
	char lenx = strlen(x), leny = strlen(y);
	char length, temp = 0;
	if (lenx >= leny) length = lenx;	// 더 길이가 긴 숫자문자열을 기준으로 함
	else leny;
	
	reverse(x);
	reverse(y);

	for (char i = 0; i <length ; i++) {
		char digitx = 0, digity = 0;	// 만약 한 문자열이 다른 것보다 긴 경우, 없는 부분은 0으로 간주함.
		if (lenx > i) digitx = x[i] - '0';
		if (leny > i) digity = y[i] - '0';

		temp += digitx + digity;
		add[i] = (temp % 10) + '0';	// 나머지 부분만 저장하고, 10의 자리 부분은 다음 덧셈으로 넘기기
		temp /= 10;
	}
	if (temp > 0) {		// add의 마지막에 \0을 넣기 위함.
		add[length] = temp + '0';
		add[length + 1] = '\0';
	}
	else add[length] = '\0';
	reverse(add);
}

char subtractor(char x[], char y[], char sub[]) {
	char lenx = strlen(x), leny = strlen(y), minus = 0, checkflag = 0;
	char* left, * right;
	reverse(x);
	reverse(y);

	if ((lenx < leny) || (lenx == leny && strcmp(x, y) < 0)) {		// 반드시 앞에 오는 수가 큰 것으로 함.
		char temp = lenx;
		lenx = leny;
		leny = temp;
		left = y;
		right = x;
		minus++;
	}
	else {
		left = x;
		right = y;
	}

	reverse(x);
	reverse(y);

	for (char i = 0; i < lenx; i++) {
		char digitx = 0, digity = 0;
		if (lenx > i) digitx = left[i] - '0';
		if (leny > i) digity = right[i] - '0';

		if ((digitx-checkflag) < digity) {	// 10을 빌려오는 경우
			sub[i] = (digitx + 10 - digity - checkflag) + '0';
			checkflag = 1;
		}
		else {
			sub[i] = (digitx - digity - checkflag) + '0';
			checkflag = 0;
		}
	}
	if (strcmp(left, right) == 0) strcpy(sub,"0\0");	// x,y가 동일한 경우.
	while (lenx > 0 && sub[lenx - 1] == '0') {	// sub의 마지막에 \0을 넣기 위함.
		lenx--;
	}
	sub[lenx] = '\0';
	reverse(sub);
	return minus;	// 부호 필요 여부를 반환
}


int main() {
	char x[82];
	char y[82];
	char add[83];
	char sub[83];
	char minus;

	while (1) {
		printf("x를 입력하세요. (80자 제한) \n");
		fgets(x, sizeof(x), stdin);
		printf("y를 입력하세요. (80자 제한) \n");
		fgets(y, sizeof(y), stdin);

		x[strcspn(x, "\n")] = '\0';
		y[strcspn(y, "\n")] = '\0';

		printf("\nX: %s\nY: %s\n\n", x, y);	

		adder(x, y, add);
		printf("X + Y = %s\n",add);

		minus=subtractor(x, y, sub);
		if (minus==1) printf("X - Y = -%s\n\n", sub);
		else printf("X - Y = %s\n\n", sub);
	}
}