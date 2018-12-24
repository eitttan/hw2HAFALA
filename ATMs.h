//
// Created by user on 12/12/18.
//

#ifndef HW2_ATMS_H
#define HW2_ATMS_H

# include "defines.h"
# include "account.h"

using std::string;

void* atm_thread (void* arg);
void open_account(int atm_id, int id, int password, int init);
void make_VIP(int atm_id, int id,int password);
void deposit(int atm_id, int id,int password,int amount);
void withdraw(int atm_id, int id,int password,int amount);
void check_balance(int atm_id, int id,int password);
void transfer(int atm_id, int source, int password, int target, int amount);
void print_to_log(string str);
bool check_account(int atm_id, int id);


class atm {
public:
    int id;
    string input;
    atm(int id, string input);
    atm();
};

#endif //HW2_ATMS_H
