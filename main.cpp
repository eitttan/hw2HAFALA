
//#include "bank.cpp"
#include "ATMs.h"
#include "account.h"
#include "defines.h"

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
    atm first = atm(1, "short_atm.txt");
    pthread_t atm_threads;
    pthread_create(&atm_threads, NULL, atm_thread, (void*)&first);
    pthread_join(atm_threads, NULL);
    //all of this will be changed

    return 0;
}
