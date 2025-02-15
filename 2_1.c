#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "block.h"
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define STAGE_HEIGHT 22
#define STAGE_WIDTH 14

typedef struct Block
{
	int x, y, shape, dir;
}Block;

typedef struct Stage
{
	int width;
	int height;
	int** info;
}Stage;

Block* createBlock()
{
	Block* block = (Block*)malloc(sizeof(Block));
	block->x = 5;
	block->y = 0;
	block->shape = rand() % 6 * 4;
	block->dir = 0;
	return block;
}

void resetBlock(Block* block)
{
	block->x = 5;
	block->y = 0;
	block->shape = rand() % 6 * 4;
	block->dir = 0;
}

Stage* createStage()
{
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	stage->width = STAGE_WIDTH;
	stage->height = STAGE_HEIGHT;
	stage->info = (int**)malloc(sizeof(int*) * stage->height);
	for (int i = 0; i < stage->height; i++)
		stage->info[i] = (int*)malloc(sizeof(int) * stage->width);

	for (int i = 0; i < stage->height; i++)
		for (int j = 0; j < stage->width; j++)
			stage->info[i][j] = 0;

	for (int i = 0; i < stage->height; i++) 
	{
		stage->info[i][0] = 1;
		stage->info[i][1] = 1;
	}
	for (int i = 0; i < stage->width; i++)
	{
		stage->info[stage->height-1][i] = 1;
		stage->info[stage->height-2][i] = 1;
	}
	for (int i = 0; i < stage->height; i++)
	{
		stage->info[i][stage->width-1] = 1;
		stage->info[i][stage->width-2] = 1;
	}
	return stage;
}

void drawStage(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for (int i = 0; i < stage->height-1; i++)
	{
		pos.X = 0; pos.Y = i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("Β");
	}
	for (int i = 0; i < stage->height-1; i++)
	{
		pos.X = 2 * (stage->width-3); pos.Y = i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("Β");
	}
	
	pos.X = 0; pos.Y = stage->height-2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("Ζ");
	for (int i = 1; i < stage->height; i++)
	{
		pos.X = i; pos.Y = stage->height-2;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("Α");
	}

	pos.X = 2 * (stage->width-3); pos.Y = stage->height - 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("Ε");
}

void updateStage(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int y = 0; y < stage->height; y++)
	{
		for (int x = 2; x < stage->width - 2; x++)
		{
			if (stage->info[y][x] == 2)
			{
				COORD pos = { 2 * x - 2, y };
				SetConsoleCursorPosition(hConsoleOut, pos);
				printf("♂");
			}
		}
	}
}

int checkCollision(Block* block, Stage* stage)
{
	for (int y = 0; y <  4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[block->shape + block->dir][y][x] * stage->info[block->y+y][block->x+x] > 0)
				return 1;
		}
	}
	return 0;
}

void drawBlock(Block* block)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			COORD pos = { 2 * (block->x + j) -2, block->y + i };
			SetConsoleCursorPosition(hConsoleOut, pos);
			if (blockModel[block->shape+block->dir][i][j])
				printf("♂");
		}
	}

	//目辑 昏力
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

void eraseBlock(Block* block)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			COORD pos = { 2 * (block->x + j)-2, block->y + i };
			SetConsoleCursorPosition(hConsoleOut, pos);
			if(blockModel[block->shape+block->dir][i][j])
				printf(" ");
		}
	}

	//目辑 昏力
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

void moveBlock(Block* block,Stage* stage, int key)
{
	switch (key)
	{
	case LEFT:
		eraseBlock(block);
		block->x--;
		if (checkCollision(block, stage))
			block->x++;
		drawBlock(block);
		break;
	case RIGHT:
		eraseBlock(block);
		block->x++;
		if (checkCollision(block, stage))
			block->x--;
		drawBlock(block);
		break;
	case DOWN:
		eraseBlock(block);
		block->y++;
		if (checkCollision(block, stage))
			block->y--;
		drawBlock(block);
		break;
	case UP:
		eraseBlock(block);
		block->dir++;
		block->dir = block->dir % 4;
		if (checkCollision(block, stage))
		{
			if(block->dir == 0)
				block->dir = 3;
			else
				block->dir--;
		}
		drawBlock(block);
		break;
	}
}

void landBlock(Block* block, Stage* stage)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[block->shape + block->dir][y][x])
				stage->info[block->y + y][block->x + x] = 2;
		}
	}
}

void downBlock(Block* block, Stage* stage)
{
	eraseBlock(block);
	block->y++;
	if (checkCollision(block, stage))
	{
		block->y--;
		landBlock(block, stage);
		resetBlock(block);
		updateStage(stage);
	}
	drawBlock(block);
}

void printInfo(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {32, 0};
	SetConsoleCursorPosition(hConsoleOut, pos);
	for (int i = 0; i < stage->height; i++)
	{
		pos.Y = i;
		pos.X = 32;
		SetConsoleCursorPosition(hConsoleOut, pos);
		for (int j = 0; j < stage->width; j++)
			printf("%d ", stage->info[i][j]);
	}
}

int main()
{
	srand(time(NULL));
	Stage* stage = createStage();
	Block* block = createBlock();
	drawStage(stage);
	drawBlock(block);

	int t = 0;
	int key = 0;
	while (1)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == 224)
			{
				key = _getch();
				moveBlock(block,stage ,key);
			}
		}
		if (t == 100)
		{
			downBlock(block, stage);
			t = 0;
		}
		t++;
		//printInfo(stage);
		Sleep(10);
	}
	return 0;
}