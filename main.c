#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "ELTPRIM.h"
#include "LSTPRIM.h"
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
    /*0 : Noir  1 : Bleu foncé  2 : Vert foncé  3 : Turquoise  4 : Rouge foncé  5 : Violet
    6 : Vert caca d'oie   7 : Gris clair  8 : Gris foncé  9 : Bleu fluo  10 : Vert fluo
    11 : Turquoise  12 : Rouge fluo  13 : Violet 2  14 : Jaune  15 : Blanc*/
}
int dateverifier (int jj,int mm,int aa) // verifer la date
{
    /*SYSTEMTIME time;
    GetLocalTime(&time);
    printf("%d %d %d",time.wYear,time.wMonth,time.wDay);
    ,test2=0;
    if ((aa== time.wYear)&&(mm==time.wMonth)&&(jj== time.wDay))
                test2=1;*/

    //verif annee
    int test=0;
    if(aa>=0000 && aa<=9999)
    {
        //verif mois
        if(mm>=1 && mm<=12)
        {
            //verif jour
            if((jj>=1 && jj<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
            {
                test=1;
            }
            else if((jj>=1 && jj<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
            {
                test=1;
            }
            else if((jj>=1 && jj<=28) && (mm==2))
            {
                test=1;
            }
            else if(jj==29 && mm==2 && (aa%400==0 ||(aa%4==0 && aa%100!=0)))
            {
                test=1;
            }

        }

    }
    return test;
}
int elementexiste(LISTE L,ELEMENT e)
{
    NOEUD n=L->tete;
    int test=0;
    while(n->suivant != NULL)
    {
        if ((n->info->jour == e->jour)&&(n->info->mois == e->mois)&&(n->info->annee == e->annee))
        {
            test=1;
        }

        n=n->suivant;

    }
    return test;
}
int ConvMois (char* ch) // renvoie le rang du mois a partir de son nom
{
    if (strcmp(ch,"Janvier")==0)
        return 1;
    else if (strcmp(ch,"Fevrier")==0)
        return 2;
    else if (strcmp(ch,"Mars")==0)
        return 3;
    else if (strcmp(ch,"Avril")==0)
        return 4;
    else if (strcmp(ch,"Mai")==0)
        return 5;
    else if (strcmp(ch,"Juin")==0)
        return 6;
    else if (strcmp(ch,"Juillet")==0)
        return 7;
    else if (strcmp(ch,"Aout")==0)
        return 8;
    else if (strcmp(ch,"September")==0)
        return 9;
    else if (strcmp(ch,"October")==0)
        return 10;
    else if (strcmp(ch,"November")==0)
        return 11;
    else if (strcmp(ch,"December")==0)
        return 12;
    else return 0 ;
}
void SwapNoeud (ELEMENT* n, ELEMENT* p) // Permutation de 2 noeuds
{

    ELEMENT temp;
    elementAffecter(&temp,*n);
    elementAffecter(n,*p);
    elementAffecter(p,temp);

}
void SwapListe (LISTE *L, LISTE* M)  //Permutation de 2 listes
{
    LISTE N=listeCreer("aux");
    ListeAffecter(&N,*L);
    ListeAffecter(L,*M);
    ListeAffecter(M,N);
    listeDetruire(N);
}
void tri_cle(LISTE T[],int clecaspos, int cleguerisons, int cledeces, int clevaccins,int mode_tri) // tri par code de tri
{
    int jj,mm,aa;
    do
    {
        printf("\t\t\t\t\t\t\t\t\tEnter the day : ");
        scanf("%i",&jj);
        fflush(stdin);
        printf("\t\t\t\t\t\t\t\t\tEnter the month : ");
        scanf("%i",&mm);
        fflush(stdin);
        printf("\t\t\t\t\t\t\t\t\tEnter the year : ");
        scanf("%i",&aa);
        fflush(stdin);
    }
    while(dateverifier(jj,aa,mm)==1);
    LISTE L = listeCreer("Specefique");
    for (int i = 0 ; i < 24 ; i++)
    {

        NOEUD n = T[i]->tete ;
        for (int k = 1 ; k <= T[i]->lg ; k++)
        {
            if ((n->info->jour == jj)&&(n->info->mois == mm)&&(n->info->annee == aa))
            {
                strcpy(n->info->nom_gouv,T[i]->Nom_gouvernorat);
                inserer(L,n->info,L->lg+1);
            }
            n = n->suivant;
        }


    }
    if(L->lg==0)
        printf("\t\t\t\t\t\t\t\t\tNo corresponding date found\n\n\n");
    else
    {

        if(clecaspos==1 && L->lg!=0)
        {
            NOEUD n=L->tete,p;
            p=L->tete;
            while(n->suivant != NULL)
            {
                do
                {
                    if
                    (n->info->Cas_positifs < p->info->Cas_positifs)
                    {
                        ELEMENT temp;
                        elementAffecter(&temp,n->info);
                        elementAffecter(&n->info,p->info);
                        elementAffecter(&p->info,temp);

                    }
                    p=p->suivant;
                }
                while (p != NULL);
                n=n->suivant;
                p=n;

            }
            if (cleguerisons==2)
            {

                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;



                }


                if (cledeces==3 && clevaccins==4)
                {
                    NOEUD n=L->tete,p;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }

                }
                else if (cledeces==4 && clevaccins==3)
                {
                    NOEUD n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }
                }


            }
            else if (cledeces==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Deces< p->info->Deces))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;
                    if (cleguerisons==3 && clevaccins==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Deces == p->info->Deces)&&(n->info->Guerisons < p->info->Guerisons))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }

                    }
                    else if (cleguerisons==4 && clevaccins==3)
                    {
                        NOEUD n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Deces== p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines)&&(n->info->Guerisons< p->info->Guerisons)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }
            }
            else if (clevaccins==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;

                    if (cleguerisons==3 && cledeces==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Guerisons < p->info->Guerisons))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                    else if (cledeces==3 && cleguerisons==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Deces < p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }

            }

        }
        if(cleguerisons==1&& L->lg!=0)
        {

            NOEUD n=L->tete,p;
            p=L->tete;
            while(n->suivant != NULL)
            {
                do
                {
                    if
                    (n->info->Guerisons < p->info->Guerisons)
                    {
                        ELEMENT temp;
                        elementAffecter(&temp,n->info);
                        elementAffecter(&n->info,p->info);
                        elementAffecter(&p->info,temp);

                    }
                    p=p->suivant;
                }
                while (p != NULL);
                n=n->suivant;
                p=n;

            }
            if (clecaspos==2)
            {

                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;



                }


                if (cledeces==3 && clevaccins==4)
                {
                    NOEUD n=L->tete,p;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }

                }
                else if (cledeces==4 && clevaccins==3)
                {
                    NOEUD n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }
                }


            }
            else if (cledeces==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces< p->info->Deces))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;
                    if (clecaspos==3 && clevaccins==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Deces == p->info->Deces)&&(n->info->Guerisons == p->info->Guerisons))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }

                    }
                    else if (clecaspos==4 && clevaccins==3)
                    {
                        NOEUD n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces== p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines)&&(n->info->Guerisons== p->info->Guerisons)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }
            }
            else if (clevaccins==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Guerisons== p->info->Guerisons)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;

                    if (clecaspos==3 && cledeces==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Guerisons == p->info->Guerisons)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Cas_positifs < p->info->Cas_positifs))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                    else if (cledeces==3 && clecaspos==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Guerisons == p->info->Guerisons)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Deces < p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }

            }
        }
        if(cledeces==1&& L->lg!=0)
        {
            NOEUD n=L->tete,p;
            p=L->tete;
            while(n->suivant != NULL)
            {
                do
                {
                    if
                    (n->info->Deces < p->info->Deces)
                    {
                        ELEMENT temp;
                        elementAffecter(&temp,n->info);
                        elementAffecter(&n->info,p->info);
                        elementAffecter(&p->info,temp);

                    }
                    p=p->suivant;
                }
                while (p != NULL);
                n=n->suivant;
                p=n;

            }
            if (clecaspos==2)
            {

                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Deces == p->info->Deces))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;



                }


                if (cleguerisons==3 && clevaccins==4)
                {
                    NOEUD n=L->tete,p;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons)&&(n->info->Deces == p->info->Deces))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }

                }
                else if (cleguerisons==4 && clevaccins==3)
                {
                    NOEUD n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }
                }


            }
            else if (cleguerisons==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Guerisons < p->info->Guerisons)&&(n->info->Deces== p->info->Deces))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;
                    if (clecaspos==3 && clevaccins==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Deces == p->info->Deces)&&(n->info->Guerisons == p->info->Guerisons))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }

                    }
                    else if (clecaspos==4 && clevaccins==3)
                    {
                        NOEUD n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces== p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines)&&(n->info->Guerisons== p->info->Guerisons)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }
            }
            else if (clevaccins==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Deces== p->info->Deces)&&(n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;

                    if (clecaspos==3 && cleguerisons==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                    else if (cleguerisons==3 && clecaspos==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Guerisons < p->info->Guerisons)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Guerisons ==  p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }

            }
        }
        if(clevaccins==1&& L->lg!=0)
        {
            NOEUD n=L->tete,p;
            p=L->tete;
            while(n->suivant != NULL)
            {
                do
                {
                    if
                    (n->info->Nombre_de_vaccines < p->info->Nombre_de_vaccines)
                    {
                        ELEMENT temp;
                        elementAffecter(&temp,n->info);
                        elementAffecter(&n->info,p->info);
                        elementAffecter(&p->info,temp);

                    }
                    p=p->suivant;
                }
                while (p != NULL);
                n=n->suivant;
                p=n;

            }
            if (clecaspos==2)
            {

                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;



                }


                if (cleguerisons==3 && cledeces==4)
                {
                    NOEUD n=L->tete,p;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }

                }
                else if (cleguerisons==4 && cledeces==3)
                {
                    NOEUD n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;
                    }
                    n=L->tete;
                    p=L->tete;
                    while(n->suivant != NULL)
                    {
                        do
                        {
                            if
                            ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                            {
                                ELEMENT temp;
                                elementAffecter(&temp,n->info);
                                elementAffecter(&n->info,p->info);
                                elementAffecter(&p->info,temp);

                            }
                            p=p->suivant;
                        }
                        while (p != NULL);
                        n=n->suivant;
                        p=n;

                    }
                }


            }
            else if (cleguerisons==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Guerisons < p->info->Guerisons)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;
                    if (clecaspos==3 && cledeces==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines)&&(n->info->Guerisons == p->info->Guerisons))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }

                    }
                    else if (clecaspos==4 && cledeces==3)
                    {
                        NOEUD n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Guerisons == p->info->Guerisons)&&(n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines)&&(n->info->Guerisons== p->info->Guerisons)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }
            }
            else if (cledeces==2)
            {
                NOEUD n=L->tete,p;
                p=L->tete;
                while(n->suivant != NULL)
                {
                    do
                    {
                        if
                        ((n->info->Deces < p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                        {
                            ELEMENT temp;
                            elementAffecter(&temp,n->info);
                            elementAffecter(&n->info,p->info);
                            elementAffecter(&p->info,temp);

                        }
                        p=p->suivant;
                    }
                    while (p != NULL);
                    n=n->suivant;
                    p=n;

                    if (clecaspos==3 && cleguerisons==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs == p->info->Cas_positifs)&&(n->info->Guerisons < p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                    else if (cleguerisons==3 && clecaspos==4)
                    {
                        NOEUD n=L->tete,p;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Guerisons < p->info->Guerisons)&&(n->info->Nombre_de_vaccines== p->info->Nombre_de_vaccines)&&(n->info->Deces == p->info->Deces))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;
                        }
                        n=L->tete;
                        p=L->tete;
                        while(n->suivant != NULL)
                        {
                            do
                            {
                                if
                                ((n->info->Cas_positifs < p->info->Cas_positifs)&&(n->info->Guerisons ==  p->info->Guerisons)&&(n->info->Deces == p->info->Deces)&&(n->info->Nombre_de_vaccines == p->info->Nombre_de_vaccines))
                                {
                                    ELEMENT temp;
                                    elementAffecter(&temp,n->info);
                                    elementAffecter(&n->info,p->info);
                                    elementAffecter(&p->info,temp);

                                }
                                p=p->suivant;
                            }
                            while (p != NULL);
                            n=n->suivant;
                            p=n;

                        }
                    }
                }

            }
        }
        if (mode_tri==2&& L->lg!=0)
            listeAfficher2(L);
        else
            listeAfficher3(L);
    }

}
void Tri_Liste_par_Dates (LISTE T)  // tri par dates des liste
{
    NOEUD n=T->tete,p;
    p=T->tete;
    while(n->suivant != NULL)
    {
        do
        {
            if
            ((n->info->annee < p->info->annee)||((n->info->annee == p->info->annee)&&(n->info->mois < p->info->mois))||((n->info->annee == p->info->annee)&&(n->info->mois == p->info->mois)&&(n->info->jour < p->info->jour)))
            {
                ELEMENT temp;
                elementAffecter(&temp,n->info);
                elementAffecter(&n->info,p->info);
                elementAffecter(&p->info,temp);

            }
            p=p->suivant;
        }
        while (p != NULL);
        n=n->suivant;
        p=n;

    }

}
void Tri_Tableau_alphabetique (LISTE T[], int taille) // tri des gouvernorats par ordre alphabetique
{
    int j,i;
    for (i=0; i<24; i++)
    {
        for (j=0; j<24; j++)
        {

            if (strcmp( T[i]->Nom_gouvernorat,T[j]->Nom_gouvernorat ) < 0)
            {
                SwapListe(&T[i],&T[j]);
            }
        }
    }
}
void Tri_Tableau_alphabetique_inv (LISTE T[], int taille) // tri des gouvernorats par ordre alphabetique inverse
{
    int j,i;
    for (i=0; i<24; i++)
    {
        for (j=0; j<24; j++)
        {

            if (strcmp( T[i]->Nom_gouvernorat,T[j]->Nom_gouvernorat ) > 0)
            {
                SwapListe(&T[i],&T[j]);
            }
        }
    }
}
int num_ligne (char* path) // renvoie le nombre des lignes dans un fichier text
{
    FILE *fp;
    char filename[50] ;
    strcpy(filename,path);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
        return 1;
    }
    int nbr_ligne=0;
    char lfp;
    for ( lfp = getc(fp); lfp != EOF ; lfp=getc(fp))
    {
        if (lfp == '\n')
            nbr_ligne++;
    }
    fclose(fp);
    return nbr_ligne;
}
int doc_txt(char* path,LISTE gouvernorats[]) // lire les donnes a partir d'une fichier texte
{
    char gouv_list [24][14] = { "Ariana","Beja","Ben Arous","Bizerte","Gabes","Gafsa",
                                "Jendouba","Kairouan","Kasserine","Kebili","La Manouba","Le Kef",
                                "Mahdia","Medenine","Monastir","Nabeul","Sfax","Sidi Bouzid",
                                "Siliana","Sousse","Tataouine","Tozeur","Tunis","Zaghouan"
                              };
    FILE *fp;
    char str[100];
    char filename[50] ;

    strcpy(filename,path);
    int i;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
        return 1;
    }


    for ( i= 0; i<=num_ligne(filename) ; i++)
    {

        fgets(str,100,fp);
        int j=0,test=0;
        char gouv[15];
        strcpy(gouv,"");
        while ((j<24)&&(test==0)) // recherche du nom de gouvernorat dans un ligne du document txt
        {
            if (strstr(str,gouv_list[j])!= NULL)
            {
                strcpy(gouv,gouv_list[j]);
                test=1;
            }

            else
                j++;
        }

        char* token;

        test=0;

        token=strtok(str," ");
        ELEMENT e=elementCreer();
        while(token)
        {
            if (strstr(gouv," ")== NULL)
                switch(test)
                {
                case 0 :
                    e->jour=atoi(token);
                    break;
                case 1 :
                    e->mois=ConvMois(token);
                    break;
                case 2 :
                    e->annee=atoi(token);
                    break;
                case 4 :
                    e->Cas_positifs=atoi(token);
                    break;
                case 5 :
                    e->Guerisons=atoi(token);
                    break;
                case 6 :
                    e->Deces=atoi(token);
                    break;
                case 7 :
                    e->Nombre_de_vaccines=atoi(token);
                    break;


                }
            else if (strstr(gouv," ")!= NULL)
                switch(test)
                {
                case 0 :
                    e->jour=atoi(token);
                    break;
                case 1 :
                    e->mois=ConvMois(token);
                    break;
                case 2 :
                    e->annee=atoi(token);
                    break;
                case 5 :
                    e->Cas_positifs=atoi(token);
                    break;
                case 6 :
                    e->Guerisons=atoi(token);
                    break;
                case 7 :
                    e->Deces=atoi(token);
                    break;
                case 8 :
                    e->Nombre_de_vaccines=atoi(token);
                    break;


                }


            test++;
            token=strtok(NULL," ");
        }
        // printf("%s",gouv);
        test=0;
        j=0;
        while (( j <24)&&(test==0)) // recherche de liste du gouvernorat corespondant
        {

            if (strcmp(gouv,gouvernorats[j]->Nom_gouvernorat)==0)
            {
                test=1;
                inserer(gouvernorats[j],e,gouvernorats[j]->lg+1);


            }
            else j++;

        }

    }
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t Upload Succesful !!\n\n");
    fclose(fp);

    return 0;
}
void supprimer_donnees(LISTE gouvernorats[]) // supprimer un element
{
    int i;
    int choix;
    char gouv[20];

    printf("\t\t\t\t\t\t\t\t 1 - Delete state  :  \n");
    printf("\t\t\t\t\t\t\t\t 2 - Delete data in state\n");
    do
    {
        printf("\t\t\t\t\t\t\t\t Choose :");
        scanf("%i",&choix);

    }
    while (choix<1 || choix>2);
    if (choix==1){
        printf("\t\t\t\t\t\t\t\t\tName of state  :  \n");
        fflush(stdin);
        fgets(gouv,20,stdin);
        i=0;
        while (i<24)
        {
            if (strcmp(gouv,gouvernorats[i]->Nom_gouvernorat)==0)
            {
                for (int k = i ; k<24 ; k++)
                    gouvernorats[i]=gouvernorats[i+1];
            }
        }}


        else if (choix==2){

            char gouv[20];
            int jj,mm,aa;
            printf("\t\t\t\t\t\t\t\t\tName of state  :  ");
            fflush(stdin);
            gets(gouv);
            do
            {
                printf("\t\t\t\t\t\t\t\t\tEnter the day : ");
                scanf("%i",&jj);
                fflush(stdin);
                printf("\t\t\t\t\t\t\t\t\tEnter the month : ");
                scanf("%i",&mm);
                fflush(stdin);
                printf("\t\t\t\t\t\t\t\t\tEnter the year : ");
                scanf("%i",&aa);
                fflush(stdin);
            }
            while(dateverifier(jj,aa,mm)==1);
            fflush(stdin);
            for (int i = 0 ; i < 24 ; i++)
            {
                if (strcmp(gouv,gouvernorats[i]->Nom_gouvernorat)==0)
                {
                    NOEUD n = gouvernorats[i]->tete ;

                    for (int k = 1 ; k <= gouvernorats[i]->lg ; k++)
                    {
                        if ((n->info->jour == jj)&&(n->info->mois == mm)&&(n->info->annee == aa))
                        {
                            supprimer(gouvernorats[i],k) ;
                        }
                        n = n->suivant ;


                    }

                }
            }
        }
    }
