//
// save.c
// Created by Moreau Enzo
//

/**
 *\file save.c
 *\brief programme pour la sauvegarde
 *\author Moreau Enzo
 *\date  09 Fevrier 2024
 *\version 1.0
 *
 */

#include "../libs/commun.h"

/**
 *
 *\fn int save_settings(void)
 *\brief fonction de sauvegarde des parametres
 *
 */

// fonction de sauvegarde des parametres
int save_settings(void)
{
    FILE *fichier = NULL;
    fichier = fopen("save/settings.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
    }
    fprintf(fichier, "1920 1080 \n");
    fclose(fichier);
    return 0;
}

/**
 *
 *\fn int load_settings(int * lEcran,int * LEcran)
 *\param lEcran Largeur de l'ecran
 *\param LEcran Longueur de l'ecran
 *\brief fonction de sauvegarde des parametres
 *
 */

int load_settings(int *wEcran, int *hEcran)
{
    FILE *fichier = NULL;
    fichier = fopen("save/settings.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d %d", wEcran, hEcran);
    fclose(fichier);
    return 0;
}

int save_pos(int xcarte, int ycarte, p_mv pmv, map_t map,int touche)
{
    int i,y;
    for(i = 0;pmv.equipe[i] && i < 4;i++);
    FILE *fichier = NULL;
    fichier = fopen("save/save.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
        return -1;
    }
    else if (fichier != NULL)
    {
        // int count = 0;
        int value;
        // long int pos;

        fscanf(fichier, "%d", &value);
        if (value == 0)
        {
            rewind(fichier);
            fprintf(fichier, "%d", 1);

            
        }if(value == 2){
            fprintf(fichier," %d %d %d\n",map.argent,map.nvEquipe,touche);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->equipe, map.listeArtefact[1]->equipe, map.listeArtefact[2]->equipe, map.listeArtefact[3]->equipe, map.listeArtefact[4]->equipe, map.listeArtefact[5]->equipe, map.listeArtefact[6]->equipe, map.listeArtefact[7]->equipe, map.listeArtefact[8]->equipe, map.listeArtefact[9]->equipe);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->possession, map.listeArtefact[1]->possession, map.listeArtefact[2]->possession, map.listeArtefact[3]->possession, map.listeArtefact[4]->possession, map.listeArtefact[5]->possession, map.listeArtefact[6]->possession, map.listeArtefact[7]->possession, map.listeArtefact[8]->possession, map.listeArtefact[9]->possession);
        }
        if(value != 3){
            fprintf(fichier, " %d %d %d %d %d %d %d\n", xcarte, ycarte, pmv.c->x, pmv.c->y, *(pmv.d), *(pmv.NightP), *pmv.equipe[0]->pv);
            fprintf(fichier, "%d %d %d %d %d %d %d\n", map.Zone2, map.Zone3, map.Zone4, map.Zone5, map.argent, map.nvEquipe,touche);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->equipe, map.listeArtefact[1]->equipe, map.listeArtefact[2]->equipe, map.listeArtefact[3]->equipe, map.listeArtefact[4]->equipe, map.listeArtefact[5]->equipe, map.listeArtefact[6]->equipe, map.listeArtefact[7]->equipe, map.listeArtefact[8]->equipe, map.listeArtefact[9]->equipe);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->possession, map.listeArtefact[1]->possession, map.listeArtefact[2]->possession, map.listeArtefact[3]->possession, map.listeArtefact[4]->possession, map.listeArtefact[5]->possession, map.listeArtefact[6]->possession, map.listeArtefact[7]->possession, map.listeArtefact[8]->possession, map.listeArtefact[9]->possession);
            fprintf(fichier,"%d",i-1);
            for(y = 1;y<i;y++){
                fprintf(fichier," %d %d",pmv.equipe[y]->type,*pmv.equipe[y]->pv);
            }
            fprintf(fichier,"\n");
        }
        
        fclose(fichier);
    }
    return 0;
}

int load_pos(int *xcarte, int *ycarte, int *xpos, int *ypos, map_t *map, int *pv, p_mv *pmv, int **tabparam,int * touche)
{
    int y;
    FILE *fichier = NULL;
    int last = 0;
    fichier = fopen("save/save.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d", &last);
    if (last == 1)
    {
        fscanf(fichier, " %d %d %d %d %d %d %d\n", xcarte, ycarte, xpos, ypos, pmv->d, pmv->NightP, pv);
        fscanf(fichier, "%d %d %d %d %d %d %d\n", tabparam[0], tabparam[1], tabparam[2], tabparam[3], tabparam[4], tabparam[5],touche);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[6], tabparam[7], tabparam[8], tabparam[9], tabparam[10], tabparam[11], tabparam[12], tabparam[13], tabparam[14], tabparam[15]);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[16], tabparam[17], tabparam[18], tabparam[19], tabparam[20], tabparam[21], tabparam[22], tabparam[23], tabparam[24], tabparam[25]);
        fscanf(fichier, "%d",tabparam[26]);
        for(y = 0;y<(*tabparam[26]);y++){//31 max
            fscanf(fichier," %d %d",tabparam[27+y],tabparam[28+y]);
        }
    }else if(last == 2){
        fscanf(fichier, "%d %d %d\n", tabparam[4], tabparam[5],touche);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[6], tabparam[7], tabparam[8], tabparam[9], tabparam[10], tabparam[11], tabparam[12], tabparam[13], tabparam[14], tabparam[15]);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[16], tabparam[17], tabparam[18], tabparam[19], tabparam[20], tabparam[21], tabparam[22], tabparam[23], tabparam[24], tabparam[25]);
        rewind(fichier);
        fprintf(fichier, "%d", 0);
    }
    fclose(fichier);
    return last;
}

//param = 1 pour garder la progression et = 0 pour effacer la progression
void nouvelle_partie(int param){
    FILE *fichier = fopen("save/save.txt", "r+");
    if(param){
        fprintf(fichier, "%d", 2);
    }else{
        fprintf(fichier, "%d", 3);
    }
    fclose(fichier);
}

void effacer_sauvg(){
    FILE *fichier = fopen("save/save.txt", "w");
    fprintf(fichier, "%d", 0);
    fclose(fichier);
}



/*
new load layout  test

save :
    leader
    ennemi mort
    variable d'exploration
    layout obj et load texture

obj :
    transition :
        sous marine
        manoir
        grotte

début combat 

boss boss

apres boss variable exploration avec dialogue



afficher niv Zone dans la carte !

chargement layout objet + cas particulier

lumiere dans grotte

*/