#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "TI.h"
#include <time.h>
#include <string.h>

#define FONT "./font/Arial.ttf"
#define FONT2 "./font/04b_25__.ttf"

/* **************************************************************** */

//Initialise structure
struct Env_t {
    int w,h;
    int state;
    int coef;
    int fontsize;
    int nb_joueurs;
    int size_w;
    int size_h;
    SDL_Texture* text;
    SDL_Texture* fleche_droite;
    SDL_Texture* fleche_gauche;
    SDL_Texture* color_bouton_new_game;
    SDL_Texture* name;
    SDL_Texture* bande_rose;
    SDL_Texture* bande_rose2;
    SDL_Texture* back;
    SDL_Texture* pointe;

    char name1[16];
    char name2[16];
    char name3[16];
    char name4[16];
    char name5[16];

    int pos1, pos2, pos3, pos4, pos5;
    int camp1, camp2, camp3, camp4, camp5; //0 attaque, 1 defense

    int curseur_fleche;
    int selection;
    game g;

    int bout, roi, dame, cavalier, valet, reste;

};

/* **************************************************************** */

//Load textures into env structure
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]) {
    Env * env = malloc(sizeof(struct Env_t));

    SDL_GetWindowSize(win, &env->w, &env->h);
    env->state=0;

    env->color_bouton_new_game = IMG_LoadTexture(ren, "./Textures/color_bouton_new_game.png");
    if (!env->color_bouton_new_game)
        ERROR("IMG_LoadTexture: color_bouton_new_game.png\n");

    env->fleche_droite= IMG_LoadTexture(ren, "./Textures/fleche_droite.png");
    if (!env->fleche_droite)
        ERROR("IMG_LoadTexture: fleche_droite.png\n");

    env->fleche_gauche= IMG_LoadTexture(ren, "./Textures/fleche_gauche.png");
    if (!env->fleche_gauche)
        ERROR("IMG_LoadTexture: fleche_gauche.png\n");

    env->name= IMG_LoadTexture(ren, "./Textures/name.png");
    if (!env->name)
        ERROR("IMG_LoadTexture: name.png\n");

    env->bande_rose= IMG_LoadTexture(ren, "./Textures/bande_rose.png");
    if (!env->bande_rose)
        ERROR("IMG_LoadTexture: bande_rose.png\n");

    env->bande_rose2= IMG_LoadTexture(ren, "./Textures/bande_rose2.png");
    if (!env->bande_rose2)
        ERROR("IMG_LoadTexture: bande_rose2.png\n");

    env->back= IMG_LoadTexture(ren, "./Textures/back.png");
    if (!env->back)
        ERROR("IMG_LoadTexture: back.png\n");


    env->pointe= IMG_LoadTexture(ren, "./Textures/pointe.png");
    if (!env->pointe)
        ERROR("IMG_LoadTexture: pointe.png\n");

    env->g = new_game();
    env->nb_joueurs = get_nb_player(env->g);
    env->curseur_fleche = 0;
    env->selection=1;
    env->pos1=0;
    env->pos2=0;
    env->pos3=0;
    env->pos4=0;
    env->pos5=0;
    env->name1[env->pos1]='\0';
    env->name2[env->pos2]='\0';
    env->name3[env->pos3]='\0';
    env->name4[env->pos4]='\0';
    env->name5[env->pos5]='\0';
    env->camp1=1;
    env->camp2=0;
    env->camp3=0;
    env->camp4=0;
    env->camp5=1;

    env->bout=0;
    env->roi=0;
    env->dame=0;
    env->cavalier=0;
    env->valet=0;
    env->reste=0;

    return env;
}




/* **************************************************************** */
void render_points(SDL_Window* win, SDL_Renderer* ren, Env * env){
    //posx, posy: coordonées du début de la grille
    SDL_GetWindowSize(win, &env->w, &env->h);
    int posx = env->w;
    int posy = env->h;
    if (posx>posy)
        env->coef = (env->h * 0.2);
    else
        env->coef = (env->w * 0.2);

    
    //color
    SDL_Color bleu_fond = {129,236,236,255};
    SDL_Color white = { 255, 255, 255, 255 };
    

    //background bleu
    SDL_SetRenderDrawColor(ren, bleu_fond.r, bleu_fond.g, bleu_fond.b, bleu_fond.a);

    //bouton back
    SDL_Rect back = {env->w*0.01, env->h*0.9, 0, 0};
    SDL_QueryTexture(env->back, NULL, NULL, &back.w, &back.h);
    back.w = env->coef*0.5;
    back.h = env->coef*0.5;
    SDL_RenderCopy(ren, env->back, NULL, &back);

    //Texte Preneurs
    TTF_Font * font2 = TTF_OpenFont(FONT2, env->fontsize*0.7);
    SDL_Surface* surf = TTF_RenderText_Blended(font2, "Preneurs", white);
    env->text = SDL_CreateTextureFromSurface(ren, surf); 
    SDL_Rect rect;
    int size_h, size_w;
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font2, "Preneurs", &size_w, &size_h);
    rect.x = env->w*0.05;
    rect.y =env->h/8;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    //chiffre 
    char str_x[12];
    sprintf(str_x, "%d", env->bout);
    TTF_Font * font = TTF_OpenFont(FONT2, env->fontsize*0.7);
    surf = TTF_RenderText_Blended(font, str_x, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, str_x, &size_w, &size_h);
    env->size_w=size_w;
    env->size_h=size_h;
    rect.x = (env->w/2) - (size_w/2);
    rect.y = env->h/3;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    TTF_CloseFont(font2);
    TTF_CloseFont(font);
 

    //fleche droite
    SDL_Rect rect_new = {env->w/2+size_w+env->fontsize*0.1, env->h/3+env->fontsize*0.22, 0, 0};
    SDL_QueryTexture(env->fleche_droite, NULL, NULL, &rect_new.w, &rect_new.h);
    rect_new.w = env->fontsize*0.7;
    rect_new.h = env->fontsize*0.7;
    SDL_RenderCopy(ren, env->fleche_droite, NULL, &rect_new);

    //fleche gauche
    rect_new.x = env->w/2-(2*(size_w+env->fontsize*0.1));
    rect_new.y = env->h/3+env->fontsize*0.22;
    SDL_QueryTexture(env->fleche_gauche, NULL, NULL, &rect_new.w, &rect_new.h);
    rect_new.w = env->fontsize*0.7;
    rect_new.h = env->fontsize*0.7;
    SDL_RenderCopy(ren, env->fleche_gauche, NULL, &rect_new);

}

