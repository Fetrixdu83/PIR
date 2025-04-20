#include "../driver/Role.h"

Message* message_global = NULL; // Global message list

int end(Player** players)
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
            Player* wh = WH_create_player();
            save_WH_id(wh);
            return wh;
        case COMPANY:
            return Company_create_player();
        case EMPLOYEE:
            Player* employee = Employee_create_player();
            company_add_employee(employee);
            return employee;
        default:
            return NULL;
    }
}

Player* init_player(int id){
    printf("Please input the code of a special card for the player n: %x.\n", id+1);
    int card;
    scanf("%x", &card);
    Player* player = create_player(card);
    player->num = id;
    
    if (player==NULL) {
        printf("Error during initialisation.\n");
        printf("The code %x does not correspond to any special card.\n", card);
        return init_player(id);
    }

    switch(player->role){
        case BH:
            printf("Initialisation Black Hat...\n");
            return player;
        case WH:
            printf("Initialisation White Hat...\n");
            return player;
        case COMPANY:
            printf("Initialisation company...\n");
            return player;
        case EMPLOYEE:
            printf("Initialisation employee...\n");
            return player;
        default:
            printf("No role has been recognized.\n");
            return NULL;
    }
}

int play(Player* player, id card, char target)
{
    /**
     * -2 card not matching the role of the player
     * -1 role or card not matching this version of the game was detected => error
     * 0 card played was not permitted => effect to be discussed
     * 1 the played card was considered
     * 2 card cannot be played at this place
     * 3 player does not have enough money
     */
    if(card!=COMMON_CARD && player->role!=(card>>CARD_BITS)){
        // card not common and does not correspond to the role of its player
        return FAILURE_CARD_NOT_MATCHING_PLAYER;
    }
    switch(player->role)
    {
        case BH:
            return BH_play(player, card, target);
        case WH:
            return WH_play(player, card, target);
        case COMPANY:
            return Company_play(player, card, target);
        case EMPLOYEE:
            return Employee_play(player, card, target);
        default:
            return FAILURE_CARD_NOT_MATCHING_GAME_VERSION;
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