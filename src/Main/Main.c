//Inculde the header file
//Include the header file
#include "../Roles/driver/Role.h"
#include "../RFID/RFID.h"

int main(int argc, char *argv[])
{
    Player player[4];
    init_game(4); // Initialize the game with 4 players
    while (1)
    {
        
    }

    return 0;
}



void init_game(int nb_players)
{
    int i = 0;
    while (i < nb_players)
    {
        //fonction qui raise un flag (que je vais nommé CD) quand un carte est detectee et return son id
        int card = card_detected();
        if(CD = 1){
            create_player(card);
            CD = 0; // Reset the flag after creating the player
        }
    }
}

int main(int argc, char *argv[])
{
    Player player[4];
    init_game(4); // Initialize the game with 4 players
    while (1)
    {
        
    }

    return 0;
}