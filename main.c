#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"


//보드 구성 매개변수 
static int board_nr;
static int food_nr;
static int festival_nr;



//function prototypes (미리 구성하고 하나씩 짜면 되는 것) 
#if 0
int isGraduated(void); //졸업한 플레이어 있는지 확인. 
void generatePlayers(int n, int initEnergy); //새 플레이어 생성. 
void printGrades(int player); //플레이어 성적 기록 
void goForward(int player, int step); //플레이어가 보드에서 step단계로 이동.(플레이어 졸업했는지 확인) 
void printPlayerStatus(void); //각 턴이 시작될 때마다 모든 플레이어 상태 출력.
float calcAverageGrade(int player); //플레이어 평균 성적 계산. 
smmGrade_e takeLecture(int player, char *lectureName, int credit); //강의 듣기(선수 성적 입력) 
void* findGrade(int player, char *lectureName); //플레이어 성적 기록에서 성적 찾기 
void printGrades(int player); //모든 성적 기록 인쇄 
#endif




int rolldie(int player)
{
    char c;
    printf("주사위를 굴리려면 아무 키나 눌러주세요.(등급을 보려면 g를 눌러주세요:");
    c = getchar();
    fflush(stdin);
    
#if 0
    if (c == 'g')
        printGrades(player);
#endif
    
    return (rand()%MAX_DIE + 1);
}

#if 0
//플레이어가 노드에 머무르는 동작 코드 
void actionNode(int player)
{
    switch(type)
    {
        //case 강의:
        default:
            break;
    }
}
#endif


int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    srand(time(NULL));
    
    
    //1. 매개변수 가져오기 ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");
    while () //read a node parameter set
    {
        //매개변수 set 저장 
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    

    //2. 음식 카드 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    while () //음식 매개변수 
    {
        //매개변수 set 저장 
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
    
    //3. 축제 카드 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while () //read a festival card string
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    
    
    
    //2. 플레이어 구성 ---------------------------------------------------------------------------------
    /*
    do
    {
        //input player number to player_nr
    }
    while ();
    generatePlayers();
    */
    
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while () //is anybody graduated?
    {
        int die_result;
        
        //4-1. initial printing
        //printPlayerStatus();
        
        //4-2. die rolling (if not in experiment)
        
        
        //4-3. go forward
        //goForward();
        pos = pos + rand()%6+1; //주사위 랜덤 
		//4-4. take action at the destination node of the board
        //actionNode();
        
        //4-5. next turn
        
    }

    
    return 0;
}
