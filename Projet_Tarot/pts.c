#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct players{
    char nickname[20];
    int pts;
} players;
/*
void nb_players (){
    int nb_player;
    printf("Combien etes vous?");
    scanf("%d", &nb_player);
    for(int i=1; i<=nb_player; i++){
        players player  + str(i);
        printf("Pseudo du joueur 1:\n");
        fgets((player + str(i)).nickname, sizeof((player + str(i)).nickname), stdin);
    }
    printf("nb players : %d\n", nb_player);
}
*/