void modifier_data(LISTE gouvernorats[]) // modifier un element
{
    char gouv[20];
    int jj,mm,aa;
    printf("\t\t\t\t\t\t\t\tName of state  :  ");
    gets(gouv);
    printf("\n\n");
    fflush(stdin);

    do
    {
        printf("\t\t\t\t\t\t\t\t\tEnter the day : ");
        scanf("%i",&jj);
        printf("\n\n");
        fflush(stdin);
        printf("\t\t\t\t\t\t\t\t\tEnter the month : ");
        scanf("%i",&mm);
        printf("\n\n");
        fflush(stdin);
        printf("\t\t\t\t\t\t\t\t\tEnter the year : ");
        scanf("%i",&aa);
        printf("\n\n");
        fflush(stdin);
    }
    while(dateverifier(jj,aa,mm)==1);
    printf("\t\t\t\t\t\t\t\t\tChoose data to change : \n");
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t\t1 : Positive cases \n");
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t\t2 : Recovred \n");
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t\t3 : Deceased  \n");
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t\t4 : Numbre of vaccines  \n");
    printf("\n\n");
    int choix;
    scanf("%i",&choix);
    fflush(stdin);

    for (int i = 0 ; i < 24 ; i++)
    {
        if (strcmp(gouv,gouvernorats[i]->Nom_gouvernorat)==0)
        {
            NOEUD n = gouvernorats[i]->tete ;
            for (int k = 1 ; k <= gouvernorats[i]->lg ; k++)
            {
                if ((n->info->jour == jj)&&(n->info->mois == mm)&&(n->info->annee == aa))
                {
                    elementModifier(&n->info,choix);
                }
                n = n->suivant;
            }
            listeAfficher(gouvernorats[i]);

        }
        Tri_Liste_par_Dates(gouvernorats[i]);
    }
}

