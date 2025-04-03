#ifndef COMPANY_H
#define COMPANY_H

#include "Role.h"

#define CO_FIREWALL                 0x31
#define CO_BACKUP                   0x32
#define CO_SECURE_BUILDING          0x33
#define CO_CONFERENCE               0x34
#define CO_UNFAIR_COMPETETION       0x35
#define CO_                         0x36
#define CO_PROMOTE_EM               0x37
#define CO_FINANCE_WH               0x38

Player* Company_create_player();
int Company_play(Player* player, id card, char target);
int Company_end();

#endif