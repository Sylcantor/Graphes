


#ifndef _UNIONFIND_

#define _UNIONFIND_

#include <stdio.h>
#include "wnodelist.h"

typedef struct partition{
  int nb_element;
  int nb_partition;
  int* element_id_partition;
  nodl** node_list;
  int* node_l_nb;
} partition;


/**
 * Create a new partition
 * @condition: p is not null
 * @param n the number of elements in the partition
*/
void init_partition(partition* p, int n);


/**
 * Find the group of an element
 * @condition: p is initialized and id_element is in the partition
 * @param p the partition
 * @param id_element the element
 * @return the group of the element
*/
int find(partition* p, int id_element);

/**
 * Merge two groups
 * @condition: p is not null, p is initialized and id_groupe_1 and id_groupe_2 are in the partition
 * @param p the partition
 * @param id_groupe_1 the first group
 * @param id_groupe_2 the second group
*/
void make_union(partition* p, int id_elt_1, int id_elt_2);

/**
 * Free the partition
 * @param p the partition
*/
void free_partition(partition* p);


#endif