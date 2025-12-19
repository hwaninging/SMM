#include "smm_common.h"
#include "smm_database.h"
#include <stdio.h>
#include <stdlib.h>

//데이터베이스 배열 선언
smmList_t smmList[MAX_LIST_NUM];

//내부 함수 원형
static smmdbNode_t* get_node(int listNo, int index);
static void update_index(int listNo, int index, smmdbNode_t* node_p);
static void update_all_index(int listNo, smmdbNode_t* startNode_p);

//1. 데이터베이스 초기화
void smmdb_init(void)
{
    int i; //변수 선언은 맨 위
    for (i = 0; i < MAX_LIST_NUM; i++) {
        smmList[i].head_p = NULL;
        smmList[i].tail_p = NULL;
        smmList[i].count = 0;
        smmList[i].index = -1;
        smmList[i].node_p = NULL;
    }
}

// 2. 리스트에 객체 추가
void smmdb_addTail(int listNo, void* obj_p)
{
    smmdbNode_t* newNode_p; /* 변수 선언을 함수 최상단으로 이동 (C89 필수) */

    if (listNo < 0 || listNo >= MAX_LIST_NUM) {
        printf("[ERROR] 리스트 번호(%d)가 범위를 벗어납니다.\n", listNo);
        return;
    }
    
    //새 노드 생성
    newNode_p = (smmdbNode_t*)malloc(sizeof(smmdbNode_t));
    if (newNode_p == NULL) {
        printf("[ERROR] 노드 메모리 할당 실패.\n");
        return;
    }
    
    //데이터 설정
    newNode_p->data_p = obj_p;
    newNode_p->next_p = NULL;
    newNode_p->index = smmList[listNo].count;
    
    if (smmList[listNo].head_p == NULL) {
        newNode_p->prev_p = NULL;
        smmList[listNo].head_p = newNode_p;
        smmList[listNo].tail_p = newNode_p;
    } else {
        newNode_p->prev_p = smmList[listNo].tail_p;
        smmList[listNo].tail_p->next_p = newNode_p;
        smmList[listNo].tail_p = newNode_p;
    }

    smmList[listNo].count++;
}

//3. 인덱스로 내부 노드 가져오기 (내부 전용)
static smmdbNode_t* get_node(int listNo, int index)
{
    smmdbNode_t* current_p = NULL;
    int i;

    if (listNo < 0 || listNo >= MAX_LIST_NUM || index < 0 || index >= smmList[listNo].count) {
        return NULL;
    }
    
    if (smmList[listNo].index == index) {
        return smmList[listNo].node_p;
    }
    
    if (index <= smmList[listNo].count / 2) {
        current_p = smmList[listNo].head_p;
        for (i = 0; i < index; i++) {
            current_p = current_p->next_p;
        }
    } else { 
        current_p = smmList[listNo].tail_p;
        for (i = smmList[listNo].count - 1; i > index; i--) {
            current_p = current_p->prev_p;
        }
    }

    if (current_p != NULL) {
        update_index(listNo, index, current_p);
    }
    
    return current_p;
}

// 4. 외부에서 데이터를 가져가는 인터페이스
void* smmdb_getData(int listNo, int index)
{
    smmdbNode_t* node_p; 
    
    node_p = get_node(listNo, index);
    if (node_p != NULL) {
        return node_p->data_p;
    }
    return NULL;
}

// 5. 리스트 카운트
int smmdb_getCount(int listNo)
{
    if (listNo < 0 || listNo >= MAX_LIST_NUM) {
        return 0;
    }
    return smmList[listNo].count;
}

//6. 내부 인덱스 관리
static void update_index(int listNo, int index, smmdbNode_t* node_p)
{
    smmList[listNo].index = index;
    smmList[listNo].node_p = node_p;
}
