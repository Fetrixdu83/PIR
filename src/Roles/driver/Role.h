#ifndef ROLE_H
#define ROLE_H


typedef unsigned int id;
typedef struct Player{
    char role;
    id piece;
    char num;
    char money;
    id* played_card;
    id place;

}Player;

#include <stdio.h>
#include <stdlib.h>
#include "BH.h"
#include "WH.h"
#include "Company.h"
#include "Employee.h"


#define BH 1
#define WH 2
#define COMPANY 3
#define EMPLOYEE 4

#define CARD_COMMON 0x0001000
#define CARD_BITS 4

#define PLACE_ENTREPRISE 0
#define PLACE_CYPERCAFE 1
#define PLACE_BANK 2
#define PLACE_LIBRARY 3
#define SUCCESS 1
#define FAILURE_WRONG_PLACE -1
#define FAILURE_NOT_ENOUGH_MONEY 0

int end();
Player* create_player(id carte);
void play(Player* player, id card, char target);

#endif