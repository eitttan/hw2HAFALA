
#include "bank.cpp"
#include "ATMs.cpp"
#include "account.h"
#include "account.cpp"
#include "defines.h"

using namespace std;
std::map <int,account> account_map;
pthread_mutex_t open_account;
pthread_mutex_t write_to_log;

int main() {
    std::cout << "Hello, hazut" << std::endl;
    std::cout << "Hello, back" << std::endl;
    return 0;
}