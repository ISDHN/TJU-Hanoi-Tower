#include "hanoi.h"
#include <math.h>
using namespace std;

/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
int steps;
int speed;
int stacks[3][10];
int tops[3];

void init();
void time();

void push(char dst, int val);
int pop(char src);

void input(char *src, char *dst, int *n, bool speed_controled);
void output(char src, char dst, int val, int kind);

void printstacks();
void print_tower();

void init_tower();
void init_disks(char src, int n);
void move_disk(int kind, char src, char dst);
void interaction();
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hanoi_internal(int n, int output_kind, char src, char tmp, char dst) {
	bool last = n == 1;
	if (!last) {
		hanoi_internal(n - 1, output_kind, src, dst, tmp);
	}
	int val = pop(src);
	push(dst, val);
	output(src, dst, val, output_kind);
	if (!last) {
		hanoi_internal(n - 1, output_kind, tmp, src, dst);
	}
}

void hanoi_base(int choose) {
	cout << endl
		 << endl
		 << endl;
	init();
	char src, dst;
	int n = 0;
	if (choose == 5) {
		cct_cls();
		init_tower();
		return;
	}
	input(&src, &dst, &n, choose == 4);
	char med = 'A' + 'B' + 'C' - src - dst;
	for (int i = n; i > 0; i--) {
		push(src, i);
	}
	if (choose > 5) {
		cct_cls();
		init_tower();
		init_disks(src, n);
	}
	if (choose < 5 || choose == 8) {
		if (choose == 4) {
			print_tower();
			cout << "Init: ";
			printstacks();
			cout << endl;
		}
		hanoi_internal(n, choose, src, med, dst);
	} else {
		if (choose == 7) {
			int next = n & 1 ? dst : med;
			int val = pop(src);
			push(next, val);
			output(src, next, val, choose);
		} else if (choose == 9) {
			interaction();
		}
	}
}

void init() {
	steps = 0;
	for (int i = 0; i < 3; i++) {
		memset(stacks[i], 0, 10);
		tops[i] = 0;
	}
}

void time() {
	if (speed == 0) {
		while (_getch() != '\r')
			;
	} else {
		Sleep(1024 - speed * 128);
	}
}

void push(char dst, int val) {
	int index = dst - 'A';
	stacks[index][tops[index]] = val;
	tops[index]++;
}

int pop(char src) {
	int index = src - 'A';
	tops[index]--;
	return stacks[index][tops[index]];
}

void input(char *src, char *dst, int *n, bool speed_controled) {
	cout << "Please input the height of Hanoi tower(1-10): " << endl;
	cin >> *n;
	while (cin.good() == 0 || *n < 0 || *n > 10) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin.ignore(INT_MAX, '\r');
		cout << "Please input the height of Hanoi tower(1-10): " << endl;
		cin >> *n;
	}
	cout << "Start column(A-C): " << endl;
	cin >> *src;
	while (*src < 'A' || *src > 'C') {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin.ignore(INT_MAX, '\r');
		cout << "Start column(A-C): " << endl;
		cin >> *src;
	}
	cout << "Destination column(A-C): " << endl;
	cin >> *dst;
	while (*dst == *src || *dst < 'A' || *dst > 'C') {
		if (*dst == *src) {
			cout << "Start column(" << *src << ") can't be the same with the destination column(" << *dst << ")! " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin.ignore(INT_MAX, '\r');
			cout << "Destination column(A-C): " << endl;
			cin >> *dst;
		} else {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin.ignore(INT_MAX, '\r');
			cout << "Destination column(A-C): " << endl;
			cin >> *dst;
		}
	}
	if (speed_controled) {
		cout << "Please input the moving speed(0-5: 0-press enter to move 1-Slowest 5-Fastest)" << endl;
		cin >> speed;
		while (cin.good() == 0 || speed > 5 || speed < 0) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> speed;
		}
	}
}

void output(char src, char dst, int val, int kind) {
	steps++;
	if (kind == 1) {
		cout << setw(2) << val << "# " << src << "-->" << dst << endl;
	} else if (kind >= 2 && kind <= 4) {
		if (kind == 4) {
			print_tower();
		}
		cout << "The" << setw(4) << steps << "th step(" << setw(2) << val << "#: " << src << "-->" << dst << ")";
		if (kind >= 3) {
			printstacks();
		}
		cout << endl;
	} else if (kind >= 7) {
		move_disk(val, src, dst);
	}
}

