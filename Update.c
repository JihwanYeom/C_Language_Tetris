/*
<과제 설명>


*/

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
#define SPACE 32
#define WHITE 15
#define RED 12
#define GREEN 10
#define BLUE 9
#define DARKRED 4
#define PURPLE 13
#define YELLOW 14
#define SKYBLUE 11

#define STAGE_HEIGHT 24
#define STAGE_WIDTH 14
#define LINE_PER_LEVEL 4
#define DEFAULT_SPEED 50

typedef struct Block
{
	int x, y, shape, dir, color, drop_score;
}Block;

typedef struct Stage
{
	int width;
	int height;
	int score;
	int level;
	int line;
	int speed;
	int** info;
}Stage;

void removeCursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

void setTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Block* createBlock()
{
	Block* block = (Block*)malloc(sizeof(Block));
	block->x = 5;
	block->y = 0;
	block->drop_score = 0;
	block->shape = rand() % 7 * 4;
	block->dir = 0;
	switch (block->shape / 4)
	{
	case 0:
		block->color = BLUE;
		break;
	case 1:
		block->color = RED;
		break;
	case 2:
		block->color = SKYBLUE;
		break;
	case 3:
		block->color = YELLOW;
		break;
	case 4:
		block->color = DARKRED;
		break;
	case 5:
		block->color = GREEN;
		break;
	case 6:
		block->color = PURPLE;
		break;
	}
	return block;
}

void updateBlock(Block* block)
{
	block->x = 5;
	block->y = 0;
	block->drop_score = 0;
	block->shape = rand() % 7 * 4;
	block->dir = 0;
	switch (block->shape / 4)
	{
	case 0:
		block->color = BLUE;
		break;
	case 1:
		block->color = RED;
		break;
	case 2:
		block->color = SKYBLUE;
		break;
	case 3:
		block->color = YELLOW;
		break;
	case 4:
		block->color = DARKRED;
		break;
	case 5:
		block->color = GREEN;
		break;
	case 6:
		block->color = PURPLE;
		break;
	}
}

void loadBlock(Block* block, Block* next)
{
	block->x = 5;
	block->y = 0;
	block->shape = next->shape;
	block->dir = 0;
	block->color = next->color;
	block->drop_score = next->drop_score;
}

void updateNext(Block* next, Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pos.X = stage->width * 2 - 1 + j;
			pos.Y = 3 + i;
			SetConsoleCursorPosition(hConsoleOut, pos);
			printf(" ");
		}
	}
	setTextColor(next->color);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pos.X = stage->width * 2 + j * 2;
			pos.Y = 3 + i;
			if (next->color == SKYBLUE || next->color == YELLOW)
				pos.X--;
			SetConsoleCursorPosition(hConsoleOut, pos);
			if (blockModel[next->shape + next->dir][i][j])
				printf("■");
		}
	}
	setTextColor(WHITE);
}

Stage* createStage()
{
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	stage->width = STAGE_WIDTH;
	stage->height = STAGE_HEIGHT;
	stage->score = 0;
	stage->level = 1;
	stage->line = 0;
	stage->speed = 50;
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
		stage->info[stage->height - 1][i] = 1;
		stage->info[stage->height - 2][i] = 1;
	}
	for (int i = 0; i < stage->height; i++)
	{
		stage->info[i][stage->width - 1] = 1;
		stage->info[i][stage->width - 2] = 1;
	}
	return stage;
}

