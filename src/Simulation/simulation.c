//Include the header file
#include "../Roles/driver/Role.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define NB_PLAYERS         4 //define maximum number of players
#define MAX_TURNS          10 //define maximum number of turns for the game (it's also company win condition)


//general structure for components and variables of the game
typedef struct Game{
    Player** players; //list of current players in the game
    int nb_players; //number of TOTAL players (so we don't have to loop on both lists constantly)
    int elapsed_turns; //to count current number of turns
}Game;

Game* init_game(int nb_players); //function to initialize all global variables of the game
Player* init_player(int id); //function to initialize all variables for each player depending on their role
void play_cards(Player** players, int nb_players); //function to play all cards in a tour

int main(int argc, char *argv[])
{
    printf("\n\nThis is simulation is played with 4 players.\nPlease attribute the ids from 1 to 4 to each player.\nEach player chooses a pile of cards and draws 3. Each player also has to draw an additional common card.\n");
    printf(ANSI_COLOR_RED   "The game is on!!!"    ANSI_COLOR_RESET);
    printf("\n\nTo initialize the game, each player must play a role specific card to register themselves.\n\n");

    Game* game;
    game = init_game(NB_PLAYERS); // Initialize the game with 4 players
    
    //to test type of players
    for(int i = 0; i<NB_PLAYERS; i++){
        printf("Player n°%x is of type ", i+1);
        switch (game->players[i]->role){
            case BH:
                printf("Black Hat\n");
                break;
            case WH:
                printf("White Hat\n");
                break;
            case COMPANY:
                printf("Company\n");
                break;
            case EMPLOYEE:
                printf("Employee\n");
                break;
            default:
                printf("ERROR! Role not recognized.\n");
                break;
        }
        play_cards (game->players, NB_PLAYERS);

    }
/*

    //to test personal messages
    notify_player(game->players[0], "Hi, I am player 1");
    notify_player(game->players[1], "Hi, I am player 2");
    
    //to test different personal messages?
    notify_player(game->players[0], "Here is a message for player 2.");
    
    //to test broadcast
    notify_broadcast("Broadcast message test");
    
    //yeah idk
    print_message(game->players, NB_PLAYERS);
*/
    return 0;
}


void play_cards(Player** players, int nb_players){
    Player* player;
    int card;
    char target;
    
    for(int i=0; i<nb_players; i++){
        if(players[i]->Alive){
            printf("May the player number %d insert the card id and the target\n", i+1);
            scanf("%x %c", &card, &target );
            printf("card: %d et target %c\n", card, target);
            /*if (play(players[i], card, target)){

            }else{
                printf("The payed card is not permitted \n");
                i--;
            }*/
        }
    }
}

Game* init_game(int nb_players){
    Game* game = malloc(sizeof(Game));

    //create the player list
    Player** players = malloc(nb_players*sizeof(Player*));
    for (int i = 0; i < nb_players; i++){
        players[i] = init_player(i);
    }
    game->players=players;

    //initialize number of total players
    game->nb_players=nb_players;

    //start turn counter to 0 (game hasn't started yet)
    game->elapsed_turns=0;

    return game;
}

Player* init_player(int id){
    printf("Please input the code of a special card for the player n°%x.\n", id+1);
    int card;
    scanf("%x", &card);
    Player* player = create_player(card);
    
    if (player==NULL) {
        printf("Error during initialisation.\n");
        printf("The code %x does not correspond to any special card.\n", card);
        return init_player(id);
    }

    switch(player->role){
        case BH:
            printf("Initialisation Black Hat...\n");
            return player;
        case WH:
            printf("Initialisation White Hat...\n");
            return player;
        case COMPANY:
            printf("Initialisation company...\n");
            return player;
        case EMPLOYEE:
            printf("Initialisation employee...\n");
            return player;
        default:
            printf("No role has been recognized.\n");
            return NULL;
    }
    
}
