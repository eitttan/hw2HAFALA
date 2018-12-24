//
// Created by user on 11/12/18.
//
#include "account.h"

account::account(int id, int password, int init) : id(id), VIP(false), password(password), balance(init), readers_num(0)
{
    if (pthread_mutex_init(&locker, NULL) || pthread_mutex_init(&VIP_locker, NULL)
                                          || pthread_mutex_init(&readers, NULL))
        //if initialize returned some value different then zero, it's an error
        exit(1);
}
account::~account()
{
    if (pthread_mutex_destroy(&locker) || pthread_mutex_destroy(&VIP_locker) || pthread_mutex_destroy(&readers))
        //if destroy returned some value different then zero, it's an error
        exit(1);
}
bool account::set_VIP()
{
    if (VIP)
        return  false;
    pthread_mutex_lock(&VIP_locker);
    sleep(1);
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
    sleep(1);
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
    sleep(1);
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

int account::get_pass() const
{
    return (password);
}

int account::get_balance ()
{
    pthread_mutex_lock(&readers);
    readers_num++;
    if (readers_num == 1)
        pthread_mutex_lock(&locker);
    sleep(1);
    pthread_mutex_unlock(&readers);
    int bal = balance;
    pthread_mutex_lock(&readers);
    readers_num--;
    if (readers_num == 0)
        pthread_mutex_unlock(&locker);
    pthread_mutex_unlock(&readers);
    return bal;
}
int account::get_balance_for_print() const
{
    return balance;
}

void account::lock()
{
    pthread_mutex_lock(&locker);
}

void account::unlock()
{
    pthread_mutex_unlock(&locker);
}

int account::transfer(int amount)
{
    if (amount < 0) //transfer from account
    {
        if (amount < balance)
        {
            balance = balance - amount;
            return balance;
        }
        else    //don't have anough money
            return -1;
    }
    else    //transfer to account
    {
        balance = balance + amount;
        return balance;
    }
}