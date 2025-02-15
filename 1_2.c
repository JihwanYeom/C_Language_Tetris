#include <stdio.h>
#include <windows.h>
#include "block.h"

void drawBlock(int x, int y, int shape)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			COORD pos = { 2 * (x + j), y + i };
			SetConsoleCursorPosition(hConsoleOut, pos);
			if (blockModel[shape][i][j])
				printf("♂");
		}
	}

	//目辑 昏力
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

void eraseBlock(int x, int y)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			COORD pos = { 2 * (x + j), y + i };
			SetConsoleCursorPosition(hConsoleOut, pos);
			printf(" ");
		}
	}

	//目辑 昏力
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

int main()
{
	int t = 0;
	drawBlock(6, 6, 4);
	drawBlock(0, 10, 12);

	while (1)
	{
		Sleep(1000);
		eraseBlock(6, 6 + t);
		drawBlock(6, 6+t+1, 4);
		eraseBlock(0, 10 + t);
		drawBlock(0, 10 + t + 1, 12);


		t++;
	}
	return 0;
}