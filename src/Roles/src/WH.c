#include "../driver/Role.h"

int WH_end() //Win condition of WH
{
}

/*pas de pointeur pour le moment j'en vois pas vraiment l'utilité*/
Player WH_create_player() //Create a player with the WH role
{
    Player WH_player;
    WH_player.role = WH;
    WH_player.piece = 2; 
    WH_player.num = 2; 
    WH_player.money = 3; 
    WH_player.played_card = NULL; 
    WH_player.place = 0; 
    return WH_player;
}


void WH_play(Player* player, id card, char target) //Play function for WH
{
    switch(card){
        case 0x0004000: // WH card 0 AKA Common card
            // Implement the effect of WH Common card
            break;
        case 0x0004001: // WH card 1
            // Implement the effect of WH card 1
            break; 
        case 0x0004002: // WH card 2
            // Implement the effect of WH card 2
            break;
        case 0x0004003: // WH card 3
            // Implement the effect of WH card 3
            break;
        case 0x0004004: // WH card 4    
            // Implement the effect of WH card 4
            break;
        case 0x0004005: // WH card 5
            // Implement the effect of WH card 5
            break;
        case 0x0004006: // WH card 6    
            // Implement the effect of WH card 6
            break;
        case 0x0004007: // WH card 7    
            // Implement the effect of WH card 7
            break;
        case 0x0004008: // WH card 8
            // Implement the effect of WH card 8
            break;
    }
}