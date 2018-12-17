//
// Created by user on 12/12/18.
//

#ifndef HW2_ATMS_H
#define HW2_ATMS_H

# include "defines.h"
# include "account.h"

void* atm_thread (void* arg);      //TODO
void open_account();      //TODO
void make_VIP();      //TODO
void deposit();      //TODO
void withdraw();      //TODO
void check_balance();      //TODO
void transfer();      //TODO

class atm {
public:
    int id;
    char *log;
    atm(int id, char* log);
};

#endif //HW2_ATMS_H
