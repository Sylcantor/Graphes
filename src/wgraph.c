

//#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "wgraph.h"

#define MAX_LINE_LENGTH 1000
#define MAX 10.0

///////////////////////////////////////////////////////////
////////////   GRAPH MANAGEMENT FUNCTIONS   ///////////////
///////////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// CHARGER UN GRAPHE PONDERE A PARTIR D'UN FLUX
// precondition: f est initialise et contient un graphe pondere au format suivant: la premiere ligne contient un entier n qui est le nombre de sommets du graphe, chaque ligne suivante contient une arete du graphe pondere representee par deux entiers compris entre 0 et n-1 (les identifiants des sommets) separes par un espace et le poids de l'arete represente par un flottant, separe par un espace
// postcondition: initialise une structure wgraph, l'affecte du graphe pondere lu sur le flux f et retourne un pointeur sur la structure graph ainsi construite
wgraph* wgraph_from_file(FILE *f){
  char line[MAX_LINE_LENGTH];
  int i, u, v;
  float p;
  wgraph *g;

  if( (g=(wgraph *)malloc(sizeof(wgraph))) == NULL )
    report_error("wgraph_from_file: malloc() error 1");
  
  /* read n */
  if( fgets(line,MAX_LINE_LENGTH,f) == NULL )
    report_error("wgraph_from_file: read error (fgets) 1");
  if( sscanf(line, "%d\n", &(g->n)) != 1 )
    report_error("wgraph_from_file: read error (sscanf) 2");
  
  /* create space for links and degrees*/
  if (g->n==0){
    g->links = NULL; g->degrees = NULL;
  }
  else {
  
  	if( (g->degrees=(int*)malloc(g->n*sizeof(int))) == NULL )
      report_error("wgraph_from_file: malloc() error 3");
    for(i=0;i<g->n;i++){
    	g->degrees[i]=0;
    }
      
    if( (g->links=(nodl**)malloc(g->n*sizeof(nodl*))) == NULL )
      report_error("wgraph_from_file: malloc() error 3");
    for(i=0;i<g->n;i++){
    	if( (g->links[i]=(nodl*)malloc(sizeof(nodl))) == NULL )
      	report_error("wgraph_from_file: malloc() error 3");
	    g->links[i]->prem=NULL;
	    g->links[i]->dern=NULL;
    }
    
  }

  /* read the links */
  while (fgets(line,MAX_LINE_LENGTH,f) != NULL ){
    int cpt = sscanf(line, "%d %d %f\n", &u, &v, &p);
    if(cpt < 2 ){
      fprintf(stderr,"Attempt to scan link #%d failed. Line read:%s\n", i, line);
      report_error("wgraph_from_file; read error (sscanf) 3");
    }
    else if (cpt == 2)
    {
      p = (float)rand()/(float)(RAND_MAX/MAX);
    }
    
    if ( (u>=g->n) || (v>=g->n) || (u<0) || (v<0) ) {
      fprintf(stderr,"Line just read: %s",line);
  
      report_error("wgraph_from_file: bad node number");
    }
    
    inserer_en_queue(v, p, g->links[u]);
    inserer_en_queue(u, p, g->links[v]);
    g->degrees[u]++;
    g->degrees[v]++;
  }
  /*
  while (fgets(line,MAX_LINE_LENGTH,f) != NULL ){
    if( sscanf(line, "%d %d %f\n", &u, &v, &p) != 3 ){
      fprintf(stderr,"Attempt to scan link #%d failed. Line read:%s\n", i, line);
      report_error("wgraph_from_file; read error (sscanf) 3");
    }
    if ( (u>=g->n) || (v>=g->n) || (u<0) || (v<0) ) {
      fprintf(stderr,"Line just read: %s",line);
      report_error("wgraph_from_file: bad node number");
    }
    
    inserer_en_queue(v, p, g->links[u]);
    inserer_en_queue(u, p, g->links[v]);
    g->degrees[u]++;
    g->degrees[v]++;
  }
  */
  
  /* compute the number of links */
  g->m=0;
  for(i=0;i<g->n;i++)
    g->m += g->degrees[i];
  g->m /= 2;
  
  return g;
}


//////////////////////////////////////////////////////
// ECRIRE UN GRAPHE PONDERE DANS UN FLUX
// precondition: f et g sont initialises
// postcondition: le graphe pondere pointe par g est ecrit sur le flux f dans le format suivant: la premiere ligne contient un entier qui est le nombre de sommets du graphe, chaque ligne suivante contient une arete du graphe pondere representee par deux entiers (les identifiants des sommets) separes par un espace et un flottant pour son poids, separe par un espace
void write_wgraph(FILE *f, wgraph* g){

	int u;
	cell* p;

	fprintf(f,"%d\n",g->n);
	for (u=0;u<g->n;u++) {
		p=g->links[u]->prem;
  	while (p!=NULL) {
			if (p->node<u) fprintf(f,"%d %d %f\n",u,p->node,p->weight);
			p=p->suiv;
		}
	}
	fflush(f);	
}



//////////////////////////////////////////////////////
// LIBERER UN GRAPHE PONDRE
// precondition: aucune
// postcondition: le graphe pondere pointe par g est detruit
void free_wgraph(wgraph *g){
	int i;
  if (g!=NULL) {
    if (g->links!=NULL) {
    	for(i=0;i<g->n;i++) {
    		free_nodl(g->links[i]);
    	}
      free(g->links);
    }
    if (g->degrees!=NULL)
      free(g->degrees);
    free(g);
  }
}


