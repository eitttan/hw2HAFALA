//
// description: bank cpp file. contain methose that the "bank" do.
// but, there isn't object class/ just methods for bank_thread
//
#ifndef HW2_BANK_C
#define HW2_BANK_C

# include "defines.h"
# include "ATMs.h"
# include "account.h"
# include "bank.h"

int bank_balance=0;
*************************************************************************
//* function name:fees
//* Description :takes fees from every non_VIP acount every 3 sec
// 	and print to log the fee.
//* input   :  none
//* output: none
//*************************************************************************

void* fees (void* arg)
{
    srand(time(NULL));
    int percent;
    int amount;
    while(true)
        // maybe we can join in the main only the atms and that way the program will finish even though this loop is endless
    {
        usleep(fee_sleep);
        string to_print="";
        for (std::map<int, account *>::iterator it = account_map.begin(); it != account_map.end(); it++) {
            account *currAcc = it->second;
            if (currAcc->get_VIP())
                continue;
            percent = (rand()%3)+2;    //rand%3 = 0/1/2   => rand%3 + 2 = 2/3/4
            amount = currAcc->take_fee(percent);
            bank_balance += amount;
            to_print += "Bank: comissions of " + to_string(percent) + " % were charged, the bank gained ";
            to_print += to_string(amount) + " $ from account " + to_string(it->first) +"\n";
        }
        print_to_log(to_print);
    }
    //pthread_exit(NULL);
}

*************************************************************************
//* function name:print
//* Description :print to screen ,the bank status every 0.5 sec
//* input   :  none
//* output: none
//*************************************************************************


void* print(void* arg)
{
    while(true)
    {
        usleep(print_sleep);
        string to_print;
        to_print = "Current bank status \n";
        for (std::map<int, account *>::iterator it = account_map.begin(); it != account_map.end(); it++)
        {
            (it->second)->lock();
        }
        for (std::map<int, account *>::iterator it = account_map.begin(); it != account_map.end(); it++) {
            account *currAcc = it->second;
            to_print += "Account " + to_string(it->first) + ": Balance - ";
            to_print += to_string(currAcc->get_balance_for_print()) + " $ , Account Password - " +
                        to_string(currAcc->get_pass()) + "\n";

        }
        to_print += "The bank has " + to_string(bank_balance) +" $";
        printf("\033[2J");
        printf("\033[1;1H");
        cout<< to_print <<endl;
        for (std::map<int, account *>::iterator it = account_map.begin(); it != account_map.end(); it++)
        {
            (it->second)->unlock();
        }
    }

}


#endif
