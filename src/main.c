
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
//#include <unistd.h>

#include "utility.h"
#include "wnodelist.h"
#include "wgraph.h"
#include "unionfind.h"
#include "priorite.h"


/******************/
/* Default values */
/******************/




/********************/
/* Output functions */
/********************/

// print help
void usage(char *c){
	fprintf(stderr,"Usage: %s -h\n",c);
	fprintf(stderr,"  -h: print current help.\n");
	fprintf(stderr,"  -i \"inputname\": input file containing the weighted graph (default value is stdin).\n");
	fprintf(stderr,"  -o \"outputname\": output results in a file named \"outputname\" (default value is stdout).\n");
	fprintf(stderr,"  -k \"kruskal\": use prim algorithm (default value is kruskal).\n");
	fprintf(stderr,"  -p \"prim\": use prim algorithm (default value is kruskal).\n");
	exit(-1);
}



void print_list_wedge(wedge* list_wedge_sorted, int size){
	int i =0;
	fprintf(stderr,"[");
	for(i=0;i<size-1;i++){
		fprintf(stderr,"%f, ",list_wedge_sorted[i].weight);
	}
	fprintf(stderr,"%f]\n",list_wedge_sorted[size-1].weight);
}

void list_wedge(wgraph* G,wedge* list_wedge_sorted){

	int k,i;
	int cpt=0;
	wedge w;

	for(i=0;i<G->n;i++){
		cell* c = G->links[i]->prem;
		for(k=0;k<G->degrees[i];k++){
			//printf("Arrete : %d -> %d\n",i,c->node);
			//printf("Weight: %f	\n",c->weight);

			w.node1 = i;
			w.node2 = c ->node;
			w.weight = c ->weight;

			if(w.node1<w.node2){
				list_wedge_sorted[cpt] = w;
				cpt++;
			}
			c = c->suiv;
			//printf("k : %d\n",k);
		}
	}
	
}

//void add_wedge(wedge* list, int u, int v){
	
//}

/**************************************************************/
/**************************************************************/
/**************************************************************/
/***************************        ***************************/
/***************************  MAIN  ***************************/
/***************************        ***************************/
/**************************************************************/
/**************************************************************/
/**************************************************************/

