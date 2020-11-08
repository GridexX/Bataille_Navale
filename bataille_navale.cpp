#include <iostream>
#include <iterator>
#include <string>
using namespace std;

#include "hide.h"

const int DIM=10;
const unsigned int NB_BAT=5;
const unsigned int LIST_BAT[NB_BAT]={5,4,3,3,2};

struct sBateau{
    unsigned int coord1[2];
    unsigned int coord2[2];
    unsigned int taille;
    unsigned int caseTouch=0;
};

struct sJoueur{
    unsigned int tabBat[DIM][DIM];
    unsigned int tabTir[DIM][DIM];
    bool tabBatCoule[NB_BAT];
    struct sBateau statBat[NB_BAT];
    unsigned int nbTouche=0;
};

typedef struct sBateau Bateau;
typedef struct sJoueur Joueur;

void triDecroissant(unsigned int tableau[],unsigned int tailletableau){
    unsigned int valeurtemporaire;
    for (unsigned int i=0; i<tailletableau; i++)
    {
        for(unsigned int j=i; j<tailletableau; j++)
        {
            if(tableau[j]>tableau[i]){
                valeurtemporaire = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = valeurtemporaire;
            }
        }
    }
}

void initTab(unsigned int tab[DIM][DIM]){
    for (unsigned int i=0; i<DIM; ++i){
        for (unsigned int j=0; j<DIM; ++j){
            tab[i][j]=0;
        }
    }
}

void fusionTab(unsigned int tab[DIM][DIM], unsigned int copieTab[DIM][DIM]){
    for (unsigned int i=0; i<DIM; i++)
    {
        for(unsigned int j=0; j<DIM; j++)
        {
            if(tab[i][j]==1 || copieTab[i][j]==1){
                tab[i][j]=1;
            }
        }
    }
}

void copierTab(unsigned int copieTab[DIM][DIM], unsigned int tabACopier[DIM][DIM]){
    for (unsigned int i=0; i<DIM; i++)
    {
        for(unsigned int j=0; j<DIM; j++)
        {
            copieTab[i][j]=tabACopier[i][j];
        }
    }
}

void afficher1Tab(unsigned int tab[DIM][DIM]){ //sert pas au final mdr
    unsigned int x=1;
    cout << "   │ " << x;
    for(x=1; x<DIM-1; ++x){
        cout << " │ " << x+1;
    }
    cout << " │ "<<DIM<< endl;
    for (unsigned int i=0; i<DIM; ++i){
        cout << " " << char(i+65) << " │";

        for (unsigned int j=0; j<DIM; ++j){
            if(tab[i][j]==0){cout << " - ";}
            if(tab[i][j]==1){cout << " ■ ";}
            if(tab[i][j]==2){cout << "\e[1m\e[91m X \e[0m";}
            if(tab[i][j]==3){cout << "\e[1m\e[34m Ø \e[0m";}
            if(j<9){ cout << "│";}
        }
        cout << endl;
    }
}

void afficher2TabCote(unsigned int tab1[DIM][DIM], unsigned int tab2[DIM][DIM]){
    cout << "                   Joueur 1                                              Joueur 2" << endl;
    unsigned int x=1;
    cout << "   │ " << x;
    for(x=1; x<DIM-1; ++x){
        cout << " │ " << x+1;
    }
    cout << " │ "<<DIM<< "          ";
    x=1;
    cout << "   │ " << x;
    for( x=1; x<DIM-1; ++x){
        cout << " │ " << x+1;
    }
    cout << " │ "<<DIM<< endl;
    for (unsigned int i=0; i<DIM; ++i){
        cout << " " << char(i+65) << " │";

        for (unsigned int j=0; j<DIM; ++j){
            if(tab1[i][j]==0){cout << " - ";}
            if(tab1[i][j]==1){cout << " ■ ";}
            if(tab1[i][j]==2){cout << "\e[1m\e[91m X \e[0m";}
            if(tab1[i][j]==3){cout << "\e[1m\e[34m Ø \e[0m";}
            if(j<9){ cout << "│";}
        }

        cout << "           " << char(i+65) << " │";

        for (unsigned int j=0; j<DIM; ++j){
            if(tab2[i][j]==0){cout << " - ";}
            if(tab2[i][j]==1){cout << " ■ ";}
            if(tab2[i][j]==2){cout << "\e[1m\e[91m X \e[0m";}
            if(tab2[i][j]==3){cout << "\e[1m\e[34m Ø \e[0m";}
            if(j<9){ cout << "│";}
        }
        cout << endl;
    }

}

void afficher2Tab(unsigned int tab1[DIM][DIM], unsigned int tab2[DIM][DIM]){
    unsigned int x=1;
    cout << "   │ " << x;
    for( x=1; x<DIM-1; ++x){
        cout << " │ " << x+1;
    }
    cout << " │ "<<DIM<< endl;
    for (unsigned int i=0; i<DIM; ++i){
        cout << " " << char(i+65) << " │";

        for (unsigned int j=0; j<DIM; ++j){
            if(tab1[i][j]==0 && tab2[i][j]==0){cout << " - ";}
            if(tab1[i][j]==1 || tab2[i][j]==1){cout << " ■ ";}
            if(j<9){ cout << "│";}
        }
        cout << endl;
    }
}

