#include "../driver/Role.h"
#include "../driver/Employee.h"

int common_card_price = 2; // picking a card costs 2 unless the player plays  the meeting then only costs 1
int printing_upgrading = 1; // initially 1 then takes +1 each time the card is played
int rest = 0; // initially 0 , after taking a break becomes 1
int password_training = 0; // initially false
int betray = 0; // an int to describe if a proposal of betrayal is available

int Employee_end() // Win condition of Employee
{
    return 0;
}

/*pas de pointeur pour le moment j'en vois pas vraiment l'utilité*/
Player *Employee_create_player() // Create a player with the Employee role
{
    Player *Employee_player = (Player *)malloc(sizeof(Player));
    Employee_player->role = EMPLOYEE;
    Employee_player->money = 3;
    Employee_player->played_card = NULL;
    Employee_player->place = 0;
    Employee_player->message = NULL; // Initialize message tab to NULL
    Employee_player->Alive = ALIVE;
    return Employee_player;
}

int Employee_play(Player *player, id card, Player *target) // Play function for Employee
{
    if (password_training){
        password_training--;
        if (!password_training){
            secured = 1;
        }
    }
    switch (card)
    {
    case COMMON_CARD: 
        switch (player->place)
        {
        case PLACE_BANK:
            player->money += 2 + rest; // Gain 2 IR
            return SUCCESS;     // Card played successfully

        case PLACE_LIBRARY:
            if (player->money >= common_card_price)
            {                       // Check if player has enough money
                player->money -= common_card_price; 
                common_card_price = 2;
                return SUCCESS;     // Card played successfully
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }

        default:
            return FAILURE_WRONG_PLACE;
        }
    case EM_OPEN_MAIL: // Employee card 1
        if (phishing){
            Company_player->money -=  (int)round((4 - rest) * (1+betray/3));
            rest = 0;
            notify_player(player, "You have been phished :') \n");
            notify_player(Company_player, "Your company was phished, you are losing money...\n You should have done some trainings... Think about it before it is too late\n");

        }
        else {
            player->money += 2+ rest;
            Company_player -> money += 2+ rest;
            rest = 0;
        }
        return SUCCESS;
    case EM_MEETING: // Employee card 2
        if (player->place == PLACE_COMPANY){
            common_card_price = 1;
            notify_player(player, "Next drawn card will only cost you one\n");
            return SUCCESS;
        }else{
            return FAILURE_WRONG_PLACE;
        }
    case EM_PRINT: 
        if (player->place == PLACE_COMPANY){
            Company_player->money +=printing_upgrading+ rest;
            printing_upgrading += 1;
            rest = 0;
            notify_player(player, "You have reported more money to your company.\n");
            return SUCCESS;
        }else{
            return FAILURE_WRONG_PLACE;
        }
    case EM_BREAK: // Employee card 4
        if (player->place == PLACE_COMPANY){
            rest = 1;
            return SUCCESS;
        }else{
            return FAILURE_WRONG_PLACE;
        }
    case EM_PWD_TRAINING:
        if (player->money>=5){
            player->money -= 5 - rest;
            notify_player(player, "The effect of this card will take place in 2 tours. You are still able to play next time.\n");
            password_training = 2;
            return SUCCESS;
        } else{
            return FAILURE_NOT_ENOUGH_MONEY;
        }

    case EM_PREPARE_BACKUP: 
        if (player -> place == PLACE_COMPANY){
            if (player->money >=3){
                player->money-= 3 - rest;
                backup = 1;
                notify_player(Company_player, "The employee prepared a backup ;) \n");
                notify_player(player, "Backup in place, the company was informed. Great Work! \n");
                return SUCCESS;
            }
        }else {
            return FAILURE_WRONG_PLACE;
        }
    case EM_PHISHING_TRAINING: 
        if(player->money>=5){
            player->money -= 5-rest;
            phishing = 0;
            notify_player(player, "You are no longer sensible to phishing techniques. Be aware, new phishing techniques may appear in the future!.\n");
            return SUCCESS;
        }else{
            return FAILURE_NOT_ENOUGH_MONEY;
        }
    case EM_BACKDOOR:
        if (betray){
            if(player->place == PLACE_COMPANY){
                if (player->money>=3){
                    player->money -=3-rest;
                    notify_player(player, "You made a backdoor, this is gonne make the company lose a lot of money. Now you win with the BH.\n");
                    //todo discuss if the black hat will know if the employee betrayed the company or not
                    return SUCCESS;
                }else{
                    return FAILURE_NOT_ENOUGH_MONEY;
                }
            }else{
                return FAILURE_WRONG_PLACE;
            }
        }else{
            notify_player(player, "You cannot do this card without a proposal of the BH. try to make him a sign he could offer you something;)\n");
            return FAILURE_CARD_NOT_PERMITTED;
        }
    }
}