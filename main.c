#include "smm_common.h"
#include "smm_object.h"
#include "smm_database.h"
#include <string.h>
#include <time.h> 
#include <stdio.h>
#include <stdlib.h> 

// 함수 원형 (Prototyping)
int load_board_config(const char* filename);
int load_food_config(const char* filename);
int load_fest_config(const char* filename);
void game_init(void);
void game_play(void);
void handle_node_action(smmPlayer_t* pPlayer, smmNode_t* pNode, int playerIndex);
void move_player(smmPlayer_t* pPlayer, int steps);
int throw_dice(void);
void printPlayerGrades(int playerIndex);

//1. 파일 로딩 구현
int load_board_config(const char* filename) {
    FILE* fp = fopen(filename, "r");
    char name[MAX_CHARNAME];
    int type, credit, energy, count = 0;
    
    if (fp == NULL) return -1;
    smmdb_init();

    while (fscanf(fp, "%s %d %d %d", name, &type, &credit, &energy) == 4) {
        void* nodeObj = smmObj_genNode(name, type, credit, energy);
        if (nodeObj != NULL) {
            smmdb_addTail(LIST_NODE, nodeObj);
            count++;
        }
    }
    fclose(fp);
    return count;
}

// 2. 주사위 및 플레이어 이동
int throw_dice(void) {
    return (rand() % MAX_DIE) + 1;
}

void move_player(smmPlayer_t* pPlayer, int steps) {

    int boardLen;
    int i;
    int newPos;
    smmNode_t* node; //루프 안에서 쓰던 변수도 여기로 이동

    boardLen = smmdb_getCount(LIST_NODE);
    
    for (i = 1; i <= steps; i++) {
        newPos = (pPlayer->currentPos + 1) % boardLen;
        pPlayer->currentPos = newPos;
        
        //시작점 통과 시 에너지 보충
        node = (smmNode_t*)smmdb_getData(LIST_NODE, newPos);
        if (node != NULL && node->type == SMM_NODE_START) {
            pPlayer->energy += node->energy;
            printf("   -> [집 통과] 에너지 %d 보충!\n", node->energy);
        }
    }
}

//3. 노드 도착 액션
void handle_node_action(smmPlayer_t* pPlayer, smmNode_t* pNode, int playerIndex) {
    int randomGrade, listNo;
    void* gradeObj;
    const char* gradeNames[] = {"A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F"};
    char choice;

    printf("   [도착] %s (%d번 노드)\n", pNode->name, pPlayer->currentPos);

    switch (pNode->type) {
        case SMM_NODE_LECTURE:
            if (pPlayer->energy >= pNode->energy) {
                printf("   * 수강하시겠습니까? (y/n): ");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    pPlayer->energy -= pNode->energy;
                    pPlayer->totalCredit += pNode->credit;
                    
                    randomGrade = rand() % 9;
                    gradeObj = smmObj_genGrade(pNode->name, pNode->credit, randomGrade);
                    listNo = LIST_PLAYER_GRADE_START + playerIndex;
                    smmdb_addTail(listNo, gradeObj);
                    
                    printf("   * 성적: %s, 남은 에너지: %d\n", gradeNames[randomGrade], pPlayer->energy);
                }
            } else {
                printf("   * 에너지가 부족하여 수강 불가!\n");
            }
            break;
        case SMM_NODE_FOOD:
            pPlayer->energy += pNode->energy;
            printf("   * 식당 도착! 에너지 %d 충전 (현재:%d)\n", pNode->energy, pPlayer->energy);
            break;
    }
}

//4. 성적 출력 함수 
void printPlayerGrades(int playerIndex) {
    int i, count, listNo;
    const char* gradeNames[] = {"A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F"};
    listNo = LIST_PLAYER_GRADE_START + playerIndex;
    count = smmdb_getCount(listNo);

    printf("\n--- [%s 님의 성적표] ---\n", smmObj_getPlayer(playerIndex)->name);
    for (i = 0; i < count; i++) {
        smmGrade_t* g = (smmGrade_t*)smmdb_getData(listNo, i);
        if (g != NULL) {
            printf(" - %-15s : %d학점 (%s)\n", g->lectureName, g->credit, gradeNames[g->grade]);
        }
    }
}

//5. 메인 함수
int main(void) {
    int playerCount, turn = 0, dice, winner = -1;
    srand((unsigned int)time(NULL));

    //초기화
    if (load_board_config("marbleBoardConfig.txt") <= 0) exit(1);
    printf("참여 인원 입력: ");
    scanf("%d", &playerCount);
    generatePlayers(playerCount, 100);

    //게임 루프
    while (winner == -1) {
        smmPlayer_t* p = smmObj_getPlayer(turn);
        printPlayerStatus();
        printf("\n[%s 님의 턴] 엔터키를 눌러 주사위 던지기...", p->name);
        fflush(stdin); getchar();

        dice = throw_dice();
        move_player(p, dice);
        handle_node_action(p, (smmNode_t*)smmdb_getData(LIST_NODE, p->currentPos), turn);

        if (isGraduated(turn) && p->currentPos == 0) winner = turn;
        turn = (turn + 1) % playerCount;
    }

    printf("\n축하합니다! %s 님이 졸업에 성공했습니다.\n", smmObj_getPlayer(winner)->name);
    printPlayerGrades(winner);

    //창이 바로 닫히지 않게
    printf("\n결과를 확인하셨으면 엔터키를 눌러 종료하세요...");
    fflush(stdin); // 입력 버퍼 비우기
    getchar();     // 사용자 입력 대기
    getchar();    

    return 0;
}
