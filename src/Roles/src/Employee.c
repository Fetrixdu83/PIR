#include "../driver/Role.h"
#include "../driver/Employee.h"

int Employee_end() //Win condition of Employee
{
    return 0;
}

/*pas de pointeur pour le moment j'en vois pas vraiment l'utilité*/
Player* Employee_create_player() //Create a player with the Employee role
{
    Player* Employee_player = (Player*) malloc(sizeof(Player));
    Employee_player->role = EMPLOYEE;
    Employee_player->piece = 4; 
    Employee_player->num = 4; 
    Employee_player->money = 3; 
    Employee_player->played_card = NULL; 
    Employee_player->place = 0; 
    return Employee_player;
}


void Employee_play(Player* player, id card, char target) //Play function for Employee
{
    switch(card){
        case 0x0003000: // Employee card 0 AKA Common card
            // Implement the effect of Employee Common card
            break;
        case 0x0003001: // Employee card 1
            // Implement the effect of Employee card 1
            break; 
        case 0x0003002: // Employee card 2
            // Implement the effect of Employee card 2
            break;
        case 0x0003003: // Employee card 3
            // Implement the effect of Employee card 3
            break;
        case 0x0003004: // Employee card 4    
            // Implement the effect of Employee card 4
            break;
        case 0x0003005: // Employee card 5
            // Implement the effect of Employee card 5
            break;
        case 0x0003006: // Employee card 6    
            // Implement the effect of Employee card 6
            break;
        case 0x0003007: // Employee card 7    
            // Implement the effect of Employee card 7
            break;
        case 0x0003008: // Employee card 8
            // Implement the effect of Employee card 8
            break;
    }
}