int afficheBatDisp(unsigned int batD[], unsigned int lenTab){
    //affiche bateau sélectionné en bleu
    char choix;
    unsigned int iselect=0;
    unsigned int bataPlacer;
    system("clear");
    while(true){
        cout << "Utilisez 'q' et 'd' pour déplacer la selection puis appuiez sur 'enter' pour le choisir un bateau" << endl;
        //renvoie la taille d'une liste si index!=0
        for (unsigned int i=0; i<lenTab; ++i){
            for (unsigned int j=0; j<batD[i]; ++j){
                if(i==iselect){
                    cout << "\e[96m■\e[0m"; //carré bleu
                }
                else{
                    cout << "■";
                }
                //cout << i << "  " << batD[i] << "  " << j;
            }
            cout << "   "; //espaces entre les bateaux
        }
        
        choix=getHiddenChar();
        if(choix=='d'){
                iselect=(iselect+1)%lenTab;

        }
        if(choix=='q'){

                if(iselect==0){
                    iselect=lenTab-1;
                }
                else{
                    --iselect;
                }
        }   
        system("clear");
        if(choix=='\n'){
            bataPlacer=batD[iselect];
            batD[iselect]=0;
            return bataPlacer;
        }
    }  
}

bool estVertical(Bateau bat){
    return bat.coord1[1]==bat.coord2[1];
}

bool estSurEau(Bateau bat, unsigned int tab[DIM][DIM]){
    unsigned int i,j;
    i=bat.coord1[0];
    j=bat.coord1[1];
    bool estSurEau=true;
    while( (i<=bat.coord2[0] && j<=bat.coord2[1]) && estSurEau){
        estSurEau= tab[j][i]==0;
        if(estVertical(bat)){
            ++i;
        }else{
            ++j;
        }
    }
    return estSurEau;
}

void affecterBatauTab(Bateau bat,unsigned int tab[DIM][DIM]){
    unsigned int i,j;
    i=bat.coord1[0];
    j=bat.coord1[1];

    while(i<=bat.coord2[0] && j<=bat.coord2[1]){
        tab[j][i]=1;
        if(estVertical(bat)){
            ++i;
        }else{
            ++j;
        }
    }
}

Bateau constructionTab(unsigned int tab[DIM][DIM], unsigned int lgBat){
    unsigned int temp;
    Bateau bat;
    char choix;
    unsigned int moit=(lgBat+lgBat%2)/2;
    unsigned int copieTab[DIM][DIM];

    bat.coord1[0]=lgBat-moit+lgBat%2;
    bat.coord1[1]=DIM/2;
    bat.coord2[0]=lgBat+moit-1;
    bat.coord2[1]=DIM/2;
    bat.taille=lgBat;
    bat.caseTouch=0;

    initTab(copieTab);
    while(true){
        affecterBatauTab(bat,copieTab);
        afficher2Tab(copieTab,tab);
        cout << "utilisez 'z','q','s','d' pour déplacer / 'r' pour tourner le bateau et 'enter' pour confirmer" << endl;
        choix=getHiddenChar();
        system("clear");
        switch (choix){
            case 'z':
                if(bat.coord1[1]>0){
                    bat.coord1[1]=bat.coord1[1]-1;
                    bat.coord2[1]=bat.coord2[1]-1;
                }
                break;

            case 's':
                if(bat.coord1[1]<DIM-1){
                        bat.coord1[1]=bat.coord1[1]+1;
                        bat.coord2[1]=bat.coord2[1]+1;
                    }
                break;

            case 'q':
                if(bat.coord1[0]>0){
                    bat.coord1[0]=bat.coord1[0]-1;
                    bat.coord2[0]=bat.coord2[0]-1;
                }
                break;

            case 'd':
                if(bat.coord2[0]<DIM-1){
                    bat.coord1[0]=bat.coord1[0]+1;
                    bat.coord2[0]=bat.coord2[0]+1;
                }
                break;

            case 'r':
                if(!estVertical(bat) && bat.coord1[0]+lgBat<=DIM){
                    temp=bat.coord2[1]-bat.coord1[1]+bat.coord1[0];
                    bat.coord2[1]=bat.coord1[1];
                    bat.coord2[0]=temp;
                }
                else if(estVertical(bat) && bat.coord1[1]+lgBat<=DIM){ 
                    temp=bat.coord2[0]-bat.coord1[0]+bat.coord2[1];
                    bat.coord2[0]=bat.coord1[0];
                    bat.coord2[1]=temp;
                }   
                break;

            case '\n':
                if(estSurEau(bat,tab)){
                    fusionTab(tab,copieTab);
                    return bat;
                }else{
                    cout << "\e[1m\e[91m Le bateau est sur un autre bateau ! \e[0m" <<endl;
                }

                break;
        }
        initTab(copieTab);
    }
}

void intiTabBatDispo(unsigned int tabBat[NB_BAT]){
    for (unsigned int i=0; i<NB_BAT; ++i){
        tabBat[i]=LIST_BAT[i];
    }
}


