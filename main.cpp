

#include "ATMs.h"
#include "account.h"
#include "defines.h"
#include "bank.h"
#include<bits/stdc++.h>


std::map <int,account*> account_map;
ofstream log_file("log.txt");
pthread_mutex_t open_account_lock;
pthread_mutex_t write_to_log_lock;

//*************************************************************************
//* function name:main
//* Description :main function to this program
//* input   :  arguments from user
//*************************************************************************

int main(int argc, char* argv[]) {
    
    pthread_mutex_init(&open_account_lock, NULL);
    pthread_mutex_init(&write_to_log_lock, NULL);

    
   // parsing

   const int NumberOfATMs = atoi(argv[1]);
    pthread_t* atm_threads = new pthread_t[NumberOfATMs];
    atm* ATMs= new atm[NumberOfATMs];
// create threads:

    for (int i = 0; i < NumberOfATMs; i++)
    {
        ATMs[i] = atm(i+1, argv[i + 2]);
        pthread_create(&atm_threads[i], NULL, atm_thread, (void*)&ATMs[i]);
    }

    pthread_t bank_thread;
    pthread_t print_thread;

    pthread_create(&bank_thread, NULL, fees, NULL);
    pthread_create(&print_thread, NULL, print, NULL);
// join threads:

    for (int i = 0; i < NumberOfATMs; i++)
    {
        pthread_join(atm_threads[i], NULL);

    }


    return 0;
}