void render_team(SDL_Window* win, SDL_Renderer* ren, Env * env){
    //posx, posy: coordonées du début de la grille
    SDL_GetWindowSize(win, &env->w, &env->h);
    int posx = env->w;
    int posy = env->h;
    if (posx>posy)
        env->coef = (env->h * 0.2);
    else
        env->coef = (env->w * 0.2);

    
    //color
    SDL_Color bleu_fond = {129,236,236,255};
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color rose_fonce = { 255, 118, 117};
    SDL_Color rose_clair = {250, 177, 160};
    

    //background bleu
    SDL_SetRenderDrawColor(ren, bleu_fond.r, bleu_fond.g, bleu_fond.b, bleu_fond.a);

    //bouton back
    SDL_Rect back = {env->w*0.01, env->h*0.9, 0, 0};
    SDL_QueryTexture(env->back, NULL, NULL, &back.w, &back.h);
    back.w = env->coef*0.5;
    back.h = env->coef*0.5;
    SDL_RenderCopy(ren, env->back, NULL, &back);


        //BANDES ROSES
    //bande rose 1
    SDL_Texture* fond=env->bande_rose2;
    int cote = env->w*0.05;

    if(env->camp1==1){
        fond = env->bande_rose;
        cote = env->w*0.15;
    }
    SDL_Rect name = {cote, env->h/7+env->coef*0.4, 0, 0};
    SDL_QueryTexture(fond, NULL, NULL, &name.w, &name.h);
    name.w = env->w*0.8;
    name.h = env->coef*0.5;
    SDL_RenderCopy(ren, fond, NULL, &name);
    fond=env->bande_rose2;
    cote = env->w*0.05;

    //bande rose 2
    if(env->camp2==1){
        fond = env->bande_rose;
        cote = env->w*0.15;
    }
    SDL_Rect name2 = {cote, env->h/7*2+env->coef*0.4, 0, 0};
    SDL_QueryTexture(fond, NULL, NULL, &name2.w, &name2.h);
    name2.w = env->w*0.8;
    name2.h = env->coef*0.5;
    SDL_RenderCopy(ren, fond, NULL, &name2);
    fond=env->bande_rose2;
    cote = env->w*0.05;

    //bande rose 3
    if(env->camp3==1){
        fond = env->bande_rose;
        cote = env->w*0.15;
    }
    SDL_Rect name3 = {cote, env->h/7*3+env->coef*0.4, 0, 0};
    SDL_QueryTexture(fond, NULL, NULL, &name3.w, &name3.h);
    name3.w = env->w*0.8;
    name3.h = env->coef*0.5;
    SDL_RenderCopy(ren, fond, NULL, &name3);
    fond=env->bande_rose2;
    cote = env->w*0.05;

    if(env->nb_joueurs>3){
        //bande rose 4
        if(env->camp4==1){
            fond = env->bande_rose;
            cote = env->w*0.15;
        }
        SDL_Rect name4 = {cote, env->h/7*4+env->coef*0.4, 0, 0};
        SDL_QueryTexture(fond, NULL, NULL, &name4.w, &name4.h);
        name4.w = env->w*0.8;
        name4.h = env->coef*0.5;
        SDL_RenderCopy(ren, fond, NULL, &name4);
        fond=env->bande_rose2;
        cote = env->w*0.05;
    }

    if(env->nb_joueurs==5){
        //bande rose 5
        if(env->camp5==1){
            fond = env->bande_rose;
            cote = env->w*0.15;
        }
        SDL_Rect name5 = {cote, env->h/7*5+env->coef*0.4, 0, 0};
        SDL_QueryTexture(fond, NULL, NULL, &name5.w, &name5.h);
        name5.w = env->w*0.8;
        name5.h = env->coef*0.5;
        SDL_RenderCopy(ren, fond, NULL, &name5);
        fond=env->bande_rose2;
        cote = env->w*0.05;
    }


    //bouton suivant
    int new_x = env->coef;
    int new_y = env->coef*0.4;
    int n=env->nb_joueurs;
    int k=0;
    int tab[n];
    if(n==3){
        tab[0]=env->camp1;
        tab[1]=env->camp2;
        tab[2]=env->camp3;
    }
    if(n==4){
        tab[0]=env->camp1;
        tab[1]=env->camp2;
        tab[2]=env->camp3;
        tab[3]=env->camp4;
    } 
    if(n==5){
        tab[0]=env->camp1;
        tab[1]=env->camp2;
        tab[2]=env->camp3;
        tab[3]=env->camp4;
        tab[4]=env->camp5;
    }
    for(int i=0; i<n-1;i++){
        if(tab[i]==tab[i+1]){
            k++;
        }
    }
    if(k+1!=n){
        SDL_Rect rect_next = {(env->w*0.99)-new_x, env->h*0.9, 0, 0};
        SDL_QueryTexture(env->color_bouton_new_game, NULL, NULL, &rect_next.w, &rect_next.h);
        rect_next.w = new_x;
        rect_next.h = new_y;
        SDL_RenderCopy(ren, env->color_bouton_new_game, NULL, &rect_next);

        env->fontsize = env->coef*0.4;
        TTF_Font * font = TTF_OpenFont(FONT, env->fontsize);

        SDL_Surface* surf1 = TTF_RenderText_Blended(font, "Suivant", white);
        env->text = SDL_CreateTextureFromSurface(ren, surf1);
        SDL_Rect next;
        SDL_QueryTexture(env->text, NULL, NULL, &next.w, &next.h);
        next.x = (env->w*0.99)-new_x*0.9;
        next.y = env->h*0.9;
        next.w = new_x*0.8;
        next.h = new_y*0.8;
        SDL_RenderCopy(ren, env->text, NULL, &next);
        SDL_FreeSurface(surf1);
        TTF_CloseFont(font);
    }




    env->fontsize = env->coef*0.4;
    //texte Equipes
    TTF_Font * font = TTF_OpenFont(FONT, env->fontsize);
    SDL_Surface * surf = TTF_RenderText_Blended(font, "Equipes", white);
    env->text = SDL_CreateTextureFromSurface(ren, surf); 
    SDL_Rect rect;
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    int size_w;
    int size_h;
    TTF_SizeText(font, "Equipes", &size_w, &size_h);
    rect.x = (env->w/2) - (size_w/2);
    rect.y = env->coef*0.1;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    //Texte Preneurs
    TTF_Font * font2 = TTF_OpenFont(FONT2, env->fontsize*0.7);
    surf = TTF_RenderText_Blended(font2, "Preneurs", rose_fonce);
    env->text = SDL_CreateTextureFromSurface(ren, surf); 
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font2, "Preneurs", &size_w, &size_h);
    rect.x = env->w*0.05;
    rect.y =env->h/8;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    //Texte Defenseurs
    surf = TTF_RenderText_Blended(font2, "Defenseurs", rose_clair);
    env->text = SDL_CreateTextureFromSurface(ren, surf); 
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font2, "Defenseurs", &size_w, &size_h);
    rect.x = (env->w*0.95)-size_w;
    rect.y =env->h/8;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    //Texte VS
    surf = TTF_RenderText_Blended(font2, "VS", white);
    env->text = SDL_CreateTextureFromSurface(ren, surf); 
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font2, "VS", &size_w, &size_h);
    rect.x = (env->w/2) - (size_w/2);
    rect.y =env->h/8;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);


    TTF_CloseFont(font2);




    //AFFICHE NOM
    cote = env->w*0.1;
    if(env->camp1==1){
        cote = env->w*0.2;
    }
    surf = TTF_RenderText_Blended(font, env->name1, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, env->name1, &size_w, &size_h);
    rect.x = cote; 
    rect.y = env->h/7+env->coef*0.4;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);
    cote = env->w*0.1;

    if(env->camp2==1){
        cote = env->w*0.2;
    }
    surf = TTF_RenderText_Blended(font, env->name2, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, env->name2, &size_w, &size_h);
    rect.x = cote; 
    rect.y = env->h/7*2+env->coef*0.4;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);
    cote = env->w*0.1;

    if(env->camp3==1){
        cote = env->w*0.2;
    }
    surf = TTF_RenderText_Blended(font, env->name3, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, env->name3, &size_w, &size_h);
    rect.x = cote; 
    rect.y = env->h/7*3+env->coef*0.4;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);
    cote = env->w*0.1;

    if(env->nb_joueurs>3){
        if(env->camp4==1){
            cote = env->w*0.2;
        }
        surf = TTF_RenderText_Blended(font, env->name4, white);
        env->text = SDL_CreateTextureFromSurface(ren, surf);
        SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
        TTF_SizeText(font, env->name4, &size_w, &size_h);
        rect.x = cote; 
        rect.y = env->h/7*4+env->coef*0.4;
        SDL_RenderCopy(ren, env->text, NULL, &rect);
        SDL_FreeSurface(surf);
        cote = env->w*0.1;
    }

    if(env->nb_joueurs>4){
        if(env->camp5==1){
            cote = env->w*0.2;
        }
        surf = TTF_RenderText_Blended(font, env->name5, white);
        env->text = SDL_CreateTextureFromSurface(ren, surf);
        SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
        TTF_SizeText(font, env->name5, &size_w, &size_h);
        rect.x = cote; 
        rect.y = env->h/7*5+env->coef*0.4;
        SDL_RenderCopy(ren, env->text, NULL, &rect);
        SDL_FreeSurface(surf);
        cote = env->w*0.1;
    }
    TTF_CloseFont(font);


}

