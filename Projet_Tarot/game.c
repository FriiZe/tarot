#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "game.h"

#define NB_CARTES_TOTAL 78
#define NB_CARTE_CHIEN 6
#define NB_CHAR_NICKNAME 20
#define NB_TOTAL_POINT 91


/*===========================================================================*
 *                                 STRUCTURES                                *
 *===========================================================================*/


/*
*   Structure d'une carte: 
*   famille: coeur,pique..atout
*   val: 1,2..21,100 *100: Excuse*
*   bout: true/false
*/
typedef struct carte_s {
	famille f;
    int val;
    bool bout;
} carte_s;
typedef struct carte_s* carte;


/*
*   Structure d'un joueur
*   place: place du joueur
*   camp du joueur
*/
typedef struct player_s{
    int place;
    role camp;
    int pts;
    char* nickname;
}player_s;
typedef struct player_s* player;


/*
*   Structure d'un game:
*   nb_player: nombre de joueur (3,4,5)
*/
typedef struct game_s{
    int nb_player;
    int nb_tours;
    int partie;
    carte* jeu;
    player* all_players;

}game_s;
typedef struct game_s* game;


/*===========================================================================*
 *                                 CLEAN                                     *
 *===========================================================================*/


void clean_term(){
	write(1,"\E[H\E[2J",7);
}

void clean_buffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}



/*===========================================================================*
 *                                 PLAYER                                    *
 *===========================================================================*/

void ask_name(player p){
    char* verif_taille = NULL;
    //+2->  "<nb>:" prend la place de 2 char (fonction new_game)
    fgets(p->nickname, sizeof(char)*(NB_CHAR_NICKNAME+2), stdin);
    if(p->nickname[0] == '\n'){
        printf("Veuillez choisir un pseudo: \n");
        ask_name(p);
    }

    verif_taille = strchr(p->nickname,'\n');
    if(verif_taille==NULL){
        printf("Veuillez choisir un pseudo plus court (%d nombre de caractere max): \n",NB_CHAR_NICKNAME);
        clean_buffer();
        ask_name(p);
    }
}

//create a new player
player new_player(int place, role camp){
    player p = (player) malloc(sizeof(player_s));
    if(p == NULL) {
		fprintf(stderr, "Error in \"new_player\" player is NULL.");
		exit(EXIT_FAILURE);
	}
    p->nickname = (char*) malloc(sizeof(char)*NB_CHAR_NICKNAME);
    if(p->nickname == NULL){
        fprintf(stderr, "Error in \"new_player\" nickname is NULL.");
		exit(EXIT_FAILURE);
    }

    ask_name(p);
    p->place = place;
    p->camp = camp;
    p->pts = 0;
    return p;
}



/*===========================================================================*
 *                                  GAME                                     *
 *===========================================================================*/
void affiche_titre(){
    printf("=========================\n     POINTS TAROT     \n=========================\n\n");
}

//create a new game
game new_game(){
    game g = (game) malloc(sizeof(game_s));
	if(g == NULL) {
		fprintf(stderr, "Error in \"new_game\" Memory.");
		exit(EXIT_FAILURE);
	}
    
    while(g->nb_player<3 || g->nb_player>6){
        printf("Combien etes vous?\n");
        char tmp[6];
        fgets(tmp, sizeof(tmp), stdin);
        g->nb_player= (int) *tmp -48;
        if(g->nb_player>6 || g->nb_player<3){
            printf("Veuillez choisir un nombre de joueurs entre 3 et 6\n");
        }
    }
    clean_term();
    affiche_titre();
    g->all_players = (player*) malloc(sizeof(player_s)*g->nb_player);
    for(int i =0; i<g->nb_player;i++){
        printf("Pseudo du joueur %d: \n",i+1);
        player p = new_player(i,ATTAQUE);
        g->all_players[i]=p;

    }

    g->nb_tours = (NB_CARTES_TOTAL-NB_CARTE_CHIEN)/g->nb_player;
    carte* jeu=(carte*) malloc(sizeof(carte_s)*NB_CARTES_TOTAL);
    if(jeu == NULL) {
		fprintf(stderr, "Error in \"new_game\" Memory.");
		exit(EXIT_FAILURE);
	}
    g->partie=1;
    g->jeu = jeu;
    return g;
}

int get_nb_player(game g){
    return g->nb_player;
}

game send_nb_player(game g, int x){
    g->nb_player=x;
    return g;
}

game send_camp(game g, role camp, int pos){
    g->all_players[pos]->camp=camp;
    for(int i=0; i<g->nb_player;i++){
        printf("%d\n", g->all_players[i]->camp);
    }
    printf("\n");
    return g;
}


game send_player(game g, int pos, char* name){
    g->all_players[pos]->nickname=name;
    return g;
}

