#include "../driver/Role.h"
#include "../driver/BH.h"

int BH_end() //Win condition of BH
{
    return 0;
}

/*pas de pointeur pour le moment j'en vois pas vraiment l'utilité*/
/*En créant un joeur on renvoit son @ qui sera stocké dans un tableau de joueur*/
Player* BH_create_player() //Create a player with the BH role
{
    Player* BH_player = malloc(sizeof(Player));
    BH_player->role = BH;
    BH_player->piece = 1; // Initialize piece to 0
    BH_player->num = 1; // Initialize num to 0
    BH_player->money = 3; // Initialize money to 0
    BH_player->played_card = NULL; // Initialize played_card to NULL
    BH_player->place = 0; // Initialize place to 0
    return BH_player;
}


void BH_play(Player* player, id card, char target) //Play function for BH
{
    switch(card){
        case 0x0001000: // BH card 0 AKA Common card
            // Implement the effect of BH Common card
            break;
        case 0x0001001: // BH card 1
            // Implement the effect of BH card 1
            break; 
        case 0x0001002: // BH card 2
            // Implement the effect of BH card 2
            break;
        case 0x0001003: // BH card 3
            // Implement the effect of BH card 3
            break;
        case 0x0001004: // BH card 4    
            // Implement the effect of BH card 4
            break;
        case 0x0001005: // BH card 5
            // Implement the effect of BH card 5
            break;
        case 0x0001006: // BH card 6    
            // Implement the effect of BH card 6
            break;
        case 0x0001007: // BH card 7    
            // Implement the effect of BH card 7
            break;
        case 0x0001008: // BH card 8
            // Implement the effect of BH card 8
            break;
    }
}