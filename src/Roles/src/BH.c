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
}


int BH_play(Player* player, id card, Player* target,int current_round) //Play function for BH
{
    
    /**
     * -1 role not mentioned was detected => error
     * 0 card played was not permitted => effect was dropped 
     * 1 the played card was considered
     */
    switch(card){
        case COMMON_CARD: // BH card 0 AKA Common card
            // Implement the effect of BH Common card
            switch (player->place):
                case PLACE_BANK:
                    player->money += 3; // Gain 3 money
                    return SUCCESS; // Card played successfully
                    break;
                case PLACE_CYPERCAFE:
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
            // Implement the effect of BH card 1
            if(player->money >= 2){
                player->money -= 2; 
                notify_player(target, "Are you interested in some big deals? Enroll in the BH team!");
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the car
            }    
            break; 
        case BH_BOTNET: // BH card 2
            // Implement the effect of BH card 2
            if(player->money >= 1){
                player->money -= 1;
                if( Last_played_botnet != player->place){
                    Nb_botnet++;
                    Last_played_botnet = player->place; // Update the last played botnet place
                }else{
                    return FAILURE_WRONG_PLACE; // Card played in a wrong place
                }
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_DDoS: // BH card 3
            // Implement the effect of BH card 3
            if(player->money >= 1){
                player->money -= 1; 
                if(Nb_botnet > 0){
                    Nb_botnet--;// Decrease the number of botnets
                    notify_player(target, "You have been attacked by a DDoS attack!");
                    target->Frozen += 1; // Freeze the target player for the next turn
                }else{
                    return FAILURE_WRONG_PLACE; // Card played in a wrong place
                }
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break; 
        case BH_BRUTE_FORCE: // BH card 4    
            // Implement the effect of BH card 4
            if(player->money >= 1 && current_round > 1){
                player->money -= 1; 
                if(taget->protectd == 1){
                    player->Frozen = 3;// Freeze the player for 3 turns if the company is protected
                }else{
                    player->Frozen = 2; // Freeze the player for 2 turns if the company is not protected
                }
                
                // il manque le mecanisme de la verification de la reussite de l'attaque
                
                return SUCCESS_BROADCAST; // Card played successfully
            }else if(current_round == 1){
                return FAILURE_CARD_NOT_PLAYABLE; // Card not playable in the first round
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_PHISHING: // BH card 5
            // Implement the effect of BH card 5
            if(player->money >= 2){
                player->money -= 2; 
                notify_player(target, "Hello Sir, 
                                        For your account security, please update your password regularly, 
                                        please click on the following link and change your password, thank you for your cooperation.\n
                                        https://www.google.com/search?q=phishing+attack+link&rlz=1C1GCEU_enFR1010FR1010&oq=phishing+attack+link&aqs=chrome..69i57j0i512l9.10345j0j7&sourceid=chrome&ie=UTF-8\n");
                
                //il manque du mecanisme pour verifier la reussite de l'attaque
                
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;    
        case BH_SQL_INJECTION: // BH card 6    
            // Implement the effect of BH card 6
            if(player->money >= 3){
                player->money -= 3; 
                if(target->protectd == 1){
                    player->money += 2;// Gain 2 money if the target is protected
                }else{
                    player->money += 3; // Gain 3 money if the target is not protected
                }
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;   
        case BH_XSS: // BH card 7    
            // Implement the effect of BH card 7
            if(player->money >= 4){
                player->money -= 4; 
                if(target->protectd == 1){
                    player->money += 3;// Gain 2 money if the target is protected
                }else{
                    player->money += 6; // Gain 3 money if the target is not protected
                }
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        case BH_PHYSICAL_ATTACK: // BH card 8
            // Implement the effect of BH card 8
            if(player->money >= 3){
                player->money -= 3; 
                return SUCCESS; // Card played successfully
            }else{
                return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
            
            } 
            break;
        default:
            return -1;
            break;
    }
}