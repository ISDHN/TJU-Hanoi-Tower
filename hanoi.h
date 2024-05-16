#pragma once
#include "cmd_console_tools.h"
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <iostream>
/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */
/*定义汉诺塔常量*/
#define GRAPHIC_X 16
#define GRAPHIC_Y 16
#define TOWER_SEPA 32
#define HANOI_HEIGHT 12
#define BASE_WIDTH 25
/*定义边框常量*/
#define Height 40

int ShowMenu();

void Hanoi(int choose);