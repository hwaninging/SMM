#ifndef smm_object_h
#define smm_object_h

#include "smm_common.h"

//객체 구조체 정의
typedef struct smmNode_s {
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
} smmNode_t;

typedef struct smmFood_s {
    char name[MAX_CHARNAME];
    int energy;
} smmFood_t;

typedef struct smmFest_s {
    char name[MAX_CHARNAME];
} smmFest_t;

typedef struct smmGrade_s {
    char lectureName[MAX_CHARNAME];
    int credit;
    int grade;
} smmGrade_t;

typedef struct smmPlayer_s {
    char name[MAX_CHARNAME];
    int energy;
    int currentPos;
    int totalCredit;
    int penalizeTurn;
} smmPlayer_t;

//함수 원형 
void* smmObj_genNode(const char* name, int type, int credit, int energy);
void* smmObj_genFood(const char* name, int energy);
void* smmObj_genFest(const char* name);
void* smmObj_genGrade(const char* lectureName, int credit, int grade);

int generatePlayers(int num, int initEnergy);
smmPlayer_t* smmObj_getPlayer(int index);
int smmObj_getPlayerCount(void);
int isGraduated(int playerIndex);
void printPlayerStatus(void);

#endif
