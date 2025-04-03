//Inculde the header file
#include "../Roles/driver/Role.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define NB_PLAYERS         4

Player** init_game();
Player* init_player(int id);

int main(int argc, char *argv[])
{
    printf("\n\nCette simulation se joue a 4 joueurs.\nVeuillez atribuer les identifiants 1 a 4 a chacun des joueurs.\nChaque joueur choisit une pile de carte et en pioche 3. Chaque joueur est aussi demande a piocher une carte commune.\n");
    printf(ANSI_COLOR_RED   "Le jeu commence !!"    ANSI_COLOR_RESET);
    printf("\n\nAfin d'initialiser le jeu, chacun des joueurs est appele a jouer une carte specifique a son role.\n\n");



    Player** players;
    players = init_game(NB_PLAYERS); // Initialize the game with 4 players
    
    
    for(int i = 0; i<NB_PLAYERS; i++){
        printf("le joueur %d est de type ", i+1);
        switch (players[i]->role){
            case BH:
                printf("Black Hat\n");
                break;
            case WH:
                printf("White Hat\n");
                break;
            case COMPANY:
                printf("entreprise\n");
                break;
            case EMPLOYEE:
                printf("employe\n");
                break;
        }
        
    }

    return 0;
}


Player** init_game(){
    Player** players = malloc(NB_PLAYERS* sizeof(Player*));
    for (int i = 0; i < NB_PLAYERS; i++){
        players[i] = init_player(i);
    }
    return players;
}

Player* init_player(int id){
    printf("Veuillez rentrer le code d'une carte speciale pour le joueur numero : %d\n", id+1);
    int card;
    scanf("%d", &card);
    Player* player = create_player(card);
    if (player==NULL) {
        printf("Erreur lors de l'initialisation\n");
        printf("Le code %d ne correspond a aucune carte speciale.\n", card);
        return init_player(id);
    }
    switch(player->role){
        case BH:
            printf("Initialisation Black Hat\n");
            return player;
        case WH:
            printf("Initialisation White Hat\n");
            return player;
        case COMPANY:
            printf("Initialisation entreprise\n");
            return player;
        case EMPLOYEE:
            printf("Initialisation employe\n");
            return player;
        default:
            printf("Aucun role reconnu. \n");
            exit(1);
    }
    
}
