#ifndef ROLE_H
#define ROLE_H

#include <stdio.h>
#include <stdlib.h>
#include "BH.h"
#include "WH.h"
#include "Company.h"
#include "Employee.h"


#define BH 0
#define WH 1
#define COMPANY 2
#define EMPLOYEE 3


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
Player* create_player(char num, id carte);
void play(Player* player, id card, char target);
void free_player(Player* player);

#endif