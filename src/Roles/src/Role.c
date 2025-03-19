#include "../driver/Role.h"

int end()
{
    return BH_end() || 
           WH_end() ||
           Company_end() ||
           Employee_end();
}

Player* create_player(char role, id carte)
{
    switch(role)
    {
        case BH:
            return BH_create_player(carte);
        case WH:
            return WH_create_player(carte);
        case COMPANY:
            return Company_create_player(carte);
        case EMPLOYEE:
            return Employee_create_player(carte);
        default:
            return NULL;
    }
}

void play(Player* player, id card, char target)
{
    switch(player->role)
    {
        case BH:
            BH_play(player, card, target);
            break;
        case WH:
            WH_play(player, card, target);
            break;
        case COMPANY:
            Company_play(player, card, target);
            break;
        case EMPLOYEE:
            Employee_play(player, card, target);
            break;
        default:
            break;
    }
}