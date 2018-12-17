//
// Created by user on 11/12/18.
//
#include "ATMs.h"

void* atm_thread (void* arg)
{
    int id;
    char* log;
    id = ((atm*)arg)->id;
    log = ((atm*)arg)->log;
    //-------------------//TODO
    //there must be a better way for it
    stringstream ss;
    string s;
    ss << log;
    ss >> s;
    std::ifstream infile(s);
    //---------
    string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        char a;
        if (iss >> a)
        {
            if (a == 'O')
            {
                //open func and whatever else neede
            }
            else if(a == 'L')
            {
                //make VIP func and whatever else neede
            }
            else if(a == 'D')
            {
                //deposit func and whatever else neede
            }
            else if(a == 'W')
            {
                //withdraw func and whatever else neede
            }
            else if(a == 'B')
            {
                //check ballance func and whatever else neede
            }
            else if(a == 'T')
            {
                //transfer func and whatever else neede
            }
            else //error
            {
                //print something
            }
        }
        else //error
            exit(1);
    }
    pthread_exit(NULL);
}

void open_account(int id, int password, int init)
{

    if (account_map.find(id) =! account_map.end()){
        cerr << this.id <<": Your transaction failed – account with the same id exists" << endl;
    }
    pthread_mutex_lock(&open_account_lock);
    account newAcc = account(id,password,init);
    account_map.insert(id,newAcc);
    pthread_mutex_unlock(&open_account_lock);
    //TODO print to log
}
void make_VIP(int id,int pass)
{
    check password;
    account_map.find(id)->set_VIP();
}
void deposit()
{
    check password;
    acount::deposit();
}
void withdraw()
{
    check password;
    acount::withdraw();
}
void check_balance()
{
    check password;
    account::get_balance();
}
void transfer()
{
    check password;
    check account2;
    acount::withdraw();
    account2::deposit();
}

atm::atm(int id, char* log): id(id), log(log)
{}