#include<stdio.h>
#include<malloc.h>
#include<windows.h>

#include "ELTPRIM.H"

ELEMENT elementCreer()
{
    ELEMENT e=(ELEMENT)malloc(sizeof(date));
    e->jour=0; // Initialisation de jour
    e->mois=0; // Initialisation du mois
    e->annee=0; // Initialisation de l'annee
    e->Cas_positifs=0; // Initialisation
    e->Guerisons=0; // Initialisation
    e->Deces=0; // Initialisation
    e->Nombre_de_vaccines=0; // Initialisation
    strcpy(e->nom_gouv,"");
    return e;
}


int dateverif (int jj,int mm,int aa)
{
    /*SYSTEMTIME time;
    GetLocalTime(&time);
    printf("%d %d %d",time.wYear,time.wMonth,time.wDay);
    ,test2=0;
    if ((aa== time.wYear)&&(mm==time.wMonth)&&(jj== time.wDay))
                test2=1;*/
    int test=0;
    //verif annee
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



    return (test);
}

void elementLire(ELEMENT* e)
{
    do
    {
        printf("\t\t\t\t\t\t\t\t\t  Enter the day : ");
        scanf("%i",&(*e)->jour);
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t  Enter the month : ");
        scanf("%i",&(*e)->mois);
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t  Enter the year : ");
        scanf("%i",&(*e)->annee);
        printf("\n\n");

    }
    while ((dateverif((*e)->jour,(*e)->mois,(*e)->mois)!=1  ));
    do
    {
        printf("\t\t\t\t\t\t\t\t\t\tPositive cases : ");
        scanf("%i",&(*e)->Cas_positifs);
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\tRecovred : ");
        scanf("%i",&(*e)->Guerisons);
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\tDeceased : ");
        scanf("%i",&(*e)->Deces);
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\tNumbre of vaccines : ");
        scanf("%i",&(*e)->Nombre_de_vaccines);
        printf("\n\n");
    }
    while ((*e)->Cas_positifs<0 ||(*e)->Guerisons<0 ||(*e)->Deces<0 ||(*e)->Nombre_de_vaccines<0 );

}

void elementAfficher(ELEMENT e)
{
    char months[12][10] =
    {
        "Janvier", "Fevrier", "Mars", "Avril",
        "Mai", "Juin", "Juillet", "Aout",
        "September", "October", "November", "December",
    };

    printf("\t\t\t\t\t\t\t\t\t\t\t %d ",e->jour);
    printf("%s %d \n", months[e->mois - 1], e->annee);
    printf("\t\t\t\t\t\t\t\t\t\t\t Positive cases : %i\n",e->Cas_positifs);
    printf("\t\t\t\t\t\t\t\t\t\t\t Recovered : %i \n",e->Guerisons);
    printf("\t\t\t\t\t\t\t\t\t\t\t Deceased : %i \n",e->Deces);
    printf("\t\t\t\t\t\t\t\t\t\t\t Number of vaccines: %i\n",e->Nombre_de_vaccines);
}
void elementAfficher2 (ELEMENT e)
{
    for(int i=strlen(e->nom_gouv); i<19; i++)
        strcat(e->nom_gouv," ");
    printf("\t\t\t\t\t\t\t %s\t \t %i              %i              %i           %i\n",e->nom_gouv,e->Cas_positifs,e->Guerisons,e->Deces,e->Nombre_de_vaccines);

}

void elementDetruire(ELEMENT e)
{
    free(e);
}

void elementAffecter(ELEMENT* e1, ELEMENT e2)
{
    *e1=e2;
}

void elementCopier(ELEMENT * e1, ELEMENT e2)
{
    // memcpy(*e1,e2,sizeof(date));
}

int elementComparer(ELEMENT e1, ELEMENT e2)
{
    if((e1->Deces==e2->Deces)&&(e1->Nombre_de_vaccines==e2->Nombre_de_vaccines)&&(e1->Guerisons==e2->Guerisons)&&(e1->Cas_positifs==e2->Cas_positifs)) return 1;
    else return 0;
}
