#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

/*===========================================================================*
 *                           STRUCTURES ET ENUM                              *
 *===========================================================================*/


typedef enum famille_e { PIQUE, TREFLE, COEUR, CARREAU, ATOUT} famille;
typedef enum role_e {ATTAQUE, DEFENSE} role;

typedef struct carte_s* carte;
typedef struct player_s* player;
typedef struct game_s* game;


/*===========================================================================*
 *                                 CLEAN                                     *
 *===========================================================================*/


void clean_term();
void clean_buffer();


/*===========================================================================*
 *                                 PLAYER                                    *
 *===========================================================================*/

void ask_name(player p);

//create a new player
player new_player(int place, role camp);


/*===========================================================================*
 *                                  GAME                                     *
 *===========================================================================*/
void affiche_titre();

//create a new game
game new_game();

int get_nb_player(game g);

game send_nb_player(game g, int x);

game send_player(game g,int pos, char* name);

game send_camp(game g, role camp, int pos);

void affiche_partie(game g);

//Demande qui a pris et affiche la composition des equipes
void chose_team(game g);



//calcule et retourne les points 
float compute(game g, int* bout);//, int* roi, int *dame, int* cavalier, int* valet, int *reste);

//demande le contrat et calcule avec le coef
float check_win(float pts,int obj);


//repartit les points de la partie entre chaque joueur
void repartition_points(game g, float pts_a, float pts_d);

//affiche les points
void affiche_points_joueurs(game g);

//demande, calcul les points finaux
void points(game g);


/*===========================================================================*
 *                              JEU DE CARTES                                *
 *===========================================================================*/

//create a new card
carte new_card(famille f, int val);

//affiche une carte
void affiche_carte(carte c);

//initialise le jeu de carte
game initialize(game g);

//affiche le jeu de carte
void affiche_jeu(game g);

