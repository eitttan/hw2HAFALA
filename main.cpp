
//#include "bank.cpp"
#include "ATMs.h"
#include "account.h"
#include "defines.h"
#include "bank.h"
std::map <int,account* > account_map;
ofstream log_file("log.txt");
pthread_mutex_t open_account_lock;
pthread_mutex_t write_to_log_lock;

int main(int argc, char* argv[]) {
    //argv[1] = num of ATMs
    //argv[i] (i > 1) = input file of ATM i-1   --check if it comes as string or char*, if char* convert to string
    pthread_mutex_init(&open_account_lock, NULL);
    pthread_mutex_init(&write_to_log_lock, NULL);

    //for the first tests of basic ATM
   // atm first = atm(1, "/home/compm/CLionProjects/hw2/short_atm.txt");
   // parsing
   const int NumberOfATMs = atoi(argv[1]);
    pthread_t* atm_threads = new pthread_t[NumberOfATMs];
    //pthread_t* ATMThreads = new pthread_t[NumberOfATMs];
    atm* ATMs= new atm[NumberOfATMs];

    for (int i = 0; i < NumberOfATMs; i++)
    {
        ATMs[i] = atm(i+1, argv[i + 2]);
        //ThreadCheck = pthread_create(&ATMThreads[i] , NULL, ATMThreadFunc, (void *)&ATMs[i]);
        pthread_create(&atm_threads[i], NULL, atm_thread, (void*)&ATMs[i]);


    }
   // pthread_t atm_threads;
   // pthread_create(&atm_threads, NULL, atm_thread, (void*)&first);
    pthread_t bank_thread;
    pthread_create(&bank_thread, NULL, fees, NULL);
    //pthread_join(atm_threads, NULL);

    for (int i = 0; i < NumberOfATMs; i++)
    {
        pthread_join(atm_threads[i], NULL);

    }
    pthread_join(bank_thread, NULL);
    //all of this will be changed

    return 0;
}
