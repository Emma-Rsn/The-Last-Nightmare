//
//save.c
//Created by Moreau Enzo
//

/**
*\file save.c
*\brief programme pour la sauvegarde 
*\author Moreau Enzo
*\date  09 Fevrier 2024
*\version 1.0
*
*/



#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

/**
*
*\fn int save_settings(void)
*\brief fonction de sauvegarde des parametres
*
*/

//fonction de sauvegarde des parametres
int save_settings(void){
    FILE* fichier = NULL;
    fichier = fopen("save/settings.txt","r+");
    if(fichier == NULL){
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

int load_settings(int * lEcran,int * LEcran){
    FILE* fichier = NULL;
    fichier = fopen("save/settings.txt","r+");
    if(fichier == NULL){
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d %d",lEcran,LEcran);
    fclose(fichier);
    return 0;
}