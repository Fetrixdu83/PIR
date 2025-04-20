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
    int card;
    char target;
    
    for(int i=0; i<game->nb_players; i++){
        if(game->players[i]->Alive && game->players[i]->Frozen == 0){
            printf("May the player number %d insert the card id, his position and the target\n", i+1);
            scanf("%x %i %c", &card, &(game->players[i]->place), &target );
            printf("card: %x position  %d et target %c\n", card, game->players[i]->place,  target);
            switch (play(game->players[i], card, game->players[target - 1], game->elapsed_turns-1)){
                case FAILURE_CARD_NOT_MATCHING_PLAYER:
                // card not matching the role of the player => error or replay to be discussed
                    printf("\n\n player not matching the card to be discussed\n\n");
                    break;
                case FAILURE_CARD_NOT_MATCHING_GAME_VERSION:
                // role not mentioned was detected => error
                    printf("ERROR : [40] please take contact with the game devellopers informing the error id \n");
                    exit(1);
                    break;
                case FAILURE_NOT_ENOUGH_MONEY:
                // card played requests more money => effect was dropped 
                    printf("\n\nThis card requests more money than what the player owns => dropped\n\n");
                    break;
                case FAILURE_WRONG_PLACE:
                // card played request player to be at a place where he is not => effect was drpped
                    printf("\n\nThis card requests the player to be at a certain place => dropped\n\n");

                    break;
                
                case SUCCESS:
                //the played card was considered
                    break;
                case NOT_IMPLEMENTED_YET:
                    printf("not implemented yet\n");
                    break;
                case SUCCESS_BROADCAST:
                    // card played was considered and a message need to be sent to all players
                    // Notify all players about the broadcast message
                    notify_broadcast("Broadcast message:  a force brutale has been conducted.\n");
                    break;
                default :
                // default case not recongnized 
                    printf("ERROR : [58] please take contact with the game devellopers informing the error id \n");
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
    player->Alive = !ALIVE;
    const char* role_str = "";  // <-- initialize properly

    switch (player->role)
    {
    case BH:
        role_str = " black hat";
        break;
    case WH:
        role_str = " white hat";
        break;
    case COMPANY:
        role_str = " company";
        break;
    case EMPLOYEE:
        role_str = "n employee";
        break;
    }

    printf("Player number %d was a%s. (S)He had %d IR.\n", (player->num)+1, role_str, player->money);
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