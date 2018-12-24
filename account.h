//
// Created by user on 11/12/18.
//

#ifndef HW2_ACCOUNT_H
#define HW2_ACCOUNT_H

#include "defines.h"

using std::string;

class account {
public:
    account(int id, int password, int init);

    ~account();

    bool set_VIP();

    bool get_VIP();     //for fees

    int take_fee(int percentage);

    int withdraw(int amount);

    int deposit(int amount);

    bool check_password(int pass) const;

    int get_pass() const;

    int get_balance();
    //transfer needs to happen "atomicly" for both accounts
    void lock();

    void unlock();

    int transfer(int amount);

private:
    int id;
    bool VIP;
    int password;
    int balance;
    pthread_mutex_t locker;
    pthread_mutex_t VIP_locker;
    pthread_mutex_t readers;
    int readers_num;
    friend class bank;

};

extern std::map <int, account* > account_map;

#endif //HW2_ACCOUNT_H
