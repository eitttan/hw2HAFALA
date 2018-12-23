//
// Created by user on 11/12/18.
//
#ifndef HW2_BANK_C
#define HW2_BANK_C

# include "defines.h"
# include "ATMs.h"
# include "account.h"

int bank_balance;

//takes fees from every non_VIP acount every 3 seconds
void* fees (void* arg)
{
    bank_balance = 0;
    srand(time(NULL));
    int percent;
    int amount;
    string to_print;
    while(true) //TODO figure what to put here
        // maybe we can join in the main only the atms and that way the program will finish even though this loop is endless
    {
        usleep(fee_sleep);
        for (std::map<int, account *>::iterator it = account_map.begin(); it != account_map.end(); it++) {
            account *currAcc = it->second;
            if (currAcc->get_VIP())
                continue;
            percent = (rand()%3)+2;    //rand%3 = 0/1/2   => rand%3 + 2 = 2/3/4
            amount = currAcc->take_fee(percent);
            bank_balance += amount;
            to_print = "Bank: comissions of " + to_string(percent) + "% were charged, the bank gained ";
            to_print += to_string(amount) + "$ from account " + to_string(it->first);
            print_to_log(to_print);
        }
    }
    pthread_exit(NULL);
}

/*
void* print(void* arg)
{
    int a=1;
}*/


#endif