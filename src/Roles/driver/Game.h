#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Roles/driver/Role.h"


#define MAX_TURNS 10
//general structure for components and variables of the game
typedef struct Game{
    Player** players; //list of current players in the game
    int nb_players; //number of TOTAL players (so we don't have to loop on both lists constantly)
    int elapsed_turns; //to count current number of turns
}Game;


Game* init_game(int nb_players); //function to initialize all global variables of the game
int end_game(Game* game); // Check the end clauses are verified
void play_cards(Game* game); //function to play all cards in a tour



#endif