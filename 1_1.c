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
			COORD pos = { 2*(x+j), y + i };
			SetConsoleCursorPosition(hConsoleOut, pos);
			if(blockModel[shape][i][j])
				printf("бс");
		}
	}
	
}

int main()
{
	drawBlock(6, 6, 4);
	drawBlock(0, 10, 12);
	return 0;
}