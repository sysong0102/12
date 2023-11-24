#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_BOARD					15 //ĭ �� 
#define N_COINPOS  				12
#define MAX_COIN				4

#define MAX_SHARKSTEP			6 
#define SHARK_INITPOS			-4 //���������� 4�� �պ��� ����
 

//�� ���� �ļ� ����
static int board_status[N_BOARD]; //���° ĭ�� �ļ��� �Ǿ��� 
static int board_coin[N_BOARD]; //i ��° ĭ�� ���� ��ΰ� 

static int board_sharkPosition; 


int board_initBoard(void)
{
	int i; 
	for (i=0;i<N_BOARD;i++)
	{
		board_status[i] = BOARDSTATUS_OK; //board_status �ʱ�ȭ 
		board_coin[i] = 0; // board_coin �ʱ�ȭ 
	}	
	
	board_sharkPosition = SHARK_INITPOS; //shark ��ġ �ʱ�ȭ 
	
	//coin �Ҵ� 
	for (i=0;i<N_COINPOS;i++)
	{
		int flag = 0;
		while(flag == 0)
		{
			int allocPos = rand()%N_BOARD; //���� ���� ĭ�� �������� ���� 0~14 �� 
			if(board_coin[allocPos] == 0)
			{
				//i��° coin �Ҵ� 
				board_coin[allocPos] = rand()%MAX_COIN+1; //1~4
				flag = 1; // while�� ���� �������� 
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



int board_getBoardStatus(int pos) // ���� static ���������� ���� main.c�� ���� 
{
	return board_status[pos]; //board_status �迭 ��� ��ȯ 
}

int board_getBoardCoin(int pos) //
{
	int coin = 	board_coin[pos]; // pos��° ����ĭ�� �ִ� ������ �ݴ� ���� 
	return coin;
}

//int board_getSharkPosition(void);

int board_stepShark(void)
{
	int step = rand()%MAX_SHARKSTEP + 1; // 1 ~ MAX_SHARKSTEP ĭ�� �������� �̵�
	int i;
	for(i=board_sharkPosition;i<board_sharkPosition+step;i++)
	{
		if(i >= 0 && i < N_BOARD)
			board_status[i] = BOARDSTATUS_NOK;
	}
	
	board_sharkPosition += step;
	
	return board_sharkPosition;
}




