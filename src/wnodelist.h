

#ifndef _NODELIST_

#define _NODELIST_

//#include <stdio.h>






///////////////////////////////////////////////////////////
///////////////////   WEIGHTED EDGE   ////////////////////////
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// CELLULE D'UNE LISTE DE NOEUDS
typedef struct wedge{
  int node1;
  int node2;
  float weight;
} wedge;


int comp_wedge (const void * a, const void * b);


///////////////////////////////////////////////////////////
///////////////////   NODE LISTS   ////////////////////////
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// CELLULE D'UNE LISTE DE NOEUDS
typedef struct cell{
  int node;
  float weight;
  struct cell* suiv;
  struct cell* prec;
} cell;

//////////////////////////////////////////////////////
// LISTE DE NOEUDS
typedef struct nodl{
  cell* prem;
  cell* dern;
} nodl;




//////////////////////////////////////////////////////
// INITIALISER UNE NODL A VIDE
// precondition: 
// postcondition: 
void init_vide (nodl* l);



//////////////////////////////////////////////////////
// INSERER UNE CELLULE APRES UNE AUTRE DANS UNE LISTE
// precondition: l est non null et pointe sur une liste non vide, p (non null) pointe sur une cellule de la liste pointee par l
// postcondition: une nouvelle cellule contenant la valeur u est inseree dans la liste pointee par l apres la cellule pointee par p 
void inserer_apres (int u, float w, nodl* l, cell* p);

//////////////////////////////////////////////////////
// INSERER UNE CELLULE EN TETE D'UNE LISTE
// precondition: l est non null et *l est initialise
// postcondition: une nouvelle cellule contenant la valeur u est inseree en tete de la liste pointee par l 
void inserer_en_tete (int u, float w, nodl* l);


//////////////////////////////////////////////////////
// INSERER UNE CELLULE EN QUEUE D'UNE LISTE
// precondition: l est non null et *l est initialise
// postcondition: une nouvelle cellule contenant la valeur u est inseree en queue de la liste pointee par l 
void inserer_en_queue (int u, float w, nodl* l);


//////////////////////////////////////////////////////
// SUPPRIMER UNE CELLULE D'UNE LISTE
// precondition: l est non null et pointe sur une liste non vide, p (non null) pointe sur une cellule de la liste pointee par l
// postcondition: la cellule pointee par p est retiree de la liste pointee par l et detruite 
void supprimer (cell* p, nodl* l);





//////////////////////////////////////////////////////
// LIBERER UNE NODELIST ET TOUTES SES CELLULES
// precondition: aucune
// postcondition: la liste pointee par l est detruite
void free_nodl(nodl* l);

//////////////////////////////////////////////////////////////////////////////////////////////////////////




#endif



