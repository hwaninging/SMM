
#include "smm_common.h"
#include "smm_object.h"
#include "smm_database.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//플레이어 객체 저장소
static smmPlayer_t* smm_players[MAX_PLAYER];
static int player_nr_local = 0;


//2. 객체 생성-----------------------------------------------------------
//2-1. 보드 노드 
void* smmObj_genNode(char* name, int type, int credit, int energy) {
      smmNode_t* newNode = (smmNode_t*)malloc(sizeof(smmNode_t));
      if (newNode == NULL) return NULL;
      
      strncpy(newNode->name, name, MAX_CHARNAME - 1);
      newNode->name[MAX_CHARNAME - 1] = '\0';
      
      newNode->type = (smmNode_e)type;
      newNode->credit = credit;
      newNode->energy = energy;
      
      return (void*)newNode; }

//2-2. 음식 카드  
void* smmObj_genFood(char* name, int energy) {
      smmFood_t* newFood = (smmFood_t*)malloc(sizeof(smmFood_t));
      if (newFood == NULL) return NULL;
      
      strncpy(newFood->name, name, MAX_CHARNAME - 1);
      newFood->name[MAX_CHARNAME - 1] = '\0';
      newFood->energy = energy;
      
      return (void*)newFood; }
//2-3. 축제 카드 
void* smmObj_genFest(char* name) {
      smmFest_t* newFest = (smmFest_t*)malloc(sizeof(smmFest_t));
      if (newFest == NULL) return NULL;
      
      strncpy(newFest->name, name, MAX_CHARNAME - 1);
      newFest->name[MAX_CHARNAME - 1] = '\0';
      
      return (void*)newFest; }
//2-4. 플레이어 객체 생성 및 초기화 
void generatePlayers(int n, int initEnergy) {
     char pName[MAX_CHARNAME];
     player_nr_local = 0;
     
     if (n > MAX_PLAYER || n <= 0) return;
     
     printf("\n--- Player Configuration ---\n");
     for (int i=0;i<n;i++) {
         printf("Enter name for Player %i: ", i+1);
         if (scanf("%s", pName) != 1)
         {
             sprintf(pName, "P%i", i+1);
         }
         while (getchar() != '\n' && !feof(stdin) && !ferror(stdin));
         
         smmPlayer_t* newPlayer = (smmPlayer_t*)malloc(sizeof(smmPlayer_t));
         if (newPlayer == NULL) break;
         
         //객체 멤버 초기화
         strncpy(newPlayer->name, pName, MAX_CHARNAME - 1);
         newPlayer->name[MAX_CHARNAME - 1] = '\0';
         newPlayer->currentPos = 0;
         newPlayer->energy = initEnergy;
         newPlayer->totalCredit = 0;
         newPlayer->gradeList_nr = LISTNO_OFFSET_GRADE + i;
         newPlayer->penalizeTurn = 0;
         
         smm_players[i] = newPlayer;
         player_nr_local++;
         
         printf("Player %s created with %i energy.\n", newPlayer->name, newPlayer->energy);
         }
     }

//3. 객체 접근 및 상태 관리 ---------------------------------------
//3-1-1. 플레이어 접근 함수
int smmObj_getPlayerCount(void)
{
    return player_nr_local;
}
//3-1-2. 플레이어 객체 접근 함수 
smmPlayer_t* smmObj_getPlayer(int playerIndex) {
             if (playerIndex >= 0 && playerIndex < player_nr_local)
             {
                 return smm_players[playerIndex];
             }
             return NULL;
}
//3-2. 플레이어 상태 출력 
void printPlayerStatus(void) {
    int playerCount = smmObj_getPlayerCount();
    smmPlayer_t* pPlayer;
    
    printf("\n==================================\n");
    printf("        CURRENT PLAYER STATUS       \n");
    printf("====================================\n");
    
    printf("%-10s | %-6s | %-6s | %-8s \n", "NAME", "ENERGY", "CREDIT", "POSITION");
    printf("------------------------------------\n");
    
    for (int i=0;i<playerCount;i++) {
        pPlayer = smmObj_getPlayer(i);
        
        if (pPlayer != NULL) {
                    printf("%-10s | %-6i | %-6i | %-8i\n", pPlayer->name, pPlayer->energy, pPlayer->totalCredit, pPlayer->currentPos);
                    }
    }
    printf("===================================\n");
}
    
//3-3. 졸업 여부 확인 (게임 종료 조건) 
int isGraduated(int playerIndex) {
    smmPlayer_t* pPlayer = smmObj_getPlayer(playerIndex);
    
    if (pPlayer == NULL) return 0;
    
    //총 학점이 30 이상이면 졸업
    if (pPlayer->totalCredit >= GRADUATE_CREDIT)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
