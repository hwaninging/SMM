
#ifndef smm_common_h
#define smm_common_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARNAME             200
#define GRADUATE_CREDIT          30
#define MAX_DIE                  6
#define MAX_PLAYER               10 //최대 플레이어 수 

//1.리스트 유형
#define LIST_NODE                0 //보드 노드 리스트 
#define LIST_FOOD                1 //음식 카드 리스트 
#define LIST_FEST                2 //축제 카트 리스트 
#define LIST_PLAYER_GRADE_START  3 //플레이어 성적 리스트 

//2. 전체 리스트 최대 개수
#define MAX_LIST                (LIST_PLAYER_GRADE_START + MAX_PLAYER) 

//3. 플레이어 객체 생성 시 성적 리스트 번호
#define LISTNO_OFFSET_GRADE      LIST_PLAYER_GRADE_START 

//노드 유형 정의 
typedef enum {
        SMM_NODE_LECTURE = 0, //0 강의 
        SMM_NODE_FOOD,        //1 식당 
        SMM_NODE_LABORATORY,  //2 실험실 
        SMM_NODE_START,       //3 집(시작) 
        SMM_NODE_GOLAB,       //4 실험(=무인도) 
        SMM_NODE_FOODCHANGE,  //5 음식 카드 
        SMM_NODE_FESTIVAL     //6 축제 카드
} smmNode_e;
        
//강의 학점 
#define SMM_GRADE_AP 0 //A+
#define SMM_GRADE_A0 1 //A0 
#define SMM_GRADE_BP 2 //B+ 
#define SMM_GRADE_B0 3 //B0
#define SMM_GRADE_CP 4 //C+ 
#define SMM_GRADE_C0 5 //C0
#define SMM_GRADE_DP 6 //D+ 
#define SMM_GRADE_D0 7 //D0
#define SMM_GRADE_F 8 //F (학점 미인정) 

#endif
