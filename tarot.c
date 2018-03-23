#include <stdio.h>
#include <stdlib.h>
#include "game.c"
#include <stdbool.h>






int main(void){
    printf("\033[H\033[2J");
    /*carte c1 = new_card(PIQUE,11);
    carte c2 = new_card(TREFLE, 5);
    carte c3 = new_card(CARREAU,7);
    carte c4 = new_card(COEUR, 1);
    carte c5 = new_card(ATOUT, 21);
    affiche_carte(c1);
    affiche_carte(c2);
    affiche_carte(c3);
    affiche_carte(c4);
    affiche_carte(c5);*/
    game g =new_game();
    g=initialize(g);
    affiche_jeu(g);
    printf("\n");
    printf("\nTEST OK \n");
    return 0;
}