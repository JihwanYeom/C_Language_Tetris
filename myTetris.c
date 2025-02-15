/*
	[파트별 설명]
	
	1. [게임 시작]
	메인함수에서 게임을 시작하기 전에 rand()함수의 시드값을 초기화 하고, removeCursor() 함수로 콘솔창의 커서를 지워줍니다  createStage()함수와 
	createBlock()함수로 Stage구조체 변수 stage와 Block구조체 변수 block과 next를 생성합니다. 이후 drawStage()함수로 스테이지를 화면에 출력하고, 
	drawBlock()과 drawNext() 함수로 낙하할 블록과 다음 블록을 출력한 뒤 updateStage()함수로 스테이지 정보를 업데이트 합니다.

	2.[게임 메인 루프]
	메인루프가 돌아가며 processKeyInput()함수로 키보드 입력을 처리하며 downBlock()함수로 블록을 1칸 내립니다 processKeyInput()은 for문 안에서 10ms
	마다 호출되며 10ms*stage->speed 만큼 시간이 지나면 for문이 종료되고 블록을 내리는 downBlock 함수가 호출됩니다. processKeyInput()함수는 키 입력에
	따라 스페이스바가 입력되었을 경우 블록을 즉시 착지시키며 방향키가 들어왔을 경우 블록을 이동시키거나 회전시킵니다.

	3.[블록 이동 및 회전]
	processKeyInput()함수에서 방향키가 들어왔을 경우 moveBlock()함수가 호출됩니다 먼저 eraseBlock()함수로 출력되어있는 블록을 지우고, 방향키에 따라 
	블록의 좌표를 이동시키고 위 방향키가 입력되었을 경우 블록을 회전시킵니다 이때 블록을 이동시킨 다음checkCollision() 함수를 호출시켰을 때 충돌이 
	감지된 경우 다시 블록의 위치를 제자리로 돌려놓습니다 모든 이동 처리가 끝나면 drawBlock()함수로 블록을 다시 출력합니다

	4.[충돌 감지]
	checkCollision() 함수는 4x4의 블록 영역과 현재 그 블록이 위치하고 있는 스테이지의 4x4 영역을 순회하며 블록이 실제로 존재하는 부분과 벽이나 
	굳은 블록이 겹치는지 확인하여 만약 겹치는 부분이 존재할 경우 1을 반환하고 아닐 경우 0을 반환합니다

	5.[블록 낙하]
	downBlock()함수가 호출되면 블록을 지우고 한칸 내려 다시 출력하며 블록의 드랍 점수를 1올립니다. 만약 checkCollision()에 의해 충돌이 감지
	된 경우 블록을 되돌리고 블록을 착지시킵니다. 

	6.[블록 착지]
	블록이 착지되면 드랍 점수를 반영하고 landBlock()함수가 굳은 블록을 스테이지에 반영합니다. 그리고 loadBlock()함수로 next 블록의 정보를 block에 
	복사하고 updateBlock()함수로 next 블록을 초기화 합니다 그리고 updateStage() 함수로 스테이지 정보를 업데이트 하고 drawNext함수로
	다음 블록을 출력합니다. 만약 새로 생성된 블록이 생성되자마자 충돌할 경우 gameOver()함수를 호출합니다

	7.[빠른 착지]
	스페이스 바를 누르면 quickLand()함수가 호출됩니다 quickLand()함수는 실행 즉시 블록을 더 내려가지 못할때 까지 밑으로 내리며 내려온 칸*2를 
	드랍 점수에 반영합니다. 이후 즉시 블록 착지 처리를 하며 이후 기능은 downBlock()의 착지 부분과 동일합니다

	8.[스테이지 갱신]
	블록이 착지하면 updateStage()함수에 의해 스테이지가 갱신됩니다. updateStage()는 eraseLine()함수를 호출하여 스테이지에 채워진 줄이 있을 경우
	줄을 삭제하고 점수, 라인, 레벨을 변경합니다. 이후 변경된 점수, 라인, 레벨을 알맞은 위치에 출력하고 스테이지 정보에 따라 굳은 블럭들을 위치와 색상에
	맞게 출력합니다. 그리고 SHOW_STAGE_INFO가 1일 경우 스테이지 정보 배열을 오른쪽에 함께 출력합니다

	9.[줄 삭제]
	eraseLine()함수는 스테이지 정보 배열을 밑에서부터 탐색하여 isFullLine()함수를 통해 채워진 라인을 판별합니다. 채워진 라인은 전부 지워지고
	줄을 위로 올려가며 swapLine() 함수를 반복하여 호출해 빈 라인과 바로 위의 라인을 바꿉니다. isEmptyLine()함수가 바로 위 라인이 빈 라인이라 판단했을
	경우 반복을 멈추고 지웠던 줄부터 다시 탐색하빈다. 줄 삭제 후 조건 달성시 스테이지 레벨을 상승시키고 삭제된 라인과 레벨에 따른 점수를 반영합니다.

	10.[게임 오버]
	블록이 재생성 되자마자 움직일 수 없는 경우 gameOver()함수가 호출됩니다 gameOver()함수는 화면에 GAMEOVER 화면을 출력하게 되며 게임을 정지하고
	아무 키보드 키를 누를 경우 프로그램을 종료합니다.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "block.h"

// 키 코드 정의
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SPACE 32

// 문자 색상 코드 정의
#define WHITE 15
#define RED 12
#define GREEN 10
#define BLUE 9
#define DARKRED 4
#define PURPLE 13
#define YELLOW 14
#define SKYBLUE 11

// 스테이지 설정 코드 정의
#define STAGE_HEIGHT 24 // 스테이지 높이
#define STAGE_WIDTH 14 // 스테이지 너비
#define LINE_PER_LEVEL 10 // 레벨업 요구 라인 수
#define DEFAULT_SPEED 50 // 기본 스피드
#define SHOW_STAGE_INFO 0 // 스테이지 정보 배열 출력 여부( 1(true) 또는 0(false) )

// 블록 구조체 : 위치와 모양, 방향, 색상, 드롭 점수를 멤버변수로 가지고 있음
typedef struct Block
{
	int x, y, shape, dir, color, drop_score;
}Block;

// 스테이지 구조체 : 스테이지의 너비와 높이, 점수, 레벨, 현 레벨에서 지운 라인 수, 낙하 속도, 스테이지 정보를 멤버변수로 가지고 있음
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

// 콘솔 입력 커서 삭제 함수
void removeCursor()
{
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

// 문자 출력 색상 변경 함수
void setTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 스테이지 구조체 변수를 동적으로 생성하여 변수와 스테이지 정보 배열을 초기화 한 뒤 반환하는 함수
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

// 스테이지 높이와 너비에 맞게 스테이지 바운더리를 출력하고 next 칸, 점수, 라인, 레벨 등의 인터페이스를 출력하는 함수
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

// 스테이지 정보 배열을 출력하는 함수
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

// 줄이 비어있는 지 확인하여 비어있을 경우 1 아닐 경우 0을 출력하는 함수
int isEmptyLine(int* line)
{
	for (int i = 2; line[i] != 1; i++)
	{
		if (line[i] >= 2)
			return 0;
	}
	return 1;
}

// 줄이 채워져있는 지 확인하여 채워져있을 경우 1 아닐 경우 0을 출력하는 함수
int isFullLine(int* line)
{
	for (int i = 2; line[i] != 1; i++)
	{
		if (line[i] == 0)
			return 0;
	}
	return 1;
}

// 두 줄을 맞바꾸는 함수
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

// 줄을 비우고 위의 줄들을 swapLine()을 이용해 아래로 당겨서 줄을 지운 뒤, 스테이지 레벨과 점수를 변경하는 함수
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

// 스테이지를 갱신하는 함수로 줄 삭제를 수행한 뒤 레벨, 라인, 점수를 출력하고 마지막으로 스테이지의 굳은 블럭을 색상에 맞게 출력한다
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
				printf("■");
				setTextColor(WHITE);
			}
			else
				printf(".");
		}
	}
	if(SHOW_STAGE_INFO)
		printInfo(stage);
}

// 게임 오버 함수, 게임 오버 화면을 화면에 출력하고 게임을 정지시키며, 다음 키보드 입력이 들어올 경우 프로그램을 종료시킨다
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

// 블록 구조체를 생성하고 초기화하여 반환하는 함수 블록의 모양은 랜덤으로 결정되고 블록은 모양에 맞는 색상을 가지도록 초기화 한다
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

// 블록 변수를 단순히 초기화하는 함수
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

// next블록의 정보를 낙하하는 블록으로 복사하는 함수
void loadBlock(Block* block, Block* next)
{
	block->x = next->x;
	block->y = next->y;
	block->shape = next->shape;
	block->dir = next->dir;
	block->color = next->color;
	block->drop_score = next->drop_score;
}

// 블록의 정보에 따라 블록을 스테이지에 출력하는 함수
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

// 블록의 정보에 따라 블록을 스테이지에서 지우는 함수
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

// next칸에 다음에 내려올 블록을 출력하는 함수
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
				printf("■");
		}
	}
	setTextColor(WHITE);
}

// 블록과 벽, 또는 굳은 블록간의 충돌 여부를 확인하는 함수 충돌일 경우 1 아닐 경우 0을 반환한다
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

// 키보드 입력에 따라 블록의 좌표와 방향 변수를 조정하여 블록을 회전 및 이동시키는 함수.
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

// 착지한 블록의 위치 정보를 스테이지 정보 배열에 반영하는 함수
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

// 블록을 한 칸 아래로 내리는 함수. 만약 더 내려갈 수 없을 경우 블록을 착지시키고, 재생성된 블록이 바로 움직일 수 없다면 게임 오버 처리
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

// 블록을 최대한 아래로 내려 착지시키는 함수. 재생성된 블록이 바로 움직일 수 없다면 게임 오버 처리
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

// 키 입력을 받아 어떤 키를 입력했는지에 따라 함수를 호출하는 함수, 스페이스 바는 quickLand(), 방향키는 moveBlock() 함수를 호출한다
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
	srand(time(NULL)); // 랜덤 시드 초기화
	removeCursor(); // 커서 삭제
	Stage* stage = createStage(); // 스테이지 구조체 변수 생성
	Block* block = createBlock(stage); // 블록 구조체 변수 block(낙하중인 블록) 생성
	Block* next = createBlock(stage); // 블록 구조체 변수 next(다음 블록) 생성 
	drawStage(stage); // 스테이지 바운더리 및 인터페이스 출력
	drawBlock(block); // 떨어지는 블록 출력
	drawNext(next, stage); // 다음 블록 출력
	updateStage(stage); // 최초 스테이지 갱신

	//메인 루프
	while (1)
	{
		for (int i = 0; i < stage->speed; i++) // 10ms*stage->speed 마다 while문 동작
		{
			processKeyInput(block, next, stage);
			Sleep(10); // 10ms마다 키 입력
		}
		downBlock(block, next, stage); // 10ms*stage->speed 마다 downBlock 호출
	}
	return 0;
}