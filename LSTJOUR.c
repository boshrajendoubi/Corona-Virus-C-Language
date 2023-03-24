#include<stdio.h>
#include<malloc.h>
#include<string.h>

#include "ELTPRIM.h"
#include "LSTPRIM.h"

NOEUD noeudCreer(ELEMENT e)
{
    NOEUD n;
    n =(NOEUD)malloc(sizeof(structNoeud));
    if(!n)
        printf ("\nPlus d'espace");
    else
    {
        elementAffecter(&n->info, e);
        n->suivant = NULL;
        n->precedent = NULL;
    }
    return n;
}
void noeudDetruire(NOEUD n)
{
    elementDetruire(n->info);
    free(n);
}
LISTE listeCreer(char* ch)
{
    LISTE L;
    L=(LISTE)malloc(sizeof(laStruct));
    if (! L)
        printf("\nProblème de mémoire");
    else
    {
        L->lg = 0;
        L->tete = NULL; /* initialiser la tête */
        L->queuee = NULL; /* initialiser la queue */
        strcpy(L->Nom_gouvernorat,ch);
    }
    return(L);
}
void listeDetruire(LISTE L)
{
    int i;
    NOEUD p, q;
    q= L->tete;
    for(i = 1; i <= L->lg; i++)
    {
        p=q;
        q=q->suivant;
        noeudDetruire(p);
    }
    free(L);
}

void inserer (LISTE L, ELEMENT e, int pos)
{
    int succee=1;
    succee++;
    int i;
    NOEUD n, p, q;
    if (estSaturee(L))
    {
        printf ("\nListe saturée");
        succee=0;
    }
    else
    {
        if ((pos < 1) || (pos > L->lg + 1))
        {
            printf ("\nPosition invalide");
            succee=0;
        }
        else
        {
            n=noeudCreer (e);
            if (L->lg == 0) /* la liste est vide */
            {
                L->tete = n;
                L->queuee = n;
            }
            else
            {
                if (pos == 1) /*insertion en tête de liste*/
                {
                    L->tete->precedent = n;
                    n->suivant=L->tete;
                    L->tete = n;
                }
                else
                {
                    if (pos == (L->lg +1)) /* ajout à la fin */
                    {
                        L->queuee->suivant = n;
                        n->precedent = L->queuee;
                        L->queuee = n;
                    }
                    else
                    {
                        q= L->tete;
                        for (i=1; i<pos; i++)
                        {
                            p = q;
                            q = q->suivant;
                        }
                        /* q désigne l’élément de rang pos et p son prédécesseur*/
                        p->suivant=n;
                        n->precedent =p;
                        n->suivant=q;
                        q->precedent =n;
                    }
                }
            }
            (L->lg)++;
        }
    }

}

