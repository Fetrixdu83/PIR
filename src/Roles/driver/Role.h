#ifndef ROLE_H
#define ROLE_H

typedef struct Message{
    char message[255];
    struct Message* next;
}Message;

typedef unsigned int id;
typedef struct Player{
    char role;
    id piece;
    char num;
    char money;
    id* played_card;
    id place;
    Message* message;
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

int end();
Player* create_player(id carte);
void play(Player* player, id card, char target);

//Add an element to the message tab of the player
void notify_player(Player* player, char message[255]);// Tab of message of 255 char max
void print_message(Player** player, int nb_players); // Print the message tab of the player
void notify_broadcast(char message[255]); // Add a message to the global message list


#endif