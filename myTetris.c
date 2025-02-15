/*
	[��Ʈ�� ����]
	
	1. [���� ����]
	�����Լ����� ������ �����ϱ� ���� rand()�Լ��� �õ尪�� �ʱ�ȭ �ϰ�, removeCursor() �Լ��� �ܼ�â�� Ŀ���� �����ݴϴ�  createStage()�Լ��� 
	createBlock()�Լ��� Stage����ü ���� stage�� Block����ü ���� block�� next�� �����մϴ�. ���� drawStage()�Լ��� ���������� ȭ�鿡 ����ϰ�, 
	drawBlock()�� drawNext() �Լ��� ������ ��ϰ� ���� ����� ����� �� updateStage()�Լ��� �������� ������ ������Ʈ �մϴ�.

	2.[���� ���� ����]
	���η����� ���ư��� processKeyInput()�Լ��� Ű���� �Է��� ó���ϸ� downBlock()�Լ��� ����� 1ĭ �����ϴ� processKeyInput()�� for�� �ȿ��� 10ms
	���� ȣ��Ǹ� 10ms*stage->speed ��ŭ �ð��� ������ for���� ����ǰ� ����� ������ downBlock �Լ��� ȣ��˴ϴ�. processKeyInput()�Լ��� Ű �Է¿�
	���� �����̽��ٰ� �ԷµǾ��� ��� ����� ��� ������Ű�� ����Ű�� ������ ��� ����� �̵���Ű�ų� ȸ����ŵ�ϴ�.

	3.[��� �̵� �� ȸ��]
	processKeyInput()�Լ����� ����Ű�� ������ ��� moveBlock()�Լ��� ȣ��˴ϴ� ���� eraseBlock()�Լ��� ��µǾ��ִ� ����� �����, ����Ű�� ���� 
	����� ��ǥ�� �̵���Ű�� �� ����Ű�� �ԷµǾ��� ��� ����� ȸ����ŵ�ϴ� �̶� ����� �̵���Ų ����checkCollision() �Լ��� ȣ������� �� �浹�� 
	������ ��� �ٽ� ����� ��ġ�� ���ڸ��� ���������ϴ� ��� �̵� ó���� ������ drawBlock()�Լ��� ����� �ٽ� ����մϴ�

	4.[�浹 ����]
	checkCollision() �Լ��� 4x4�� ��� ������ ���� �� ����� ��ġ�ϰ� �ִ� ���������� 4x4 ������ ��ȸ�ϸ� ����� ������ �����ϴ� �κа� ���̳� 
	���� ����� ��ġ���� Ȯ���Ͽ� ���� ��ġ�� �κ��� ������ ��� 1�� ��ȯ�ϰ� �ƴ� ��� 0�� ��ȯ�մϴ�

	5.[��� ����]
	downBlock()�Լ��� ȣ��Ǹ� ����� ����� ��ĭ ���� �ٽ� ����ϸ� ����� ��� ������ 1�ø��ϴ�. ���� checkCollision()�� ���� �浹�� ����
	�� ��� ����� �ǵ����� ����� ������ŵ�ϴ�. 

	6.[��� ����]
	����� �����Ǹ� ��� ������ �ݿ��ϰ� landBlock()�Լ��� ���� ����� ���������� �ݿ��մϴ�. �׸��� loadBlock()�Լ��� next ����� ������ block�� 
	�����ϰ� updateBlock()�Լ��� next ����� �ʱ�ȭ �մϴ� �׸��� updateStage() �Լ��� �������� ������ ������Ʈ �ϰ� drawNext�Լ���
	���� ����� ����մϴ�. ���� ���� ������ ����� �������ڸ��� �浹�� ��� gameOver()�Լ��� ȣ���մϴ�

	7.[���� ����]
	�����̽� �ٸ� ������ quickLand()�Լ��� ȣ��˴ϴ� quickLand()�Լ��� ���� ��� ����� �� �������� ���Ҷ� ���� ������ ������ ������ ĭ*2�� 
	��� ������ �ݿ��մϴ�. ���� ��� ��� ���� ó���� �ϸ� ���� ����� downBlock()�� ���� �κа� �����մϴ�

	8.[�������� ����]
	����� �����ϸ� updateStage()�Լ��� ���� ���������� ���ŵ˴ϴ�. updateStage()�� eraseLine()�Լ��� ȣ���Ͽ� ���������� ä���� ���� ���� ���
	���� �����ϰ� ����, ����, ������ �����մϴ�. ���� ����� ����, ����, ������ �˸��� ��ġ�� ����ϰ� �������� ������ ���� ���� ������ ��ġ�� ����
	�°� ����մϴ�. �׸��� SHOW_STAGE_INFO�� 1�� ��� �������� ���� �迭�� �����ʿ� �Բ� ����մϴ�

	9.[�� ����]
	eraseLine()�Լ��� �������� ���� �迭�� �ؿ������� Ž���Ͽ� isFullLine()�Լ��� ���� ä���� ������ �Ǻ��մϴ�. ä���� ������ ���� ��������
	���� ���� �÷����� swapLine() �Լ��� �ݺ��Ͽ� ȣ���� �� ���ΰ� �ٷ� ���� ������ �ٲߴϴ�. isEmptyLine()�Լ��� �ٷ� �� ������ �� �����̶� �Ǵ�����
	��� �ݺ��� ���߰� ������ �ٺ��� �ٽ� Ž���Ϻ��. �� ���� �� ���� �޼��� �������� ������ ��½�Ű�� ������ ���ΰ� ������ ���� ������ �ݿ��մϴ�.

	10.[���� ����]
	����� ����� ���ڸ��� ������ �� ���� ��� gameOver()�Լ��� ȣ��˴ϴ� gameOver()�Լ��� ȭ�鿡 GAMEOVER ȭ���� ����ϰ� �Ǹ� ������ �����ϰ�
	�ƹ� Ű���� Ű�� ���� ��� ���α׷��� �����մϴ�.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "block.h"

// Ű �ڵ� ����
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SPACE 32

// ���� ���� �ڵ� ����
#define WHITE 15
#define RED 12
#define GREEN 10
#define BLUE 9
#define DARKRED 4
#define PURPLE 13
#define YELLOW 14
#define SKYBLUE 11

// �������� ���� �ڵ� ����
#define STAGE_HEIGHT 24 // �������� ����
#define STAGE_WIDTH 14 // �������� �ʺ�
#define LINE_PER_LEVEL 10 // ������ �䱸 ���� ��
#define DEFAULT_SPEED 50 // �⺻ ���ǵ�
#define SHOW_STAGE_INFO 0 // �������� ���� �迭 ��� ����( 1(true) �Ǵ� 0(false) )

// ��� ����ü : ��ġ�� ���, ����, ����, ��� ������ ��������� ������ ����
typedef struct Block
{
	int x, y, shape, dir, color, drop_score;
}Block;

// �������� ����ü : ���������� �ʺ�� ����, ����, ����, �� �������� ���� ���� ��, ���� �ӵ�, �������� ������ ��������� ������ ����
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

// �ܼ� �Է� Ŀ�� ���� �Լ�
void removeCursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

// ���� ��� ���� ���� �Լ�
void setTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// �������� ����ü ������ �������� �����Ͽ� ������ �������� ���� �迭�� �ʱ�ȭ �� �� ��ȯ�ϴ� �Լ�
Stage* createStage()
{
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	stage->width = STAGE_WIDTH;
	stage->height = STAGE_HEIGHT;
	stage->score = 0;
	stage->level = 1;
	stage->line = 0;
	stage->speed = DEFAULT_SPEED;
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

// �������� ���̿� �ʺ� �°� �������� �ٿ������ ����ϰ� next ĭ, ����, ����, ���� ���� �������̽��� ����ϴ� �Լ�
void drawStage(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for (int i = 0; i < stage->height - 1; i++)
	{
		pos.X = 0; pos.Y = i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("��");
	}
	for (int i = 0; i < stage->height - 1; i++)
	{
		pos.X = 2 * (stage->width - 3); pos.Y = i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("��");
	}
	pos.X = 0; pos.Y = stage->height - 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("��");
	for (int i = 1; i < (stage->width - 2) * 2 - 1; i++)
	{
		pos.X = i; pos.Y = stage->height - 2;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("��");
	}
	pos.X = 2 * (stage->width - 3); pos.Y = stage->height - 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("��");

	pos.X = stage->width * 2 - 3;
	pos.Y = 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("��");
	pos.X = stage->width * 2 + 7;
	pos.Y = 2;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("��");
	pos.X = stage->width * 2 - 3;
	pos.Y = 7;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("��");
	pos.X = stage->width * 2 + 7;
	pos.Y = 7;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("��");
	for (int i = 0; i < 9; i++)
	{
		pos.X = stage->width * 2 + i - 2;
		pos.Y = 2;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("��");
	}
	for (int i = 0; i < 4; i++)
	{
		pos.X = stage->width * 2 - 3;
		pos.Y = 3 + i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("��");
	}
	for (int i = 0; i < 4; i++)
	{
		pos.X = stage->width * 2 + 7;
		pos.Y = 3 + i;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("��");
	}
	for (int i = 0; i < 9; i++)
	{
		pos.X = stage->width * 2 + i - 2;
		pos.Y = 7;
		SetConsoleCursorPosition(hConsoleOut, pos);
		printf("��");
	}
	pos.X = stage->width * 2 - 1;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsoleOut, pos);
	printf("[NEXT]");

	pos.X = stage->width * 2 -1;
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

// �������� ���� �迭�� ����ϴ� �Լ�
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

// ���� ����ִ� �� Ȯ���Ͽ� ������� ��� 1 �ƴ� ��� 0�� ����ϴ� �Լ�
int isEmptyLine(int* line)
{
	for (int i = 2; line[i] != 1; i++)
	{
		if (line[i] >= 2)
			return 0;
	}
	return 1;
}

// ���� ä�����ִ� �� Ȯ���Ͽ� ä�������� ��� 1 �ƴ� ��� 0�� ����ϴ� �Լ�
int isFullLine(int* line)
{
	for (int i = 2; line[i] != 1; i++)
	{
		if (line[i] == 0)
			return 0;
	}
	return 1;
}

// �� ���� �¹ٲٴ� �Լ�
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

// ���� ���� ���� �ٵ��� swapLine()�� �̿��� �Ʒ��� ��ܼ� ���� ���� ��, �������� ������ ������ �����ϴ� �Լ�
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
	if (stage->line >= LINE_PER_LEVEL && stage->level < 9)
	{
		stage->level++;
		stage->line = 0;
		stage->speed = DEFAULT_SPEED - (DEFAULT_SPEED/9) * (stage->level-1);
	}

	if (erasedLine == 1)
		stage->score += 40 *(stage->level+1);
	else if (erasedLine == 2)
		stage->score += 100 * (stage->level + 1);
	else if (erasedLine == 3)
		stage->score += 300 * (stage->level + 1);
	else if (erasedLine == 4)
		stage->score += 1200 * (stage->level + 1);
}

// ���������� �����ϴ� �Լ��� �� ������ ������ �� ����, ����, ������ ����ϰ� ���������� ���������� ���� ���� ���� �°� ����Ѵ�
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
	printf("%02d/%02d", stage->line, LINE_PER_LEVEL);

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
				printf("��");
				setTextColor(WHITE);
			}
			else
				printf(".");
		}
	}
	if(SHOW_STAGE_INFO)
		printInfo(stage);
}

// ���� ���� �Լ�, ���� ���� ȭ���� ȭ�鿡 ����ϰ� ������ ������Ű��, ���� Ű���� �Է��� ���� ��� ���α׷��� �����Ų��
void gameOver(Stage* stage)
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for (int i = 0; i < 5; i++)
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

// ��� ����ü�� �����ϰ� �ʱ�ȭ�Ͽ� ��ȯ�ϴ� �Լ� ����� ����� �������� �����ǰ� ����� ��翡 �´� ������ �������� �ʱ�ȭ �Ѵ�
Block* createBlock(Stage* stage)
{
	Block* block = (Block*)malloc(sizeof(Block));
	block->x = stage->width/2 - 2;
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

// ��� ������ �ܼ��� �ʱ�ȭ�ϴ� �Լ�
void updateBlock(Block* block, Stage* stage)
{
	block->x = stage->width/2 - 2;
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

// next����� ������ �����ϴ� ������� �����ϴ� �Լ�
void loadBlock(Block* block, Block* next)
{
	block->x = next->x;
	block->y = next->y;
	block->shape = next->shape;
	block->dir = next->dir;
	block->color = next->color;
	block->drop_score = next->drop_score;
}

// ����� ������ ���� ����� ���������� ����ϴ� �Լ�
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
				printf("��");
		}
	}
	setTextColor(WHITE);
}

// ����� ������ ���� ����� ������������ ����� �Լ�
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

// nextĭ�� ������ ������ ����� ����ϴ� �Լ�
void drawNext(Block* next, Stage* stage)
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
				printf("��");
		}
	}
	setTextColor(WHITE);
}

// ��ϰ� ��, �Ǵ� ���� ��ϰ��� �浹 ���θ� Ȯ���ϴ� �Լ� �浹�� ��� 1 �ƴ� ��� 0�� ��ȯ�Ѵ�
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

// Ű���� �Է¿� ���� ����� ��ǥ�� ���� ������ �����Ͽ� ����� ȸ�� �� �̵���Ű�� �Լ�.
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

// ������ ����� ��ġ ������ �������� ���� �迭�� �ݿ��ϴ� �Լ�
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

// ����� �� ĭ �Ʒ��� ������ �Լ�. ���� �� ������ �� ���� ��� ����� ������Ű��, ������� ����� �ٷ� ������ �� ���ٸ� ���� ���� ó��
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
		updateBlock(next, stage);
		updateStage(stage);
		drawNext(next, stage);
	}
	if (checkCollision(block, stage))
		gameOver(stage);
	drawBlock(block);
}

// ����� �ִ��� �Ʒ��� ���� ������Ű�� �Լ�. ������� ����� �ٷ� ������ �� ���ٸ� ���� ���� ó��
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
	updateBlock(next, stage);
	updateStage(stage);
	drawNext(next, stage);
	if (checkCollision(block, stage))
		gameOver(stage);
	drawBlock(block);
}

// Ű �Է��� �޾� � Ű�� �Է��ߴ����� ���� �Լ��� ȣ���ϴ� �Լ�, �����̽� �ٴ� quickLand(), ����Ű�� moveBlock() �Լ��� ȣ���Ѵ�
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
	srand(time(NULL)); // ���� �õ� �ʱ�ȭ
	removeCursor(); // Ŀ�� ����
	Stage* stage = createStage(); // �������� ����ü ���� ����
	Block* block = createBlock(stage); // ��� ����ü ���� block(�������� ���) ����
	Block* next = createBlock(stage); // ��� ����ü ���� next(���� ���) ���� 
	drawStage(stage); // �������� �ٿ���� �� �������̽� ���
	drawBlock(block); // �������� ��� ���
	drawNext(next, stage); // ���� ��� ���
	updateStage(stage); // ���� �������� ����

	//���� ����
	while (1)
	{
		for (int i = 0; i < stage->speed; i++) // 10ms*stage->speed ���� while�� ����
		{
			processKeyInput(block, next, stage);
			Sleep(10); // 10ms���� Ű �Է�
		}
		downBlock(block, next, stage); // 10ms*stage->speed ���� downBlock ȣ��
	}
	return 0;
}