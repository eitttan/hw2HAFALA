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
    bool withdraw();        //TODO  --mutex
    void deposit();         //tODO  --mutex
    bool check_password() const;      //TODO  --read
    int get_balance () const;       //TODO --read
    int get_updated_balance () const;       //TODO --lock
private:
    int id;
    bool VIP;
    int password;
    int balance;
    pthread_mutex_t locker;
    pthread_mutex_t VIP_locker;

};

#endif //HW2_ACCOUNT_H