void affiche_partie(game g){
    clean_term();
    printf("===============\n  PARTIE N°%d\n===============\n\n",g->partie);
}

//Demande qui a pris et affiche la composition des equipes
void chose_team(game g){
    int x;
    int y;
    int preneurs;
    int i=0;
    //liste les joueurs
    printf("Liste des joueurs:\n");
    while (i<g->nb_player){
        printf("%d: %s",i+1,g->all_players[i]->nickname);
        i++;
    }
    //recupere les joueurs attaquants
    if(g->nb_player==3){
        printf("\nEquipe preneuse : <x>\n");
	    preneurs = scanf("%d", &x);
    }
    if(g->nb_player==4){
        printf("\nEquipe preneuse : <x>\n");
	    preneurs = scanf("%d", &x);
    }

    if(g->nb_player==5){
        printf("\nEquipe preneuse : <x> <y>\n");
	    preneurs = scanf("%d %d", &x, &y);
    }
    if(preneurs==EOF){
        printf("Erreur\n");
    }

    affiche_partie(g);
    //calcul et affiche la compostion des equipes
    if(g->nb_player<5){
        printf("Attaquant:\n | %s",g->all_players[x-1]->nickname);
        g->all_players[x-1]->camp= ATTAQUE;
        printf("Defenseurs:\n ");
        for(int i=0; i<g->nb_player;i++){
            if (i!=x-1){
                printf("| %s ",g->all_players[i]->nickname);
                g->all_players[i]->camp= DEFENSE;
            } 
        }
    }else{
        printf("Attaquants:\n | %s | %s",g->all_players[x-1]->nickname,g->all_players[y-1]->nickname);
        g->all_players[x-1]->camp= ATTAQUE;
        g->all_players[y-1]->camp= ATTAQUE;
        printf("Defenseurs:\n ");
        for(int i=0; i<g->nb_player;i++){
            if (i!=x-1 && i!=y-1){
                printf("| %s ",g->all_players[i]->nickname);
                g->all_players[i]->camp= DEFENSE;
            } 
        }
    }


}



//calcule et retourne les points 
float compute(game g, int* bout){//, int* roi, int *dame, int* cavalier, int* valet, int *reste){
    clean_term();
    affiche_partie(g);
    float res=0;
    int roi=0;
    int dame=0;
    int cavalier=0;
    int valet=0;
    int reste=0;
    int rep;
    printf("\nNb bout: \n");
    rep = scanf("%d", bout);
    printf("\nNb roi: \n");
    rep = scanf("%d", &roi);
    printf("\nNb dame: \n");
    rep = scanf("%d", &dame);
    printf("\nNb cavalier: \n");
    rep = scanf("%d", &cavalier);
    printf("\nNb : valet\n");
    rep = scanf("%d", &valet);
    printf("\nNb reste: \n");
    rep = scanf("%d", &reste);
    res += (*bout*4.5);
    res += (roi*4.5);
    res += (dame*3.5);
    res += (cavalier*2.5);
    res += (valet*1.5);
    res += (reste*0.5);
    return res;
}


//demande le contrat et calcule avec le coef
float check_win(float pts, int obj){
    float bonus=pts-obj;
    int rep;
    int contrat=0;
    if (bonus>0) bonus+=25;
    else{
        bonus-=25;
    }
    printf("\nContrat: \n1. Petite\n2. Garde\n3. Garde sans\n4. Garde contre\n");
    rep = scanf("%d", &contrat);
    int coef;
    switch(contrat){
        case 1:
            coef = 1;
            break;
        case 2:
            coef = 2;
            break;
        case 3:
            coef = 4;
            break;
        case 4:
            coef = 6;
            break;
        default: break;
    }

    bonus *=coef;
    return bonus;
}


//repartit les points de la partie entre chaque joueur
void repartition_points(game g, float pts_a, float pts_d){
    //calcul points pour chaque joueur
    if(g->nb_player<5) pts_d = -1*pts_a/(g->nb_player-1); // a modifier car les pts defenseur ne sont pas juste le neg cest 91 - pts a non? ERREUR ICI !!
    else{
        pts_d = -1*2*pts_a/(g->nb_player-2);
    }
    //associe pts a chaque joueur selon l'equipe
    for(int i=0; i<g->nb_player;i++){
        if(g->all_players[i]->camp==ATTAQUE) g->all_players[i]->pts+=pts_a;
        else{
            g->all_players[i]->pts+=pts_d;
        }
    }
}

//affiche les points
void affiche_points_joueurs(game g){
    affiche_partie(g);
    for(int i=0; i<g->nb_player;i++){
        printf("%d : %s",g->all_players[i]->pts, g->all_players[i]->nickname);
    }
    printf("\n\n");
}

