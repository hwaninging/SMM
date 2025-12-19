#ifndef smm_common_h
#define smm_common_h

// 1. 핵심 상수
#define MAX_CHARNAME        32  
#define MAX_PLAYER          4   
#define MAX_DIE             6   
#define GRADUATE_CREDIT     15  // 졸업에 필요한 최소 학점

// 2. 열거형 정의

// 2-1. 보드 노드 유형 (smmNode_e)
typedef enum {
    SMM_NODE_LECTURE = 0,   // 0. 강의
    SMM_NODE_FOOD,          // 1. 식당
    SMM_NODE_LABORATORY,    // 2. 실험실
    SMM_NODE_START,         // 3. 집
    SMM_NODE_GOLAB,         // 4. 실험
    SMM_NODE_FOODCHANGE,    // 5. 보충 찬스
    SMM_NODE_FESTIVAL       // 6. 축제
} smmNode_e;

// 2-2. 성적 유형 (smmGrade_e)
typedef enum {
    SMM_GRADE_AP = 0,       
    SMM_GRADE_A0,           
    SMM_GRADE_BP,           
    SMM_GRADE_B0,           
    SMM_GRADE_CP,           
    SMM_GRADE_C0,           
    SMM_GRADE_DP,           
    SMM_GRADE_D0,           
    SMM_GRADE_F             
} smmGrade_e;

// 2-3. 리스트 유형 (smmList_e)
typedef enum {
    LIST_NODE = 0,          // 0. 보드 노드
    LIST_FOOD,              // 1. 음식 카드
    LIST_FEST,              // 2. 축제 카드
    // 플레이어 성적 리스트 시작 인덱스 (LIST_PLAYER_GRADE_START + playerIndex)
    LIST_PLAYER_GRADE_START 
} smmList_e;


#endif
