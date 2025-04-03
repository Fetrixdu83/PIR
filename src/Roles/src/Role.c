#include "../driver/Role.h"

Message* message_global = NULL; // Global message list

int end()
{
    return BH_end() || 
           WH_end() ||
           Company_end() ||
           Employee_end();
}

Player* create_player(id carte)//si le format RFID est sur 32 BIT
{
    switch(carte >> CARD_BITS) // On ne garde que les bits spécifiques au role
    {
        case BH:
            return BH_create_player();
        case WH:
            return WH_create_player();
        case COMPANY:
            return Company_create_player();
        case EMPLOYEE:
            return Employee_create_player();
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

void notify_broadcast(char message[255])
{
    Message* new_message = malloc(sizeof(Message));
    
    if (new_message == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(new_message->message, message);
    new_message->next = NULL;
    if (message_global == NULL) {
        message_global = new_message;
    }
    else
    {
        Message* current = message_global;
        while (current != NULL && current->next != NULL) {
            current = current->next;
        }
        current->next = new_message;
    }
}

void notify_player(Player* player, char message[255])
{
    Message* new_message = malloc(sizeof(Message));
    
    if (new_message == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(new_message->message, message);
    new_message->next = NULL;
    if (player->message == NULL) {
        player->message = new_message;
    }
    else
    {
        Message* current = player->message;
        while (current != NULL && current->next != NULL) {
            current = current->next;
        }
        current->next = new_message;
    }
}

void print_message(Player** players, int nb_players)
{
    //print pour tout les joueurs
    for(int i = 0; i < nb_players; i++) {
        Message* current = players[i]->message;
        printf("Messages for the  %d: ( Roles : %d) \n", players[i]->num, players[i]->role);
        while (current != NULL){
            Message* to_free = current; // Store the message to free later
            printf("%s\n", current->message);
            current = current->next;
            free(to_free);
        }
    }
    //print les messages globaux
    Message* current = message_global;
    printf("Messages globaux:\n");
    while (current != NULL) {
        Message* to_free = current; // Store the message to free later
        printf("%s\n", current->message);
        current = current->next;
        free(to_free);
    }
}