void drawStage(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for (int i = 0; i < stage->height - 1; i++)
	{
		pos.X = 0; pos.Y = i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("│");
	}
	for (int i = 0; i < stage->height - 1; i++)
	{
		pos.X = 2 * (stage->width - 3); pos.Y = i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("│");
	}
	pos.X = 0; pos.Y = stage->height - 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("└");
	for (int i = 1; i < (stage->width - 2) * 2 - 1; i++)
	{
		pos.X = i; pos.Y = stage->height - 2;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("─");
	}
	pos.X = 2 * (stage->width - 3); pos.Y = stage->height - 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("┘");

	pos.X = stage->width * 2 - 3;
	pos.Y = 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("┌");
	pos.X = stage->width * 2 + 7;
	pos.Y = 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("┐");
	pos.X = stage->width * 2 - 3;
	pos.Y = 7;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("└");
	pos.X = stage->width * 2 + 7;
	pos.Y = 7;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("┘");
	for (int i = 0; i < 9; i++)
	{
		pos.X = stage->width * 2 + i - 2;
		pos.Y = 2;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("─");
	}
	for (int i = 0; i < 4; i++)
	{
		pos.X = stage->width * 2 - 3;
		pos.Y = 3 + i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("│");
	}
	for (int i = 0; i < 4; i++)
	{
		pos.X = stage->width * 2 + 7;
		pos.Y = 3 + i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("│");
	}
	for (int i = 0; i < 9; i++)
	{
		pos.X = stage->width * 2 + i - 2;
		pos.Y = 7;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("─");
	}
	pos.X = stage->width * 2 - 1;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("[NEXT]");

	pos.X = stage->width * 2 - 1;
	pos.Y = 10;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("[LEVEL]");

	pos.X = stage->width * 2 - 1;
	pos.Y = 14;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("[LINES]");

	pos.X = stage->width * 2 - 1;
	pos.Y = 18;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("[SCORE]");
}

void printInfo(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { stage->width * 2 + 10, 0 };
	SetConsoleCursorPosition(hConsoleOut, pos);
	for (int i = 0; i < stage->height; i++)
	{
		pos.Y = i;
		pos.X = stage->width * 2 + 10;
		SetConsoleCursorPosition(hConsoleOut, pos);
		for (int j = 0; j < stage->width; j++)
			printf("%d ", stage->info[i][j]);
	}
}

int isEmptyLine(int* line)
{
	for (int i = 2; line[i] != 1; i++)
	{
		if (line[i] >= 2)
			return 0;
	}
	return 1;
}

int isFullLine(int* line)
{
	for (int i = 2; line[i] != 1; i++)
	{
		if (line[i] == 0)
			return 0;
	}
	return 1;
}

void swapLine(int* line1, int* line2)
{
	int temp[100];
	for (int i = 2; line1[i] != 1; i++)
		temp[i] = line1[i];
	for (int i = 2; line2[i] != 1; i++)
		line1[i] = line2[i];
	for (int i = 2; line2[i] != 1; i++)
		line2[i] = temp[i];
}

void eraseLine(Stage* stage)
{
	int erasedLine = 0;
	for (int i = stage->height - 3; i > 0; i--)
	{
		if (isFullLine(stage->info[i]))
		{
			for (int j = 2; stage->info[i][j] != 1; j++)
				stage->info[i][j] = 0;
			for (int j = i; !isEmptyLine(stage->info[j - 1]); j--)
			{
				swapLine(stage->info[j], stage->info[j - 1]);
			}
			i++;
			erasedLine++;
		}
	}
	stage->line += erasedLine;
	if (stage->line >= stage->level * 4 && stage->level < 9)
	{
		stage->level++;
		stage->line = 0;
		stage->speed = 55 - 5 * stage->level;
	}

	if (erasedLine == 1)
		stage->score += 40 * (stage->level + 1);
	else if (erasedLine == 2)
		stage->score += 100 * (stage->level + 1);
	else if (erasedLine == 3)
		stage->score += 300 * (stage->level + 1);
	else if (erasedLine == 4)
		stage->score += 1200 * (stage->level + 1);
}

void updateStage(Stage* stage)
{
	eraseLine(stage);
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;

	pos.X = stage->width * 2 + 2;
	pos.Y = 12;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("%d", stage->level);

	pos.X = stage->width * 2 + 1 - 1;
	pos.Y = 16;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("     ");
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("%02d/%02d", stage->line, stage->level * 4);

	pos.X = stage->width * 2 - 2;
	pos.Y = 20;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("%09d", stage->score);

	for (int y = 0; y < stage->height - 2; y++)
	{
		for (int x = 2; x < stage->width - 2; x++)
		{
			pos.X = 2 * x - 2;
			pos.Y = y;
			SetConsoleCursorPosition(hConsoleOut, pos);
			if (stage->info[y][x] >= 2)
			{
				switch (stage->info[y][x] - 2)
				{
				case 0:
					setTextColor(BLUE);
					break;
				case 1:
					setTextColor(RED);
					break;
				case 2:
					setTextColor(SKYBLUE);
					break;
				case 3:
					setTextColor(YELLOW);
					break;
				case 4:
					setTextColor(DARKRED);
					break;
				case 5:
					setTextColor(GREEN);
					break;
				case 6:
					setTextColor(PURPLE);
					break;
				}
				printf("■");
				setTextColor(WHITE);
			}
			else
				printf(".");
		}
	}
	printInfo(stage);
}

