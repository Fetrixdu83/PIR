//Include the header file
#include "../Roles/driver/Role.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define NB_PLAYERS         4
#define MAX_TURNS          10 //define maximum number of turns for the game (it's also company win condition)


//general structure for components and variables of the game
typedef struct Game{
    Player** players; //list of current players in the game
    Player ** Eliminated_players; //players that have been eliminated during the game for whatever reason, depending on what we do this might not be definitive
    int nb_players; //number of total players (so we don't have to loop on both lists constantly)
    int elapsed_turns; //to count current number of turns
}Game;

Game* init_game(); //function to initialize all global variables of the game
Player* init_player(int id); //function to initialize all variables for each player depending on their role


int main(int argc, char *argv[])
{
    printf("\n\nCette simulation se joue a 4 joueurs.\nVeuillez atribuer les identifiants 1 a 4 a chacun des joueurs.\nChaque joueur choisit une pile de carte et en pioche 3. Chaque joueur est aussi demande a piocher une carte commune.\n");
    printf(ANSI_COLOR_RED   "Le jeu commence !!"    ANSI_COLOR_RESET);
    printf("\n\nAfin d'initialiser le jeu, chacun des joueurs est appele a jouer une carte specifique a son role.\n\n");

    Game* game;
    game = init_game(NB_PLAYERS); // Initialize the game with 4 players
    
    //to test type of players
    for(int i = 0; i<NB_PLAYERS; i++){
        printf("player %x is of type ", i+1);
        switch (game->players[i]->role){
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

    //to test personal messages
    notify_player(game->players[0], "Hi, I am player 1");
    notify_player(game->players[1], "Hi, I am player 2");
    
    //to test different personal messages?
    notify_player(game->players[0], "Here is a message for player 2.");
    
    //to test broadcast
    notify_broadcast("Broadcast message test");
    
    //yeah idk
    print_message(game->players);
    return 0;
}

Game* init_game(int nb_players){
    Game* game = malloc(sizeof(Game));

    //start turn counter to 0 (game hasn't started yet)
    game->elapsed_turns=0;

    //create the player list
    Player** players = malloc(nb_players*sizeof(Player*));
    for (int i = 0; i < nb_players; i++){
        players[i] = init_player(i);
    }
    game->players=players;

    //allocate space for eliminated player list but it's empty for now
    Player** eliminated_players = malloc(nb_players* sizeof(Player*));
    game->Eliminated_players=eliminated_players;

    return game;
}

Player* init_player(int id){
    printf("Veuillez rentrer le code d'une carte speciale pour le joueur numero : %x\n", id+1);
    int card;
    scanf("%x", &card);
    Player* player = create_player(card);
    
    if (player==NULL) {
        printf("Erreur lors de l'initialisation\n");
        printf("Le code %x ne correspond a aucune carte speciale.\n", card);
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
            return NULL;
    }
    
}
