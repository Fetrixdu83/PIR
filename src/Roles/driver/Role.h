#ifndef ROLE_H
#define ROLE_H

typedef struct Message{
    char message[255];
    struct Message* next;
}Message;

typedef unsigned int id;
typedef struct Player{
    char role; // player role
    id piece;  // player pion  
    char num;  // player id in the board
    char money;// player IR
    id* played_card;// played cards
    id place;  // player location
    Message* message; // saved messages
    int Alive; // is alive 
    char Frozen; // is frozen for the next round
}Player;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BH.h"
#include "WH.h"
#include "Company.h"
#include "Employee.h"

#define BH 1
#define WH 2
#define COMPANY 3
#define EMPLOYEE 4

#define CARD_BITS 4

#define PLACE_COMPANY 0
#define PLACE_CYPERCAFE 1
#define PLACE_BANK 2
#define PLACE_LIBRARY 3

#define FAILURE_CARD_NOT_MATCHING_PLAYER -2
#define FAILURE_CARD_NOT_MATCHING_GAME_VERSION -1
#define FAILURE_CARD_NOT_PERMITTED 0
#define SUCCESS 1
#define SUCCESS_BROADCAST 11
#define FAILURE_WRONG_PLACE 2
#define FAILURE_NOT_ENOUGH_MONEY 3
#define NOT_IMPLEMENTED_YET 4

#define ALIVE 1
#define DEAD 0

#define COMMON_CARD 0x1


int end(Player** players);
Player* init_player(int id); //function to initialize all variables for each player depending on their role
Player* create_player(id carte);
int play(Player* player, id card, Player* target,int current_round); // Play function for all players

//Add an element to the message tab of the player
void notify_player(Player* player, char message[255]);// Tab of message of 255 char max
void print_message(Player** player, int nb_players); // Print the message tab of the player
void notify_broadcast(char message[255]); // Add a message to the global message list


#endif