void printstacks() {
	for (int i = 0; i < 3; i++) {
		cout << " " << char(i + 'A') << ":";
		for (int j = 0; j < tops[i]; j++) {
			cout << setw(2) << stacks[i][j];
		}
		int blanks = (10 - tops[i]) * 2;
		for (int j = 0; j < blanks; j++) {
			cout << " ";
		}
	}
}

void print_tower() {
	time();
	cct_gotoxy(0, 0);
	cct_cls();
	cct_gotoxy(10, 13);
	cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTT" << endl;
	cct_gotoxy(12, 14);
	cout << "A         B         C ";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < tops[i]; j++) {
			cct_gotoxy(10 + 10 * i, 12 - j);
			cout << setw(2) << stacks[i][j];
		}
	}
	cct_gotoxy(10, 17);
}

void init_tower() {
	for (int i = 0; i < 3; i++) {
		cct_showch(GRAPHIC_X + i * TOWER_SEPA - 12, GRAPHIC_Y + 1, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 25);
		for (int j = 0; j <= HANOI_HEIGHT; j++) {
			cct_showch(GRAPHIC_X + TOWER_SEPA * i, GRAPHIC_Y - j, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		}
	}

	cct_gotoxy(0, Height - 1);
	cct_setcolor(0, 7);
}

void init_disks(char src, int n) {
	int Start = (src - 'A') * TOWER_SEPA;
	for (int i = n; i > 0; i--) {
		cct_showch(GRAPHIC_X + Start - i, GRAPHIC_Y + i - n, ' ', i, i, i * 2 + 1);
		Sleep(50);
	}
	cct_gotoxy(0, Height - 1);
	cct_setcolor(0, 7);
}

void move_disk(int kind, char src, char dst) {
	int src_index = src - 'A';
	int dst_index = dst - 'A';
	int distance = dst - src;
	int space = src_index * TOWER_SEPA;

	int floor = tops[src_index];
	for (int i = 0; i + floor < GRAPHIC_Y - 1; i++) {
		cct_showch(GRAPHIC_X - kind + space, GRAPHIC_Y - floor - i, ' ', COLOR_BLACK, COLOR_BLACK, 2 * kind + 1);
		if (i + floor <= HANOI_HEIGHT) {
			cct_showch(GRAPHIC_X + space, GRAPHIC_Y - floor - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		}
		cct_showch(GRAPHIC_X - kind + space, GRAPHIC_Y - floor - i - 1, ' ', kind, kind, 2 * kind + 1);
		Sleep(100);
	}

	int length = distance * TOWER_SEPA;
	int direction = distance > 0 ? 1 : -1;
	for (int j = 0; abs(j) <= abs(length); j += direction) {
		cct_showch(GRAPHIC_X + space - kind + j - direction, 1, ' ', COLOR_BLACK, COLOR_BLACK, 2 * kind + 1);
		cct_showch(GRAPHIC_X + space - kind + j, 1, ' ', kind, kind, 2 * kind + 1);
		Sleep(100);
	}

	for (int i = 0; i + tops[dst_index] <= GRAPHIC_Y; i++) {
		cct_showch(GRAPHIC_X + space - kind + length, i, ' ', COLOR_BLACK, COLOR_BLACK, 2 * kind + 1);
		if (i >= GRAPHIC_Y - HANOI_HEIGHT) {
			cct_showch(GRAPHIC_X + space + length, i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		}
		cct_showch(GRAPHIC_X + space - kind + length, 1 + i, ' ', kind, kind, 2 * kind + 1);
		Sleep(100);
	}

	cct_gotoxy(0, 35);
	cct_setcolor(0, 7);
}

void interaction() {
	while (true) {
		cct_gotoxy(0, 20);
		cin.clear();
		cout << "How to move:(uasge example：AC= move the top of A to C，Q=exit): ";
		cout << "                                                                    ";
		cct_gotoxy(64, 20);

		char src, dst;
		cin >> src;
		if (src == 'Q' || src == 'q') {
			cout << "Game end." << endl;
			return;
		}
		cin >> dst;

		if (src < 'A' || src > 'C' || dst < 'A' || dst > 'C') {
			continue;
		}

		if (src == dst) {
			continue;
		}

		int src_index = src - 'A';
		if (tops[src_index] == 0) {
			continue;
		}

		int dst_index = dst - 'A';
		if (tops[dst_index] == 0 || stacks[src_index][tops[src_index] - 1] < stacks[dst_index][tops[dst_index] - 1]) {
			int val = pop(src);
			push(dst, val);
			output(src, dst, val, 9);
		}
	}
}
