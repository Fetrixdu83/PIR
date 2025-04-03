#ifndef BH_H
#define BH_H

#include "Role.h"

#define BH_CORRUPT                 0x11
#define BH_BOTNET                  0x12
#define BH_DDoS                    0x13
#define BH_BRUTE_FORCE             0x14
#define BH_PHISHING                0x15
#define BH_SQL_INJECTION           0x16
#define BH_XSS                     0x17
#define BH_PHYSICAL_ATTACK         0x18

Player* BH_create_player();
void BH_play(Player* player, id card, char target);
int BH_end();


#endif