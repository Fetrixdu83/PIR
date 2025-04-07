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
    BH_player->message = NULL; // Initialize message tab to NULL
    BH_player->Alive = ALIVE;
    return BH_player;
}


int BH_play(Player* player, id card, char target) //Play function for BH
{
    /**
     * -1 role not mentioned was detected => error
     * 0 card played was not permitted => effect was dropped 
     * 1 the played card was considered
     */
    switch(card){
        case COMMON_CARD: // BH card 0 AKA Common card
            // Implement the effect of BH Common card
            break;
        case BH_CORRUPT: // BH card 1
            // Implement the effect of BH card 1
            break; 
        case BH_BOTNET: // BH card 2
            // Implement the effect of BH card 2
            break;
        case BH_DDoS: // BH card 3
            // Implement the effect of BH card 3
            break;
        case BH_BRUTE_FORCE: // BH card 4    
            // Implement the effect of BH card 4
            break;
        case BH_PHISHING: // BH card 5
            // Implement the effect of BH card 5
            break;
        case BH_SQL_INJECTION: // BH card 6    
            // Implement the effect of BH card 6
            break;
        case BH_XSS: // BH card 7    
            // Implement the effect of BH card 7
            break;
        case BH_PHYSICAL_ATTACK: // BH card 8
            // Implement the effect of BH card 8
            break;
        default:
            return -1;
            break;
    }
}