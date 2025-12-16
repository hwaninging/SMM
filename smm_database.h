
#ifndef smm_database_h
#define smm_database_h

#include "smm_common.h"

typedef struct smmNode_s {
        int index; //노드의 인덱스(순서 빨리 찾기) 
        void* data_p; // 실제 객체 데이터 포인터 
        struct smmNode_s* next_p; //다음 노드 포인터 
        struct smmNode_s* prev_p; //이전 노드 포인터 
} smmNode_t; 

//함수 
void smmdb_init(void); 

void smmdb_addTail(int listNo, void* data); //리스트 끝에 데이터 추가

int smmadb_deleteData(int list_nr, int index); //데이터 삭제

void* smmdb_getData(int listNo, int index); //인덱스번째 데이터 반환

int smmdb_getCount(int listNo); //데이터베이스 길이 반환  

#endif
