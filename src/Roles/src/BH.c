#include "../driver/Role.h"
#include "../driver/BH.h"

int Last_played_botnet = -1;
int Nb_botnet = 0;
int phishing = 0;

int BH_end() // Win condition of BH
{
    if(Company_player->money<=0){
        Company_player->Alive = 0;
        notify_broadcast("The company lost its resources and declared bankruptcy\nThe black Hat team wins\n");
        return BH;
    }
    if (!Company_player->Alive){
        notify_broadcast("The company is dead the black team win\n");
    }
    return 0;
}

/*pas de pointeur pour le moment j'en vois pas vraiment l'utilité*/
/*En créant un joeur on renvoit son @ qui sera stocké dans un tableau de joueur*/
Player *BH_create_player() // Create a player with the BH role
{
    Player *BH_player = malloc(sizeof(Player));
    BH_player->role = BH;
    BH_player->money = 3;          // Initialize money to 0
    BH_player->played_card = NULL; // Initialize played_card to NULL
    BH_player->place = 0;          // Initialize place to 0
    BH_player->message = NULL;     // Initialize message tab to NULL
    BH_player->Alive = ALIVE;
    return BH_player;
}

int BH_play(Player *player, id card, Player *target, int current_round) // Play function for BH
{

    /**
     * -1 role not mentioned was detected => error
     * 0 card played was not permitted => effect was dropped
     * 1 the played card was considered
     */
    switch (card)
    {
    case COMMON_CARD: // BH card 0 AKA Common card
        // Implement the effect of BH Common card
        switch (player->place)
        {
        case PLACE_BANK:
            player->money += 3; // Gain 3 money
            return SUCCESS;     // Card played successfully

        case PLACE_LIBRARY:
            if (player->money >= 2)
            {                       // Check if player has enough money
                player->money -= 2; // Lose 2 money
                return SUCCESS;     // Card played successfully
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }

        default:
            return FAILURE_WRONG_PLACE;
        }

    case BH_CORRUPT: // BH card 1
        // Implement the effect of BH card 1
        if (player->money >= 2)
        {
            player->money -= 2;
            notify_player(target, "Are you interested in some big deals? Enroll in the BH team!\n");
            betray_proposal = 1; //corrupt proposal
            return SUCCESS; // Card played successfully
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the car
        }

    case BH_BOTNET: // BH card 2
        if (player->money >= 1)
        {
            player->money -= 1;
            if (Last_played_botnet != player->place)
            {
                Nb_botnet++;
                Last_played_botnet = player->place; // Update the last played botnet place
            }
            else
            {
                return FAILURE_WRONG_PLACE; // Card played in a wrong place
            }
            return SUCCESS; // Card played successfully
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
        }

    case BH_DDoS: // BH card 3
        if (player->money >= 1)
        {
            player->money -= 1;
            if (Nb_botnet > 0)
            {
                Nb_botnet--; // Decrease the number of botnets
                srand(time(NULL));
                if((rand()%60)<protect_box){
                    notify_player(player, "Oups, this attack did not succeed for an unknown reason. Maybe you should retry it another time.\n");
                    return SUCCESS;
                }
                if (target->honey_pot)
                { // a honey pot is in place
                    notify_player(player, "Oups, a honey pot was in place... the effect of this attack was dropped. Good news: the honey pot was dropped too\n");
                    target->honey_pot = 0;
                    return SUCCESS;
                }
                else
                {
                    notify_player(target, "You have been attacked by a DDoS attack!\n");
                    if (target == Company_player )
                    {
                        if(backup){
                            // the company did backup and won't be frozen
                            notify_player(target, "You did the backup, no worries ;)\n");
                        }
                        else{
                            if(firewall_activated){
                                // the company did protect itself with a firewall
                                notify_player(target, "You have a firewall. The DDoS is failing :)\n");
                            }
                            else{
                                target->Frozen += 1; // Freeze the target player for the next turn
                                notify_player(target, "You will not be able to play next round :')\n");
                            }
                        }
                        
                    }
                    else
                    {
                        target->Frozen += 1; // Freeze the target player for the next turn
                        notify_player(target, "You will not be able to play next round :')\n");
                    }
                }
            }
            else
            {
                return FAILURE_CARD_NOT_PERMITTED; // Card played in a wrong place
            }
            return SUCCESS; // Card played successfully
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
        }

    case BH_BRUTE_FORCE: // BH card 4
        if (player->money >= 1 && current_round > 1)
        {
            player->money -= 1;
            srand(time(NULL));
            if((rand()%60)<protect_box){
                notify_player(player, "Oups, this attack did not succeed for an unknown reason. Maybe you should retry it another time.\n");
                return SUCCESS;
            }
            if (secured_passwords)
            {
                player->Frozen += 3; // Freeze the player for 3 turns if the company is protected
                notify_player(player, "You are making a brute force attack, there might be a result in some tours.\n");
            }
            else
            {
                player->Frozen += 2; // Freeze the player for 2 turns if the company is not protected
                Company_player->money -= (int)round((10 * (1 + betray / 3))/(1+firewall_activated));
                player->money += 10/(1+firewall_activated);
                if(firewall_activated){
                    notify_player(Company_player, "The brute force attack made you lose only 5 IR as you have a firewall\n");
                    notify_player(player, "You are making a brute force attack, unfortunately the company has a firewall, but you are still going to win 5 IR.\n");
                }else{
                    notify_player(Company_player, "The brute force attack made you lose 10 IR\n");
                    notify_player(player, "You are making a brute force attack, there is no defense, you are going to win 10 IR.\n");
                }
                
            }
            notify_broadcast("The company is being attacked by a brute force. This attack may slow down its functionning which may lead to a money loss\n");

            return SUCCESS; // Card played successfully
        }
        else if (current_round == 1)
        {
            return FAILURE_CARD_NOT_PERMITTED; // Card not playable in the first round
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
        }

    case BH_PHISHING: // BH card 5
        // Implement the effect of BH card 5
        if (player->money >= 2)
        {
            player->money -= 2;
            notify_player(target, "Hello Sir, \nFor your account security, please update your password regularly, \nplease click on the following link and change your password, thank you for your cooperation.\n https://www.google.com/search?q=phishing+attack+link&rlz=1C1GCEU_enFR1010FR1010&oq=phishing+attack+link&aqs=chrome..69i57j0i512l9.10345j0j7&sourceid=chrome&ie=UTF-8\n");
            phishing = 1;
            // il manque du mecanisme pour verifier la reussite de l'attaque

            return SUCCESS; // Card played successfully
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
        }

    case BH_SQL_INJECTION: // BH card 6
        // Implement the effect of BH card 6
        if (player->money >= 3)
        {
            player->money -= 3;
            srand(time(NULL));
            if((rand()%60)<protect_box){
                notify_player(player, "Oups, this attack did not succeed for an unknown reason. Maybe you should retry it another time.\n");
                return SUCCESS;
            }
            if (Company_player->honey_pot)
            {
                notify_player(player, "Oups, a honey pot was in place... the effect of this attack was dropped. Good news: the honey pot was dropped too\n");
                Company_player->honey_pot = 0;
                return SUCCESS;
            }
            else
            {
                if (awared_developers)
                {
                    player->money += 2; // Gain 2 money if the Company is protected
                }
                else
                {
                    player->money += 4; // Gain 4 money if the Company is not protected
                }
                return SUCCESS; // Card played successfully
            }
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
        }

    case BH_XSS:
        if (player->money >= 4)
        {
            player->money -= 4;
            srand(time(NULL));
            if((rand()%60)<protect_box){
                notify_player(player, "Oups, this attack did not succeed for an unknown reason. Maybe you should retry it another time.\n");
                return SUCCESS;
            }
            if (Company_player->honey_pot)
            {
                notify_player(player, "Oups, a honey pot was in place... the effect of this attack was dropped. Good news: the honey pot was dropped too\n");
                Company_player->honey_pot = 0;
                return SUCCESS;
            }
            else
            {
                if (secured_XSS)
                {
                    player->money += 3; // Gain 3 money if the target is protected
                    Company_player->money -= (int)round((3* (1 + betray / 3)) / (1+firewall_activated));
                }
                else
                {
                    player->money += 6/(1+firewall_activated); // Gain 6 money if the target is not protected
                    Company_player->money -= (int)round((6 * (1 + betray / 3))/(1+firewall_activated));
                }
                notify_player(Company_player, "You were attacked by an XSS attack !! \n");
                return SUCCESS;
            }
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }

    case BH_PHYSICAL_ATTACK: // BH card 8
        if (player->money >= 3)
        {
            if (player->place == PLACE_COMPANY)
            {
                player->money -= 3;
                if (!secured_againt_physical)
                {
                    notify_broadcast("The company went through a physical attack !! The servers were harmed. The company will suffer from this attack for a tour.\n");
                    Company_player->Frozen += 1;
                    Company_player->money -= (int)round(3 * (1 + betray / 3));
                    ;
                }
                else
                {
                    notify_player(player, "The company has already secured all of its entries. You should try attacking virtually ;) \n");
                }
                return SUCCESS; // Card played successfully
            }
            else
            {
                return FAILURE_WRONG_PLACE;
            }
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY; // Not enough money to play the card
        }
    default:
        return FAILURE_CARD_NOT_PERMITTED;
    }
}