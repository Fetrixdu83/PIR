#include "../driver/Game.h"
#include "../driver/Role.h"

Game *init_game(int nb_players)
{
    Game *game = malloc(sizeof(Game));

    // start turn counter to 0 (game hasn't started yet)
    game->elapsed_turns = 0;

    // create the player list
    Player **players = malloc(nb_players * sizeof(Player *));
    for (int i = 0; i < nb_players; i++)
    {
        players[i] = init_player(i);
        players[i]->num = i;
        players[i]->piece = i;
        players[i]->Frozen = 0; // Initialize Frozen to 0 (not frozen)
    }
    game->players = players;
    game->nb_players = nb_players;

    return game;
}

void play_cards(Game *game)
{
    int card;
    int target;

    for (int i = 0; i < game->nb_players; i++)
    {
        if (game->players[i]->Alive)
        {
            printf("May the player number %d insert the card id, his position and the target\n", i + 1);
            scanf("%x %i %d", &card, &(game->players[i]->place), &target);
            printf("card: %x position  %d et target %d\n", card, game->players[i]->place, target);
            switch (play(game->players[i], card, game->players[target - 1], game->elapsed_turns - 1))
            {
            case FAILURE_CARD_NOT_MATCHING_PLAYER:
                // card not matching the role of the player => error or replay to be discussed
                printf("\n\n player not matching the card to be discussed\n\n");
                break;
            case FAILURE_CARD_NOT_MATCHING_GAME_VERSION:
                // role not mentioned was detected => error
                printf("ERROR : [40] please take contact with the game devellopers informing the error id \n");
                exit(1);
                break;
            case FAILURE_NOT_ENOUGH_MONEY:
                // card played requests more money => effect was dropped
                printf("\n\nThis card requests more money than what the player owns => dropped\n\n");
                break;
            case FAILURE_WRONG_PLACE:
                // card played request player to be at a place where he is not => effect was drpped
                printf("\n\nThis card requests the player to be at a certain place => dropped\n\n");

                break;

            case SUCCESS:
                // the played card was considered
                break;
            case NOT_IMPLEMENTED_YET:
                printf("not implemented yet\n");
                break;
            case FROZEN:
                printf("This player is frozen, he can't play so the action is going to be dropped\n");
                break;
            case FAILURE_CARD_NOT_PERMITTED:
                printf("Card not permitted please check that it corresponds to your role and is a Card\n");
            default:
                // default case not recongnized
                printf("ERROR : [58] please take contact with the game devellopers informing the error id \n");
                exit(1);
                break;
            }
        }
    }
    if (secured_XSS){
        // Upgrading system is necessary over the time
        secured_XSS--;
    }
    game->elapsed_turns++;
}

void eliminate_player(Game *game, Player *player)
{
    if (player != NULL)
    {
        player->Alive = !ALIVE;
        const char *role_str = ""; // <-- initialize properly

        switch (player->role)
        {
        case BH:
            role_str = " black hat";
            break;
        case WH:
            role_str = " white hat";
            break;
        case COMPANY:
            role_str = " company";
            break;
        case EMPLOYEE:
            role_str = "n employee";
            break;
        }

        printf("Player number %d was a%s. (S)He had %d IR.\n", (player->num) + 1, role_str, player->money);
    }
    else
    {
        printf("You chose to skip the voting for this tour.\n\n");
    }
}

int end_game(Game *game)
{
    /**
     * Retruns 0 if the game is not finished
     * -1 if a draw
     * the int representing the Winner role
     */
    if (game->elapsed_turns > MAX_TURNS)
    {
        if (white_hat->Alive){
            return WH; 
        }
        return -1;
    }
    else
    {
        return end(game->players, game->nb_players);
    }
}