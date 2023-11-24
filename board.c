#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_BOARD					15 //칸 수 
#define N_COINPOS  				12
#define MAX_COIN				4

#define MAX_SHARKSTEP			6 
#define SHARK_INITPOS			-4 //시작점보다 4개 앞부터 시작
 

//상어에 의한 파손 여부
static int board_status[N_BOARD]; //몇번째 칸이 파손이 되었나 
static int board_coin[N_BOARD]; //i 번째 칸이 동전 몇개인가 

static int board_sharkPosition; 


int board_initBoard(void)
{
	int i; 
	for (i=0;i<N_BOARD;i++)
	{
		board_status[i] = BOARDSTATUS_OK; //board_status 초기화 
		board_coin[i] = 0; // board_coin 초기화 
	}	
	
	board_sharkPosition = SHARK_INITPOS; //shark 위치 초기화 
	
	//coin 할당 
	for (i=0;i<N_COINPOS;i++)
	{
		int flag = 0;
		while(flag == 0)
		{
			int allocPos = rand()%N_BOARD; //동전 놓을 칸을 랜덤으로 지정 0~14 중 
			if(board_coin[allocPos] == 0)
			{
				//i번째 coin 할당 
				board_coin[allocPos] = rand()%MAX_COIN+1; //1~4
				flag = 1; // while문 조건 빠져나옴 
			}
		}
	}
	
	return 0;	
}

int board_printBoardStatus(void)
{
	int i;
	
	printf("--------BOARD STATUS--------\n");
	for (i=0;i<N_BOARD;i++)
	{
		printf("|");
		if (board_status[i] == BOARDSTATUS_NOK)
			printf("X");
		else
			printf("O");
			
	}
	printf("|\n");
	printf("-----------------------------\n");
	
	return 0;
}



int board_getBoardStatus(int pos) // 내부 static 전역변수의 값을 main.c에 제공 
{
	return board_status[pos]; //board_status 배열 요소 반환 
}

int board_getBoardCoin(int pos) //
{
	int coin = 	board_coin[pos]; // pos번째 보드칸에 있는 동전을 줍는 동작 
	return coin;
}

//int board_getSharkPosition(void);

int board_stepShark(void)
{
	int step = rand()%MAX_SHARKSTEP + 1; // 1 ~ MAX_SHARKSTEP 칸을 랜덤으로 이동
	int i;
	for(i=board_sharkPosition;i<board_sharkPosition+step;i++)
	{
		if(i >= 0 && i < N_BOARD)
			board_status[i] = BOARDSTATUS_NOK;
	}
	
	board_sharkPosition += step;
	
	return board_sharkPosition;
}




