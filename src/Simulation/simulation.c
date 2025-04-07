//Include the header file
#include "../Roles/driver/Game.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define NB_PLAYERS         4 //define maximum number of players
#define MAX_TURNS          10 //define maximum number of turns for the game (it's also company win condition)




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
        
    }
    int end = 0 ; // integer that permits to play more tours
    while( ! end ){
        play_cards (game);
        // print the messages at the end of the tour
        end = end_game(game);
    }

    switch(end){
        case -1:
        // a draw 

            break;

        case 0 :
        // game is not finished we should not be at this point => error
            printf("ERROR : [58] please take contact with the game devellopers informing the error id \n");
            exit(1);
            break;
        default :
        // the player with id  = end - 1 won should print winning message:
        // should end the game too

            break;
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






