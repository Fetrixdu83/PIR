#ifndef WH_H
#define WH_H

#include "Role.h"

#define WH_BLACK_BOX                0x21
#define WH_GREY_BOX                 0x22
#define WH_WHITE_BOX                0x23
#define WH_SELF_HONEY_POT           0x24
#define WH_PLACED_HONEY_POT         0x25
#define WH_VPN                      0x26
#define WH_UPGRADE                  0x27
#define WH_TRAINING                 0x28

Player* WH_create_player();
void WH_play(Player* player, id card, char target);
int WH_end();

#endif