void render_ask_name(SDL_Window* win, SDL_Renderer* ren, Env * env){
    //posx, posy: coordonées du début de la grille
    SDL_GetWindowSize(win, &env->w, &env->h);
    int posx = env->w;
    int posy = env->h;
    if (posx>posy)
        env->coef = (env->h * 0.2);
    else
        env->coef = (env->w * 0.2);

    
    //color
    SDL_Color bleu_fond = {129,236,236,255};
    SDL_Color white = { 255, 255, 255, 255 };

    //background bleu
    SDL_SetRenderDrawColor(ren, bleu_fond.r, bleu_fond.g, bleu_fond.b, bleu_fond.a);


    //BANDES ROSES
    //bande rose 1
    SDL_Rect name = {env->w*0.05, env->h/7+env->coef*0.4, 0, 0};
    SDL_QueryTexture(env->bande_rose2, NULL, NULL, &name.w, &name.h);
    name.w = env->w*0.8;
    name.h = env->coef*0.5;
    SDL_RenderCopy(ren, env->bande_rose2, NULL, &name);

    //bande rose 2
    SDL_Rect name2 = {env->w*0.05, env->h/7*2+env->coef*0.4, 0, 0};
    SDL_QueryTexture(env->bande_rose2, NULL, NULL, &name2.w, &name2.h);
    name2.w = env->w*0.8;
    name2.h = env->coef*0.5;
    SDL_RenderCopy(ren, env->bande_rose2, NULL, &name2);

    //bande rose 3
    SDL_Rect name3 = {env->w*0.05, env->h/7*3+env->coef*0.4, 0, 0};
    SDL_QueryTexture(env->bande_rose2, NULL, NULL, &name3.w, &name3.h);
    name3.w = env->w*0.8;
    name3.h = env->coef*0.5;
    SDL_RenderCopy(ren, env->bande_rose2, NULL, &name3);

    if(env->nb_joueurs>3){
        //bande rose 4
        SDL_Rect name4 = {env->w*0.05, env->h/7*4+env->coef*0.4, 0, 0};
        SDL_QueryTexture(env->bande_rose2, NULL, NULL, &name4.w, &name4.h);
        name4.w = env->w*0.8;
        name4.h = env->coef*0.5;
        SDL_RenderCopy(ren, env->bande_rose2, NULL, &name4);
    }

    if(env->nb_joueurs==5){
        //bande rose 5
        SDL_Rect name5 = {env->w*0.05, env->h/7*5+env->coef*0.4, 0, 0};
        SDL_QueryTexture(env->bande_rose2, NULL, NULL, &name5.w, &name5.h);
        name5.w = env->w*0.8;
        name5.h = env->coef*0.5;
        SDL_RenderCopy(ren, env->bande_rose2, NULL, &name5);
    }
    

    //bouton back
    SDL_Rect back = {env->w*0.01, env->h*0.9, 0, 0};
    SDL_QueryTexture(env->back, NULL, NULL, &back.w, &back.h);
    back.w = env->coef*0.5;
    back.h = env->coef*0.5;
    SDL_RenderCopy(ren, env->back, NULL, &back);

    //bouton suivant
    int new_x = env->coef;
    int new_y = env->coef*0.4;
    if(env->pos1!=0 && env->pos2!=0 && env->pos3!=0){
        if(env->nb_joueurs==3 || (env->nb_joueurs==4 && env->pos4!=0) || (env->nb_joueurs==5 && env->pos4!=0 && env->pos5!=0)){
            SDL_Rect rect_next = {(env->w*0.99)-new_x, env->h*0.9, 0, 0};
            SDL_QueryTexture(env->color_bouton_new_game, NULL, NULL, &rect_next.w, &rect_next.h);
            rect_next.w = new_x;
            rect_next.h = new_y;
            SDL_RenderCopy(ren, env->color_bouton_new_game, NULL, &rect_next);
        }
    }

    //FLECHE SELECTION
    if(env->curseur_fleche<15){
        SDL_Rect pointe;
        switch(env->selection){
            case 1:
                pointe.x = env->w*0.01; pointe.y = env->h/7+env->coef*0.5;
                break;
            case 2:
                pointe.x = env->w*0.01; pointe.y = env->h/7*2+env->coef*0.5;
                break;
            case 3:
                pointe.x = env->w*0.01; pointe.y = env->h/7*3+env->coef*0.5;
                break;
            case 4:
                pointe.x = env->w*0.01; pointe.y = env->h/7*4+env->coef*0.5;
                break;
            case 5:
                pointe.x = env->w*0.01; pointe.y = env->h/7*5+env->coef*0.5;
                break;
            default: break;
        }
        SDL_QueryTexture(env->pointe, NULL, NULL, &pointe.w, &pointe.h);
        pointe.w = env->coef*0.2;
        pointe.h = env->coef*0.2;
        SDL_RenderCopy(ren, env->pointe, NULL, &pointe);
    }
    if(env->curseur_fleche>25) env->curseur_fleche=0;
    env->curseur_fleche+=1;


    env->fontsize = env->coef*0.4;
    //texte Nom des joueurs
    TTF_Font * font = TTF_OpenFont(FONT, env->fontsize);
    SDL_Surface * surf = TTF_RenderText_Blended(font, "Nom des joueurs", white);
    env->text = SDL_CreateTextureFromSurface(ren, surf); 
    SDL_Rect rect;
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    int size_w;
    int size_h;
    TTF_SizeText(font, "Nom des joueurs", &size_w, &size_h);
    rect.x = (env->w/2) - (size_w/2);
    rect.y = env->coef*0.1;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);


    //AFFICHE NOM
    surf = TTF_RenderText_Blended(font, env->name1, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, env->name1, &size_w, &size_h);
    rect.x = env->w*0.1; 
    rect.y = env->h/7+env->coef*0.4;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);


    surf = TTF_RenderText_Blended(font, env->name2, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, env->name2, &size_w, &size_h);
    rect.x = env->w*0.1; 
    rect.y = env->h/7*2+env->coef*0.4;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    surf = TTF_RenderText_Blended(font, env->name3, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, env->name3, &size_w, &size_h);
    rect.x = env->w*0.1; 
    rect.y = env->h/7*3+env->coef*0.4;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    if(env->nb_joueurs>3){
        surf = TTF_RenderText_Blended(font, env->name4, white);
        env->text = SDL_CreateTextureFromSurface(ren, surf);
        SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
        TTF_SizeText(font, env->name4, &size_w, &size_h);
        rect.x = env->w*0.1; 
        rect.y = env->h/7*4+env->coef*0.4;
        SDL_RenderCopy(ren, env->text, NULL, &rect);
        SDL_FreeSurface(surf);
    }

    if(env->nb_joueurs>4){
        surf = TTF_RenderText_Blended(font, env->name5, white);
        env->text = SDL_CreateTextureFromSurface(ren, surf);
        SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
        TTF_SizeText(font, env->name5, &size_w, &size_h);
        rect.x = env->w*0.1; 
        rect.y = env->h/7*5+env->coef*0.4;
        SDL_RenderCopy(ren, env->text, NULL, &rect);
        SDL_FreeSurface(surf);
    }

    //texte suivant
    if(env->pos1!=0 && env->pos2!=0 && env->pos3!=0){
        if(env->nb_joueurs==3 || (env->nb_joueurs==4 && env->pos4!=0) || (env->nb_joueurs==5 && env->pos4!=0 && env->pos5!=0)){
            surf = TTF_RenderText_Blended(font, "Suivant", white);
            env->text = SDL_CreateTextureFromSurface(ren, surf);
            SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
            TTF_SizeText(font, "Suivant", &size_w, &size_h);
            rect.x = (env->w*0.99)-new_x*0.9;
            rect.y = env->h*0.9;
            rect.w = new_x*0.8;
            rect.h = new_y*0.8;
            SDL_RenderCopy(ren, env->text, NULL, &rect);
            SDL_FreeSurface(surf);
        }

    }

    TTF_CloseFont(font); 



}

