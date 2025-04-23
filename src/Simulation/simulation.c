//Include the header file
#include "../Roles/driver/Game.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define NB_PLAYERS         4 //define maximum number of players
#define MAX_TURNS          10 //define maximum number of turns for the game (it's also company win condition)

Player* get_eliminated_player(Game * game);



int main(int argc, char *argv[])
{
    printf("\n\nThis is simulation is played with 4 players.\nPlease attribute the ids from 1 to 4 to each player.\nEach player chooses a stack of cards and draws 3. Each player also has to draw an additional common card.\n");
    printf(ANSI_COLOR_RED   "Win conditions :\n "    ANSI_COLOR_RESET);
    printf("\t Black hats : Eliminating the company by stealing its resources (can corrupt its employees to help them win)\n\n");
    printf("\t Company : Eliminating all of the threats (black hats and the employees if they join them) should keep always enough money to survive\n\n");
    printf("\t White hat : this role is kind of neutral as he tries to help the company protect itself against attack. He decides to help the company or not and can receive financial aids. Its goal is to survive until the end of the game. If so, he wins\n\n");
    printf("\t Employees : Naturally win with the company, therefore, some employees may be corrupted and join the dark side of the moon (Money, so it's said, is the root of all evil today) they win with the black hats\n\n");
    
    printf("Initially all players have 3 IRs except the Company that has 6.\n");
    
    printf(ANSI_COLOR_RED   "\t \t Let the game start!!!"    ANSI_COLOR_RESET);
    printf("\n\nTo initialize the game, each player must play a role specific card to register themselves.\n\n");

    Game* game = init_game(NB_PLAYERS); // Initialize the game with 4 players
    
    printf("\n");
    //to test type of players
    for(int i = 0; i<NB_PLAYERS; i++){
        printf("Player n: %x is of type ", i+1);
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
    printf("\n");

    // paly a first tour with no voting 
    play_cards (game);
    int end = end_game(game) ; // integer that permits to play more tours
    Player* to_eliminate = NULL;// no one to eliminate for the moment
    while( ! end ){
        play_cards (game);
        // print the messages at the end of the tour
        printf(ANSI_COLOR_RED       "Global messages:\n"        ANSI_COLOR_RESET);

        print_global_messages();

        print_message(game->players, game->nb_players);
        // vote to eliminate a player
        to_eliminate = get_eliminated_player(game);
        eliminate_player(game, to_eliminate);
        
        end = end_game(game);
    }

    switch(end){
        case -1:
        // a draw 
            printf(ANSI_COLOR_RED       "The game ended : IT IS A DRAW \nPlayers can divulgate their identities\n"        ANSI_COLOR_RESET);
            break;

        case 0 :
        // game is not finished we should not be at this point => error
            printf("ERROR : [58] please take contact with the game devellopers informing the error id \n");
            exit(1);
            break;
        case BH:
            printf(ANSI_COLOR_RED       "The Black hat team won. \n"        ANSI_COLOR_RESET);
            if(betray){
                printf(ANSI_COLOR_RED       "They were helped by an employee of the company \n"        ANSI_COLOR_RESET);
            }
        break;

        case COMPANY:
            printf(ANSI_COLOR_RED       "Despite all of the attacks this community has eliminated all of the threats ;) The company won\n"        ANSI_COLOR_RESET);
        break;

        case WH:
            printf(ANSI_COLOR_RED       "The White hat has accomplished his goal to survive until the end and it paid : He won !!\n"        ANSI_COLOR_RESET);
        break;

        default:
            printf(ANSI_COLOR_RED       "ERROR: [100] please refer to the developers with the associated code.\n"        ANSI_COLOR_RESET);
        break;
        }
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
    for(int i=0; i < game->nb_players; i ++){
        if(game->players[i]->num==id ){
            if(game->players[i]->Alive == ALIVE){
                return game->players[i];
            }
            else{
                printf("Player %d is already dead !!\n", i);
            }
        }
    }
    printf("Please select a playing id or 0 for none\n");

    // if we go this far in the code => the selected id was either not playing or out of range
    // recall function
    return get_eliminated_player(game);
}




