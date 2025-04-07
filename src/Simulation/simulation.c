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

    Game* game = init_game(NB_PLAYERS); // Initialize the game with 4 players
    
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

    // paly a first tour with no voting 
    play_cards (game);
    int end = end_game(game) ; // integer that permits to play more tours
    Player* to_eliminate = NULL;// no one to eliminate for the moment
    while( ! end ){
        play_cards (game);
        // print the messages at the end of the tour

        // vote to eliminate a player
        to_eliminate = get_eliminated_player(game);
        eliminate_player(game, to_eliminate);
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

Player* get_eliminated_player(Game * game){
    //this function should print messages to make the game master select the eliminated player
    int id;
    printf("Please vote for eliminating a player : \n");
    printf("type the id of the if so eliminated player or 0 otherwise\n");
    scanf("%d", &id);
    id -- ;//to rebase the id to [|0-n|] 
    
    if (id==-1){
        return NULL; //No one was eliminated
    }
    for(int i=0; i < NB_PLAYERS; i ++){
        if(game->players[i]->num==id ){
            if(game->players[i]->Alive == ALIVE){
                return game->players[i];
            }
            else{
                printf("Player %i is already dead !!\n");
            }
        }
    }
    printf("Please select a playing id or 0 for none\n");

    // if we go this far in the code => the selected id was either not playing or out of range
    // recall function
    return get_eliminated_player(game);
}