//page ou on choisit le nombre de joueur
void render_ask_num(SDL_Window* win, SDL_Renderer* ren, Env * env){
    //posx, posy: coordonées du début de la grille
    SDL_GetWindowSize(win, &env->w, &env->h);
    int posx = env->w;
    int posy = env->h;
    if (posx>posy)
        env->coef = (env->h * 0.2);
    else
        env->coef = (env->w * 0.2);

    
    //color
    SDL_Color bleu_fond = {129,236,236,255};
    SDL_Color white = { 255, 255, 255, 255 };

    //background bleu
    SDL_SetRenderDrawColor(ren, bleu_fond.r, bleu_fond.g, bleu_fond.b, bleu_fond.a);

    
    env->fontsize = env->coef*0.5;

    //texte Nombre de joueurs
    TTF_Font * font = TTF_OpenFont(FONT, env->fontsize);
    SDL_Surface * surf = TTF_RenderText_Blended(font, "Nombre de joueurs", white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect rect;
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    int size_w;
    int size_h;
    TTF_SizeText(font, "Nombre de joueurs", &size_w, &size_h);
    rect.x = (env->w/2) - (size_w/2);
    rect.y = env->coef*0.2;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);

    //chiffre 
    char str_x[12];
    sprintf(str_x, "%d", env->nb_joueurs);
    surf = TTF_RenderText_Blended(font, str_x, white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, str_x, &size_w, &size_h);
    env->size_w=size_w;
    env->size_h=size_h;
    rect.x = (env->w/2) - (size_w/2);
    rect.y = env->h/3;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);
 

    //fleche droite
    SDL_Rect rect_new = {env->w/2+size_w+env->fontsize*0.1, env->h/3+env->fontsize*0.22, 0, 0};
    SDL_QueryTexture(env->fleche_droite, NULL, NULL, &rect_new.w, &rect_new.h);
    rect_new.w = env->fontsize*0.7;
    rect_new.h = env->fontsize*0.7;
    SDL_RenderCopy(ren, env->fleche_droite, NULL, &rect_new);

    //fleche gauche
    rect_new.x = env->w/2-(2*(size_w+env->fontsize*0.1));
    rect_new.y = env->h/3+env->fontsize*0.22;
    SDL_QueryTexture(env->fleche_gauche, NULL, NULL, &rect_new.w, &rect_new.h);
    rect_new.w = env->fontsize*0.7;
    rect_new.h = env->fontsize*0.7;
    SDL_RenderCopy(ren, env->fleche_gauche, NULL, &rect_new);

    //bouton suivant
    int new_x = env->coef*2;
    int new_y = env->coef*0.8;
    SDL_Rect rect_next = {env->w/2-new_x/2, env->h/3+3*env->fontsize, 0, 0};
    SDL_QueryTexture(env->color_bouton_new_game, NULL, NULL, &rect_next.w, &rect_next.h);
    rect_next.w = new_x;
    rect_next.h = new_y;
    SDL_RenderCopy(ren, env->color_bouton_new_game, NULL, &rect_next);

    //texte Suivant
    surf = TTF_RenderText_Blended(font, "Suivant", white);
    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    TTF_SizeText(font, "Suivant", &size_w, &size_h);
    rect.x = env->w/2-new_x/2+new_x*0.1;
    rect.y = env->h/3+3*env->fontsize+new_y*0.1;
    rect.w = new_x*0.8;
    rect.h = new_y*0.8;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);


    TTF_CloseFont(font); 
    
}


