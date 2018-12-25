//
// description: account cpp file. module of accounts. contain
// properties and methods on accounts. 
//		
#include "account.h"
//*************************************************************************
//* function name: account
//* Description  : account c'tor
//* input   :   1. account id
//              2. account password
//		3. init balance
//* output: account object 
//*************************************************************************
account::account(int id, int password, int init) : id(id), VIP(false), password(password), balance(init), readers_num(0)
{
    if (pthread_mutex_init(&locker, NULL) || pthread_mutex_init(&VIP_locker, NULL)
                                          || pthread_mutex_init(&readers, NULL))
        //if initialize returned some value different then zero, it's an error
        exit(1);
}
//*************************************************************************
//* function name: account
//* Description  : account d'tor
//* input   :  None
//* output: none 
//*************************************************************************
account::~account()
{
    if (pthread_mutex_destroy(&locker) || pthread_mutex_destroy(&VIP_locker) || pthread_mutex_destroy(&readers))
        //if destroy returned some value different then zero, it's an error
        exit(1);
}
//*************************************************************************
//* function name: set_vip
//* Description  : set account vip
//* input   : None
//* output: true if success, else - false 
//*************************************************************************
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
//*************************************************************************
//* function name: get_vip
//* Description  : get account vip field
//* input   : None
//* output: true if VIP, else - false 
//*************************************************************************
bool account::get_VIP()
{
    if (VIP || pthread_mutex_trylock(&VIP_locker))
        return true;
    pthread_mutex_unlock(&VIP_locker);
    return false;
}
//*************************************************************************
//* function name: withdraw
//* Description  : withdraw from account
//* input   : amount
//* output: new balance 
//*************************************************************************
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
//*************************************************************************
//* function name: deposit
//* Description  : deposit to account
//* input   : amount
//* output: new balance 
//*************************************************************************
int account::deposit(int amount)
{
    pthread_mutex_lock(&locker);
    balance = balance + amount;
    sleep(1);
    int ret = balance;
    pthread_mutex_unlock(&locker);
    return ret;
}
//*************************************************************************
//* function name: take_fee
//* Description  : teke_fee from account and update balance
//* input   : percentage
//* output: amount of fee
//*************************************************************************
int account::take_fee(int percentage)
{
    pthread_mutex_lock(&locker);
    int fee = balance * percentage / 100;
    balance = balance - fee;
    pthread_mutex_unlock(&locker);
    return fee;
}
//*************************************************************************
//* function name: check_password
//* Description  : check if password correct
//* input   : password
//* output: true if correct pass, else -false 
//*************************************************************************
bool account::check_password(int pass) const
{
    return (pass == password);
}

//*************************************************************************
//* function name: get_pass
//* Description  : get account password
//* input   : 
//* output: password 
//*************************************************************************
int account::get_pass() const
{
    return (password);
}

//*************************************************************************
//* function name: get_balance
//* Description  : get account balance
//* input   : none
//* output: balance 
//*************************************************************************
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
//*************************************************************************
//* function name: get_balance_for_print
//* Description  : get the balance in specific moment
//* input   : 
//* output: balance
//*************************************************************************
int account::get_balance_for_print() const
{
    return balance;
}
//*************************************************************************
//* function name: lock
//* Description  :lock the account
//* input   : none
//* output:none
//*************************************************************************
void account::lock()
{
    pthread_mutex_lock(&locker);
}
//*************************************************************************
//* function name: unlock
//* Description  :unlock the account
//* input   : none
//* output:none
//*************************************************************************
void account::unlock()
{
    pthread_mutex_unlock(&locker);
}
//*************************************************************************
//* function name: transfer
//* Description  :transfer to another account
//* input   : amount
//* output: new balance
//*************************************************************************
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
