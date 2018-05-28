#include <stdio.h>
#include <stdlib.h>
#include "game.c"
#include <stdbool.h>






int main(void){
    printf("\033[H\033[2J");
    affiche_titre();
    game g =new_game();
    g=initialize(g);
    while (true){
        affiche_points_joueurs(g);
        chose_team(g);
        points(g);
    }
    
    printf("\n");
    printf("\nTEST OK \n");
    return 0;
}