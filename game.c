#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NB_CARTES_TOTAL 78
#define NB_CARTE_CHIEN 6



typedef enum famille_e { PIQUE, TREFLE, COEUR, CARREAU, ATOUT} famille;
typedef enum role_e {ATTAQUE, DEFENSE} role;



/*Structure d'une carte: 
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


/*Structure d'un game:
*   nb_player: nombre de joueur (3,4,5)
*/
typedef struct game_s{
    int nb_player;
    int nb_tours;
    carte* jeu;

}game_s;
typedef struct game_s* game;


/*Structure d'un joueur
*   place: place du joueur
*   camp du joueur
*/
typedef struct player_s{
    int place;
    role* camp;
}player_s;
typedef struct player_s* player;






//create a new game
game new_game(){
    game g = (game) malloc(sizeof(game_s));
	if(g == NULL) {
		fprintf(stderr, "Error in \"new_game\" Memory.");
		exit(EXIT_FAILURE);
	}
    g->nb_player = 3;
    g->nb_tours = (NB_CARTES_TOTAL-NB_CARTE_CHIEN)/3;
    carte* jeu=(carte*) malloc(sizeof(carte_s)*NB_CARTES_TOTAL);
    if(jeu == NULL) {
		fprintf(stderr, "Error in \"new_game\" Memory.");
		exit(EXIT_FAILURE);
	}
    g->jeu = jeu;
    return g;
}

//create a new player
player new_player(int place, role* camp){
    player p = (player) malloc(sizeof(player_s));
    if(p == NULL) {
		fprintf(stderr, "Error in \"new_player\" player is NULL.");
		exit(EXIT_FAILURE);
	}
    p->place = place;
    p->camp = camp;
    return p;
}

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

void affiche_jeu(game g){
    for(int i=0; i<NB_CARTES_TOTAL; i++){
        affiche_carte(g->jeu[i]);
    }
}

void message(){
    printf("Message ok\n");
}
