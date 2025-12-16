
#ifndef smm_object_h
#define smm_object_h

#include "smm_common.h"

//1. 객체 구조체
//1-1. 보드 노드 
  typedef struct {
        char name[MAX_CHARNAME];  //노드 이름 
        smmNode_e type;           //노드 유형 
        int credit;               //획득/소모 학점 
        int energy;               //소모/보충 에너지 
  } smmNode_t;

//1-2. 음식 카드
  typedef struct {
          char name[MAX_CHARNAME];
          int energy; //획득하는 에너지 값
  } smmFood_t;

//1-3. cnrwp zkem
  typedef struct {
          char name[MAX_CHARNAME];
  } smmFest_t;
          
//1-4. 플레이어
  typedef struct {
          char name[MAX_CHARNAME];
          int currentPos;    //현재 보드판 위치
          int energy;        //현재 남은 에너지
          int totalCredit;   //현재 누적 학점
          int gradeList_nr;  //플레이어의 성적 리스트 번호
          int penaliseTurn;  //페널티 턴 수 (0이면 행동 가능)
  } smmPlayer_t;
    
//2. 객체 생성

void* smmObj_genNode(char* name, int type, int credit, int energy);
void* smmObj_genFood(char* name, int energy);
void* smmObj_genFest(char* name);

//플레이어 설정 함수
void generatePlayers(int n, int initEnergy);

//3. 객체 접근 및 상태 관리 
smmPlayer_t* smmObj_getPlayer(int playerIndex);
int smmObj_getPlayerCount(void);

//게임 상태 관리
int isGraduated(int playerIndex);
void printPlayerStatus(void); 

#endif 
