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
void company_add_employee(Player* employee);
void promote_employees(int ir);
void save_WH_id(Player* wh);
void finance_WH(int ir);

extern Player* employees[2];
extern Player* white_hat;

extern int firewall_activated;
extern int backup;
extern int prepare_action; // this int represents the number of tour the action selected takes
extern int secured; // initially the company did not secure the physical access to its buildings

#endif