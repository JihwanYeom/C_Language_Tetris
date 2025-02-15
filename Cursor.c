#include <stdio.h>
#include <windows.h>
#include "block.h"

int main()
{	
	//	<Ŀ�� ��ġ�� �̵�>
	//1. COORD : x, y��ǥ�� ǥ���ϴ� ����ü
	
	COORD pos1 = { 2, 4 };
	COORD pos2 = { 4, 8 };

	//2. STD_OUTPUT_HANDLE : ����Ǹ� ��µǴ� �ܼ� â,
	//	�ܼ�â�� Handle ���� ���´�
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//3. �ܼ��� Handle ���� �޾ƿ���
	//	 pos1�� Ŀ���� ��ġ��Ų��.
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("�ȳ��ϼ���");
	SetConsoleCursorPosition(hConsoleOut, pos2);
	printf("�ȳ��ϼ���2");
	//getchar()
	//	<Ŀ���� ��ġ ���� ������>

	//1. �ܼ� â ��ũ���� ����ִ� ���� ���� ����
	CONSOLE_SCREEN_BUFFER_INFO conScreenInfo;

	//2. �ܼ� â ��ũ���� ���� ���� ������ curinfo�� ����
	GetConsoleScreenBufferInfo(hConsoleOut, &conScreenInfo);

	//3. CONSOLE_SCREEN_BUFFER_INFO�� ���ǵ� ���� Ŀ�� ��ǥ ���
	printf("\n[%d, %d]\n", conScreenInfo.dwCursorPosition.X, conScreenInfo.dwCursorPosition.Y);

	//	<Ŀ�� ������ ����>
	//4. ���� ǥ�õ� Ŀ���� Ȱ��ȭ ����
	CONSOLE_CURSOR_INFO curCursorInfo;
	//5. ���� Ŀ���� ���� ������ �޾ƿ��� 
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	//6. Ŀ�� ���� ǥ�� ���� ���� ������ �ֿܼ� ������Ʈ
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	return 0;
}