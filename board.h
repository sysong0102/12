//board���� macro���� 
#define N_BOARD					15 //ĭ ��
#define BOARDSTATUS_OK  		1 //����ִ� ĭ 
#define BOARDSTATUS_NOK  		0 // �ļյ� ĭ 

//coin���� macro����
#define N_COINPOS  				12
#define MAX_COIN				4 //�ִ� 4���� ������ �� ĭ�� ��

//shark���� macro����
#define MAX_SHARKSTEP			6 //����� �ִ� �̵� ���ɼ�  
#define SHARK_INITPOS			-4 //���������� 4�� �պ��� ����
 
 
int board_initBoard(void); //���� �ʱ�ȭ 
int board_printBoardStatus(void); // ��ü ������ ���� ��� 

int board_getBoardStatus(int pos); //���� ���� ��� 
int board_getBoardCoin(int pos); //Ư�� ĭ�� �ļ� ���� ��� 

int board_getSharkPosition(void); //����� ��ġ ��� 
int board_stepShark(void); // ��� ���� ��� 