//page avec le bouton nouvelle partie
void render_new_game(SDL_Window* win, SDL_Renderer* ren, Env * env) {

    //posx, posy: coordonées du début de la grille
    SDL_GetWindowSize(win, &env->w, &env->h);
    int posx = env->w;
    int posy = env->h;

    if (posx>posy)
        env->coef = (env->h * 0.2);
    else
        env->coef = (env->w * 0.2);

    
    //background bleu
    SDL_Color bleu_fond = {129,236,236,255};
    SDL_SetRenderDrawColor(ren, bleu_fond.r, bleu_fond.g, bleu_fond.b, bleu_fond.a);

    //bouton
    int new_x = env->coef*3;
    int new_y = env->coef;
    SDL_Rect rect_new = {env->w/2-new_x/2, env->h/2-new_y/2, 0, 0};
    SDL_QueryTexture(env->color_bouton_new_game, NULL, NULL, &rect_new.w, &rect_new.h);
    rect_new.w = new_x;
    rect_new.h = new_y;
    SDL_RenderCopy(ren, env->color_bouton_new_game, NULL, &rect_new);
    

    //TEXTE
    env->fontsize = env->coef*0.4;

    SDL_Color white = { 255, 255, 255, 255 };
    TTF_Font * font = TTF_OpenFont(FONT, env->fontsize); //label font
    if (!font) ERROR("TTF_OpenFont: %s\n", FONT);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL

    SDL_Surface * surf;
    char text_tab[15] = {'N','o','u','v','e','l','l','e',' ','p','a','r','t','i','e'};
    surf = TTF_RenderText_Blended(font, text_tab, white);

    env->text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect rect;
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);

    //centre le texte 
    int rebord = env->coef*0.2;
    rect.w= rect_new.w-rebord*2;
    rect.h= rect_new.h-rebord*2;
    rect.x= env->w/2-new_x/2+rebord;
    rect.y= env->h/2-new_y/2+rebord;

    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_FreeSurface(surf);


    TTF_CloseFont(font);   

}


