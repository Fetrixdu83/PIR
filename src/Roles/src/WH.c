#include "../driver/Role.h"
#include "../driver/WH.h"

// initially no security is in place
int protect_box = 0;
int secured_XSS = 0;
int awared_developers = 0;
int vpn = 0; // no vpn in place at the beginning some actions should be played at a specified place

int WH_end() // Win condition of WH
{
    return 0;
}

/*pas de pointeur pour le moment j'en vois pas vraiment l'utilité*/
Player *WH_create_player() // Create a player with the WH role
{
    Player *WH_player = (Player *)malloc(sizeof(Player));
    WH_player->role = WH;
    WH_player->money = 3;
    WH_player->played_card = NULL;
    WH_player->place = 0;
    WH_player->message = NULL; // Initialize message tab to NULL
    WH_player->Alive = ALIVE;
    return WH_player;
}

int WH_play(Player *player, id card, Player *target) // Play function for WH
{
    switch (card)
    {
    case COMMON_CARD:
        switch (player->place)
        {
        case PLACE_BANK:
            player->money += 2; // Gain 2 IR
            return SUCCESS;     // Card played successfully

        case PLACE_LIBRARY:
            if (player->money >= 2)
            { // Check if player has enough money
                player->money -= 2;
                return SUCCESS; // Card played successfully
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }

        default:
            return FAILURE_WRONG_PLACE;
        }
    case WH_BLACK_BOX:
        if (player->money >= 1)
        {
            protect_box = 12; // 12 out of 60 <=> 1 out of 5
            return SUCCESS;
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }

    case WH_GREY_BOX:
        if (player->money >= 2)
        {
            protect_box = 15; // 15 out of 60 <=> 1 out of 4 chances
            return SUCCESS;
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }
    case WH_WHITE_BOX:
        if (player->money >= 3)
        {
            protect_box = 20; // 20 out of 60 <=> 1 out of 3 to the protection to take place
            return SUCCESS;
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }
    case WH_SELF_HONEY_POT:
        if (player->money >= 1)
        {
            player->honey_pot = 1;
            return SUCCESS;
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }
    case WH_PLACED_HONEY_POT:
        if (vpn || player->place == PLACE_COMPANY)
        {
            if (player->money >= 2)
            {
                target->honey_pot = 2;
                return SUCCESS;
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }
        }else{
            notify_player(player, "You are not able to play this card here (consider going to the company or using a vpn ;)\n");
            return FAILURE_WRONG_PLACE;
        }

    case WH_VPN:
        if (player->money >= 1)
        {
            notify_player(player, "You are using a VPN. All your specific actions can now be played anywhere in the world as your conversations will be encrypted. Check different types of encryptions here : https://www.fortinet.com/resources/cyberglossary/encryption \n");
            vpn = 1;
            return SUCCESS;
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }
        

    case WH_UPGRADE:
    if (vpn || player->place == PLACE_COMPANY)
        {
        if (player->money >= 4)
        {
            player->money -= 4;
            secured_XSS = NB_TOURS_NECESSARY_FOR_UPGRADE;
            notify_player(player, "Well done, you have upgraded the systems. Remember to do this regularly as new vulnerabilities may appear. Keep up to date with the CVE (Common Vulnerabilities and Exposures) organization (https://cve.org) ;)\n");
            return SUCCESS;
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }
        }else{
            notify_player(player, "You are not able to play this card here (consider going to the company or using a vpn ;)\n");
            return FAILURE_WRONG_PLACE;
        }
    case WH_TRAINING:
        if (player->money >= 3)
        {
            player->money -= 3;
            awared_developers = 1;
            return SUCCESS;
        }
        else
        {
            return FAILURE_NOT_ENOUGH_MONEY;
        }
    default:
        return FAILURE_CARD_NOT_PERMITTED;
    }
}