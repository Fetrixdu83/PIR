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
    switch(card){
        case COMMON_CARD: // BH card 0 AKA Common card
            // Implement the effect of BH Common card
            switch (player->place):
                case PLACE_BANK:
                    player->money += 3; // Gain 3 money
                    return SUCCESS; // Card played successfully
                    break;
                case PLACE_CYBERCAFE:
                    return FAILURE_WRONG_PLACE; // Card played in a wrong place
                    break;
                case PLACE_LIBRARY:
                    if(player->money >= 2) // Check if player has enough money
                        player->money -= 2; // Lose 2 money
                        return SUCCESS; // Card played successfully
                    else
                        return FAILURE_NOT_ENOUGH_MONEY; 
                    break;
                case PLACE_ENTREPRISE:
                    return FAILURE_WRONG_PLACE; 
                    break;
            break;
        case BH_CORRUPT: // BH card 1
        case BH_CORRUPT: // BH card 1
            // Implement the effect of BH card 1
            if(player->money >= 2){
                player->money -= 2; 
                
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            }    
            break; 
        case BH_BOTNET: // BH card 2
        case BH_BOTNET: // BH card 2
            // Implement the effect of BH card 2
            if(player->money >= 1){
                player->money -= 1; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_DDoS: // BH card 3
        case BH_DDoS: // BH card 3
            // Implement the effect of BH card 3
            if(player->money >= 1){
                player->money -= 1; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_BRUTE_FORCE: // BH card 4    
        case BH_BRUTE_FORCE: // BH card 4    
            // Implement the effect of BH card 4
            if(player->money >= 1){
                player->money -= 1; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_PHISHING: // BH card 5
        case BH_PHISHING: // BH card 5
            // Implement the effect of BH card 5
            if(player->money >= 2){
                player->money -= 2; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_SQL_INJECTION: // BH card 6    
        case BH_SQL_INJECTION: // BH card 6    
            // Implement the effect of BH card 6
            if(player->money >= 3){
                player->money -= 3; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_XSS: // BH card 7    
        case BH_XSS: // BH card 7    
            // Implement the effect of BH card 7
            if(player->money >= 4){
                player->money -= 4; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_PHYSICAL_ATTACK: // BH card 8
        case BH_PHYSICAL_ATTACK: // BH card 8
            // Implement the effect of BH card 8
            if(player->money >= 3){
                player->money -= 3; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
    }
}