#ifndef ELTJOUR_H
#define ELTJOUR_H

typedef struct
{
    int jour;
    int mois;
    int annee;
    int Cas_positifs;
    int Guerisons;
    int Deces;
    int Nombre_de_vaccines;
    char nom_gouv[20];

} date,*ELEMENT;

#endif // ELTJOUR_H_INCLUDED
