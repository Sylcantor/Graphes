


//#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "unionfind.h"

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

void make_union(partition* p, int id_groupe_1, int id_groupe_2){
    int i;
    
    if(p->node_l_nb[id_groupe_2] > p->node_l_nb[id_groupe_1]){
        int tmp_id_grp = id_groupe_1;
        id_groupe_1 = id_groupe_2;
        id_groupe_2 = tmp_id_grp;
    }

    for(i=0;i<p->nb_element;i++){
        if(p->element_id_partition[i] == id_groupe_2){
            p->element_id_partition[i] = id_groupe_1;
        }
    }
    p->node_l_nb[id_groupe_1] += p->node_l_nb[id_groupe_2];
    p->node_l_nb[id_groupe_2] = 0;
}


void free_partition(partition* p){
    free(p->element_id_partition);
    free(p->node_l_nb);
    free(p->node_list);
    free(p);
}