int supprimer (LISTE L, int pos )
{
    int i;
    int succee=1;
    NOEUD p, q;
    if (estVide(L))
    {
        printf ("\nListe vide");
        succee=0;
    }
    else
    {
        if ((pos < 1) || (pos > L->lg))
        {
            printf ("\nPosition invalide");
            succee=0;
        }
        else
        {
            if (L->lg ==1) /* un seul element donc pos == 1*/
            {
                q=L->tete;
                L->tete = NULL;
                L->queuee = NULL;
            }
            else
            {
                if (pos == 1) /*suppression en tête de liste*/
                {
                    q=L->tete;
                    L->tete=L->tete->suivant;
                    L->tete->precedent = NULL;
                }
                else
                {
                    if (pos == L->lg)
                    {
                        q=L->queuee;
                        L->queuee = L->queuee->precedent;
                        L->queuee->suivant = NULL;
                    }
                    else
                    {
                        q= L->tete;
                        for (i=1; i<pos; i++)
                        {
                            p = q;
                            q = q->suivant;
                        }

                        q->suivant->precedent = p;
                        p->suivant=q->suivant;
                    }
                }
            }
            noeudDetruire(q);
            (L->lg)--;
        }
    }
    return succee;
}
ELEMENT recuperer(LISTE L, int pos)
{

    ELEMENT elt= elementCreer();
    int i;
    NOEUD p;
    if (estVide(L))
        printf ("\nListe vide");
    else
    {
        if ((pos < 1) || (pos > L->lg))
            printf ("\nPosition invalide");

        else
        {

            p= L->tete;
            for (i=1; i<pos; i++)
                p = p->suivant;

            elementAffecter(&elt,p->info);
        }

    }
    return(elt);
}
int estVide(LISTE L)
{
    return (L->lg == 0);
}
int estSaturee(LISTE L)
{
    return (L->lg == LongMax);
}
int listeTaille(LISTE L)
{
    return (L->lg);
}
void listeAfficher(LISTE L)
{
    if (L->lg==0)
        printf("No data found");
    else
    {
        int i=1;
        NOEUD p;
        p= L->tete;
        printf("\n\t\t\t\t\t\t\t\t\t\t\t%s \n\n",L->Nom_gouvernorat);
        for(i = 1; i <= L->lg; i++)
        {
            elementAfficher(p->info);
            printf("\n");
            p= p->suivant;
        }
    }
}
void listeAfficher2(LISTE L)
{
    int i=1;
    NOEUD p;
    p= L->tete;
    printf("\n\n");
    printf("\t\t\t\t\t\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t\t    Positive cases  |   Recovered    |   Deceased    |   Numbre of vaccines\n");
    printf("\t\t\t\t\t\t------------------------------------------------------------------------------------------------------------\n");
    for(i = 1; i <= L->lg; i++)
    {
        elementAfficher2(p->info);
        printf("\t\t\t\t\t\t------------------------------------------------------------------------------------------------------------\n");
        p= p->suivant;
    }
}
void listeAfficher3(LISTE L)
{
    int i=1;
    NOEUD p;
    p= L->queuee;
     printf("\n\n");
    printf("\t\t\t\t\t\t------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t\t    Positive cases  |   Recovered    |   Deceased    |   Numbre of vaccines\n");
    printf("\t\t\t\t\t\t------------------------------------------------------------------------------------------------------------\n");

    for(i = 1; i <= L->lg; i++)
    {
        elementAfficher2(p->info);
        printf("\n");
        p= p->precedent;
    }
}
LISTE listeCopier(LISTE L)
{
    LISTE LR = listeCreer(L->Nom_gouvernorat);
    int i;
    ELEMENT elt;
    for(i = 1; i <= L->lg; i++)
    {
        elt=elementCreer();
        elementCopier(&elt, recuperer(L,i));
        inserer(LR,elt, i);
    }
    return LR;
}
int  listeComparer (LISTE L1,LISTE L2 )
{
    int test= 1;
    int i=1;

    if (listeTaille(L1) != listeTaille(L2)) test= 0;

    while ((i<=listeTaille(L1)) && (test))
    {
        if (elementComparer(recuperer(L1,i),recuperer(L2,i))!=0)
            test=0;
        i++;
    }

    return test;
}
void NoeudAffecter(NOEUD* n1, NOEUD n2)
{
    *n1=n2;
}
void ListeAffecter(LISTE* L1, LISTE L2)
{
    *L1=L2;
}
void elementModifier(ELEMENT* e,int choix)
{
    switch(choix)
    {
    case 1 :
        printf("\t\t\t\t\t\t\t\t\tNew data :  ");
        scanf("%i",&(*e)->Cas_positifs); // scanf("%i",e->dec);  // scanf("%i",*((*e).dec));
        break;
    case 2 :
        printf("\t\t\t\t\t\t\t\t\tNew data :  ");
        scanf("%i",&(*e)->Guerisons);
        break;
    case 3 :
        printf("\t\t\t\t\t\t\t\t\tNew data :  ");
        scanf("%i",&(*e)->Deces);
        break;
    case 4 :
        printf("\t\t\t\t\t\t\t\t\tNew data :  ");
        scanf("%i",&(*e)->Nombre_de_vaccines);
        break;
    }

}

