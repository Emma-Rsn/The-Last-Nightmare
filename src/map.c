//
//map.c
//Created by Moreau Enzo Rasson Emma
//

/**
*\file map.c
*\brief Programme s'occupant de la création, l'initialisation et la gestion de la carte de jeu 
*\author Moreau Enzo Rasson Emma
*\date  Fevrier 2024
*\version 1.0
*
*/


#include "../libs/commun.h"

/**
*
*\fn case_t creation_case()
*\return Une case de 64*64 pixels
*\brief Fonction qui crée et initialise une case correspondant à un carré de 64*64 pixels
*/
case_t creation_case(){
    case_t c;
    c.etat=1;
    c.Rectangle.x=0;
    c.Rectangle.y=0;
    c.Rectangle.w=64;
    c.Rectangle.h=64;
    c.ntexture = 0;
    return c;
}

/**
*
*\fn grille_t creation_grille(int bord)
*\param bord Indique les bords de maps bloqués (9 valeurs différentes)
*\return Une grille de 30*16 cases
*\brief Fonction qui crée et initialise une grille de cases
*/
grille_t creation_grille(int bord){
    grille_t g;
    int i,j;
    int taille=64;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            g.tabGrille[i][j]=creation_case();
            switch (bord){
                case 0 : if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;break;
                case 1 : if(j == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //N
                case 2 : if(i == (LONG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //E
                case 3 : if(j == (LARG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //S
                case 4 : if(i == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //O
                case 5 : if(j == 0 || i == (LONG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //NE
                case 6 : if(j == (LARG-1) || i == (LONG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //SE
                case 7 : if(j == (LARG-1) || i == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //SO
                case 8 : if(j == 0 || i == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //NO
                default: break;
            }
            g.tabGrille[i][j].Rectangle.x=taille*i;
            g.tabGrille[i][j].Rectangle.y=taille*j+56;
            g.tabGrille[i][j].x=i;
            g.tabGrille[i][j].y=j;
        }
    }
    return g;

}

/**
*
*\fn carte_t creation_carte(int x,int y)
*\param x Position x de la carte dans la matrice tabMap de la carte
*\param y Position y de la carte dans la matrice tabMap de la carte
*\return Une carte initialisée
*\brief Fonction qui crée et initialise une carte 
*/
carte_t creation_carte(int x,int y){
    carte_t carte;
    int bord = 0; //variable pour savoir si on est en bordure de map
    carte.nZone=0;
    carte.xcarte=x;
    carte.ycarte=y;
    if(x == 0) bord = 1;
    if(x == (ROWS-1)) bord = 3;
    if(y == 0) bord = 4;
    if(y == (COLUMNS-1)) bord = 2;
    if(x == 0 && y == 0) bord = 8;
    if(x == 0 && y == (COLUMNS-1)) bord = 5;
    if(x == (ROWS-1) && y == 0) bord = 7;
    if(x == (ROWS-1) && y == (COLUMNS-1)) bord = 6;
    carte.grille=creation_grille(bord);
    carte.etat_brouillard=1;
    carte.nbObj = 0;
    carte.nrlayout = 0;
    return carte;
}


/**
*
*\fn map_t creation_map()
*\return Une map correspond à la carte de jeu entière
*\brief Fonction qui crée et initialise une map avec une matrice de cartes
*/
map_t creation_map (){
    map_t m;
    int i,j;
    m.tabTexture = NULL;
    m.Nightmare = 0;
    m.nvEquipe=2;
    m.bonusEquipeN=BONUS_EQUIPE_N;
    m.bonusZoneN=BONUS_ZONE_N;
    m.argent=0;
    m.Zone2 = 0;
    m.Zone3 = 0;
    m.Zone4 = 0;
    m.Zone5 = 0;
    m.plongee = 0;
    m.talisman = 0;
    m.talisman = 0;
    m.nb_emplacement=1;
    m.prix_emplacement=20;
    m.plongee = 0;
    m.cle = 0;
    m.talisman = 0;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            m.tabMap[i][j]=creation_carte(i,j);
        }
    }
    return m;
}

//map pour test
int afficher_grille(grille_t grille, SDL_Renderer *renderer){
    int i,j;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            SDL_RenderDrawRect(renderer, &(grille.tabGrille[i][j].Rectangle));
            //zone de test
            if(grille.tabGrille[i][j].etat == 3)SDL_RenderFillRect(renderer, &(grille.tabGrille[i][j].Rectangle));

        }
    }
    return 0;
}

/**
*
*\fn int afficherMap(SDL_Renderer *renderer,map_t * map,carte_t * cartec)
*\param renderer Rendu de la fenetre SDL
*\param map Map de jeu
*\param cartec Carte où le joueur se situe au moment d'afficher la map
*\brief Fonction qui affiche la carte
*/
int afficher_carte(SDL_Renderer *renderer,map_t * map,carte_t * cartec){
    int i,j;
    int n = 0;
    if(map->Nightmare)n=map->nbN;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            SDL_RenderCopy(renderer, map->tabTexture[cartec->grille.tabGrille[i][j].ntexture + n], NULL,&(cartec->grille.tabGrille[i][j].Rectangle));
        }
    }
    return 0;
}

/**
*
*\fn int creer_map(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui initialise la map de jeu procéduralement
*/
int creer_map(map_t * map){

    int x,y;
    int choix,choix2;
    srand( time( NULL ) );


    int xZone1 = rand() % 2 + 2;
    int yZone1 = rand() % 2 + 2;

    map->tabMap[xZone1][yZone1].nZone=1;

    //Initialisation des zones dans les coins de la map
    map->tabMap[0][0].nZone=5;
    map->tabMap[0][1].nZone=5;
    map->tabMap[1][0].nZone=5;
    map->tabMap[1][1].nZone=5;

    map->tabMap[4][0].nZone=4;
    map->tabMap[4][1].nZone=4;
    map->tabMap[5][0].nZone=4;
    map->tabMap[5][1].nZone=4;

    map->tabMap[0][4].nZone=3;
    map->tabMap[0][5].nZone=3;
    map->tabMap[1][4].nZone=3;
    map->tabMap[1][5].nZone=3;

    map->tabMap[4][4].nZone=2;
    map->tabMap[4][5].nZone=2;
    map->tabMap[5][4].nZone=2;
    map->tabMap[5][5].nZone=2;

    map->tabMap[3][0].nZone=4;


    //Cas particulier de la génération où la zone 3 du manoir n'est pas dans le coin en haut à droite
    if(xZone1==3&&yZone1==2){
        
        //Remplissage "logique" des zones en fonction du cas particulier
        map->tabMap[0][2].nZone=5;

        map->tabMap[0][3].nZone=3;
        map->tabMap[1][3].nZone=3;
        map->tabMap[2][2].nZone=3;

        map->tabMap[0][5].nZone=2;
        map->tabMap[1][5].nZone=2; 
        map->tabMap[2][4].nZone=2;
        map->tabMap[2][5].nZone=2;
        map->tabMap[3][3].nZone=2;
        map->tabMap[3][4].nZone=2;
        map->tabMap[3][5].nZone=2;

        map->tabMap[3][1].nZone=4;

        //Choix pour les cartes du manoir (zone 3)
        choix=rand() % 2;
        if(!choix){
            map->tabMap[1][2].nZone=3;
            map->tabMap[2][3].nZone=2;
        }
        else{
            map->tabMap[1][2].nZone=5;
            map->tabMap[2][3].nZone=3;
        }
        //Choix pour les cartes adjacentes de la plage ou de la foret (zone 2 et zone 4)
        choix=rand() % 3;
        switch(choix){
            //Cas si on rempli 1 case de la zone plage et 3 de la zone foret
            case 0:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            
            break;
            //Cas si on rempli 2 cases de la zone plage et 2 de la zone foret
            case 1:
            choix2=rand() % 3;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else if(choix2==1){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Troisième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;

            }
            break;
            //Cas si on rempli 3 cases de la zone plage et 1 de la zone foret
            case 2:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;
 
            }
            break;
        }
        //Choix pour les cartes adjacentes de la foret et de la grotte (zone 4 et zone 5)
        choix=rand() % 2;
        if(map->tabMap[2][2].nZone==1){
            choix=1;
        }
        if(choix==0){
            map->tabMap[2][1].nZone=5;
            map->tabMap[2][0].nZone=4;
        }
        else{
            map->tabMap[2][1].nZone=4;
            map->tabMap[2][0].nZone=5;
        }
    }





    //Cas général
    else{
        map->tabMap[xZone1-1][yZone1].nZone=3;
        map->tabMap[xZone1][yZone1-1].nZone=4;
        map->tabMap[xZone1][yZone1+1].nZone=2;

        map->tabMap[3][1].nZone=4;
        
        choix=rand() % 2;
        if(choix==0){
            map->tabMap[xZone1+1][yZone1].nZone=2;
        }
        else{
            map->tabMap[xZone1+1][yZone1].nZone=4;
        }

        if(xZone1==2&&yZone1==2){
            map->tabMap[3][3].nZone=2;
        }


        //Remplissage des cases adjacentes la zone manoir et grotte (zone 3 et 5)
        if(xZone1==2&&yZone1==3){
            map->tabMap[0][3].nZone=3;
        }
        else{
            map->tabMap[1][3].nZone=3;
        }
        for(x=2;x>=0;x--){
            for(y=3;y>=0;y--){
                if(map->tabMap[x][y].nZone==0){
                    map->tabMap[x][y].nZone=5;
                }
            }
        }

        //Remplissage des cases adjacentes la zone manoir et plage (zone 3 et 2)
        for(x=2;x<=3;x++){
            for(y=3;y<=5;y++){
                if(map->tabMap[x][y].nZone==0){
                    map->tabMap[x][y].nZone=2;
                }
            }
        }

        //Choix pour les cartes adjacentes de la plage ou de la foret (zone 2 et zone 4)
        choix=rand() % 3;
        switch(choix){
            //Cas si on rempli 1 case de la zone plage et 3 de la zone foret
            case 0:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            
            break;
            //Cas si on rempli 2 cases de la zone plage et 2 de la zone foret
            case 1:
            choix2=rand() % 3;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else if(choix2==1){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Troisième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;

            }
            break;
            //Cas si on rempli 3 cases de la zone plage et 1 de la zone foret
            case 2:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;
 
            }
            break;
        }
        //Choix pour les cartes adjacentes de la foret et de la grotte (zone 4 et zone 5)
        choix=rand() % 2;
        if(map->tabMap[2][2].nZone==1)choix=1;
        if(choix==0){
            map->tabMap[2][1].nZone=5;
            map->tabMap[2][0].nZone=4;
        }
        else{
            map->tabMap[2][1].nZone=4;
            map->tabMap[2][0].nZone=5;
        }

        if(map->tabMap[2][3].nZone==1){
            map->tabMap[3][2].nZone=4;
        }
    }
    
    return (sauvegarde_map(map));

}

/**
*
*\fn int sauvegarde_map(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui sauvegarde le numéro de zone de chaque carte de la map dans un fichier
*/
int sauvegarde_map(map_t * map){
    //Sauvegarde de la map dans un fichier
    FILE * file;
    int x,y;

    file=fopen("save/map.txt","w");
    if(file){
        for(x=0;x<ROWS;x++){
            for(y=0;y<COLUMNS;y++){
                fprintf(file,"%d",map->tabMap[x][y].nZone);
                if(y!=COLUMNS-1){
                    fprintf(file," ");
                }
                
            }
            fprintf(file,"\n");
        }

        


        fclose(file);
        return 0;
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    return 0;
}

/**
*
*\fn int creer_map_layout(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui initialise les layouts carte par carte procéduralement
*/
int creer_map_layout(map_t * map){

    if(load_layout_texture(map)){
        return 1;
    }

    int choix;
    srand( time( NULL ) );

    load_layout(&map->tabMap[5][5],"layout/layout2_1.txt");
    load_layout(&map->tabMap[5][0],"layout/layout4_1.txt");

    //Zone 2 sous marine
    load_layout(&map->tabMap[5][4],"layout/layout2_2.txt"); //Entrée boss zone 2

    if(map->tabMap[5][3].nZone == 2){
        if(map->tabMap[4][3].nZone == 2){
            if(map->tabMap[5][2].nZone == 2){
                choix=rand() % 2;
                if(choix == 1){
                    //Paire [5][2]/[5][3]
                    load_layout(&map->tabMap[5][2],"layout/layout2_3.txt");
                    load_layout(&map->tabMap[5][3],"layout/layout2_4.txt");
                    load_layout(&map->tabMap[4][3],"layout/layout2_5.txt"); //tout seul
                    //zone 4
                    load_layout(&map->tabMap[4][2],"layout/layout4_6.txt"); //tout seul
                }else{
                    //Paire [4][3]/[5][3]
                    load_layout(&map->tabMap[5][2],"layout/layout2_6.txt"); //tout seul
                    load_layout(&map->tabMap[5][3],"layout/layout2_7.txt");
                    load_layout(&map->tabMap[4][3],"layout/layout2_8.txt");
                    //zone 4
                    load_layout(&map->tabMap[4][2],"layout/layout4_6.txt"); //tout seul
                }
            }else{
                if(map->tabMap[4][2].nZone==2){
                    //Paire [4][3]/[5][3]
                    load_layout(&map->tabMap[5][3],"layout/layout2_7.txt");
                    load_layout(&map->tabMap[4][3],"layout/layout2_8.txt");
                    //zone 4
                    load_layout(&map->tabMap[5][2],"layout/layout4_6.txt");
                    load_layout(&map->tabMap[4][2],"layout/layout2_6.txt");
                }
                else{
                    //Paire [4][3]/[5][3]
                    load_layout(&map->tabMap[5][3],"layout/layout2_7.txt");
                    load_layout(&map->tabMap[4][3],"layout/layout2_8.txt");
                    //zone 4
                    //Paire [5][2]/[4][2]
                    load_layout(&map->tabMap[5][2],"layout/layout4_7.txt");
                    load_layout(&map->tabMap[4][2],"layout/layout4_8.txt");
                }
            }
        }else if(map->tabMap[5][2].nZone == 2){
            //Paire [5][2]/[5][3]
            load_layout(&map->tabMap[5][2],"layout/layout2_3.txt");
            load_layout(&map->tabMap[5][3],"layout/layout2_4.txt");
            //zone 4
            //Paire [4][2]/[4][3]
            load_layout(&map->tabMap[4][2],"layout/layout4_3.txt");
            load_layout(&map->tabMap[4][3],"layout/layout4_4.txt");
        }else{
            load_layout(&map->tabMap[5][3],"layout/layout2_5.txt"); //tout seul
            //zone 4
            choix=rand() % 2;
            if(choix == 1){
                //Paire [4][2]/[4][3]
                load_layout(&map->tabMap[5][2],"layout/layout4_5.txt"); //tout seul
                load_layout(&map->tabMap[4][3],"layout/layout4_4.txt");
                load_layout(&map->tabMap[4][2],"layout/layout4_3.txt");
            }else{
                if(map->tabMap[4][2].nZone==2){
                    load_layout(&map->tabMap[4][3],"layout/layout4_6.txt"); //tout seul
                    load_layout(&map->tabMap[4][2],"layout/layout2_6.txt");
                    load_layout(&map->tabMap[5][2],"layout/layout4_6.txt");
                }
                else{
                    //Paire [4][2]/[5][2]
                    load_layout(&map->tabMap[4][3],"layout/layout4_6.txt"); //tout seul
                    load_layout(&map->tabMap[4][2],"layout/layout4_8.txt");
                    load_layout(&map->tabMap[5][2],"layout/layout4_7.txt");
                }
            }
        }
    }else{
        if(map->tabMap[4][2].nZone == 2){
            load_layout(&map->tabMap[4][2],"layout/layout2_3.txt");
            load_layout(&map->tabMap[4][3],"layout/layout2_4.txt");
            //zone4
            load_layout(&map->tabMap[5][2],"layout/layout4_3.txt");
            load_layout(&map->tabMap[5][3],"layout/layout4_4.txt");
        }else{
            load_layout(&map->tabMap[4][3],"layout/layout2_5.txt");
            //zone4
            choix=rand() % 2;
            if(choix == 1){
                //Paire [5][2]/[4][2]
                load_layout(&map->tabMap[5][3],"layout/layout4_6.txt"); //tout seul
                load_layout(&map->tabMap[5][2],"layout/layout4_7.txt");
                load_layout(&map->tabMap[4][2],"layout/layout4_8.txt");
            }else{
                //Paire [5][3]/[5][2]
                load_layout(&map->tabMap[4][2],"layout/layout4_5.txt"); //tout seul
                load_layout(&map->tabMap[5][3],"layout/layout4_4.txt");
                load_layout(&map->tabMap[5][2],"layout/layout4_3.txt");
            }
        }
    }
    //Choix layout entrée boss
    choix=rand()%2;
    if(choix==0){
        load_layout(&map->tabMap[4][0],"layout/layout4_2.txt");
        load_layout(&map->tabMap[5][1],"layout/layout4_10.txt");
    }
    else{
        load_layout(&map->tabMap[5][1],"layout/layout4_9.txt");
        load_layout(&map->tabMap[4][0],"layout/layout4_10.txt");
    }
    //Layout foret bloc
    load_layout(&map->tabMap[3][0],"layout/layout4_10.txt");
    load_layout(&map->tabMap[4][1],"layout/layout4_10.txt");

    if(map->tabMap[3][2].nZone==1){
        load_layout(&map->tabMap[3][1],"layout/layout4_11.txt");
    }
    else{
        load_layout(&map->tabMap[3][1],"layout/layout4_10.txt");
    }

    //Layout transition foret grotte
    if(map->tabMap[2][2].nZone==1){
        if(map->tabMap[2][0].nZone==4){
            load_layout(&map->tabMap[2][1],"layout/layout4_11.txt"); //Transition zone spawn
            load_layout(&map->tabMap[2][0],"layout/layout4_12.txt"); //Transition zone grotte
            load_layout(&map->tabMap[1][0],"layout/layout5_4.txt"); //Transition zone foret
            load_layout(&map->tabMap[1][1],"layout/layout5_3.txt"); //Carrefour
        }
        else{
            load_layout(&map->tabMap[2][1],"layout/layout4_13.txt"); //Transition zone grotte et zone spawn
            load_layout(&map->tabMap[2][0],"layout/layout5_6.txt"); //Cul de sac
            load_layout(&map->tabMap[1][1],"layout/layout5_4.txt"); //Transition zone foret
            load_layout(&map->tabMap[1][0],"layout/layout5_3.txt"); //Carrefour

        }
        
    }
    else if(map->tabMap[2][1].nZone==4){
        load_layout(&map->tabMap[2][1],"layout/layout4_12.txt"); //Transition zone grotte
        load_layout(&map->tabMap[2][2],"layout/layout5_4.txt"); //Cul de sac
        load_layout(&map->tabMap[1][1],"layout/layout5_4.txt"); //Transition zone foret
        load_layout(&map->tabMap[1][0],"layout/layout5_3.txt"); //Carrefour
        if(map->tabMap[2][0].nZone==4){
            load_layout(&map->tabMap[2][0],"layout/layout4_10.txt");
        }
        else{
            load_layout(&map->tabMap[2][0],"layout/layout5_4.txt");
        }
    }
    else{
        load_layout(&map->tabMap[2][0],"layout/layout4_12.txt"); //Transition zone grotte
        load_layout(&map->tabMap[1][0],"layout/layout5_4.txt"); //Transition zone foret
        load_layout(&map->tabMap[1][1],"layout/layout5_3.txt"); //Carrefour
        if(map->tabMap[2][2].nZone==5){
            load_layout(&map->tabMap[2][2],"layout/layout5_5.txt"); //Semi cul de sac
            load_layout(&map->tabMap[2][1],"layout/layout5_5.txt"); //Semi cul de sac
        }
        else{
            load_layout(&map->tabMap[2][1],"layout/layout5_6.txt"); //Cul de sac
        }
            
    }

    //Choix layout entrée sous-marine
    choix=rand()%2;
    if(choix==0){
        //Entrée de la zone sous-marine en [3][5]
        load_layout(&map->tabMap[3][5],"layout/layout2_11.txt"); //Transition sous marine bordure bas droite
        if(map->tabMap[3][3].nZone==1){
            load_layout(&map->tabMap[3][4],"layout/layout2_13.txt"); //Transition spawn zone plage bordure bas
        }
        else{
            load_layout(&map->tabMap[3][4],"layout/layout2_9.txt"); //Bordure eau bas
        }
        load_layout(&map->tabMap[4][5],"layout/layout2_19.txt");  //Transition plage
        load_layout(&map->tabMap[4][4],"layout/layout2_5.txt"); //Carrefour
        /*if(map->tabMap[3][2].nZone==1){
            load_layout(&map->tabMap[3][3],"layout/layout2_13.txt"); //Transition zone 1
        }*/
    }
    else{
        //Entrée de la zone sous-marine en [3][4]
        if(map->tabMap[3][3].nZone==1){
            load_layout(&map->tabMap[3][4],"layout/layout2_14.txt"); //Transition sous marine et transition spawn zone plage
        }
        else{
            load_layout(&map->tabMap[3][4],"layout/layout2_12.txt"); //Transition sous marine
        }
        load_layout(&map->tabMap[3][5],"layout/layout2_10.txt"); //Bordure eau bas droite

        //Zone sous-marine transition
        load_layout(&map->tabMap[4][4],"layout/layout2_19.txt"); //Transition plage   -------> Vérifier bas et gauche pour les objets si gauche et gauche bas alors bloquer bas
        load_layout(&map->tabMap[4][5],"layout/layout2_6.txt"); //Cul de sac
        /*if(map->tabMap[3][2].nZone==1){
            load_layout(&map->tabMap[3][3],"layout/layout2_13.txt"); //Transition zone 1
        }*/
    }

    //Layout zone plage 
    load_layout(&map->tabMap[2][5],"layout/layout2_16.txt"); //Bordure eau à droite
    if(map->tabMap[2][3].nZone==1){
        load_layout(&map->tabMap[2][4],"layout/layout2_15.txt"); //Transition spawn zone plage
    }
    else{
        load_layout(&map->tabMap[2][4],"layout/layout2_17.txt"); //Full sable
    }

    //Gestion bloc spawn et le cas particulier où le manoir n'est pas dans le coin haut droit
    load_layout(&map->tabMap[0][0],"layout/layout5_7.txt");

    if(map->tabMap[3][2].nZone==1){
        load_layout(&map->tabMap[2][2],"layout/layout3_3.txt"); //Chemin vers le manoir transition haute et transition basse zone 1
        load_layout(&map->tabMap[1][2],"layout/layout3_4.txt"); //Chemin transition basse et entrée vers le manoir transition droite
        load_layout(&map->tabMap[1][3],"layout/layout3_5.txt"); //Manoir 
        load_layout(&map->tabMap[1][4],"layout/layout3_6.txt"); //Manoir cul sac
        load_layout(&map->tabMap[0][3],"layout/layout3_2.txt"); //Entrée du boss
        load_layout(&map->tabMap[0][4],"layout/layout3_1.txt"); //Boss

        load_layout(&map->tabMap[1][5],"layout/layout2_16.txt"); //Bordure eau à droite
        load_layout(&map->tabMap[0][5],"layout/layout2_18.txt"); //Bordure eau haut droite

        load_layout(&map->tabMap[3][2],"layout/layout1_1.txt"); //Spawn avec transition dans 3 zones, fermé en bas
        load_layout(&map->tabMap[3][3],"layout/layout2_13.txt"); //Transition zone 1 de la plage
        load_layout(&map->tabMap[2][3],"layout/layout2_17.txt"); //Full sable

    }

    else{

        //Layout manoir
        load_layout(&map->tabMap[1][4],"layout/layout3_5.txt"); //Manoir 
        load_layout(&map->tabMap[1][5],"layout/layout3_6.txt"); //Manoir cul sac
        load_layout(&map->tabMap[0][4],"layout/layout3_2.txt"); //Entrée du boss
        load_layout(&map->tabMap[0][5],"layout/layout3_1.txt"); //Boss

        //Gestion layout zone chemin vers le manoir et bloc spawn pour un spawn en [2][2]
        if(map->tabMap[2][2].nZone==1){
            load_layout(&map->tabMap[1][2],"layout/layout3_7.txt"); //Chemin vers le manoir transition droite et transition basse zone 1
            load_layout(&map->tabMap[1][3],"layout/layout3_8.txt"); //Chemin transition gauche et entrée vers le manoir transition droite

            load_layout(&map->tabMap[2][2],"layout/layout1_1.txt"); //Spawn avec transition dans 3 zones, fermé en bas
            load_layout(&map->tabMap[2][3],"layout/layout2_15.txt"); //Transition zone 1 de la plage
            if(map->tabMap[3][2].nZone==2){
                load_layout(&map->tabMap[3][2],"layout/layout2_20.txt"); //Cul de sac plage
                load_layout(&map->tabMap[3][3],"layout/layout2_17.txt"); //Full plage
            }
            else{
                load_layout(&map->tabMap[3][2],"layout/layout4_6.txt"); //Cul de sac foret
                load_layout(&map->tabMap[3][3],"layout/layout2_20.txt"); //Cul de sac plage
            }
        }
        //Gestion layout zone chemin vers le manoir et bloc spawn pour un spawn en [2][3]
        else if(map->tabMap[2][3].nZone==1){
            load_layout(&map->tabMap[1][3],"layout/layout3_3.txt"); //Chemin vers le manoir transition haute et transition basse zone 1
            load_layout(&map->tabMap[0][3],"layout/layout3_4.txt"); //Chemin transition basse et entrée vers le manoir transition droite

            load_layout(&map->tabMap[2][3],"layout/layout1_1.txt"); //Spawn avec transition dans 3 zones, fermé en bas
            load_layout(&map->tabMap[2][2],"layout/layout4_11.txt"); //Transition zone 1 de la foret
            load_layout(&map->tabMap[3][2],"layout/layout4_10.txt"); //Foret quelconque
            if(map->tabMap[3][3].nZone==2){
                load_layout(&map->tabMap[3][3],"layout/layout2_20.txt"); //Cul de sac plage
            }
            else{
                load_layout(&map->tabMap[3][3],"layout/layout4_6.txt"); //Cul de sac foret
            }
        }
        //Gestion layout zone chemin vers le manoir et bloc spawn pour un spawn en [3][3]
        else if(map->tabMap[3][3].nZone==1){
            load_layout(&map->tabMap[2][3],"layout/layout3_3.txt"); //Chemin vers le manoir transition haute et transition basse zone 1
            load_layout(&map->tabMap[1][3],"layout/layout3_4.txt"); //Chemin transition gauche et entrée vers le manoir transition droite

            load_layout(&map->tabMap[3][3],"layout/layout1_1.txt"); //Spawn avec transition dans 3 zones, fermé en bas
            load_layout(&map->tabMap[3][2],"layout/layout4_11.txt"); //Transition zone 1 de la foret
            load_layout(&map->tabMap[2][2],"layout/layout5_6.txt"); //Cul de sac
        }
    }

    //Gestion transition manoir grotte en fonction du point de spawn
    if(map->tabMap[0][3].nZone==5){
        load_layout(&map->tabMap[0][3],"layout/layout5_1.txt"); //Zone boss
        load_layout(&map->tabMap[0][2],"layout/layout5_2.txt"); //Zone entrée boss
        load_layout(&map->tabMap[0][1],"layout/layout5_3.txt"); //Carrefour
    }
    else{
        load_layout(&map->tabMap[0][2],"layout/layout5_1.txt"); //Zone boss
        load_layout(&map->tabMap[0][1],"layout/layout5_2.txt"); //Zone entrée boss
    }
    if(map->tabMap[1][2].nZone==5){
        if(map->tabMap[2][2].nZone==5){
            if(map->tabMap[0][3].nZone==5)
                load_layout(&map->tabMap[1][2],"layout/layout5_3.txt"); //Carrefour
            else{
                load_layout(&map->tabMap[1][2],"layout/layout5_8.txt"); //Coin haut droit
            }
        }else{
            load_layout(&map->tabMap[1][2],"layout/layout5_6.txt"); //Cul de sac
        }
    } 
    return (sauvegarde_map_layout(map));
}

/**
*
*\fn int sauvegarde_map_brouillard(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui sauvegarde le brouillard de la map
*/
int sauvegarde_map_brouillard(map_t * map){
    FILE * file;
    int x,y;

    file=fopen("save/mapbrouillard.txt","w");
    if(file){
        for(x=0;x<ROWS;x++){
            for(y=0;y<COLUMNS;y++){
                fprintf(file,"%d",map->tabMap[x][y].etat_brouillard);
            }
            fprintf(file,"\n");
        }
        fclose(file);
        return 0;
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    return 0;
}

/**
*
*\fn int sauvegarde_map_layout(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui sauvegarde le numéro de layout de chaque carte de la map dans un fichier
*/
int sauvegarde_map_layout(map_t * map){
    //Sauvegarde de la map des layouts dans un fichier
    FILE * file;
    int x,y;

    file=fopen("save/maplayout.txt","w");
    if(file){
        for(x=0;x<ROWS;x++){
            for(y=0;y<COLUMNS;y++){
                fprintf(file,"%d",map->tabMap[x][y].nrlayout);
                if(y!=COLUMNS-1){
                    fprintf(file," ");
                }
                
            }
            fprintf(file,"\n");
        }
        fclose(file);
        return 0;
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    return 0;
}

/**
*
*\fn int load_brouillard(map_t *map)
\*\param map Map de jeu
*\brief Fonction qui charge le brouillard de la map
*/
int load_brouillard(map_t *map){
    FILE * file;
    int x,y;

    file=fopen("save/mapbrouillard.txt","r");
    if(file){
        for (x = 0; x < ROWS; ++x) {
            for (y = 0; y < COLUMNS; ++y) {
                char caractere;
                fscanf(file, "%c", &caractere);
                map->tabMap[x][y].etat_brouillard = caractere - '0';
            }
            fscanf(file, "\n");
        }
        fclose(file);
        return 0;
    }
    else{
        return 1;
    }
    return 0;
}

/**
*
*\fn int remplir_map(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui soit charge à partir d'un fichier, s'il existe, les numéros de zone dans chaque carte de la map soit appelle la fonction creer_map()
*/
int remplir_map(map_t *map){
    FILE * file;

    int x=0;
    int y=0;
    int i,j;
    char numZone;

    file=fopen("save/map.txt","r");
    if(file){
        fscanf(file,"%c",&numZone);

        while(!feof(file)){
            if(numZone=='\n'){
                x++;
                y=0;
            }
            else if(numZone>='1'&&numZone<='5'){
                map->tabMap[x][y].nZone=numZone - '0';
                //test
                if(map->tabMap[x][y].nZone==1 || map->tabMap[x][y].nZone==2 || map->tabMap[x][y].nZone==3){
                    for(i=0;i<LONG;i++){
                        for(j=0;j<LARG;j++){
                            map->tabMap[x][y].grille.tabGrille[i][j].ntexture = 0;//plus tard info dans un fichier
                        }
                    }
                }

                y++;
            }
            fscanf(file,"%c",&numZone);
        }
        fclose(file);
        return 1;
    }
    else{
        creer_map(map);
        return 0;
    }
}

/**
*
*\fn int load_layout_texture(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui charge les données d'un fichier pour les layout de texture
*/
int load_layout_texture(map_t * map) {
    FILE *file;
    file = fopen("save/maplayout.txt", "r");
    int i = 0, j = 0,nr;
    char num[5];
    char res[50];
    if (file) {
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLUMNS; j++) {
                if (fscanf(file, "%d",&nr) != 1) {
                    printf("Erreur à la ligne %d, colonne %d.\n", i, j);
                    fclose(file);
                    return 1;
                }
                strcpy(res,"layout/layout");
                sprintf(num,"%d",map->tabMap[i][j].nZone);
                strcat(res,num);
                strcat(res,"_");
                sprintf(num,"%d",nr);
                strcat(res,num);
                strcat(res,".txt");
                load_layout(&map->tabMap[i][j],res);
            }
            fscanf(file,"\n");
        }
    }else {
        return 0;
    }

    fclose(file);
    return 1;
}

/**
*
*\fn int load_layout_texture(map_t * map)
\*\param map Map de jeu
*\brief Fonction qui charge les données d'un fichier pour les layout d'objets
*/
int load_layout_obj(map_t * map) {
    int i = 0, j = 0,nr;
    char num[5];
    char res[50];
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            strcpy(res,"layoutobj/layout");
            sprintf(num,"%d",map->tabMap[i][j].nZone);
            strcat(res,num);
            strcat(res,"_");
            nr = map->tabMap[i][j].nrlayout;
            sprintf(num,"%d",nr);
            strcat(res,num);
            //cas particulier
            if(map->tabMap[5][3].nZone==2 && nr==2){
                strcat(res,"_1");
            }
            else if(map->tabMap[i][j].nZone==3 && (nr==5 || nr==2) && (map->tabMap[i][j-1].nrlayout ==6 || map->tabMap[i][j-1].nrlayout == 8) ){
                strcat(res,"_1");
            }
            strcat(res,".txt");
            load_obj(&map->tabMap[i][j],res);
        }
    }

    return 1;
}

/**
*
*\fn int load_layout(carte_t *c, char *namefile)
\*\param c Carte dans laquelle on a chargé le layout
\*\param namefile nom du fichier à charger
*\brief Fonction qui charge un layout à partir d'un fichier dans une carte
*/

int load_layout(carte_t *c, char *namefile) {
    FILE *file;
    file = fopen(namefile, "r");
    int i = 0, j = 0;
    int len = strlen(namefile);
    char digit[2];

    if(namefile[len-6]=='_'){
        c->nrlayout = atoi(&namefile[len-5]);
    }
    else{
        digit[0]=namefile[len-6];
        digit[1]=namefile[len-5];
        c->nrlayout = atoi(digit);
    }

    if (file) {
        for (i = 0; i < LARG; i++) {
            for (j = 0; j < LONG; j++) {
                if (fscanf(file, "%d", &c->grille.tabGrille[j][i].ntexture) != 1) {
                    printf("Erreur à la ligne %d, colonne %d.\n", i, j);
                    fclose(file);
                    return 1;
                }
            }
            fscanf(file,"\n");
        }
    } else {
        printf("Fichier inexistant\n");
        return 1;
    }

    fclose(file);
    return 0;
}

/**
*
*\fn float min(float a, float b)
\*\param a Premier float
\*\param b Deuxième float
*\brief Fonction qui retourne le plus petit float entre a et b
*/
float min(float a, float b) {
    return (a < b) ? a : b;
}

/**
*
*\fn int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map,carte_t * cartec)
*\param event Pile des évènements SDL
*\param map Map de jeu
*\param renderer Rendu de la fenetre SDL
*\param we Largeur de l'écran
*\param he Hauteur de l'écran
*\param etat_map Indique si la carte a été explorée ou non
*\param cartec Carte où le joueur se situe au moment d'afficher la map
*\brief Fonction qui affiche en mode réduit l'entièreté de la map
*/
int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map,carte_t * cartec){
    int i, j;

    SDL_Rect Rectangle;
    SDL_Rect Rectanglep;

    // Marges
    float margeX = (*we) * 0.1;
    float margeY = (*he) * 0.1;

    // Largeur et hauteur utilisables
    float largeurUtilisable = (*we) - 2 * margeX;
    float hauteurUtilisable = (*he) - 2 * margeY;

    // Taille de chaque carré
    float taille_carre = min(largeurUtilisable, hauteurUtilisable) / 6;

    //Taille du petit carré de l'emplacement actuel
    float taille_pcarre = taille_carre/3;

    // Coordonnées du premier carré
    float firstX = margeX + ((*we) - 2 * margeX - taille_carre * 6) / 2;
    float firstY = margeY + ((*he) - 2 * margeY - taille_carre * 6) / 2;
    Rectangle.x = (int)firstX;
    Rectangle.y = (int)firstY;
    Rectangle.w = (int)taille_carre;
    Rectangle.h = (int)taille_carre;

    //Initialisation du petit carré de l'emplacement actuel
    Rectanglep.x = (int)firstX + (taille_pcarre);
    Rectanglep.y = (int)firstY + (taille_pcarre);
    Rectanglep.w=(int)taille_pcarre;
    Rectanglep.h=(int)taille_pcarre;

    if((*etat_map) == 1){

        SDL_Surface* surface = SDL_CreateRGBSurface(0, *we, *he, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        // Copie les pixels du rendu actuel dans la surface
        SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
        // Créer une texture à partir de la surface
        SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_Rect tecran = {0,0,*we,*he};

        while((*etat_map) < 2){
            while (SDL_PollEvent(&event) != 0) {
                if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_x)){
                    (*etat_map)=2;
                }
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
            SDL_SetRenderDrawColor(renderer,0,0,0,100);
            SDL_RenderFillRect(renderer, &tecran);
            for(i=0;i<ROWS;i++){
                Rectangle.y = (int)(firstY + i * taille_carre);
                for(j=0;j<COLUMNS;j++){
                    if(map.tabMap[i][j].etat_brouillard != 1){
                        switch(map.tabMap[i][j].nZone){
                            case 1: SDL_SetRenderDrawColor(renderer, 206,206,206,255);break;
                            case 2: SDL_SetRenderDrawColor(renderer, 86,115,154,255);break;
                            case 3: SDL_SetRenderDrawColor(renderer, 153,81,43,255);break;
                            case 4: SDL_SetRenderDrawColor(renderer, 104,157,113,255);break;
                            case 5: SDL_SetRenderDrawColor(renderer, 115,8,0,255);break;
                            default: break;
                        }
                    }else{
                       SDL_SetRenderDrawColor(renderer, 0,0,0,255); 
                    }
                    Rectangle.x = (int)(firstX + j * taille_carre);
                    SDL_RenderFillRect(renderer, &Rectangle);
                    if(cartec->ycarte == j && cartec->xcarte == i){
                        SDL_SetRenderDrawColor(renderer, 255,255,0,255);
                        Rectanglep.x = Rectangle.x+taille_pcarre;
                        Rectanglep.y = Rectangle.y+taille_pcarre;;
                        SDL_RenderFillRect(renderer, &Rectanglep); 
                    }
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }
        (*etat_map) = 0;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(targetTexture);
    }
    return 0;
}

/**
*
*\fn int chargement_Zone(map_t * map,SDL_Renderer *renderer,int nZone,Mix_Music* gMusic)
*\param map Map de jeu
*\param renderer Rendu de la fenetre SDL
*\param nZone Zone courante du joueur
*\param gMusic Pointeur sur la musique courante
*\brief Fonction qui charge les textures et la musique d'une zone quand le joueur y rentre
*/
int chargement_Zone(map_t * map,SDL_Renderer *renderer,int nZone,Mix_Music* gMusic){
    int m = nZone;
        switch (nZone)
        {
        case 1:
            creation_tab_texture(map,renderer,1,0);
            map->nbN = 7;
            map->nvZone=1;
            break;
        case 2:
            creation_tab_texture(map,renderer,2,0);
            map->nbN = 63;
            map->nvZone=2;
            if(map->Zone2 == 0)map->Zone2 = 1;
            break;
        case 3:
            creation_tab_texture(map,renderer,3,0);
            map->nbN = 67;
            map->nvZone=4;
            if(map->Zone3 == 0)map->Zone3 = 1;
            break;
        case 4:
            creation_tab_texture(map,renderer,4,0);
            map->nbN = 41;
            map->nvZone=1;
            if(map->Zone4 == 0)map->Zone4 = 1;
            break;
        case 5:
            creation_tab_texture(map,renderer,5,0);
            map->nbN = 40;
            map->nvZone=6;
            if(map->Zone5 == 0)map->Zone5 = 1;
            break;
        
        default:
            map->tabTexture = NULL;
            break;
        }
        if(!map->Nightmare)newMusic(m,gMusic);
    return 0;
}

/**
*
*\fn int zone_fini(map_t map)
*\param map Map de jeu
*\return Booléen pour savoir si la zone est finie
*\brief Fonction qui vérifie si le joueur peut sortir d'une zone s'il l'a fini ou non
*/
int zone_fini(map_t map){
    switch(map.zoneChargee){
        case 2 : if(map.Zone2 != 1 || map.plongee == 0)return 1;else return 0;break;
        case 3 : if(map.Zone3 != 1 || map.cle == 0)return 1;else return 0;break;
        case 4 : if(map.Zone4 != 1)return 1;else return 0;break;
        case 5 : if(map.Zone5 != 1)return 1;else return 0;break;
        default : return 1;
    }
}

/**
*
*\fn void lumiere(SDL_Renderer *renderer,carte_t *cartec,case_t *c)
*\param renderer Rendu de la fenêtre SDL
*\param cartec Carte courante du joueur
*\param c Case qui sera la source de lumière
*\brief Fonction qui applique un filtre sur l'écran pour donner un effet d'obscurcissement
*/
void lumiere(SDL_Renderer *renderer,carte_t *cartec,case_t *c){
    int i,j;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            SDL_SetRenderDrawColor(renderer, 0,0,0,255); 
            if(cartec->grille.tabGrille[i][j].x == c->x && cartec->grille.tabGrille[i][j].y == c->y){
               SDL_SetRenderDrawColor(renderer, 0,0,0,0);  
            }
            else if((cartec->grille.tabGrille[i][j].x == c->x+1 || cartec->grille.tabGrille[i][j].x == c->x-1 || cartec->grille.tabGrille[i][j].x == c->x) && (cartec->grille.tabGrille[i][j].y == c->y+1 || cartec->grille.tabGrille[i][j].y == c->y-1 || cartec->grille.tabGrille[i][j].y == c->y)){
                SDL_SetRenderDrawColor(renderer, 0,0,0,100); 
            }else if((cartec->grille.tabGrille[i][j].x == c->x+2 || cartec->grille.tabGrille[i][j].x == c->x-2 || cartec->grille.tabGrille[i][j].y == c->y+2 || cartec->grille.tabGrille[i][j].y == c->y-2) && ((cartec->grille.tabGrille[i][j].y > c->y-2 && cartec->grille.tabGrille[i][j].y < c->y+2) || (cartec->grille.tabGrille[i][j].x > c->x-2 && cartec->grille.tabGrille[i][j].x < c->x+2))){
                SDL_SetRenderDrawColor(renderer, 0,0,0,170); 
            }else if((cartec->grille.tabGrille[i][j].x == c->x+3 || cartec->grille.tabGrille[i][j].x == c->x-3 || cartec->grille.tabGrille[i][j].y == c->y+3 || cartec->grille.tabGrille[i][j].y == c->y-3) && (cartec->grille.tabGrille[i][j].y == c->y || cartec->grille.tabGrille[i][j].x == c->x)){
                SDL_SetRenderDrawColor(renderer, 0,0,0,220);
            }
            SDL_RenderFillRect(renderer, &(cartec->grille.tabGrille[i][j].Rectangle));
        }
    }
}

