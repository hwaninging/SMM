#ifndef smm_database_h
#define smm_database_h

#include "smm_common.h"

// MAX_LIST_NUM은 smm_common.h의 LIST_PLAYER_GRADE_START를 사용하여 계산
#define MAX_LIST_NUM (LIST_PLAYER_GRADE_START + MAX_PLAYER)

// 리스트 노드 구조체 
typedef struct smmdbNode_s {
    void* data_p;      // 데이터 포인터 
    struct smmdbNode_s* next_p; 
    struct smmdbNode_s* prev_p; 
    int index;         
} smmdbNode_t; 

// 리스트 관리 구조체
typedef struct {
    smmdbNode_t* head_p; 
    smmdbNode_t* tail_p; 
    int count;           
    int index;           
    smmdbNode_t* node_p; 
} smmList_t;


// 함수 원형

void smmdb_init(void);
void smmdb_addTail(int listNo, void* obj_p);
void* smmdb_getData(int listNo, int index);
int smmdb_getCount(int listNo);

#endif
