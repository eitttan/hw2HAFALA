//
// Created by user on 11/12/18.
//
#include "ATMs.h"

void* atm_thread (void* arg)
{

}

void open_account(int id, int password, int init)
{

    if (account_map.find(id) =! account_map.end()){
        cerr << this.id <<": Your transaction failed – account with the same id exists" << endl;
    }
    pthread_mutex_lock(&open_account_lock);
    account newAcc = account(id,password,init);
    account_map.insert(id,newAcc);
    pthread_mutex_unlock(&open_account_lock);
    //TODO print to log
}
void make_VIP(int id,int pass)
{
    check password;
    account_map.find(id)->set_VIP();
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