int main(int argc, char **argv){


///////////////////////////////////////////////////////////
//////////   DECLARATIONS AND DEFAULT VALUES   ////////////
///////////////////////////////////////////////////////////
 
	FILE* fin=NULL;
	FILE* fout=NULL;

	int i;

/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	int u,v,r;
	srand(time(NULL));

//////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////
////////////////   PARSE COMMAND LINE   ///////////////////
///////////////////////////////////////////////////////////


	// default values
	char name_in[100]="";
	char name_out[100]="";
	int input_file_given=0;
	int output_file_given=0;
	int kruskal=0;
	int prim=0;

	// user's values
  
	for (i=1; i<argc; i++) {
		if ((strcmp(argv[i],"-h")==0) || (strcmp(argv[i],"--help")==0) ) {
			usage(argv[0]);     
		}
		else if ((strcmp(argv[i],"-i")==0) || (strcmp(argv[i],"--input")==0) ) {
			if (i==argc-1)
				usage(argv[0]);
			input_file_given=1;
			strcpy(name_in,argv[++i]);
		}
		else if ((strcmp(argv[i],"-o")==0) || (strcmp(argv[i],"--output")==0) ) {
			if (i==argc-1)
				usage(argv[0]);
			output_file_given=1;
			strcpy(name_out,argv[++i]);
		}
		else if ((strcmp(argv[i],"-k")==0) || (strcmp(argv[i],"--kruskal")==0) ) {
			kruskal=1;
			if(prim==1){
				usage(argv[0]);
			}
		}
		else if ((strcmp(argv[i],"-p")==0) || (strcmp(argv[i],"--prim")==0) ) {
			prim=1;
			if(kruskal==1){
				usage(argv[0]);
			}
		}
		else usage(argv[0]);
	}
    
	if(kruskal==0 && prim==0){
		kruskal=1;
	}
  
  
  
///////////////////////////////////////////////////////////
///////////////////   OPEN FILES   ////////////////////////
///////////////////////////////////////////////////////////



	if (input_file_given==0) {
		fin=stdin;
	}
	else {
		if ( (fin=fopen(name_in,"r"))==NULL)
			report_error("name_in -- fopen: error");
	}


	if (output_file_given==0) 
		fout=stdout;
	else {
		if ( (fout=fopen(name_out,"w"))==NULL)
			report_error("name_out -- fopen: error");
	}
	


///////////////////////////////////////////////////////////
/////////////////   LOADING WEIGHTED GRAPH   ///////////////////////
///////////////////////////////////////////////////////////


/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	wgraph* G = wgraph_from_file(fin);

	//fclose(fin);

	//fprintf(stderr,"Il y a %d sommets et %d aretes !\n",G->n,G->m);


	//fprintf(stderr,"Il y a %d voisins !\n",G->degrees[4]);
	
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////
  


///////////////////////////////////////////////////////////
//////////////////   DATA STRUCTURE   /////////////////////
///////////////////////////////////////////////////////////

  
/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Kruskal
	wedge* kruslal_tree;
	wedge* list_wedge_sorted;
	partition* p;
	if(kruskal==1){
		if ( (kruslal_tree = (wedge*) malloc((G->n-1)*sizeof(wedge))) == NULL )
			report_error("malloc() error");
		if ( (list_wedge_sorted = (wedge*) malloc((G->m)*sizeof(wedge))) == NULL )
			report_error("malloc() error");
		list_wedge(G,list_wedge_sorted);
		qsort(list_wedge_sorted,(size_t)(G->m),sizeof(wedge),comp_wedge);



		if ( (p = (partition*) malloc((G->n-1)*sizeof(partition))) == NULL)
			report_error("malloc() error");

		init_partition(p,G->n);
	}

    // Prim
	wedge* prim_tree;
	if ( (prim_tree = (wedge*) malloc((G->m)*sizeof(wedge))) == NULL )
		report_error("malloc() error");
	pqueue* q;
	int* in_queue;
	float* weight;
	int* father;
	cell* c;
	if(prim==1){
		if ( (q = (pqueue*) malloc(sizeof(pqueue))) == NULL)
			report_error("malloc() error");	
		init_pqueue(q,G->n);

		if ( (in_queue = (int*) malloc((G->n)*sizeof(int))) == NULL )
			report_error("malloc() error");
		
		if ( (weight = (float*) malloc((G->n)*sizeof(float))) == NULL )
			report_error("malloc() error");
		
		
		if ( (father = (int*) malloc((G->n)*sizeof(int))) == NULL )
			report_error("malloc() error");
		
		for (i=0; i<G->n; i++) {
			in_queue[i]=1;
			weight[i]=INT_MAX;
			father[i]=-1;
		}	
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  

///////////////////////////////////////////////////////////
/////////////////   COMPUTE MST   /////////////////////
///////////////////////////////////////////////////////////

	fprintf(stderr,"Begin computation.\n");
	fflush(stderr);

/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Kruskal algorithm implementation with union-find data structure (à revoir)
	if(kruskal==1){
		int cpt = 0;
		for(i=0;i<G->m;i++){
			u = list_wedge_sorted[i].node1;
			u = find(p,u);
			v = list_wedge_sorted[i].node2;
			v = find(p,v);
			if(u!=v){
				kruslal_tree[cpt] = list_wedge_sorted[i];  // si on change au dessus par G->n-1, il faut changer ici aussi avec un compteur pour l'indice du tableau kruslal_tree
				//printf("Arrete : %d -> %d\n",u,v);
				//printf("Weight: %f	\n",list_wedge_sorted[i].weight);
				cpt++;
				make_union(p,u,v);
			}
		}
	}
	//Prime algorithm implementation
	if(prim==1){
		r = rand() % G->n;
		update_pqueue(q,r,0);
		while(!isempty_pqueue(q)){
			u = extractmin_pqueue(q);
			in_queue[u] = 0;

			// neighbor of u
			c = G->links[u]->prem;
			for(i=0;i<G->degrees[u];i++){
				// if v is in queue and weight of edge (u,v) is less than weight of v
				if(in_queue[c->node] && c->weight < weight[c->node]){
					// update weight of v
					weight[c->node] = c->weight;  // ici il faudrait mettre le poid dans un tableau de wedge
					// update father of v
					father[c->node] = u;	
					// update priority queue
					update_pqueue(q,c->node,c->weight);
					prim_tree[c->node].node1 = u;
					prim_tree[c->node].node2 = c->node;
					prim_tree[c->node].weight = c->weight;
				}
				c = c->suiv;
			}
		}
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////
//////////////////   OUTPUT RESULTS   /////////////////////
///////////////////////////////////////////////////////////


	fprintf(stderr,"\nOutputing results.\n");
  	fflush(stderr);


/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//afficher le resultat kruskal
	if(kruskal==1){
		for(i=0;i<G->n-1;i++){
			fprintf(fout,"%d %d %f\n",kruslal_tree[i].node1,kruslal_tree[i].node2,kruslal_tree[i].weight);
		}
	}
	//afficher le resultat prim
	if(prim==1){
		for(i=0;i<G->m;i++){
			if(prim_tree[i].weight > 0){
				fprintf(fout,"%d %d %f\n",prim_tree[i].node1,prim_tree[i].node2,prim_tree[i].weight);
			}
		}
	}



//////////////////////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////
////////////   CLOSE FILES AND FREE MEMORY  ///////////////
///////////////////////////////////////////////////////////

	if (fin!=NULL) {
		fclose(fin);
		fin=NULL;
		fprintf(stderr,"\nInput file closed.\n");
		fflush(stderr);
	}

	
	if (fout!=NULL) {
		fclose(fout);
		fprintf(stderr,"Output file closed.\n");
		fflush(stderr);
	}


/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	if(G!=NULL) free_wgraph(G);
	//if(list_wedge_sorted!=NULL) free(list_wedge_sorted);
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////



	return 0;
}

/**************************************************************/
/**************************************************************/
/*************************            *************************/
/*************************  FIN MAIN  *************************/
/*************************            *************************/
/**************************************************************/
/**************************************************************/


