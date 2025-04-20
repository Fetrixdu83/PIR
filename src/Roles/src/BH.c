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
            switch (player->place){
                case PLACE_BANK:
                    player->money += 3; // Gain 3 money
                    return SUCCESS; // Card played successfully

                case PLACE_LIBRARY:
                    if(player->money >= 2){ // Check if player has enough money
                        player->money -= 2; // Lose 2 money
                        return SUCCESS; // Card played successfully
                    }
                    else{
                        return FAILURE_NOT_ENOUGH_MONEY; 
                    }

                default:
                    return FAILURE_WRONG_PLACE; 
            }

        case BH_CORRUPT: // BH card 1
            // Implement the effect of BH card 1
            if(player->money >= 2){
                player->money -= 2; 
                
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            }    

        case BH_BOTNET: // BH card 2
            // Implement the effect of BH card 2
            if(player->money >= 1){
                player->money -= 1; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 

        case BH_DDoS: // BH card 3
            // Implement the effect of BH card 3
            if(player->money >= 1){
                player->money -= 1; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            } 

        case BH_BRUTE_FORCE: // BH card 4    
            // Implement the effect of BH card 4
            if(player->money >= 1){
                player->money -= 1; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            } 

        case BH_PHISHING: // BH card 5
            // Implement the effect of BH card 5
            if(player->money >= 2){
                player->money -= 2; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            } 

        case BH_SQL_INJECTION: // BH card 6    
            // Implement the effect of BH card 6
            if(player->money >= 3){
                player->money -= 3; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            } 

        case BH_XSS: // BH card 7    
            // Implement the effect of BH card 7
            if(player->money >= 4){
                player->money -= 4; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            } 

        case BH_PHYSICAL_ATTACK: // BH card 8
            if(player->money >= 3){
                if(player->place == PLACE_COMPANY){
                    player->money -= 3; 
                    if(!secured){
                        notify_broadcast("The company went through a physical attack !! The servers were harmed. The company will suffer from this attack for a tour.\n");
                        prepare_action += 1;
                        Company_player->money-=3;
                    }
                    else{
                        notify_player(player, "The company has already secured all of its entries. You should try attacking virtually ;) \n");
                    }
                    return SUCCESS; // Card played successfully
                }
                else{
                    return FAILURE_WRONG_PLACE;
                }
                
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
        default:
            return FAILURE_CARD_NOT_PERMITTED;
    }
}