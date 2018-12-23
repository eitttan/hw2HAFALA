//
// Created by user on 11/12/18.
//

#ifndef HW2_DEFINES_H
#define HW2_DEFINES_H

#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <pthread.h>
#include <mutex>
#include <cstdbool>
#include "account.h"
#include "ATMs.h"
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>

//global
using namespace std;
using std::string;
extern pthread_mutex_t open_account_lock;
extern pthread_mutex_t write_to_log_lock;
extern ofstream log_file;
//extern int bank_balance;

#define atm_sleep 100000
#define fee_sleep 3000000
#define print_sleep 500000
#endif //HW2_DEFINES_H
