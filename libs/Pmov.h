#ifndef __PMOV_H__
#define __PMOV_H__

//#include "../libs/commun.h"



/**
*
*\struct personnage_equipe
*\param nom prenom du personnage
*\param pv les pv du personnage
*\param nomATQ1 nom de l'attaque de base du personnage
*\param nomATQ2 nom de l'attaque particuliere de personnage
*\param nomATQspe nom de l'attaque special du personnage dans le cauchemar
*\brief structure de personnage de l'equipe
*/

/*
struct personnage_equipe{
    //coordonées du personnage et taille dans un rect
    char * nom;
    int pv;
    char * nomATQ1;
    char * nomATQspe;
    int vitesse;
    combattant_t * combattant;
};
*/
/**
*
*\struct personnage
*\param r taille du personnage
*\param d direction orienté{N,E,S,O}{0,1,2,3}
*\param e etat du personnage
*\param nom prenom du personnage
*\brief structure de personnage
*/


struct personnage{
    //coordonées du personnage et taille dans un rect
    carte_t * carte;
    case_t * c;
    SDL_Rect r;//{x,y,w,h}
    int d; //direction orienté{N,E,S,W}{0,1,2,3}
    int e; //etat du personnage
    char * nom;
    combattant_t *equipe[4];

};

void pinput(p_mv * pmv,SDL_Event event,carte_t ** carte,map_t *map,SDL_Renderer * renderer,int * transi);

int affp(p_mv * pmv,SDL_Renderer *renderer);

void col_p(SDL_Rect * obj_r,p_mv * pp);

p_mv initp(carte_t * carte,case_t * c);

//p_eq *initp_eq(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse,int camp);

void desctruction_p_eq(p_mv * p);

void transition(SDL_Renderer * renderer,int * transi,int we,int he) ;

#endif