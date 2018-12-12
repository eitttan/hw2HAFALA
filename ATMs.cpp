//
// Created by user on 11/12/18.
//
#include "ATMs.h"

void* atm_thread (void* arg)
{

}

void open_account()
{
    lock(open_account_lock);
    acount constructor;
    unlock(open_account_lock);
}
void make_VIP()
{
    check password;
    set_VIP();
}
void deposit()
{
    check password;
    acount::deposit();
}
void withdraw()
{
    check password;
    acount::withdraw();
}
void check_balance()
{
    check password;
    account::get_balance();
}
void transfer()
{
    check password;
    check account2;
    acount::withdraw();
    account2::deposit();
}