void render(SDL_Window* win, SDL_Renderer* ren, Env * env) {
    switch(env->state){
        case 0:
            render_new_game(win,ren,env);
            break;
        case 1:
            render_ask_num(win,ren,env);
            break;
        case 2:
            render_ask_name(win,ren,env);
            break;
        case 3:
            render_team(win,ren,env);
            break;
        case 4:
            render_points(win,ren,env);
            break;
        default: 
            break;
    }
}




/* **************************************************************** */

bool process_points(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e) {
    if (e->type == SDL_QUIT)
        return true;

    if (e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_ESCAPE:
                return true; break;
            default: break;
        }
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        //bouton back
        SDL_Rect back = {env->w*0.01, env->h*0.9, 0, 0};
        back.w = env->coef*0.5;
        back.h = env->coef*0.5;

        if(SDL_PointInRect(&mouse, &back)){
            env->state = 3;
        }
    }
    return false;
}

bool process_team(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e) {
    if (e->type == SDL_QUIT)
        return true;

    if (e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_ESCAPE:
                return true; break;
            default: break;
        }
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        //bouton back
        SDL_Rect back = {env->w*0.01, env->h*0.9, 0, 0};
        back.w = env->coef*0.5;
        back.h = env->coef*0.5;


        //BANDES
        int cote = env->w*0.05;
        if(env->camp1==1){
            cote = env->w*0.15;
        }
        SDL_Rect name = {cote, env->h/7+env->coef*0.4, 0, 0};
        name.w = env->w*0.8;
        name.h = env->coef*0.5;
        cote = env->w*0.05;

        //bande rose 2
        if(env->camp2==1){
            cote = env->w*0.15;
        }
        SDL_Rect name2 = {cote, env->h/7*2+env->coef*0.4, 0, 0};
        name2.w = env->w*0.8;
        name2.h = env->coef*0.5;
        cote = env->w*0.05;

        //bande rose 3
        if(env->camp3==1){
            cote = env->w*0.15;
        }
        SDL_Rect name3 = {cote, env->h/7*3+env->coef*0.4, 0, 0};
        name3.w = env->w*0.8;
        name3.h = env->coef*0.5;
        cote = env->w*0.05;

        if(env->nb_joueurs>3){
            //bande rose 4
            if(env->camp4==1){
                cote = env->w*0.15;
            }
            SDL_Rect name4 = {cote, env->h/7*4+env->coef*0.4, 0, 0};
            name4.w = env->w*0.8;
            name4.h = env->coef*0.5;
            cote = env->w*0.05;
            if(SDL_PointInRect(&mouse, &name4)){
                if(env->camp4==0) env->camp4=1;
                else env->camp4=0;
            }
        }

        if(env->nb_joueurs==5){
            //bande rose 5
            if(env->camp5==1){
                cote = env->w*0.15;
            }
            SDL_Rect name5 = {cote, env->h/7*5+env->coef*0.4, 0, 0};
            name5.w = env->w*0.8;
            name5.h = env->coef*0.5;
            cote = env->w*0.05;
            
            if(SDL_PointInRect(&mouse, &name5)){
                if(env->camp5==0) env->camp5=1;
                else env->camp5=0;                
            }
        }

        //bouton suivant
        int new_x = env->coef;
        int new_y = env->coef*0.4;
        int n=env->nb_joueurs;
        int k=0;
        int tab[n];
        if(n==3){
            tab[0]=env->camp1;
            tab[1]=env->camp2;
            tab[2]=env->camp3;
        }
        if(n==4){
            tab[0]=env->camp1;
            tab[1]=env->camp2;
            tab[2]=env->camp3;
            tab[3]=env->camp4;
        } 
        if(n==5){
            tab[0]=env->camp1;
            tab[1]=env->camp2;
            tab[2]=env->camp3;
            tab[3]=env->camp4;
            tab[4]=env->camp5;
        }
        for(int i=0; i<n-1;i++){
            if(tab[i]==tab[i+1]){
                k++;
            }
        }
        if(k+1!=n){
            SDL_Rect rect = { (env->w*0.99)-new_x*0.9, env->h*0.9,0,0};
            rect.w = new_x*0.8;
            rect.h = new_y*0.8;
            if(SDL_PointInRect(&mouse, &rect)){
                env->state = 4;
                role camp=ATTAQUE;
                if(env->camp1==1) camp = DEFENSE;
                env->g = send_camp(env->g, camp,0);
                camp=ATTAQUE;
                if(env->camp2==1) camp = DEFENSE;
                env->g = send_camp(env->g, camp,1);
                camp=ATTAQUE;
                if(env->camp3==1) camp = DEFENSE;
                env->g = send_camp(env->g, camp,2);
                camp=ATTAQUE;
                if(env->nb_joueurs>3){
                    if(env->camp4==1) camp = DEFENSE;
                    env->g = send_camp(env->g, camp,3);
                    camp=ATTAQUE;
                }
                if(env->nb_joueurs==5){
                    if(env->camp5==1) camp = DEFENSE;
                    env->g = send_camp(env->g, camp,4);
                    camp=ATTAQUE;
                }

            }
        }

        if(SDL_PointInRect(&mouse, &back)){
            env->state = 2;
        }
        if(SDL_PointInRect(&mouse, &name)){
            if(env->camp1==0) env->camp1=1;
            else env->camp1=0;
        }
        if(SDL_PointInRect(&mouse, &name2)){
            if(env->camp2==0) env->camp2=1;
            else env->camp2=0;
        }
        if(SDL_PointInRect(&mouse, &name3)){
            if(env->camp3==0) env->camp3=1;
            else env->camp3=0;
        }
        
    }
    return false;
}

