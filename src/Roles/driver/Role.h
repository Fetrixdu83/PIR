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

#define CARD_BITS 4




int end();
Player* create_player(id carte);
void play(Player* player, id card, char target);

#endif