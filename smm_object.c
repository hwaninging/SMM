//
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODENR      100
#define MAX_NODETYPE    7
#define MAX_GRADE       9

#define SMMNODE_TYPE_LECTURE       0
#define SMMNODE_TYPE_RESTAURANT    1
#define SMMNODE_TYPE_LABORATORY    2
#define SMMNODE_TYPE_HOME          3
#define SMMNODE_TYPE_GOTOLAB       4
#define SMMNODE_TYPE_FOODCHANGE    5
#define SMMNODE_TYPE_FESTIVAL      6

static int smm_nodNr = 0; //첨에 암것도 저장X 
static char smm_name[MAX_NODENR][MAX_CHARNAME];
static int smm_type[MAX_NODENR];
static int smm_credit[MAX_NODENR];
static int smm_energy[MAX_NODENR];



//object generation
//node 정보 그룹을 만들어준것 
int smmObj_genNode(char* name, int type, int credit, int energy) //input은 위에 4가지 
{
     strcpy(smm_name[smm_nodeNr], name];
    smm_type[smm_nodeNr] = type;
    smm_type[smm_nodeNr] = credit;
    smm_type[smm_nodeNr] = energy;
    
    smm_nodeNr++; //하나 더 늘려주는  
    
    return (smm_nodeNr); //몇 개가 저장돼있는지 확인하기 위해  
}



//member retrieving
char* smmObj_getName(int node_nr) //4개 해야됑 아마도  
{
      return (smm_name[node_nr]);
} 

char* smmObj_getType(int node_nr)
{
      return (smm_type[node_nr]);
} 

#if 0
//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

