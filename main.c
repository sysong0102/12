#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_CHARNAME	200
#define MAX_DIE			6

#define N_PLAYER				3 // player �� 
#define PLAYERSTATUS_LIVE		0 //����ִٴ� ���� 0�̶�� ������ 
#define PLAYERSTATUS_DIE		1 
#define PLAYERSTATUS_END		2

//�÷��̾� �𵨸� 
int player_position[N_PLAYER]; //��ġ 
char player_name[N_PLAYER][MAX_CHARNAME]; //�̸� 
int player_coin[N_PLAYER]; //���� ���� �� 
int player_status[N_PLAYER];// 0 - live, 1 - die, 2 - end
char player_statusString[3][MAX_CHARNAME] = {"LIVE", "DIE", "END"};


void opening(void)
{
	printf("============================\n");
	printf("****************************\n");
	printf("          SHARK GAME        \n");
	printf("****************************\n");
	printf("============================\n\n\n");
	
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int rolldie(void)
{
	return rand()%MAX_DIE+1;
} 


void printPlayerPosition(int player)
{
	int i;
	
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(player_position[player] == i)
			printf("%c", player_name[player][0]);
		else
		{
			if (board_getBoardStatus(i) == BOARDSTATUS_NOK)
				printf("X");
			else
				printf(" ");
		}	
	}
	printf("|\n");
}

void printPlayerStatus(void)
{
	int i;
	printf("player status ---\n");
	for (i=0;i<N_PLAYER;i++)
	{
		printf("%s : pos = %i, coin = %i, status = %s\n", player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
		printPlayerPosition(i);
	}
	printf("----------------------\n");
}

void checkDie(void)
{
	int i;
	for(i = 0;i< N_BOARD; i++)
	{	
		if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
		{
			player_status[i] = PLAYERSTATUS_DIE;
			printf("%s has died!", player_name[i]);
		}
	}
}

int game_end(void)
{
	int i;
	int flag_end = 1;
	
	//if all the players are died?
	for (i=0;i<N_PLAYER;i++)
	{
		
		if (player_status[i] == PLAYERSTATUS_LIVE)
		{
			flag_end = 0;
			break;
		}
		
	}
	return flag_end;
}

int getAlivePLayer(void)
{
	int i;
	int cnt = 0;
	for (i=0;i<N_PLAYER;i++)
	{
		if (player_status[i] == PLAYERSTATUS_END)
			cnt++;
	}
	return cnt;

}

int getWinner(void)
{
	int i;
	int winner = 0;
	int max_coin = -1;
	
	for (i = 0;i<N_PLAYER;i++)
	{
		if (player_status[i] == PLAYERSTATUS_LIVE && player_coin[i] > max_coin)
		{
			max_coin = player_coin[i];
			winner = i;
		}
	}
	return winner;
}

int main(int argc, char *argv[]) 
{
	int turn = 0; // ���° �÷��̾� ���� turn 
	int i;

	srand((unsigned)time(NULL)); 
    
	//0. opening
	opening();
	
	//1. �ʱ�ȭ &�÷��̾� �̸� ����
	board_initBoard();
	
	//step1-2 : initialize player
	for (i=0;i<N_PLAYER;i++)
	{
		player_position[i] = 0; // ��ŸƮ ���� 
		player_coin[i] = 0; //���� ��ŸƮ 
		player_status[i] = PLAYERSTATUS_LIVE; // �÷��̾��� �ʱ� ���� ������� 
		printf("Player %i's name : ", i); //�÷��̾��� �̸� �Է� �ޱ� 
		scanf("%s", player_name[i]); // �̸� �Է� 
 	}

	
	//2. �ݺ���(�÷��̾� ��)
	do {
		int step;
		int coinResult;
		char c;
		int pos = player_position[turn];
		
		
		//������ �� �ִ� ��Ȳ�̶�� �ؿ��� �����Ŵ - �ȳ������� 
		if(player_status[turn] != PLAYERSTATUS_LIVE) //����ִ� ��찡 �ƴϸ� ���� �ڵ带 �ٷ� �Ѿ��. 
		{
			turn = (turn + 1)%N_PLAYER; // ���ѹݺ��� �Ͼ�� �ʵ��� 
			continue;
		}
		
		
		
		//2-1. ���� & �÷��̾��� ���� ���
		board_printBoardStatus();
		//for(i=0;i<N_PLAYER;i++)
		//	printPlayerPosition(i);	
		printPlayerStatus();
		
		//2-2. �ֻ��� ������	
		printf("%s turn!! ", player_name[turn]);
		printf("Press any key to roll a die! : \n");
		scanf("%d", &c);
		fflush(stdin); //���ۿ� �׿��ٰ� ���α׷����� ���� -> ���ۿ� �׿����� �� ���� -> ���� �ö����� �Է��� �ް� �Ѿ 
		step = rolldie();
		
		
		
 		//2-3. �̵�	
		player_position[turn] += step;
		if (player_position[turn] >= N_BOARD) // ���ܻ��� ó�� -  
		{
			player_position[turn] = N_BOARD-1;
		}
			
		if (player_position[turn]==N_BOARD-1)
		{
			player_status[turn] = PLAYERSTATUS_END;
			printf("%s reached to the end!! (coin : %d)\n", player_name[turn], player_coin[turn]); 
		}
		printf("Die result : %d, %s moved to %d!\n", step, player_name[turn], player_position[turn]);
		
		
		//2-4. ���� �ݱ�
		coinResult = board_getBoardCoin(player_position[turn]);
		if (coinResult > 0)
       {        
          player_coin[turn] += coinResult;
          printf("-> Lucky! %s got %i coins \n", player_name[turn], coinResult); 
       }
       else
           printf("-> Sorry, I see nothing there.\n");

		//2-5. ���������� ���� ����
		turn = (turn + 1)%N_PLAYER; //wrap around - N_PLAYER�� �Ǵ� ���� ���ư� 
		
		//2-6. ��� ���� if(����: ��� �÷��̾ �ѹ��� ���� ����) 
		if (turn == 0) 
		{	
			//��� ����
			int shark_pos = board_stepShark();
			printf("shark moved to %i\n"); 
			checkDie();
		} 
		
	} while (game_end() != 1); // �Ѹ��� �÷��̾ �� while�� �ѹ��� ���� �� 

	//3. ���� (���� ���, ��� ��)
		
	int alive_players = getAlivePLayer();
	printf("alive player num is %d\n", alive_players);
	
	int winner = getWinner();
	printf("the winner is %s", player_name[winner]);
	
	system("PAUSE");
	return 0;
}

	
