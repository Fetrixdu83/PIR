#include "../driver/Role.h"
#include "../driver/WH.h"

int protect_box = 0;

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
    return NOT_IMPLEMENTED_YET;
    switch (card)
    {
    case COMMON_CARD:
        switch (player->place)
        {
        case PLACE_BANK:
            player->money += 2 ; // Gain 2 IR
            return SUCCESS;            // Card played successfully

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
    case WH_BLACK_BOX: // WH card 1
        // Implement the effect of WH card 1
        break;
    case WH_GREY_BOX: // WH card 2
        // Implement the effect of WH card 2
        break;
    case WH_WHITE_BOX: // WH card 3
        // Implement the effect of WH card 3
        break;
    case WH_SELF_HONEY_POT: // WH card 4
        // Implement the effect of WH card 4
        break;
    case WH_PLACED_HONEY_POT: // WH card 5
        // Implement the effect of WH card 5
        break;
    case WH_VPN: // WH card 6
        // Implement the effect of WH card 6
        break;
    case WH_UPGRADE: // WH card 7
        // Implement the effect of WH card 7
        break;
    case WH_TRAINING: // WH card 8
        // Implement the effect of WH card 8
        break;
    }
}