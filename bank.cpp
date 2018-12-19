//
// Created by user on 11/12/18.
//
/*
# include "defines.h"
# include "ATMs.h"
# include "account.h"
#include "main.cpp"


//takes fees from every non_VIP acount every 3 seconds
void* fees ()
{
    for (std::map<int, account*>::iterator it = account_map.begin(); it != account_map.end(); ++it) {
        account *currAcc = it->second;
        if (currAcc->get_VIP()) continue;
        int balance = currAcc->get_balance();
        int twopercent = round(0.02 * balance);
        int amount = rand() % twopercent + twopercent;
        currAcc->deposit(amount);
        //TODO : insert to bank account (maybe);
        //TODO : printmessage
        //toDO : is need threads? for case the map changed?
    }
    sleep(3);
    fees();
}
*/
/*
void* print(void* arg)
{
    int a=1;
}*/