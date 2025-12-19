#include "smm_common.h"
#include "smm_object.h"
#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

// 전역 변수: 플레이어 객체 배열
static smmPlayer_t* players[MAX_PLAYER];
static int playerCount = 0;

void* smmObj_genNode(const char* name, int type, int credit, int energy) {
    smmNode_t* newNode = (smmNode_t*)malloc(sizeof(smmNode_t));
    if (newNode != NULL) {
        strncpy(newNode->name, name, MAX_CHARNAME - 1);
        newNode->name[MAX_CHARNAME - 1] = '\0';
        newNode->type = type;
        newNode->credit = credit;
        newNode->energy = energy;
    }
    return (void*)newNode;
}

void* smmObj_genFood(const char* name, int energy) {
    smmFood_t* newFood = (smmFood_t*)malloc(sizeof(smmFood_t));
    if (newFood != NULL) {
        strncpy(newFood->name, name, MAX_CHARNAME - 1);
        newFood->name[MAX_CHARNAME - 1] = '\0';
        newFood->energy = energy;
    }
    return (void*)newFood;
}

void* smmObj_genFest(const char* name) {
    smmFest_t* newFest = (smmFest_t*)malloc(sizeof(smmFest_t));
    if (newFest != NULL) {
        strncpy(newFest->name, name, MAX_CHARNAME - 1);
        newFest->name[MAX_CHARNAME - 1] = '\0';
    }
    return (void*)newFest;
}

void* smmObj_genGrade(const char* lectureName, int credit, int grade) {
    smmGrade_t* newGrade = (smmGrade_t*)malloc(sizeof(smmGrade_t));
    if (newGrade != NULL) {
        strncpy(newGrade->lectureName, lectureName, MAX_CHARNAME - 1);
        newGrade->lectureName[MAX_CHARNAME - 1] = '\0';
        newGrade->credit = credit;
        newGrade->grade = grade;
    }
    return (void*)newGrade;
}

int generatePlayers(int num, int initEnergy) {
    int i; 
    playerCount = 0;

    for (i = 0; i < num; i++) {
        players[i] = (smmPlayer_t*)malloc(sizeof(smmPlayer_t));
        if (players[i] != NULL) {
            printf("%d 번째 플레이어 이름을 입력하세요: ", i + 1);
            scanf("%s", players[i]->name);
            players[i]->energy = initEnergy;
            players[i]->currentPos = 0; 
            players[i]->totalCredit = 0;
            players[i]->penalizeTurn = 0; 
            playerCount++;
        }
    }
    return 0;
}

smmPlayer_t* smmObj_getPlayer(int index) {
    if (index >= 0 && index < playerCount) return players[index];
    return NULL;
}

int smmObj_getPlayerCount(void) {
    return playerCount;
}

int isGraduated(int playerIndex) {
    if (players[playerIndex] == NULL) return 0;
    return (players[playerIndex]->totalCredit >= GRADUATE_CREDIT);
}

void printPlayerStatus(void) {
    int i;
    printf("\n--- 현재 플레이어 상태 ---\n");
    for (i = 0; i < playerCount; i++) {
        smmPlayer_t* p = players[i];
        if (p != NULL) {
            printf("[#%d %s] 위치: %d, 에너지: %d, 학점: %d\n", 
                   i + 1, p->name, p->currentPos, p->energy, p->totalCredit);
        }
    }
    printf("-------------------------\n");
}
