#include "smm_common.h"
#include "smm_database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

#define LIST_END          -1

static smmNode_t* list_database[MAX_LIST]; //리스트 헤드 포인터
static smmNode_t* listPtr[MAX_LIST]; //캐싱을 위한 포인터
static int list_cnt[MAX_LIST]; //리스트 개수 카운터

//내부 함수: 노드 생성
static smmNode_t* genNode(void)
{
       //노드 생성을 위한 메모리 할당
       smmNode_t* ndPtr = (smmNode_t*)malloc(sizeof(smmNode_t));
       if (ndPtr != NULL)
       {
                 ndptr->next_p = NULL;
                 ndptr->data_p = NULL; 
                 ndptr->prev_p = NULL; 
       }
       
       return ndPtr;
}

//내부 함수: 인덱스로 노드 검색
static smmNode_t* smmList(int list_nr, int index)
{
       smmNode_t* ndPtr = list_database[list_nr];
       
       //lsitPtr 활용 검색
       if (listPtr[list_nr] != NULL && listPtr[list_nr]->index <= index)
       {
           ndPtr = listPtr[list_nr];
       }
       
       //잘못된 입력 검사
       if (index < -1)
       {
                 printf("[ERROR] smmList() : 리스트가 NULL이거나 인덱스가 잘못되었습니다. (index : %i)\n", index);
                 return NULL;
        }
       if (index >= list_cnt[list_nr])
    {
        printf("[ERROR] smmList() : 인덱스가 리스트 길이보다 큽니다. (len:%i, index:%i)\n", list_cnt[list_nr], index);
        return NULL;
    }
    
    // 인덱스를 찾을 때까지 다시 
    while (ndPtr != NULL)
    {
        if (ndPtr->index == index)
             break;
        ndPtr = ndPtr->next_p; // 다음 노드 이동
    }
    
    return ndPtr;
}

// 내부 함수: 인덱스 업데이트 (삭제 시)
static int updateIndex(int list_nr)
{
    int index=0;
    smmNode_t* ndPtr = list_database[list_nr];
    
    while ( ndPtr != NULL ) // 끝 노드까지
    {
        ndPtr->index = index++;
        ndPtr = ndPtr->next_p; // 다음 노드 이동
    }
    
    return index;
}


// API 함수: 리스트 끝에 데이터 추가
int smmdb_addTail(int list_nr, void* obj)
{
    smmNode_t* ndPtr;
    smmNode_t* newNdPtr;
    
    if (obj == NULL)
    {
        printf("[ERROR] smmdb_addTail() : addTail 실패 : 입력 객체 포인터가 NULL입니다.\n");
        return -1;
    }
    
    newNdPtr = genNode();
    if (newNdPtr == NULL)
    {
        printf("[ERROR] smmdb_addTail() : addTail 실패 : 노드 생성에 실패했습니다.\n");
        return -1; 
    }
    newNdPtr->data_p = obj; // 객체 데이터 포인터 저장
    
    // 리스트 마지막에 노드 추가
    if (list_database[list_nr] == NULL)
    {
        list_database[list_nr] = newNdPtr;
        newNdPtr->index = 0;
    }
    else
    {
        ndPtr = smmList(list_nr, list_cnt[list_nr]-1);
        
        ndPtr->next_p = newNdPtr;
        newNdPtr->prev_p = ndPtr; // 이중 연결 리스트
        newNdPtr->index = ndPtr->index+1;
    }
    
    listPtr[list_nr] = newNdPtr; // 캐싱 포인터 업데이트
    
    list_cnt[list_nr]++;
    
    return 0;
}


// API 함수: 인덱스로 데이터 삭제
int smmdb_deleteData(int list_nr, int index)
{
    smmNode_t* ndPrevPtr;
    smmNode_t* ndNextPtr;
    smmNode_t* delNdPtr;
    
    // 삭제할 노드 검색
    if ( (delNdPtr = smmList(list_nr, index)) == NULL)
    {
        printf("[ERROR] smmdb_deleteData() : deleteData 실패: 입력된 인덱스가 유호하지 않습니다.  (%i)!\n", index);
        return -1;
    }
    
    ndPrevPtr = delNdPtr->prev_p;
    if (ndPrevPtr != NULL)
    {
        // 이전 노드의 next를 다음 노드에 연결
        ndPrevPtr->next_p = delNdPtr->next_p;
    } else {
        // Head 노드를 삭제하는 경우, Head 업데이트
        list_database[list_nr] = delNdPtr->next_p;
    }

    ndNextPtr = delNdPtr->next_p;
    if (ndNextPtr != NULL)
    {
        // 다음 노드의 prev를 이전 노드에 연결
        ndNextPtr->prev_p = delNdPtr->prev_p;
    }
    
    // 동적 메모리 해제
    free(delNdPtr->data_p); // 객체 데이터 메모리 해제
    free(delNdPtr);         // 노드 자체 메모리 해제
    
    list_cnt[list_nr]--;
    
    if (list_cnt[list_nr] == 0)
    {
        list_database[list_nr] = NULL;
    }
    else
    {
        updateIndex(list_nr); // 인덱스 재정렬
    }
    
    return 0;
}


// API 함수: 리스트 길이 반환
int smmdb_getCount(int list_nr)
{
    return list_cnt[list_nr];
}


// API 함수: 인덱스로 데이터 객체 반환
void* smmdb_getData(int list_nr, int index)
{
    void* obj = NULL;
    smmNode_t* ndPtr;
    
    // 노드 검색
    if ((ndPtr = smmList(list_nr, index)) != NULL)
    {
        obj = (void*)ndPtr->data_p;
        listPtr[list_nr] = ndPtr; // 캐싱 포인터 업데이트
    }
    
    if (obj == NULL)
        printf("[ERROR] smmdb_getData() : there is no data of index %i\n", index);
    
    return obj;
}

// API 함수: 데이터베이스 초기화
void smmdb_init(void)
{
    for (int i = 0; i < MAX_LIST; i++)
    {
        list_database[i] = NULL;
        listPtr[i] = NULL;
        list_cnt[i] = 0;
    }
}
