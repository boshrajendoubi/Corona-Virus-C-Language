#ifndef LSTJOUR_H_INCLUDED
#define LSTJOUR_H_INCLUDED

#include "ELTPRIM.h"

typedef struct structNoeud
{
    ELEMENT info;
    struct structNoeud * precedent;
    struct structNoeud * suivant;
} structNoeud, * NOEUD;

typedef struct
{
    NOEUD tete;
    NOEUD queuee ;
    char Nom_gouvernorat [20];
    int lg;
} laStruct,*LISTE;

#endif // LSTJOUR_H_INCLUDED
