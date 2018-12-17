//
// Created by user on 12/12/18.
//

#ifndef HW2_ATMS_H
#define HW2_ATMS_H

# include "defines.h"
# include "account.h"

void* atm_thread (void* arg);      //TODO
void open_account(int id, int password, int init);      //TODO
void make_VIP(int id,int pass);      //TODO
void deposit(int id,int pass,int amount);     //TODO
void withdraw(int id,int pass,int amount);      //TODO
void check_balance(int id,int pass);      //TODO
void transfer(int source, int pass, int target, int amount);      //TODO

class atm {
public:
    int id;
    char *log;
    atm(int id, char* log);
};

#endif //HW2_ATMS_H
