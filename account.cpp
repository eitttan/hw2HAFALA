//
// Created by user on 11/12/18.
//
#include "account.h"

account::account(int id, int password, int init) : id(id), VIP(false), password(password), balance(init)
{
    if (pthread_mutex_init(&locker, NULL) || pthread_mutex_init(&VIP_locker, NULL))
        //if initialize returned some value different then zero, it's an error
        exit(1);
}
account::~account()
{
    if (pthread_mutex_destroy(&locker) || pthread_mutex_destroy(&VIP_locker))
        //if destroy returned some value different then zero, it's an error
        exit(1);
}
bool account::set_VIP()
{
    if (VIP)
        return  false;
    pthread_mutex_lock(&VIP_locker);
    VIP = true;
    pthread_mutex_unlock(&VIP_locker);
    return  true;
}
bool account::get_VIP()
{
    if (VIP || pthread_mutex_trylock(&VIP_locker))
        return true;
    pthread_mutex_unlock(&VIP_locker);
    return false;
}
int account::withdraw(int amount)
{
    pthread_mutex_lock(&locker);
    if (balance < amount)
    {
        pthread_mutex_unlock(&locker);
        return -1;
    }
    balance = balance - amount;
    int ret = balance;
    pthread_mutex_unlock(&locker);
    return ret;
}
int account::deposit(int amount)
{
    pthread_mutex_lock(&locker);
    balance = balance + amount;
    int ret = balance;
    pthread_mutex_unlock(&locker);
    return ret;
}
int account::take_fee(int percentage)
{
    pthread_mutex_lock(&locker);
    int fee = balance * percentage / 100;
    balance = balance - fee;
    pthread_mutex_unlock(&locker);
    return fee;
}
bool account::check_password(int pass) const
{
    return (pass == password);
}
int account::get_balance () const
{
    return balance;
}
int account::get_updated_balance ()
{
    pthread_mutex_lock(&locker);
    int bal = balance;
    pthread_mutex_unlock(&locker);
    return bal;
}
