//
// Created by user on 11/12/18.
//

#ifndef HW2_ACCOUNT_H
#define HW2_ACCOUNT_H

#include "defines.h"

using std::string;

class account {
public:
    int id;
    bool VIP;
    int password;
    int balance;
    pthread_mutex_t lock;
    account();
    ~account();
    bool set_VIP();     //TODO --probably read
    void withdraw();        //TODO  --mutex
    void deposit();         //tODO  --mutex
    bool check_pass();      //TODO  --read
    void transfer();           //TODO -two mutexes  --use withdraw and deposit
    int get_balance () const;       //TODO --read


};

#endif //HW2_ACCOUNT_H
