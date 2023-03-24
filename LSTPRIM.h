#ifndef LSTPRIM_H_INCLUDED
#define LSTPRIM_H_INCLUDED
#include "LSTSDD.H"
#include"ELTPRIM.h"
#define LongMax 100
NOEUD noeudCreer(ELEMENT e);
void noeudDetruire(NOEUD n);
void NoeudAffecter(NOEUD* e1, NOEUD e2);
LISTE listeCreer(char*);
void listeDetruire(LISTE);
int estVide(LISTE);
int estSaturee(LISTE);
int listeTaille(LISTE);
ELEMENT recuperer(LISTE, int);
void inserer(LISTE, ELEMENT,int);
int supprimer(LISTE, int);
void listeAfficher(LISTE);
void listeAfficher2(LISTE);
void listeAfficher3(LISTE);
LISTE listeCopier(LISTE);
int  listeComparer(LISTE, LISTE);
void ListeAffecter(LISTE* L1, LISTE L2);
void elementModifier(ELEMENT*,int);


#endif // LSTPRIM_H_INCLUDED
