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
#include <fstream>
#include <sstream>

//global
using namespace std;
using std::string;
extern std::map <account*, int > account_map;
extern pthread_mutex_t open_account_lock;
extern pthread_mutex_t write_to_log_lock;

#endif //HW2_DEFINES_H
