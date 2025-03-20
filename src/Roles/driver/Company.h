#ifndef COMPANY_H
#define COMPANY_H

Player Company_create_player();
void Company_play(Player* player, id card, char target);
int Company_end();

#endif