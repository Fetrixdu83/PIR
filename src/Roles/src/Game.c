#include "../driver/Game.h"


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
    game->nb_players = nb_players;

    return game;
}

void play_cards(Game* game){
    Player* player;
    int card;
    char target;
    
    for(int i=0; i<game->nb_players; i++){
        if(game->players[i]->Alive){
            printf("May the player number %d insert the card id, his position and the target\n", i+1);
            scanf("%x %i %c", &card, &(game->players[i]->place), &target );
            printf("card: %d position  %d et target %c\n", card,game->players[i]->place,  target);
            if (play(game->players[i], card, target)){

            }else{
                printf("The payed card is not permitted \n");
                i--;
            }
        }
    }
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