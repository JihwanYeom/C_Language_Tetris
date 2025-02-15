#include <stdio.h>
#include <windows.h>
#include "block.h"

int main()
{	
	//	<커서 위치의 이동>
	//1. COORD : x, y좌표를 표현하는 구조체
	
	COORD pos1 = { 2, 4 };
	COORD pos2 = { 4, 8 };

	//2. STD_OUTPUT_HANDLE : 실행되면 출력되는 콘솔 창,
	//	콘솔창의 Handle 값을 얻어온다
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//3. 콘솔의 Handle 값을 받아오고
	//	 pos1에 커서를 위치시킨다.
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("안녕하세요");
	SetConsoleCursorPosition(hConsoleOut, pos2);
	printf("안녕하세요2");
	//getchar()
	//	<커서의 위치 정보 얻어오기>

	//1. 콘솔 창 스크린에 담겨있는 정보 버퍼 정의
	CONSOLE_SCREEN_BUFFER_INFO conScreenInfo;

	//2. 콘솔 창 스크린에 현재 상태 정보를 curinfo로 전달
	GetConsoleScreenBufferInfo(hConsoleOut, &conScreenInfo);

	//3. CONSOLE_SCREEN_BUFFER_INFO에 정의된 현재 커서 좌표 출력
	printf("\n[%d, %d]\n", conScreenInfo.dwCursorPosition.X, conScreenInfo.dwCursorPosition.Y);

	//	<커서 깜빡임 제거>
	//4. 현재 표시된 커서의 활성화 해제
	CONSOLE_CURSOR_INFO curCursorInfo;
	//5. 현재 커서의 상태 정보를 받아오기 
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	//6. 커서 보임 표시 끄고 상태 정보를 콘솔에 업데이트
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	return 0;
}