
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

void print_list_wedge(wedge* tab, int size){
	int i =0;
	while (i<size)
	{
		printf("%f",tab[i].weight);
	}
	
}

wedge* list_wedge(wgraph* G){

	wedge list[G->m];

	
	//if ( (list = (wedge*) malloc((G->m)*sizeof(wedge))) == NULL ){}
		//report_error("malloc() error");


	wedge w;
	int k,i;
	i= 0;
	k=0;

	while(G->links[i]!=NULL){
		w.node1 = i;
		cell* c = G->links[i]->prem;
		while (c!=NULL)
		{
			w.node2 = c->node;
			w.weight = c->weight;
			list[k]=w;

			c = c->suiv;
			k++;
		}
		
		i++;
	}	

	return list;
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

	fprintf(stderr,"Il y a %d sommets et %d aretes !\n",G->n,G->m);


	wedge* tab = list_wedge(G);

	free_wgraph(G);
	free(tab);
	print_list_wedge(tab,G->m);
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////
  


///////////////////////////////////////////////////////////
//////////////////   DATA STRUCTURE   /////////////////////
///////////////////////////////////////////////////////////

  
/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  

///////////////////////////////////////////////////////////
/////////////////   COMPUTE MST   /////////////////////
///////////////////////////////////////////////////////////

	fprintf(stderr,"Begin computation.\n");
	fflush(stderr);

/////////////////////////////////////////////   A FAIRE   ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////



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


