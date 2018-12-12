
#include "bank.cpp"
#include "ATMs.h"
#include "account.h"
#include "account.cpp"
#include "defines.h"

using namespace std;
std::map <int,account> account_map;
pthread_mutex_t open_account_lock;
pthread_mutex_t write_to_log_lock;

int main() {
    std::cout << "Hello, hazut" << std::endl;
    std::cout << "Hello, back" << std::endl;
    return 0;
}