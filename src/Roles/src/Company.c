#include "../driver/Role.h"
#include "../driver/Company.h"

int Company_end() //Win condition of Company
{
    return 0;
}

Player* Company_create_player() //Create a player with the Company role
{
    Player* Company_player = (Player*) malloc(sizeof(Player));
    Company_player->role = COMPANY;
    Company_player->piece = 3; 
    Company_player->num = 3; 
    Company_player->money = 6; 
    Company_player->played_card = NULL; 
    Company_player->place = 0; 
    Company_player->message = NULL; // Initialize message tab to NULL
    Company_player->Alive = ALIVE;
    return Company_player;
}


int Company_play(Player* player, id card, char target) //Play function for Company
{
    switch(card){
        case COMMON_CARD: // Company card 0 AKA Common card
            // Implement the effect of Company Common card
            break;
        case CO_FIREWALL: // Company card 1
            // Implement the effect of Company card 1
            break; 
        case CO_BACKUP: // Company card 2
            // Implement the effect of Company card 2
            break;
        case CO_SECURE_BUILDING: // Company card 3
            // Implement the effect of Company card 3
            break;
        case CO_CONFERENCE: // Company card 4    
            // Implement the effect of Company card 4
            break;
        case CO_UNFAIR_COMPETETION: // Company card 5
            // Implement the effect of Company card 5
            break;
        case CO_: // Company card 6    
            // Implement the effect of Company card 6
            break;
        case CO_PROMOTE_EM: // Company card 7    
            // Implement the effect of Company card 7
            break;
        case CO_FINANCE_WH: // Company card 8
            // Implement the effect of Company card 8
            break;
    }
}