/**
*
*\fn int nb_texture_chargement(map_t *map, char* namefile)
*\param map Map du jeu
*\param namefile Nom du fichier des textures
*\brief Fonction qui affecte le nombre de texture d'une zone à la map
*/
int nb_texture_chargement(map_t *map, char* namefile){
    FILE * file;
    int nb_zone[5] = {0,0,0,0,0};
    char line[80];
    int i=-1;

    file=fopen(namefile,"r");

    if(file){
        while (fgets(line, 80, file)){
            if(line[0]>='0'&&line[0]<='5') {
                i=atoi(line)-1;
                fgets(line, 80, file);
                nb_zone[i]=atoi(line);
            }     
        }

        for(i=0;i<5;i++){
            map->nbTexture[i]=nb_zone[i];
        }
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    fclose(file);
    return 0;
}

/**
*
*\fn int detruire_tab_path(map_t *map)
*\param map Map du jeu
*\brief Fonction qui détruit le tableau de chemin des textures
*/
int detruire_tab_path(map_t *map){
    int i,k;
    if(map->tabPath!=NULL){
        for (i=0;i<NB_ZONE;i++){
            for(k=0;k<map->nbTexture[i];k++){
                free(map->tabPath[i][k]);
            }
            free(map->tabPath[i]);
        }
        free(map->tabPath);
        map->tabPath=NULL;
    }
    return 0;
}

/**
*
*\fn int creation_tab_path(map_t *map,char * namefile)
*\param map Map du jeu
*\param namefile Nom du fichier de texture
*\brief Fonction qui crée le tableau de chemin des textures
*/
int creation_tab_path(map_t *map,char * namefile){
    FILE * file;
    int i = 0;
    int j,k=-1;
    char line[80];

    map->tabPath = malloc(sizeof(char ** )*NB_ZONE);
    for (i=0;i<NB_ZONE;i++){
        map->tabPath[i] = malloc(sizeof(char *)*map->nbTexture[i]);
    }
    file=fopen(namefile,"r");
    i=-1;
    if(file){
        while (fgets(line, 80, file)){
            if(line[0]>='0'&&line[0]<='5') {
                i=atoi(line)-1;
                k=-1;
                fgets(line, 80, file);
            }
            else{
                if(i >= 0 && i < NB_ZONE && k < map->nbTexture[i] - 1){
                    k++;
                    for(j=0; line[j]!='\n' && j < 79; j++){}
                    line[j]='\0';
                    map->tabPath[i][k]=malloc(sizeof(char)*strlen(line)+1);
                    strcpy(map->tabPath[i][k],line);
                }
            }
        }
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    fclose(file);
    return 0;


}

/**
*
*\fn int creation_tab_texture(map_t *map, SDL_Renderer *renderer, int nbZone, int eop)
*\param map Map du jeu
*\param renderer Rendu de la fenêtre SDL
*\param nbZone Zone courante du joueur
*\param eop Variable pour savoir si on est à la fin du programme ou non
*\brief Fonction qui crée le tableau de textures SDL
*/
int creation_tab_texture(map_t *map, SDL_Renderer *renderer, int nbZone, int eop) {
    int i = 0;
    SDL_Surface *surf;

    if(nbZone < 1 || nbZone > NB_ZONE) {
        printf("Erreur : nbZone hors limites\n");
        return 1;
    }

    // Libération des textures précédentes si elles existent
    if(map->tabTexture != NULL) {
        int nbTexturesToDestroy = eop == 1 ? NB_ZONE : map->nbTexture[map->zoneChargee-1];
        for(i = 0; i < nbTexturesToDestroy; i++) {
            if(map->tabTexture[i] != NULL) {
                SDL_DestroyTexture(map->tabTexture[i]);
                map->tabTexture[i] = NULL;
            }
        }
        free(map->tabTexture);
        map->tabTexture = NULL;
    }

    if(eop != 1) {
        map->zoneChargee = nbZone;
        map->tabTexture = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * map->nbTexture[nbZone-1]);

        if(map->tabTexture == NULL) {
            printf("Erreur d'allocation mémoire pour map->tabTexture\n");
            return 1;
        }

        for(i = 0; i < map->nbTexture[map->zoneChargee-1]; i++) {
            surf = IMG_Load(map->tabPath[map->zoneChargee-1][i]);
            if (surf == NULL) {
                fprintf(stderr, "Erreur de chargement de l'image : %s\n", SDL_GetError());
            }
            map->tabTexture[i] = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
        }
    }
    return 0;
}