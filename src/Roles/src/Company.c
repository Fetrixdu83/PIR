#include "../driver/Role.h"
#include "../driver/Company.h"

int firewall_activated = 0;
int backup = 0;
int prepare_action = 0; // this int represents the number of tour the action selected takes
int secured = 0; // initially the company did not secure the physical access to its buildings
Player* employees[2] = {NULL, NULL};
Player* white_hat = NULL;

int Company_end() //Win condition of Company
{
    return 0;
}

Player* Company_create_player() //Create a player with the Company role
{
    Player* Company_player = (Player*) malloc(sizeof(Player));
    Company_player->role = COMPANY;
    Company_player->money = 6; 
    Company_player->played_card = NULL; 
    Company_player->place = 0; 
    Company_player->message = NULL; // Initialize message tab to NULL
    Company_player->Alive = ALIVE;
    return Company_player;
}

void company_add_employee(Player* employee){
    for(int i=0; i<2; i++){
        if (employees[i]==NULL){
            employees[i] = employee;
            break;
        }
    }
}

void save_WH_id(Player* wh){
    white_hat = wh;
}

void promote_employees(int ir){
    for (int i=0; i<2; i++){
        if(employees[i]!=NULL ){
            if(employees[i]->Alive){
                employees[i]->money+=ir;
            }
        }
    }
}

void finance_WH(int ir){
    if(white_hat!=NULL){
        if (white_hat->Alive){
            white_hat->money+=ir;
            notify_player(white_hat, "You received a financement from the company for a value of %d IR\n", ir);
        }
    }
}



int Company_play(Player* player, id card, char target) //Play function for Company
{
    if (prepare_action){
        prepare_action-=1;
        notify_player(player, "You cannot play this tour, action was not considered. \n");
    }
    else{
        switch(card){
        case COMMON_CARD: // Company card 0 AKA Common card
            switch (player->place){
                case PLACE_BANK:
                    player->money += 4; // Gets 4 IR as investment
                    return SUCCESS; // Card played successfully

                case PLACE_LIBRARY:
                    if(player->money >= 2){ // Check if player has enough money
                        player->money -= 2; // Lose 2 money
                        return SUCCESS; // Card played successfully
                    }
                    else
                        return FAILURE_NOT_ENOUGH_MONEY; 

                default :
                    return FAILURE_WRONG_PLACE; 
            }
        case CO_FIREWALL: // Company card 1
            if (player->money>=6){
                player->money -= 6;
                firewall_activated = 1;
                return SUCCESS;
            }
            else{
                return FAILURE_NOT_ENOUGH_MONEY;
            }

        case CO_BACKUP: // Company card 2
            if (player->money>=2){
                player->money-=2;
                if (backup){
                    notify_player(player, "Your employee did prepare a backup. You are able to play\n");
                }else{
                    notify_player(player, "You will not be able to play during next tour as you will be putting the backup in place\n");
                    prepare_action = 1;
                }
                return SUCCESS;
            }
            else {
                return FAILURE_NOT_ENOUGH_MONEY;
            }

        case CO_SECURE_BUILDING: // Company card 3
            if (player->money>=5){
                if (player->place == PLACE_COMPANY){
                    player->money-=5;
                    secured = 1;
                    return SUCCESS;
                }
                else{
                    return FAILURE_WRONG_PLACE;
                }
            }
            else{
                return FAILURE_NOT_ENOUGH_MONEY;
            }
        case CO_CONFERENCE: // Company card 4    
            if (player->money>=2){
                notify_broadcast("All players should show up at the company next tour! 🥁ThCon is having place🥁\n ");
                player->money-=2;
            }

        case CO_UNFAIR_COMPETETION: // Company card 5
            // Implement the effect of Company card 5
            return NOT_IMPLEMENTED_YET;
            break;
        case CO_: // Company card 6    
            // Implement the effect of Company card 6
            return NOT_IMPLEMENTED_YET;
            break;
        case CO_PROMOTE_EM: // Company card 7    
            if (player->money>=6){
                player->money-=6;
                promote_employees(4);
                return SUCCESS;
            }
            else{
                return FAILURE_NOT_ENOUGH_MONEY;
            }
        case CO_FINANCE_WH: // Company card 8
            if (player->money>=6){
                player->money-=6;
                finance_WH(4);
                return SUCCESS;
            }
            else{
                return FAILURE_NOT_ENOUGH_MONEY;
            }
    }
    }
    
}