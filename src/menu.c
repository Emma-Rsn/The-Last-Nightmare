//
//menu.c
//Created by Moreau Enzo
//

/**
*\file menu.c
*\brief programme pour afficher le menu
*\author Moreau Enzo Pasquier Lina
*\date  Janvier 2024
*\version 
*
*/


#include "../libs/commun.h"


/**
*\fn int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run)
*\param we Largeur de l'ecran
*\param he Longueur de l'ecran
*\param event permet de savoir si il y a un evenement
*\param renderer rendu de la fenetre
*\param run pointeur pour continuer le programme
*\brief fonction qui affiche et gere les texte cliquable du menu 
*/

//fonction qui affiche et gere les texte cliquable du menu 
int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run){

        SDL_RenderClear(renderer);


        //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColor = {255, 255, 255};
        
        SDL_Surface* textSurfaceQ = TTF_RenderText_Solid(font,"Quitter", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);
        

        SDL_Surface* textSurfaceC = TTF_RenderText_Solid(font,"Continuer", textColor);
        if (!textSurfaceC) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            return -1;
        }

        SDL_Texture* textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);
        

        SDL_Surface* textSurfaceT = TTF_RenderText_Solid(font,"The Last Nightmare", textColor);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            return -1;
        }
        
        SDL_Texture* textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);
        

        TTF_CloseFont(font);
        font=NULL;


        //creation rectangle pour les textes
        SDL_Rect  r_text_C= {((*we)/2)-((textSurfaceC->w)/2),((*he)/2),textSurfaceC->w,textSurfaceC->h};
        SDL_Rect  r_text_T= {((*we)/2)-((textSurfaceT->w)/2),10,textSurfaceT->w,textSurfaceT->h};
        SDL_Rect  r_text_Q= {((*we)/2)-((textSurfaceQ->w)/2),((*he)/2)+200,textSurfaceQ->w,textSurfaceQ->h};
        
        SDL_FreeSurface(textSurfaceT);
        SDL_FreeSurface(textSurfaceC);
        SDL_FreeSurface(textSurfaceQ);


        if(SDL_QueryTexture(textTextureQ,NULL,NULL,&r_text_Q.w,&r_text_Q.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

        if(SDL_QueryTexture(textTextureC,NULL,NULL,&r_text_C.w,&r_text_C.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }

         if(SDL_QueryTexture(textTextureT,NULL,NULL,&r_text_T.w,&r_text_T.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }

        
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE){
            int etat=1;
            while(etat){

                while (SDL_PollEvent(&event) != 0) {

                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        //pour continuer le jeu
                        if((r_text_C.x<=event.button.x) && ((r_text_C.x+r_text_C.w)>=event.button.x) && ((r_text_C.y+r_text_C.h)>=event.button.y) && (r_text_C.y<=event.button.y)){
                            etat=0;
                        }
                        //pour quitter le jeu
                        else if((r_text_Q.x<=event.button.x) && ((r_text_Q.x+r_text_Q.w)>=event.button.x) && ((r_text_Q.y+r_text_Q.h)>=event.button.y) && (r_text_Q.y<=event.button.y)){
                            etat=0;
                            *run=0;
                        }  
                                            
                    }           
                }
        
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            
            SDL_RenderClear(renderer);

            
            SDL_RenderCopy(renderer, textTextureQ, NULL, &r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, &r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, &r_text_T);


            SDL_RenderPresent(renderer);
            SDL_Delay(100);
      
            }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureC);
        SDL_DestroyTexture(textTextureT);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        
        }



    return 0;
}

/*int console_command(SDL_Event event,char * command){
    if(command == NULL){
        command = malloc(80);
    }
    if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_j)){
        scanf("%s",command);
    }
    return 0;
}

int console_aff(SDL_Renderer * renderer,int we,int he,char * command){
    TTF_Font  * police = TTF_OpenFont("fonts/alagard.ttf", 20); 
    SDL_Color blanc = {255, 255, 255};
    if (police == NULL){
        TTF_CloseFont(police);
        TTF_Quit();
        fprintf(stderr,"probleme a l'ouverture de la police\n");
        return -1;
    }
    SDL_Rect r = {0,we-32,he,32};
    SDL_SetRenderDrawColor(renderer, 0,0,0,120);
    SDL_RenderFillRect(renderer, &r);
    SDL_Surface * texte = TTF_RenderText_Solid(police, command, blanc);
    if (!texte){
        SDL_FreeSurface(texte);
        TTF_CloseFont(police);
        police = NULL;
        TTF_Quit();
        printf("probleme de texte\n");
        return -1;
    }
    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer,texte);
    SDL_Rect textRect = {r.x+5, r.y+5, texte->w, texte->h};
    if(!text_texture){
        printf("Impossible de creeer la texture\n");
        TTF_CloseFont(police);
        police = NULL;
        TTF_Quit();
        return -1;
    }
    SDL_RenderCopy(renderer, text_texture, NULL, &textRect);
    return 0;
}*/