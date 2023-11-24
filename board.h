//board관련 macro정의 
#define N_BOARD					15 //칸 수
#define BOARDSTATUS_OK  		1 //살아있는 칸 
#define BOARDSTATUS_NOK  		0 // 파손된 칸 

//coin관련 macro정의
#define N_COINPOS  				12
#define MAX_COIN				4 //최대 4개의 코인이 한 칸에 들어감

//shark관련 macro정의
#define MAX_SHARKSTEP			6 //상어의 최대 이동 가능수  
#define SHARK_INITPOS			-4 //시작점보다 4개 앞부터 시작
 
 
int board_initBoard(void); //보드 초기화 
int board_printBoardStatus(void); // 전체 보드의 상태 출력 

int board_getBoardStatus(int pos); //동전 습득 명령 
int board_getBoardCoin(int pos); //특정 칸의 파손 여부 출력 

int board_getSharkPosition(void); //상어의 위치 출력 
int board_stepShark(void); // 상어 전진 명령 






