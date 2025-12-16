
#ifndef smm_database_h
#define smm_database_h

#include "smm_common.h"

#define LISTNO_NODE             0
#define LISTNO_FOODCARD         1
#define LISTNO_FESTCARD         2
#define LISTNO_OFFSET_GRADE     3

int smmdb_addTail(int list_nr, void* obj);          //add data to tail
int smmdb_deleteData(int list_nr, int index);       //delete data
int smmdb_len(int list_nr);                   //get database length
void* smmdb_getData(int list_nr, int index);        //get index'th data

//데이터베이스 노드 구조체
typedef struct smmNode_s {
        void* data_p; //실제 객체 데이터를 가리키는 포인터 
        struct smmNode_s* next_p; //다음 노드를 가리키는 포인터 
} smmNode_t;

//함수 원형
void smmdb_init(void); 
void smmdb_addTail(int listNo, void* data);
void* smmdb_getData(int listNo, int index);
int smmdb_getCount(int listNo);

#endif