void placerBat(unsigned int tab[DIM][DIM], Bateau statBat[NB_BAT]){
    unsigned int batDispo[NB_BAT];
    unsigned int cpt=NB_BAT;
    unsigned int tailleBat;

    intiTabBatDispo(batDispo);
    initTab(tab);
    while(cpt>0){   //affichage Bateau et liste ceux restant
        triDecroissant(batDispo,NB_BAT);
        tailleBat=afficheBatDisp(batDispo,cpt);
        statBat[cpt-1]=constructionTab(tab,tailleBat);
        --cpt;

        //system("clear");
    }
}

bool estBatCoule(Joueur Jcible, unsigned int numBat){
    return Jcible.statBat[numBat].caseTouch==Jcible.statBat[numBat].taille;
}

bool estBatTouche(sBateau bat, unsigned int coordX, unsigned int coordY){
    bool estTouche=false;
    unsigned int i=bat.coord1[0];
    unsigned int j=bat.coord1[1];
    while (i<=bat.coord2[0] && j<=bat.coord2[1] && !estTouche){
       estTouche=  j==coordX && i==coordY;
        if(estVertical(bat)){
            ++i;
        }else{
            ++j;
        }
    }
    return estTouche;
} 

bool estbatToucheCoule(Bateau bat){
    return bat.caseTouch==bat.taille;
}

void torpillage(Joueur &Jtir, Joueur &Jcible, unsigned int numJ){
    char carX;
    unsigned int entY, tirX, tirY;
    int cpt;
    bool estTouche,aTrouveBatTouche, estDejaTouche;
    do{

        cout<< "Joueur n°" << numJ <<", entrez les coordonées de la torpille (Ex: A9) >";
        cin >> carX >> entY;

         tirY=entY-1;
    if( !(carX<'A' || carX>'J')){
        tirX=int(carX-65);
    }else
    {
        tirX=int(carX-97);
    }
    estDejaTouche= Jtir.tabTir[tirX][tirY]==2 || Jtir.tabTir[tirX][tirY]==3;
    if(estDejaTouche){
        cout << "\e[91mCASE DEJA VISE\e[0m"<<endl;
    }
   
    }while( ((carX<'A' || carX>'J')&&(carX<'a' || carX>'j')) || entY>DIM || estDejaTouche);
    

    //détermine si la torpille à touché un bateau
    estTouche= Jcible.tabBat[tirX][tirY]==1;

    if(estTouche){
        cout << "\e[91mBATEAU TOUCHE\e[0m";
        Jtir.nbTouche++;
        Jtir.tabTir[tirX][tirY]=2;

        //test si bateau est touché coulé
        cpt=-1;
        aTrouveBatTouche=false;
        while(cpt<5 && !aTrouveBatTouche){
            cpt++;
            if(!(Jtir.tabBatCoule[cpt])){
                aTrouveBatTouche=estBatTouche(Jcible.statBat[cpt],tirX,tirY);
            }
            
        }
        Jcible.statBat[cpt].caseTouch++;
        if(estbatToucheCoule(Jcible.statBat[cpt])){
            cout << "\e[1m\e[91m COULE !\e[0m";
            Jtir.tabBatCoule[cpt]=true;
        }
        cout << endl;
    }else{
        cout << endl << "\e[34mA L'EAU \e[0m" << endl;
        Jtir.tabTir[tirX][tirY]=3;
    }  
}

unsigned int casesTotal(){
    unsigned int s=0;
    for (unsigned int i=0; i<NB_BAT; i++){
        s+=LIST_BAT[i];
    }
    return s;
}

bool gagne(Joueur J1, Joueur J2){
    return J1.nbTouche==casesTotal() || J2.nbTouche==casesTotal();
}

unsigned int joueurGagnant(Joueur J1, Joueur J2){
    if (gagne(J1,J1)){
        return 1;
    }else{
        return 2;
    }
}

void initTabBatCoule(bool tabBatC[NB_BAT]){
    for (unsigned int i=0; i<NB_BAT; ++i){
        tabBatC[i]=false;
    }
}

int main(){
    Joueur J1, J2;
    bool tour=true;
    initTab(J1.tabTir);
    initTabBatCoule(J1.tabBatCoule);
    initTabBatCoule(J2.tabBatCoule);
    initTab(J2.tabTir);

    placerBat(J1.tabBat,J1.statBat);
    system("clear");
    placerBat(J2.tabBat,J2.statBat);
    system("clear");

    while (!gagne(J1,J2)){
        if(tour){
            afficher2TabCote(J1.tabTir,J2.tabTir);
            cout << endl << endl;
            torpillage(J1,J2,1);
        }else{
            afficher2TabCote(J1.tabTir,J2.tabTir);
            cout << endl << endl;
            torpillage(J2,J1,2);
        }
        
        tour=!tour;  

        for (unsigned int i=0; i<NB_BAT; ++i){
        cout << J1.tabBatCoule[i];
        }  
        cout <<endl;
    }

    cout << "Bravo, le joueur n° " << joueurGagnant(J1,J2) << " à gagné !!!" << endl;

    return 0;
}
