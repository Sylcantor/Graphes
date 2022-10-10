


//#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "unionfind.h"

//////////////////////////////////////////////////////
// INITIALISER UNE PARTITION
// precondition: 
// postcondition: 
void init_partition(partition* p, int n){

    int i;

    p->nb_element = n;
    p->nb_partition = n;

    if(p->nb_element==0){
        p->element_id_partition=NULL;p->node_l_nb=NULL;p->node_list=NULL;
    }
    else{

        if( (p->element_id_partition =(int*)malloc(p->nb_element*sizeof(int))) == NULL )
            report_error("init_partition: malloc() error");
        for(i=0;i<p->nb_element;i++){
            p->element_id_partition[i] = i;
        }

        if( (p->node_list =(int**)malloc(p->nb_element*sizeof(int*))) == NULL )
            report_error("init_partition: malloc() error");
        for(i=0;i<p->nb_element;i++){
            if( (p->node_list[i] =(int*)malloc(p->nb_element*sizeof(int))) == NULL )
                report_error("init_partition: malloc() error");
            p->node_list[i][0] = i;
        }

        if( (p->node_l_nb =(int*)malloc(p->nb_element*sizeof(int))) == NULL )
            report_error("init_partition: malloc() error");
        for(i=0;i<p->node_l_nb;i++){
            p->node_l_nb[i] = 1;
        }
    }
}

int find(partition* p, int id_element){
    return(p->element_id_partition[id_element]);
}

void make_union(partition* p, int id_elt_1, int id_elt_2){
    int tmp,i;

    int groupe_1 = find(p,id_elt_1);
    int groupe_2 = find(p,id_elt_2);

    int grp_1_nb_elt = p->node_l_nb[groupe_1];
    int grp_2_nb_elt = p->node_l_nb[groupe_2];

    if(grp_1_nb_elt==grp_2_nb_elt){
        if(groupe_2>groupe_1){
            tmp = groupe_1;
            groupe_1 = groupe_2;
            groupe_2 = tmp;
        }
    }
    else if(grp_2_nb_elt>grp_1_nb_elt){
        tmp = groupe_1;
        groupe_1 = groupe_2;
        groupe_2 = tmp;

        tmp = grp_1_nb_elt;
        grp_1_nb_elt = grp_2_nb_elt;
        grp_2_nb_elt = tmp;
    }

    for(i=0;i<grp_2_nb_elt;i++){
        p->element_id_partition[p->node_list[groupe_2][i]] = groupe_1;

        p->node_list[groupe_1][p->node_l_nb[groupe_1]+i] = p->node_list[groupe_2][i];
        // A verifier
    }
}