//demande, calcul les points finaux
void points(game g){
    int equipe = 0;
    int rep;
    printf("\n\nCompter les cartes de quel équipe ?\n1. Attaquants\n2. Defenseurs\n");
    rep = scanf("%d", &equipe);
    if (rep==EOF) {
        clean_term();
        points(g);
    }
    int bout=0;
    float pts = compute(g, &bout);
    float pts_a=0;
    float pts_d=0;
    if (equipe == 1){
        pts_a = pts; pts_d = NB_TOTAL_POINT-pts_a;
    }else{
        pts_d = pts; pts_a = NB_TOTAL_POINT-pts_a;
    }
    printf("\nAttaquants : %.2f pts\n",pts_a);
    printf("Defenseurs : %.2f pts\n",pts_d);
    
    switch (bout){
        case 0:
            pts_a = check_win(pts_a, 56);
            break;
        case 1:
            pts_a = check_win(pts_a, 51);
            break;
        case 2:
            pts_a = check_win(pts_a, 41);
            break;
        case 3:
            pts_a = check_win(pts_a, 36);
            break;
        default: break;    
    }

    repartition_points(g, pts_a, pts_d);
    g->partie+=1;
}


/*===========================================================================*
 *                              JEU DE CARTES                                *
 *===========================================================================*/

//create a new card
carte new_card(famille f, int val){
    carte c = (carte) malloc(sizeof(carte_s));
    if(c == NULL) {
		fprintf(stderr, "Error in \"new_card\" the card is NULL.");
		exit(EXIT_FAILURE);
	}
    c->f=f;
    if(val<1 || val>21){
        if(val!=100){
            fprintf(stderr, "Error in \"new_card\" Choose an other value.");
		    exit(EXIT_FAILURE);
        }
        c->val = val;
        c->bout = true;
        return c;
    }
    c->val = val;
    if(val==1 || val==21){
        c->bout = true;
    }else{
        c->bout=false;
    }
    return c;
}

//affiche une carte
void affiche_carte(carte c){
    if(!c){
        fprintf(stderr, "Error in \"affiche_carte\" the card is NULL.");
		exit(EXIT_FAILURE);
    }
    
    famille fam = c->f;
    int val = c->val;
    switch(fam){
        case PIQUE: switch(val){
                case 11: printf("VP "); break;
                case 12: printf("CP "); break;
                case 13: printf("DP "); break;
                case 14: printf("RP "); break;
                default: printf("%dP ",val); break;
            } break;
        case TREFLE: switch(val){
                case 11: printf("VT "); break;
                case 12: printf("CT "); break;
                case 13: printf("DT "); break;
                case 14: printf("RT "); break;
                default: printf("%dT ",val); break;
            } break;
        case CARREAU:printf("\033[31m"); switch(val){
                case 11: printf("VCa "); break;
                case 12: printf("CCa "); break;
                case 13: printf("DCa "); break;
                case 14: printf("RCa "); break;
                default: printf("%dCa ",val); break;
            } break;
        case COEUR:  printf("\033[31m"); switch(val){
                case 11: printf("VCo "); break;
                case 12: printf("CCo "); break;
                case 13: printf("DCo "); break;
                case 14: printf("RCo "); break;
                default: printf("%dCo ",val); break;
            } break;
        case ATOUT: printf("\033[36m"); switch(val){
                case 100: printf("E "); break;
                default: printf("%d ",val); break;
            } break;
        default: break;
    }
    printf("\033[0m");
    
}

//initialise le jeu de carte
game initialize(game g){
    printf("\n");
    if(!g){
        fprintf(stderr, "Error in \"initialize\" the game is NULL.");
		exit(EXIT_FAILURE);
    }
    int t=0;
    for(int i=1; i<15;i++){
        carte c = new_card(PIQUE, i);
        g->jeu[(14*t)+i-2]=c;
    }
    t++;
    for(int i=1; i<15;i++){
        carte c = new_card(TREFLE, i);
        g->jeu[(14*t)+i-2]=c;
    }
    t++;
    for(int i=1; i<15;i++){
        carte c = new_card(COEUR, i);
        g->jeu[(14*t)+i-2]=c;
    }
    t++;
    for(int i=1; i<15;i++){
        carte c = new_card(CARREAU, i);
        g->jeu[(14*t)+i-2]=c;
    }
    t++;
    for(int i=1; i<22;i++){
        carte c = new_card(ATOUT, i);
        g->jeu[(14*t)+i-2]=c;
    }
    return g;
}

//affiche le jeu de carte
void affiche_jeu(game g){
    for(int i=0; i<NB_CARTES_TOTAL; i++){
        affiche_carte(g->jeu[i]);
    }
}

