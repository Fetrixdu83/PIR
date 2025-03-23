#ifndef ROLE_H
#define ROLE_H

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


typedef unsigned int id;

typedef struct Player{
    char role;
    id piece;
    char num;
    char money;
    id* played_card;
    id place;

}Player;


int end();
Player* create_player(id carte);
void play(Player* player, id card, char target);

#endif