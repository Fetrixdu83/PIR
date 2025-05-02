#include "../driver/Role.h"

Message *message_global = NULL; // Global message list

int end(Player **players, int nb_players)
{
    if(BH_end()) {return BH;}// Black team wins
    else {
        return Company_end(players, nb_players); // returns COMPANY if the end condition for company is satisfied, 0 otherwise
    }
    
}

Player *create_player(id carte) // si le format RFID est sur 32 BIT
{
    Player *player = NULL;
    switch (carte >> CARD_BITS) // On ne garde que les bits spécifiques au role
    {
    case BH:
        return BH_create_player();
    case WH:
        player = WH_create_player();
        save_WH_id(player);
        return player;
    case COMPANY:
        return Company_create_player();
    case EMPLOYEE:
        player = Employee_create_player();
        company_add_employee(player);
        return player;
    default:
        return NULL;
    }
}

Player *init_player(int id)
{
    printf("\nPlease input the code of a specific card for the player n: %x.\n", id + 1);
    int card;
    scanf("%x", &card);
    Player *player = create_player(card);
    player->num = id;
    player->honey_pot = 0; //initially no honey pot is put

    if (player == NULL)
    {
        printf("Error during initialisation.\n");
        printf("The code %x does not correspond to any special card.\n", card);
        return init_player(id);
    }

    switch (player->role)
    {
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

int play(Player *player, id card, Player *target, int current_round) // Play function for all players
{
    /**
     * -2 card not matching the role of the player
     * -1 role or card not matching this version of the game was detected => error
     * 0 card played was not permitted => effect to be discussed
     * 1 the played card was considered
     * 2 card cannot be played at this place
     * 3 player does not have enough money
     * 4 player is frozen
     * 5 card was not iplemented for the moment
     */

    if(player->Frozen){
        notify_player(player, "You are frozen during this tour. :') \n");
        player->Frozen--;
        return FROZEN;
    }
    if (card != COMMON_CARD && player->role != (card >> CARD_BITS))
    {
        // card not common and does not correspond to the role of its player
        return FAILURE_CARD_NOT_MATCHING_PLAYER;
    }
    switch (player->role)
    {
    case BH:
        return BH_play(player, card, target, current_round);
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

void notify_broadcast(char *message)
{
    Message *new_message = malloc(sizeof(Message));

    if (new_message == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    new_message->message = malloc(strlen(message) + 1); // +1 for the '\0'
    strcpy(new_message->message, message);
    new_message->next = NULL;

    if (message_global == NULL)
    {
        message_global = new_message;
    }
    else
    {
        Message *current = message_global;
        while (current != NULL && current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_message;
    }
}

void notify_player(Player *player, char *message)
{
    Message *new_message = malloc(sizeof(Message));

    if (new_message == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    new_message->message = malloc(strlen(message) + 1);
    if (new_message->message == NULL)
    {
        printf("Memory allocation for message failed\n");
        free(new_message);
        return;
    }
    strcpy(new_message->message, message);
    new_message->next = NULL;
    if (player->message == NULL)
    {
        player->message = new_message;
    }
    else
    {
        Message *current = player->message;
        while (current != NULL && current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_message;
    }
}

void print_message(Player **players, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        if (players[i]->Alive)
        {
            Message *current = players[i]->message;
            const char *role = NULL;
            switch (players[i]->role)
            {
            case BH:
                role = "Black hat";
                break;
            case WH:
                role = "White hat";
                break;
            case COMPANY:
                role = "company";
                break;
            case EMPLOYEE:
                role = "employee";
                break;
            }
            printf("Messages for the  %d: ( Roles : %s)  \n", (players[i]->num)+1, role);
            printf("IR: %d\n", players[i]->money);
            while (current != NULL)
            {
                Message *to_free = current; // Store the message to free later
                printf("%s\n", current->message);
                current = current->next;
                free(to_free->message);
                free(to_free);
            }
            players[i]->message = NULL;
            printf("\n");
        }
    }
}

void print_global_messages()
{
    // print les messages globaux
    Message *current = message_global;
    printf("\n The company has %d IR.\n", Company_player->money);
    while (current != NULL)
    {
        Message *to_free = current; // Store the message to free later
        printf("%s\n", current->message);
        current = current->next;
        free(to_free->message);
        free(to_free);
    }
    message_global = NULL; 
}