void drawBlock(Block* block)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	setTextColor(block->color);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			COORD pos = { 2 * (block->x + j) - 2, block->y + i };
			SetConsoleCursorPosition(hConsoleOut, pos);
			if (blockModel[block->shape + block->dir][i][j])
				printf("■");
		}
	}
	setTextColor(WHITE);
}

void eraseBlock(Block* block)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			COORD pos = { 2 * (block->x + j) - 2, block->y + i };
			SetConsoleCursorPosition(hConsoleOut, pos);
			if (blockModel[block->shape + block->dir][i][j])
				printf(".");
		}
	}

}

int checkCollision(Block* block, Stage* stage)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockModel[block->shape + block->dir][y][x] * stage->info[block->y + y][block->x + x] > 0)
				return 1;
		}
	}
	return 0;
}

void gameOver(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for (int i = 0; i < 6; i++)
	{
		pos.Y = stage->height / 2 - 4 + i;
		for (int j = 0; j < stage->width * 2; j++)
		{
			pos.X = j;
			SetConsoleCursorPosition(hConsoleOut, pos);
			printf(" ");
		}
	}
	pos.Y = stage->height / 2 - 3;
	pos.X = stage->width / 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	setTextColor(RED);
	printf("GAME OVER");

	setTextColor(WHITE);
	pos.Y = stage->height / 2 - 1;
	pos.X = stage->width / 2 - 5;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("Press any key to quit");

	pos.Y = stage->height + 20;
	pos.X = 0;
	SetConsoleCursorPosition(hConsoleOut, pos);
	while (1)
	{
		int key = 0;
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key != 0)
				exit(0);
		}
	}
}

void moveBlock(Block* block, Stage* stage, int key)
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
		block->drop_score++;
		if (checkCollision(block, stage))
		{
			block->y--;
			block->drop_score--;
		}
		drawBlock(block);
		break;
	case UP:
		eraseBlock(block);
		block->dir++;
		block->dir = block->dir % 4;
		if (checkCollision(block, stage))
		{
			if (block->dir == 0)
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
				stage->info[block->y + y][block->x + x] = (block->shape / 4) + 2;
		}
	}
}

void quickLand(Block* block, Block* next, Stage* stage)
{
	eraseBlock(block);
	while (checkCollision(block, stage) != 1)
	{
		block->y++;
		block->drop_score += 2;
	}
	block->y--;
	block->drop_score -= 2;
	stage->score += block->drop_score;
	landBlock(block, stage);
	loadBlock(block, next);
	updateBlock(next);
	updateStage(stage);
	updateNext(next, stage);
	if (checkCollision(block, stage))
		gameOver(stage);
	drawBlock(block);
}



void downBlock(Block* block, Block* next, Stage* stage)
{
	eraseBlock(block);
	block->y++;
	block->drop_score++;
	if (checkCollision(block, stage))
	{
		block->y--;
		block->drop_score--;
		stage->score += block->drop_score;
		landBlock(block, stage);
		loadBlock(block, next);
		updateBlock(next);
		updateStage(stage);
		updateNext(next, stage);
	}
	if (checkCollision(block, stage))
		gameOver(stage);
	drawBlock(block);
}

void processKeyInput(Block* block, Block* next, Stage* stage)
{
	int key = 0;
	if (_kbhit() != 0)
	{
		key = _getch();
		if (key == SPACE)
			quickLand(block, next, stage);
		if (key == 224)
		{
			key = _getch();
			moveBlock(block, stage, key);
		}
	}
}

int main()
{
	srand(time(NULL));
	Stage* stage = createStage();
	Block* block = createBlock();
	Block* next = createBlock();
	drawStage(stage);
	drawBlock(block);
	printInfo(stage);
	updateNext(next, stage);
	updateStage(stage);
	removeCursor();
	while (1)
	{
		for (int i = 0; i < stage->speed; i++)
		{
			processKeyInput(block, next, stage);
			Sleep(10);
		}
		downBlock(block, next, stage);
	}
	return 0;
}