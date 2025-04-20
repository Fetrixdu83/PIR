#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Role.h"
#include <math.h>

#define EM_OPEN_MAIL                0x41
#define EM_MEETING                  0x42
#define EM_PRINT                    0x43
#define EM_BREAK                    0x44
#define EM_PWD_TRAINING             0x45
#define EM_PHISHING_TRAINING        0x46
#define EM_PREPARE_BACKUP           0x47
#define EM_BACKDOOR                 0x48

extern int betray;

Player* Employee_create_player();
int Employee_play(Player* player, id card, Player* target);
int Employee_end();

#endif