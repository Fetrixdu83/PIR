#include "../driver/Role.h"

int Company_end() //Win condition of Company
{
}

/*pas de pointeur pour le moment j'en vois pas vraiment l'utilité*/
Player Company_create_player() //Create a player with the Company role
{
    Player Company_player;
    Company_player.role = COMPANY;
    Company_player.piece = 3; 
    Company_player.num = 3; 
    Company_player.money = 6; 
    Company_player.played_card = NULL; 
    Company_player.place = 0; 
    return Company_player;
}


void Company_play(Player* player, id card, char target) //Play function for Company
{
    switch(card){
        case 0x0002000: // Company card 0 AKA Common card
            // Implement the effect of Company Common card
            break;
        case 0x0002001: // Company card 1
            // Implement the effect of Company card 1
            break; 
        case 0x0002002: // Company card 2
            // Implement the effect of Company card 2
            break;
        case 0x0002003: // Company card 3
            // Implement the effect of Company card 3
            break;
        case 0x0002004: // Company card 4    
            // Implement the effect of Company card 4
            break;
        case 0x0002005: // Company card 5
            // Implement the effect of Company card 5
            break;
        case 0x0002006: // Company card 6    
            // Implement the effect of Company card 6
            break;
        case 0x0002007: // Company card 7    
            // Implement the effect of Company card 7
            break;
        case 0x0002008: // Company card 8
            // Implement the effect of Company card 8
            break;
    }
}