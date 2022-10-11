
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

void add_wedge(wedge* list, int u, int v){
	
}



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

	int u,v;


//////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////
////////////////   PARSE COMMAND LINE   ///////////////////
///////////////////////////////////////////////////////////


	// default values
	char name_in[100]="";
	char name_out[100]="";
	int input_file_given=0;
	int output_file_given=0;

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
		else usage(argv[0]);
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
	
	wedge* list_wedge_sorted;
	if ( (list_wedge_sorted = (wedge*) malloc((G->m)*sizeof(wedge))) == NULL )
		report_error("malloc() error");
	list_wedge(G,list_wedge_sorted);
	qsort(list_wedge_sorted,(size_t)(G->m),sizeof(wedge),comp_wedge);

	wedge* kruslal_tree;
	if ( (kruslal_tree = (wedge*) malloc((G->m)*sizeof(wedge))) == NULL )
		report_error("malloc() error");


	partition* p;
	if ( (p = (partition*) malloc((G->n)*sizeof(partition))) == NULL)
		report_error("malloc() error");

	init_partition(p,G->n);

	//print_list_wedge(list_wedge_sorted,G->m);
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  

///////////////////////////////////////////////////////////
/////////////////   COMPUTE MST   /////////////////////
///////////////////////////////////////////////////////////

	fprintf(stderr,"Begin computation.\n");
	fflush(stderr);

/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	for(i=0;i<G->m;i++){
		u = list_wedge_sorted[i].node1;
		v = list_wedge_sorted[i].node2;
		if(find(p,u)!=find(p,v)){
			fprintf(stderr,"In progress.\n"); //TODO
			kruslal_tree[0] = w
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
	if(list_wedge_sorted!=NULL) free(list_wedge_sorted);

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


