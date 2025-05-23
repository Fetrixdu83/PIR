#include "../driver/Role.h"
#include "../driver/Company.h"

int firewall_activated = 0;
int bourse = 0; // initially the company is not public
int backup = 0;
int secured_againt_physical = 0; // initially the company did not secure the physical access to its buildings
Player *employees[2] = {NULL, NULL};
Player *white_hat = NULL;
Player *Company_player = NULL;

int Company_end(Player** players, int nb_players) // Win condition of Company
{
    //wins if all black hats are dead and the if corrupted employees too
    for (int i=0; i< nb_players; i++){
        if (players[i]->Alive && players[i]->role==BH) return 0; // at least a black hat is still alive => game not finished
    } 
    //if all no black hat is alive we check if there is still a corrupted employee
    if(betray){
        // we check that the corrupted employee is alive or not (we declared a table as we plan to add the possibility to play with 2 employees : NB must add a mechanism to check which is the corrupted employee todo)
        for(int i=0; i<2; i++){ 
            if (employees[i]!=NULL){
                if(employees[i]->Alive){
                    return 0;
                }
            }
        }
    }
    return COMPANY; // No black hat is alive and neither corrupted employee  
}

Player *Company_create_player() // Create a player with the Company role
{
    Company_player = (Player *)malloc(sizeof(Player));
    Company_player->role = COMPANY;
    Company_player->money = 6;
    Company_player->played_card = NULL;
    Company_player->place = 0;
    Company_player->message = NULL; // Initialize message tab to NULL
    Company_player->Alive = ALIVE;
    return Company_player;
}

void company_add_employee(Player *employee)
{
    for (int i = 0; i < 2; i++)
    {
        if (employees[i] == NULL)
        {
            employees[i] = employee;
            break;
        }
    }
}

void save_WH_id(Player *wh)
{
    white_hat = wh;
}

void promote_employees(int ir)
{
    for (int i = 0; i < 2; i++)
    {
        if (employees[i] != NULL)
        {
            if (employees[i]->Alive)
            {
                employees[i]->money += ir;
            }
        }
    }
}

void finance_WH(int ir)
{
    if (white_hat != NULL)
    {
        if (white_hat->Alive)
        {
            white_hat->money += ir;
            char buffer[128]; // create a buffer to hold the final message
            sprintf(buffer, "You received a financement from the company for a value of %d IR\n", ir);
            notify_player(white_hat, buffer);
        }
    }
}

int Company_play(Player *player, id card, Player *target) // Play function for Company
{
    if (player->Frozen)
    {
        player->Frozen -= 1;
        notify_player(player, "You cannot play this tour, action was not considered. \n");
        return SUCCESS;
    }
    else
    {
        switch (card)
        {
        case COMMON_CARD: // Company card 0 AKA Common card
            switch (player->place)
            {
            case PLACE_BANK:
                player->money += 4 + bourse; // Gets 4 IR as investment + 2 if the company is public (bourse)
                return SUCCESS;     // Card played successfully

            case PLACE_LIBRARY:
                if (player->money >= 2)
                {                       // Check if player has enough money
                    player->money -= 2; // Lose 2 money
                    return SUCCESS;     // Card played successfully
                }
                else
                    return FAILURE_NOT_ENOUGH_MONEY;

            default:
                return FAILURE_WRONG_PLACE;
            }
        case CO_FIREWALL: // Company card 1
            if (player->money >= 6)
            {
                player->money -= (int)round(6 * (1 + betray / 3));
                ;
                firewall_activated = 1;
                return SUCCESS;
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }

        case CO_BACKUP: // Company card 2
            if (player->money >= 2)
            {
                player->money -= 2;
                if (backup)
                {
                    notify_player(player, "Your employee did prepare a backup. You are able to play\n");
                }
                else
                {
                    notify_player(player, "You will not be able to play during next tour as you will be putting the backup in place\n");
                    player->Frozen += 1;
                }
                return SUCCESS;
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }

        case CO_SECURE_BUILDING: // Company card 3
            if (player->money >= 5)
            {
                if (player->place == PLACE_COMPANY)
                {
                    player->money -= (int)round(5 * (1 + betray / 3));
                    secured_againt_physical = 1;
                    return SUCCESS;
                }
                else
                {
                    return FAILURE_WRONG_PLACE;
                }
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }
        case CO_CONFERENCE: // Company card 4
            if (player->money >= 2)
            {
                notify_broadcast("All players should show up at the company next tour! 🥁ThCon is having place🥁\n ");
                player->money -= (int)round(2 * (1 + betray / 3));
                return SUCCESS;
            }
            else
                return FAILURE_NOT_ENOUGH_MONEY;

        case CO_UNFAIR_COMPETETION: // Company card 5
            // Implement the effect of Company card 5
            return NOT_IMPLEMENTED_YET;
        case CO_GOING_PUBLIC: // Company card 6
            if (player->money >= 4)
            {
                bourse = 2;
                notify_broadcast("The Company went public.\n ");
                player->money -= (int)round(4 * (1 + betray / 3));
                return SUCCESS;
            }
            else
                return FAILURE_NOT_ENOUGH_MONEY;
        case CO_PROMOTE_EM: // Company card 7
            if (player->money >= 6)
            {
                player->money -= (int)round(6 * (1 + betray / 3));
                promote_employees(4);
                return SUCCESS;
            }
            else
            {
                return FAILURE_NOT_ENOUGH_MONEY;
            }
        case CO_FINANCE_WH: // Company card 8
            if (player->money >= 6)
            {
                player->money -= (int)round(6 * (1 + betray / 3));
                finance_WH(4);
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
}