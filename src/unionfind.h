#ifndef _UNIONFIND_

#define _UNIONFIND_

#include <stdio.h>
#include "wnodelist.h"



typedef struct partition{
  int nb_element;
  int nb_partition;
  int* element_id_partition;
  int** node_list;
  int* node_l_nb;
} partition ;


//////////////////////////////////////////////////////
// INITIALISER UNE PARTITION
// precondition: p est non null et *p est initalise
// postcondition: 
void init_partition(partition* p, int n);

//////////////////////////////////////////////////////
//  RETOURNER IDENTIFIANT D UNE PARTITION
// precondition: p est non null et *p est initalise, id_element appartient a la partition
// postcondition: retourne identifiant du groupe de la partition auquel cet element appartient. 
int find(partition* p, int id_element);

//////////////////////////////////////////////////////
// UNION PARTITION
// precondition: p est non null et *p est initalise
// postcondition: la partition la plus grande est actualise en ajoutant l autre partition
void make_union(partition* p, int id_elt_1, int id_elt_2);

#endif
