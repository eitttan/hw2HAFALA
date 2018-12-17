//
// Created by user on 11/12/18.
//
#include "ATMs.h"
#include "main.cpp"
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

    if (account_map.find(id) != account_map.end()){
        cerr << id <<" : Your transaction failed – account with the same id exists" << endl;
    }
    pthread_mutex_lock(&open_account_lock);
    account* newAcc =  new account(id,password,init);
    account_map.insert( std::make_pair(id, newAcc));
    pthread_mutex_unlock(&open_account_lock);
    //TODO print to log
}
void make_VIP(int id,int pass)
{
    //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->set_VIP();
}
void deposit(int id,int pass,int amount)
{
    //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->deposit(amount);
}
void withdraw(int id,int pass,int amount)
{
    //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->withdraw(amount);
}
void check_balance(int id,int pass)
{
    //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->get_balance();
}
void transfer(int source, int pass, int target, int amount)
{
    //TODO check password;
    //TODO check account2  &1
    account* sourceAcc = account_map.find(source)->second;
    sourceAcc->withdraw(amount);
    account* targetAcc = account_map.find(target)->second;
    targetAcc->withdraw(amount);
}

atm::atm(int id, char* log): id(id), log(log)
{

}