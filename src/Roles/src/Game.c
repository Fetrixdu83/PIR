#include "../driver/Game.h"
#include "../driver/Role.h"

Game* init_game(int nb_players){
    Game* game = malloc(sizeof(Game));

    //start turn counter to 0 (game hasn't started yet)
    game->elapsed_turns=0;

    //create the player list
    Player** players = malloc(nb_players*sizeof(Player*));
    for (int i = 0; i < nb_players; i++){
        players[i] = init_player(i);
        players[i]->num = i;
        players[i]->piece = i;
        players[i]->Frozen = 0; // Initialize Frozen to 0 (not frozen)
    }
    game->players=players;
    game->nb_players = nb_players;

    return game;
}

void play_cards(Game* game){
    Player* player;
    int card;
    char target;
    
    for(int i=0; i<game->nb_players; i++){
        if(game->players[i]->Alive && game->players[i]->Frozen == 0){
            printf("May the player number %d insert the card id, his position and the target\n", i+1);
            scanf("%x %i %c", &card, &(game->players[i]->place), &target );
            printf("card: %d position  %d et target %c\n", card,game->players[i]->place,  target);
            switch (play(game->players[i], card, game->players[target - 1], game->elapsed_turns)){
                case -2:
                // card not matching the role of the player => error or replay to be discussed
                    break;
                case -1:
                // role not mentioned was detected => error
                    printf("ERROR : [34] please take contact with the game devellopers informing the error id \n");
                    exit(1);
                    break;
                case 0:
                // card played was not permitted => effect was dropped / or replay the card => should be discussed
                    break;
                case 1:
                //the played card was considered
                    break;
                case 11:
                    // card played was considered and a message need to be sent to all players
                    // Notify all players about the broadcast message
                    notify_broadcast("Broadcast message:  a force brutale has been conducted.\n");
                    break;
                default :
                // default case not recongnized 
                    printf("ERROR : [45] please take contact with the game devellopers informing the error id \n");
                    exit(1);
                    break;
            }
        
        }
        if(game->players[i]->Alive && game->players[i]->Frozen != 0){
            // Player is frozen, so they cannot play a card this turn
            game->players[i]->Frozen -=1; // decrease the frozen counter
            // Notify the player that they are frozen  
            printf("Player number %d is frozen and cannot play a card this turn.\n", i+1);
        }
    }
    game->elapsed_turns++;
}

void eliminate_player(Game* game, Player* player){
    //this function should eliminate the if so selectred player from the game
    player->Alive = ! ALIVE;
    char* role_str;
    switch (player->role)
    {
    case BH:
        strcpy(role_str, "black hat");
        break;
    case WH:
        strcpy(role_str, "white hat");
        break;
    case COMPANY:
        strcpy(role_str, "company");
        break;
    case EMPLOYEE:
        strcpy(role_str, "employee");
        break;
    }

    printf("Player number %d was a %s. (S)He had %d IR.\n", (player->num)+1, role_str, player->money);

}


int end_game(Game* game){
    /**
     * Retruns 0 if the game is not finished
     * -1 if a draw
     * the id of the id + 1 if a player with id =id won 
     */
    if (game->elapsed_turns>MAX_TURNS){
        return -1;
    }else{
        return end(game->players);
    }
}