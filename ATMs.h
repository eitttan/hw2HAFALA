//
// Created by user on 12/12/18.
//

#ifndef HW2_ATMS_H
#define HW2_ATMS_H

# include "defines.h"
# include "account.h"

void* atm_thread (void* arg);      //TODO
void open_account(int atm_id, int id, int password, int init);      //TODO
void make_VIP(int atm_id, int id,int pass);      //TODO
void deposit(int atm_id, int id,int pass,int amount);     //TODO
void withdraw(int atm_id, int id,int pass,int amount);      //TODO
void check_balance(int atm_id, int id,int pass);      //TODO
void transfer(int atm_id, int source, int pass, int target, int amount);      //TODO

class atm {
public:
    int id;
    char *input;
    atm(int id, char* input);
};

#endif //HW2_ATMS_H