int main()
{
    Color(15,2);
    LISTE L1 = listeCreer("Ariana") ; // Creation des Listes des gouvernorats
    LISTE L2 = listeCreer("Beja") ;
    LISTE L3 = listeCreer("Ben Arous") ;
    LISTE L4 = listeCreer("Bizerte") ;
    LISTE L5 = listeCreer("Gabes") ;
    LISTE L6 = listeCreer("Gafsa") ;
    LISTE L7 = listeCreer("Jendouba") ;
    LISTE L8 = listeCreer("Kairouan") ;
    LISTE L9 = listeCreer("Kasserine") ;
    LISTE L10 = listeCreer("Kebili") ;
    LISTE L11 = listeCreer("La Manouba") ;
    LISTE L12 = listeCreer("Le Kef") ;
    LISTE L13 = listeCreer("Mahdia") ;
    LISTE L14 = listeCreer("Medenine") ;
    LISTE L15 = listeCreer("Monastir") ;
    LISTE L16 = listeCreer("Nabeul") ;
    LISTE L17 = listeCreer("Sfax") ;
    LISTE L18 = listeCreer("Sidi Bouzid") ;
    LISTE L19 = listeCreer("Siliana") ;
    LISTE L20 = listeCreer("Sousse") ;
    LISTE L21 = listeCreer("Tataouine") ;
    LISTE L22 = listeCreer("Tozeur") ;
    LISTE L23 = listeCreer("Tunis") ;
    LISTE L24 = listeCreer("Zaghouan") ;

    LISTE gouvernorats[24]; // Creation du tableau des liste des gouvernorats

    gouvernorats[0] = L1 ;   // Affectation des listes aux tableau
    gouvernorats[1] = L2;
    gouvernorats[2] = L3;
    gouvernorats[3] = L4;
    gouvernorats[4] = L5;
    gouvernorats[5] = L6;
    gouvernorats[6] = L7;
    gouvernorats[7] = L8;
    gouvernorats[8] = L9;
    gouvernorats[9] = L10;
    gouvernorats[10] = L11;
    gouvernorats[11] = L12;
    gouvernorats[12] = L13;
    gouvernorats[13] = L14;
    gouvernorats[14] = L15;
    gouvernorats[15] = L16;
    gouvernorats[16] = L17;
    gouvernorats[17] = L18;
    gouvernorats[18] = L19;
    gouvernorats[19] = L20;
    gouvernorats[20] = L21;
    gouvernorats[21] = L22;
    gouvernorats[22] = L23;
    gouvernorats[23] = L24;
    // int test = doc_txt("C:\\Users\\Nassim Salhi\\Desktop\\Corona virus\\test.txt",gouvernorats);
    int choix=0;
    system("cls");
    printf("||---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|| \n");
    printf("||----------------------------------------------------------------------------------------**********************-------------------------------------------------------------------------------------------------|| \n");
    printf("||----------------------------------------------------------------------------------------**** COVID-19 NEWS****-------------------------------------------------------------------------------------------------|| \n");
    printf("||----------------------------------------------------------------------------------------**********************-------------------------------------------------------------------------------------------------|| \n");
    printf("||---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|| \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t 1 - New input\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t 2 - Modify data\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t 3 - Delete data\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t 4 - Import data\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t 5 - Show data\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t 6 - Insights \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t 7 - Exit\n");
    printf("\n\n\n\n\n\n\n\n\n");

    printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
    printf( "\t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||  MADE BY             :                                 ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||           JENDOUBI BOSHRA && SALHI NASSIM              ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||             HIGHER INSTITUT OF MANAGMENT               ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||                     2020-2021                          ||*\n");
    printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
    fflush(stdin);
    scanf("%i",&choix);
    system("cls");
    while (choix<7) // menu
    {

        if (choix==1) // entrer un element
        {

            int i=0;
            char gouv[20];
            printf("\t\t\t\t\t\t\t\t\tName of state  :  ");
            fflush(stdin);
            gets(gouv);
            while(strcmp(gouvernorats[i]->Nom_gouvernorat,gouv)!=0)
                i++;
            ELEMENT e=elementCreer();
            do
            {
                elementLire(&e);
                inserer(gouvernorats[i],e,1);
            }
            while(elementexiste(gouvernorats[i],e)==0);
                Tri_Liste_par_Dates(gouvernorats[i]);

            printf("\t\t\t\t\t\t\t\t\t\t\t 1 - New input\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 2 - Modify data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 3 - Delete data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 4 - Import data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 5 - Show data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 6 - Insights \n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 7 - Exit\n");
            printf("\n\n\n\n\n\n\n\n\n");

            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            printf( "\t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||  MADE BY             :                                 ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||           JENDOUBI BOSHRA && SALHI NASSIM              ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||             HIGHER INSTITUT OF MANAGMENT               ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                     2020-2021                          ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            fflush(stdin);
            scanf("%i",&choix);
            system("cls");
        }
        else if (choix==2) // modifier
        {
            modifier_data(gouvernorats);
            printf("\t\t\t\t\t\t\t\t\t\t\t 1 - New input\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 2 - Modify data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 3 - Delete data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 4 - Import data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 5 - Show data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 6 - Insights \n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 7 - Exit\n");
            printf("\n\n\n\n\n\n\n\n\n");

            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            printf( "\t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||  MADE BY             :                                 ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||           JENDOUBI BOSHRA && SALHI NASSIM              ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||             HIGHER INSTITUT OF MANAGMENT               ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                     2020-2021                          ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            fflush(stdin);
            scanf("%i",&choix);
            system("cls");
        }
        else if (choix==3) // supprimer
        {
            supprimer_donnees(gouvernorats);
            printf("\t\t\t\t\t\t\t\t\t\t\t 1 - New input\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 2 - Modify data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 3 - Delete data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 4 - Import data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 5 - Show data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 6 - Insights \n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 7 - Exit\n");
            printf("\n\n\n\n\n\n\n\n\n");

            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            printf( "\t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||  MADE BY             :                                 ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||           JENDOUBI BOSHRA && SALHI NASSIM              ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||             HIGHER INSTITUT OF MANAGMENT               ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                     2020-2021                          ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            fflush(stdin);
            scanf("%i",&choix);
            system("cls");
        }
        else if (choix==4) // lire a partir d'un fichier
        {
            //C:\Users\Nassim Salhi\Desktop\Corona virus\Data.txt
            printf("\t\t\t\t\t\t\t\t\t\t\tEnter the path to the file : ");
            char filename[200];
            char *newline;
            fflush(stdin);
            if (fgets(filename, sizeof(filename), stdin) == NULL)
                return -1; // Input error / EOF
            newline = strchr(filename, '\n');
            if (newline) // ? is a newline present?
                *newline = '\0';
            // printf("**%s**\n", filename);
            doc_txt(filename,gouvernorats);
            printf("\t\t\t\t\t\t\t\t\t\t\t 1 - New input\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 2 - Modify data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 3 - Delete data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 4 - Import data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 5 - Show data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 6 - Insights \n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 7 - Exit\n");
            printf("\n\n\n\n\n\n\n\n\n");

            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            printf( "\t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||  MADE BY             :                                 ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||           JENDOUBI BOSHRA && SALHI NASSIM              ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||             HIGHER INSTITUT OF MANAGMENT               ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                     2020-2021                          ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            fflush(stdin);
            scanf("%i",&choix);
            system("cls");
            fflush(stdin);
        }
        else if (choix==5) // afficher les donnes
        {

            printf("\t\t\t\t\t\t\t\t\tName of state  :  ");
            char gouv[20];
            scanf("%s",gouv);
            int trouve=0,i=0;
            while ((i<24)&&(trouve==0)) // recherche du nom de gouvernorat dans un ligne du document txt
            {
                if (strcmp(gouv,gouvernorats[i]->Nom_gouvernorat)== 0)
                {
                    Tri_Liste_par_Dates(gouvernorats[i]);
                    listeAfficher(gouvernorats[i]);
                    trouve=1;
                }

                else
                    i++;
            }
            printf("\t\t\t\t\t\t\t\t\t\t\t 1 - New input\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 2 - Modify data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 3 - Delete data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 4 - Import data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 5 - Show data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 6 - Insights \n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 7 - Exit\n");
            printf("\n\n\n\n\n\n\n\n\n");

            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            printf( "\t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||  MADE BY             :                                 ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||           JENDOUBI BOSHRA && SALHI NASSIM              ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||             HIGHER INSTITUT OF MANAGMENT               ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                     2020-2021                          ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            fflush(stdin);
            scanf("%i",&choix);
            system("cls");
        }
        else if (choix==6) //tri par cle
        {

            int clecaspos,cleguerisons, cledeces,clevaccins,mode_tri;
            fflush(stdin);
            do
            {
                printf("\t\t\t\t\t\t\t\t\tType the priority code : \n\n");
                printf("\t\t\t\t\t\t\t\t\tPositive cases     : ");
                scanf("%i",&clecaspos);
                printf("\n");
                fflush(stdin);
                printf("\t\t\t\t\t\t\t\t\tRecovered          : ");
                scanf("%i",&cleguerisons);
                printf("\n");
                fflush(stdin);
                printf("\t\t\t\t\t\t\t\t\tDeceased           : ");
                scanf("%i",&cledeces);
                printf("\n");
                fflush(stdin);
                printf("\t\t\t\t\t\t\t\t\tNumber of vaccines : ");
                scanf("%i",&clevaccins);
                printf("\n");
                fflush(stdin);

            }
            while((clecaspos<1)||(clecaspos>4)||(cledeces<1)||(cledeces>4)||(clevaccins<1)||(clevaccins>4)||(cleguerisons<1)||(cleguerisons>4));
            printf("\n");
            printf("\t\t\t\t\t\t\t\t\tType 1 for ascending order or 2 for descending : ");
            printf("\n");
            do
            {
                scanf("%i",&mode_tri);
                fflush(stdin);
            }
            while(mode_tri!=1&&mode_tri!=2);
            tri_cle(gouvernorats,clecaspos,cleguerisons,cledeces,clevaccins,mode_tri);
            printf("\t\t\t\t\t\t\t\t\t\t\t 1 - New input\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 2 - Modify data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 3 - Delete data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 4 - Import data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 5 - Show data\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 6 - Insights \n");
            printf("\t\t\t\t\t\t\t\t\t\t\t 7 - Exit\n");
            printf("\n\n\n\n\n\n\n\n\n");

            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            printf( "\t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||  MADE BY             :                                 ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||           JENDOUBI BOSHRA && SALHI NASSIM              ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||             HIGHER INSTITUT OF MANAGMENT               ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                                                        ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||                     2020-2021                          ||*\n");
            printf(" \t\t\t\t\t\t\t\t\t*||--------------------------------------------------------||*\n");
            fflush(stdin);
            scanf("%i",&choix);
            system("cls");
        }
    }

    return 0;
}