bool process_ask_name (SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e) {
    if (e->type == SDL_QUIT)
        return true;

    if (e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_ESCAPE:
                return true; break;
            case SDLK_BACKSPACE:
                switch(env->selection){
                    case 1:
                        if (env->pos1!=0){
                            env->name1[env->pos1-1]='\0';
                            env->pos1-=1;
                        }
                        break;
                    case 2:
                        if (env->pos2!=0){
                            env->name2[env->pos2-1]='\0';
                            env->pos2-=1;
                        }
                        break;
                    case 3:
                        if (env->pos3!=0){
                            env->name3[env->pos3-1]='\0';
                            env->pos3-=1;
                        }
                        break;
                    case 4:
                        if (env->pos4!=0){
                            env->name4[env->pos4-1]='\0';
                            env->pos4-=1;
                        }
                        break;
                    case 5:
                        if (env->pos5!=0){
                            env->name5[env->pos5-1]='\0';
                            env->pos5-=1;
                        }
                        break;
                    default: break;
                }
                break;
            default: break;
        }
    }

    if(e->type == SDL_TEXTINPUT){
        switch(env->selection){
            case 1:
                if (env->pos1!=15){
                    env->name1[env->pos1]=*e->text.text;
                    env->name1[env->pos1+1]='\0';
                    env->pos1+=1;
                }
                break;
            case 2:
                if (env->pos2!=15){
                    env->name2[env->pos2]=*e->text.text;
                    env->name2[env->pos2+1]='\0';
                    env->pos2+=1;
                }
                break;
            case 3:
                if (env->pos3!=15){
                    env->name3[env->pos3]=*e->text.text;
                    env->name3[env->pos3+1]='\0';
                    env->pos3+=1;
                }
                break;
            case 4:
                if (env->pos4!=15){
                    env->name4[env->pos4]=*e->text.text;
                    env->name4[env->pos4+1]='\0';
                    env->pos4+=1;
                }
                break;
            case 5:
                if (env->pos5!=15){
                    env->name5[env->pos5]=*e->text.text;
                    env->name5[env->pos5+1]='\0';
                    env->pos5+=1;
                }
                break;
            default: break;
        }
    }
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        //bouton back
        SDL_Rect back = {env->w*0.01, env->h*0.9, 0, 0};
        back.w = env->coef*0.5;
        back.h = env->coef*0.5;

        //bande rose 1
        SDL_Rect name = {env->w*0.05, env->h/7+env->coef*0.4, 0, 0};
        name.w = env->w*0.8;
        name.h = env->coef*0.5;

        //bande rose 2
        SDL_Rect name2 = {env->w*0.05, env->h/7*2+env->coef*0.4, 0, 0};
        name2.w = env->w*0.8;
        name2.h = env->coef*0.5;

        //bande rose 3
        SDL_Rect name3 = {env->w*0.05, env->h/7*3+env->coef*0.4, 0, 0};
        name3.w = env->w*0.8;
        name3.h = env->coef*0.5;

        if(env->nb_joueurs>3){
            //bande rose 4
            SDL_Rect name4 = {env->w*0.05, env->h/7*4+env->coef*0.4, 0, 0};
            name4.w = env->w*0.8;
            name4.h = env->coef*0.5;
            if(SDL_PointInRect(&mouse, &name4)){
                env->selection = 4;
                env->curseur_fleche=0;
            }
        }

        if(env->nb_joueurs==5){
            //bande rose 5
            SDL_Rect name5 = {env->w*0.05, env->h/7*5+env->coef*0.4, 0, 0};
            name5.w = env->w*0.8;
            name5.h = env->coef*0.5;
            if(SDL_PointInRect(&mouse, &name5)){
                env->selection = 5;
                env->curseur_fleche=0;
            }
        }

        int new_x = env->coef;
        int new_y = env->coef*0.4;
        SDL_Rect rect = { (env->w*0.99)-new_x*0.9, env->h*0.9,0,0};
        rect.w = new_x*0.8;
        rect.h = new_y*0.8;

        if(SDL_PointInRect(&mouse, &back)){
            env->state = 1;
            env->pos1=0;
            env->pos2=0;
            env->pos3=0;
            env->pos4=0;
            env->pos5=0;
            env->name1[env->pos1]='\0';
            env->name2[env->pos2]='\0';
            env->name3[env->pos3]='\0';
            env->name4[env->pos4]='\0';
            env->name5[env->pos5]='\0';

        }

        if(SDL_PointInRect(&mouse, &rect)){
            if(env->pos1!=0 && env->pos2!=0 && env->pos3!=0){
                if(env->nb_joueurs==3 || (env->nb_joueurs==4 && env->pos4!=0) || (env->nb_joueurs==5 && env->pos4!=0 && env->pos5!=0)){
                    env->state = 3;
                    env->g = send_player(env->g, 0, env->name1);
                    env->g = send_player(env->g, 1, env->name2);
                    env->g = send_player(env->g, 2, env->name3);
                    if(env->nb_joueurs>3) env->g = send_player(env->g, 3, env->name4);
                    if(env->nb_joueurs==5) env->g = send_player(env->g, 4, env->name5);
                }
            }
        }

        if(SDL_PointInRect(&mouse, &name)){
            env->selection = 1;
            env->curseur_fleche=0;
        }
        if(SDL_PointInRect(&mouse, &name2)){
            env->selection = 2;
            env->curseur_fleche=0;
        }
        if(SDL_PointInRect(&mouse, &name3)){
            env->selection = 3;
            env->curseur_fleche=0;
        }
        
        
    }

    return false;
}

