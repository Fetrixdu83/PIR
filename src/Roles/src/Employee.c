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
    Employee_player->money = 3; 
    Employee_player->played_card = NULL; 
    Employee_player->place = 0; 
    Employee_player->message = NULL; // Initialize message tab to NULL
    Employee_player->Alive = ALIVE;
    return Employee_player;
}


int Employee_play(Player* player, id card, Player* target) //Play function for Employee
{
    switch(card){
        case COMMON_CARD: // Employee card 0 AKA Common card
            // Implement the effect of Employee Common card
            break;
        case EM_OPEN_MAIL: // Employee card 1
            // Implement the effect of Employee card 1
            break; 
        case EM_MEETING: // Employee card 2
            // Implement the effect of Employee card 2
            break;
        case EM_PWD_TRAINING: // Employee card 3
            // Implement the effect of Employee card 3
            break;
        case EM_BREAK: // Employee card 4    
            // Implement the effect of Employee card 4
            break;
        case EM_PRINT: // Employee card 5
            // Implement the effect of Employee card 5
            break;
        case EM_PREPARE_BACKUP: // Employee card 6    
            // Implement the effect of Employee card 6
            break;
        case EM_PHISHING_TRAINING: // Employee card 7    
            // Implement the effect of Employee card 7
            break;
        case EM_BACKDOOR: // Employee card 8
            // Implement the effect of Employee card 8
            break;
    }
}