#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void reverse(char ori[]) {		// ���ڿ��� ������ �ִ� �Լ�.
	int len = strlen(ori);
	char temp;
	for (char i = 0; i < len / 2; i++) {
		temp = ori[i];
		ori[i] = ori[len - i - 1];
		ori[len - i - 1] = temp;
	}
}
 
void adder(char x[], char y[], char add[]) {	// X+Y �Լ�
	char lenx = strlen(x), leny = strlen(y);
	char length, temp = 0;
	if (lenx >= leny) length = lenx;	// �� ���̰� �� ���ڹ��ڿ��� �������� ��
	else leny;
	
	reverse(x);
	reverse(y);

	for (char i = 0; i <length ; i++) {
		char digitx = 0, digity = 0;	// ���� �� ���ڿ��� �ٸ� �ͺ��� �� ���, ���� �κ��� 0���� ������.
		if (lenx > i) digitx = x[i] - '0';
		if (leny > i) digity = y[i] - '0';

		temp += digitx + digity;
		add[i] = (temp % 10) + '0';	// ������ �κи� �����ϰ�, 10�� �ڸ� �κ��� ���� �������� �ѱ��
		temp /= 10;
	}
	if (temp > 0) {		// add�� �������� \0�� �ֱ� ����.
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

	if ((lenx < leny) || (lenx == leny && strcmp(x, y) < 0)) {		// �ݵ�� �տ� ���� ���� ū ������ ��.
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

		if ((digitx-checkflag) < digity) {	// 10�� �������� ���
			sub[i] = (digitx + 10 - digity - checkflag) + '0';
			checkflag = 1;
		}
		else {
			sub[i] = (digitx - digity - checkflag) + '0';
			checkflag = 0;
		}
	}
	if (strcmp(left, right) == 0) strcpy(sub,"0\0");	// x,y�� ������ ���.
	while (lenx > 0 && sub[lenx - 1] == '0') {	// sub�� �������� \0�� �ֱ� ����.
		lenx--;
	}
	sub[lenx] = '\0';
	reverse(sub);
	return minus;	// ��ȣ �ʿ� ���θ� ��ȯ
}


int main() {
	char x[82];
	char y[82];
	char add[83];
	char sub[83];
	char minus;

	while (1) {
		printf("x�� �Է��ϼ���. (80�� ����) \n");
		fgets(x, sizeof(x), stdin);
		printf("y�� �Է��ϼ���. (80�� ����) \n");
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