bool process_ask_num (SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e) {
    if (e->type == SDL_QUIT)
        return true;

    if (e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_ESCAPE:
                return true; break;
            default: break;
        }
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        SDL_Rect rect_droite = {env->w/2+env->size_w+env->fontsize*0.1, env->h/3+env->fontsize*0.22, 0, 0};
        rect_droite.w = env->fontsize*0.7;
        rect_droite.h = env->fontsize*0.7;

        SDL_Rect rect_gauche = { env->w/2-(2*(env->size_w+env->fontsize*0.1)), env->h/3+env->fontsize*0.22, 0, 0};
        rect_gauche.w = env->fontsize*0.7;
        rect_gauche.h = env->fontsize*0.7;

        int new_x = env->coef*2;
        int new_y = env->coef*0.8;
        SDL_Rect rect_next = {env->w/2-new_x/2, env->h/3+3*env->fontsize, 0, 0};
        rect_next.w = new_x;
        rect_next.h = new_y;


        if(SDL_PointInRect(&mouse, &rect_droite)){
            if(env->nb_joueurs<5){
                env->nb_joueurs+=1;
            }
        }
        if(SDL_PointInRect(&mouse, &rect_gauche)){
            if(env->nb_joueurs>3){
                env->nb_joueurs-=1;
            }
        }

        if(SDL_PointInRect(&mouse, &rect_next)){
            env->state = 2;
            env->g = send_nb_player(env->g, env->nb_joueurs);
        }

     }


    return false;
}

bool process_new_game (SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e) {
    if (e->type == SDL_QUIT)
        return true;

    if (e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_ESCAPE:
                return true; break;
            default: break;
        }
    }
     if (e->type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        int new_x = env->coef*3;
        int new_y = env->coef;
        SDL_Rect rect_new = {env->w/2-new_x/2, env->h/2-new_y/2, 0, 0};
        rect_new.w = new_x;
        rect_new.h = new_y;

        if(SDL_PointInRect(&mouse, &rect_new)){
            env->state=1;
        }

     }

    return false;
}

bool process (SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e) {
    switch(env->state){
        case 0:
            return process_new_game(win,ren,env,e);
        case 1:
            return process_ask_num(win,ren,env,e);
        case 2:
            return process_ask_name(win,ren,env,e);
        case 3:
            return process_team(win,ren,env,e);
        case 4:
            return process_points(win,ren,env,e);
        default: 
            break;
    }
   return false;
}

/* **************************************************************** */

void clean (SDL_Window* win, SDL_Renderer* ren, Env * env) {
    free(env);
}