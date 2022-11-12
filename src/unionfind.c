


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

        if( (p->node_list =(nodl**)malloc(p->nb_element*sizeof(nodl*))) == NULL )
            report_error("init_partition: malloc() error");
        for(i=0;i<p->nb_element;i++){
            if( (p->node_list[i] =(nodl*)malloc(p->nb_element*sizeof(nodl))) == NULL )
                report_error("init_partition: malloc() error");

            inserer_en_tete(i,0,p->node_list[i]);
        }

        if( (p->node_l_nb =(int*)malloc(p->nb_element*sizeof(int))) == NULL )
            report_error("init_partition: malloc() error");
        for(i=0;i<p->nb_element;i++){
            p->node_l_nb[i] = 1;
        }
    }
}

int find(partition* p, int id_element){
    return p->element_id_partition[id_element];
}


void make_union(partition* p, int groupe_1, int groupe_2){
    int tmp,i;

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
    /// MERGE

    //update id groupe
    cell* q; 
    for(q=p->node_list[groupe_2]->prem ; q!=p->node_list[groupe_2]->dern ; q=q->suiv){ 
        p->element_id_partition[q->node] = groupe_1;
    }

    // merging groupe
    p->node_list[groupe_1]->dern->suiv = p->node_list[groupe_2]->prem;
    p->node_list[groupe_1]->prem->prec = p->node_list[groupe_2]->dern;

    p->node_list[groupe_2]->dern->suiv = p->node_list[groupe_1]->prem;
    p->node_list[groupe_2]->prem->prec = p->node_list[groupe_1]->dern;
    
    p->node_list[groupe_1]->dern = p->node_list[groupe_2]->dern;

    p->node_l_nb[groupe_1] += p->node_l_nb[groupe_2];
    p->node_l_nb[groupe_2] = 0;
    
    //free_nodl(p->node_list[groupe_2]);
}

void free_partition(partition* p){
    free(p);
}