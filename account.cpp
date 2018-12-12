//
// Created by user on 11/12/18.
//
#include "account.h"

account::account(int id, int password, int init) : id(id), VIP(false), password(password), balance(init)
{
    pthread_mutex_init(&locker,NULL);
    pthread_mutex_init(&VIP_locker,NULL);
}
account::~account()
{
    pthread_mutex_destroy(&locker);
    pthread_mutex_destroy(&VIP_locker);

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
    return false;
}
bool account::withdraw()
{

}
void account::deposit()
{

}
bool account::check_password() const
{

}
int account::get_balance () const
{

}
int account::get_updated_balance () const
{

}
