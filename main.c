#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_CHARNAME	200
#define MAX_DIE			6

#define N_PLAYER				3 // player 수 
#define PLAYERSTATUS_LIVE		0 //살아있다는 것을 0이라고 생각함 
#define PLAYERSTATUS_DIE		1 
#define PLAYERSTATUS_END		2

//플레이어 모델링 
int player_position[N_PLAYER]; //위치 
char player_name[N_PLAYER][MAX_CHARNAME]; //이름 
int player_coin[N_PLAYER]; //누적 동전 수 
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



int rolldie(void) //주사위 굴리기 함수 
{
	return rand()%MAX_DIE+1;
} 


void printPlayerPosition(int player) //플레이어 위치 출력 함수 
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

void printPlayerStatus(void) //플레이어 상태 출력 함수 
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

void checkDie(void) //플레이어 사망 여부 
{
	int i;
	for(i = 0;i< N_BOARD; i++) // 플레이어 별로 for문 반복 
	{	
		if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK) // player_status가 파손되었을 때 
		{
			player_status[i] = PLAYERSTATUS_DIE; //player_status[i]를 PLAYERSTATUS_DIE로 변경 
			printf("%s has died!", player_name[i]); //사망 상태를 출력 
		}
	}
}

int game_end(void) //게임 종료 함수 
{
	int i; 
	int flag_end = 1;
	
	//if all the players are died?
	for (i=0;i<N_PLAYER;i++)
	{
		
		if (player_status[i] == PLAYERSTATUS_LIVE) //모든 플레이어가 PLAYERSTATUS_LIVE상태가 아니면 종료 
		{
			flag_end = 0;
			break;
		}
		
	}
	return flag_end; 
}

int getAlivePLayer(void) //생존 플레이어 수 계산 및 반환 함수 
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

int getWinner(void) //생존 플레이어 중 동전이 가장 많은 플레이어 번호 반환 
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
	int turn = 0; // 몇번째 플레이어 실행 turn 
	int i;

	srand((unsigned)time(NULL)); 
    
	//0. opening
	opening();
	
	//1. 초기화 &플레이어 이름 결정
	board_initBoard();
	
	//step1-2 : initialize player
	for (i=0;i<N_PLAYER;i++)
	{
		player_position[i] = 0; // 스타트 지점 
		player_coin[i] = 0; //코인 스타트 
		player_status[i] = PLAYERSTATUS_LIVE; // 플레이어의 초기 상태 살아있음 
		printf("Player %i's name : ", i); //플레이어의 이름 입력 받기 
		scanf("%s", player_name[i]); // 이름 입력 
 	}

	
	//2. 반복문(플레이어 턴)
	do {
		int step;
		int coinResult;
		char c;
		int pos = player_position[turn];
		
		
		//게임할 수 있는 상황이라면 밑에를 실행시킴 - 안끝났으면 
		if(player_status[turn] != PLAYERSTATUS_LIVE) //살아있는 경우가 아니면 다음 코드를 바로 넘어간다. 
		{
			turn = (turn + 1)%N_PLAYER; // 무한반복이 일어나지 않도록 
			continue;
		}
		
		
		
		//2-1. 보드 & 플레이어의 상태 출력
		board_printBoardStatus();
		//for(i=0;i<N_PLAYER;i++)
		//	printPlayerPosition(i);	
		printPlayerStatus();
		
		//2-2. 주사위 던지기	
		printf("%s turn!! ", player_name[turn]); //플레이어 턴 출력 
		printf("Press any key to roll a die! : \n"); 
		scanf("%d", &c);
		fflush(stdin); //버퍼에 쌓였다가 프로그램으로 들어옴 -> 버퍼에 쌓여있을 수 있음 -> 여기 올때마다 입력을 받고 넘어감 
		step = rolldie(); // 주사위 굴리기 함수 호출 
		
		
		
 		//2-3. 이동	
		player_position[turn] += step; //player_position[turn]값에 주사위 결과를 더함 
		if (player_position[turn] >= N_BOARD) // 예외사항 처리 -  N_BOARD 이상 갔을 때 
		{
			player_position[turn] = N_BOARD-1;
		}
			
		if (player_position[turn]==N_BOARD-1) //보드 맨 끝까지 이동한 경우에 대한 처리 
		{
			player_status[turn] = PLAYERSTATUS_END; 
			printf("%s reached to the end!! (coin : %d)\n", player_name[turn], player_coin[turn]); 
		}
		printf("Die result : %d, %s moved to %d!\n", step, player_name[turn], player_position[turn]); // 이동 결과 출력 
		
		
		//2-4. 동전 줍기
		coinResult = board_getBoardCoin(player_position[turn]); //이동한 위치에서 board_getBoardCoin 함수 호출 
		if (coinResult > 0) //동전이 존재하는 경우 동전 습득 정보를 츨력 
       {        
          player_coin[turn] += coinResult; // 반환된 동전 값을 player_coin[turn]에 더함 
          printf("-> Lucky! %s got %i coins \n", player_name[turn], coinResult); 
       }
       else
           printf("-> Sorry, I see nothing there.\n");

		//2-5. 다음턴으로 가는 동작
		turn = (turn + 1)%N_PLAYER; //wrap around - N_PLAYER가 되는 순간 돌아감 
		
		//2-6. 상어 동작 if(조건: 모든 플레이어가 한번씩 턴을 돈다) 
		if (turn == 0) 
		{	
			//상어 동작
			int shark_pos = board_stepShark(); //상어 이동 진행 
			printf("shark moved to %i\n");  
			checkDie(); //상어 이동 후 플레이어의 생존 여부 확인 
		} 
		
	} while (game_end() != 1); // 한명의 플레이어가 이 while문 한번에 도는 것  
	//3. 정리 (승자 계산, 출력 등)
		
	int alive_players = getAlivePLayer();
	printf("alive player num is %d\n", alive_players);
	
	int winner = getWinner();
	printf("the winner is %s", player_name[winner]);
	
	system("PAUSE");
	return 0;
}

	
