
#include "bank.cpp"
#include "ATMs.h"
#include "account.h"
#include "defines.h"

extern std::map <int,account* > account_map;
extern ofstream log_file("log.txt");

int main(int argc, char* argv[]) {
    //argv[1] = num of ATMs
    //argv[i] (i > 1) = input file of ATM i-1

    //for the first tests of basic ATM
    atm first = atm(1, "short_atm");
    pthread_mutex_init(&open_account_lock, NULL);
    pthread_mutex_init(&write_to_log_lock, NULL);
    pthread_t atm_threads;
    pthread_create(&atm_threads, NULL, atm_thread, &first);
    pthread_join(atm_threads, NULL);
    //all of this will be changed

    return 0;
}