//
// Created by user on 11/12/18.
//
#include "ATMs.h"
#include "main.cpp"

void* atm_thread (void* arg)
{
    int atm_id;
    char* input;
    atm_id = ((atm*)arg)->id;
    input = ((atm*)arg)->input;
    //-------------------//TODO
    //there must be a better way for it
    stringstream ss;
    string s;
    ss << input;
    ss >> s;
    std::ifstream infile(s);
    //---------
    string line;
    int id, password, amount, t_id;

    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        char a;
        if (iss >> a)
        {
            if (a == 'O')   //O <account id> <password> <amount>
            {
                if (!(iss >> id >> password >> amount))
                    // not enough arguments
                    continue;
                open_account(atm_id, id, password, amount);
            }
            else if(a == 'L')   //L <account id> <password>
            {
                if (!(iss >> id >> password))
                    // not enough arguments
                    continue;
                make_VIP(atm_id, id, password);
            }
            else if(a == 'D')   //D <account id> <password> <amount>
            {
                if (!(iss >> id >> password >> amount))
                    // not enough arguments
                    continue;
                deposit(atm_id, id, password, amount);
            }
            else if(a == 'W')   //W <account id> <password> <amount>
            {
                if (!(iss >> id >> password >> amount))
                    // not enough arguments
                    continue;
                withdraw(atm_id, id, password, amount);
            }
            else if(a == 'B')   //B <account id> <password>
            {
                if (!(iss >> id >> password))
                    // not enough arguments
                    continue;
                check_balance(atm_id, id, password);
            }
            else if(a == 'T')   //T <account id> <password> <target account id> <amount>
            {
                if (!(iss >> id >> password >> t_id >> amount))
                    // not enough arguments
                    continue;
                transfer(atm_id, id, password, t_id, amount);
            }
            else //no such command
            {
                continue;
            }
        }
        else //empty line
            continue;
    }
    pthread_exit(NULL);
}

void open_account(int atm_id, int id, int password, int init)
{
    string to_print;
    pthread_mutex_lock(&open_account_lock);
    if (account_map.find(id) != account_map.end())
    {
        pthread_mutex_unlock(&open_account_lock);
        to_print = "Eror " + atm_id + " : Your transaction failed – account with the same id exists" ;
    }
    else
    {
        account *newAcc = new account(id, password, init);
        account_map.insert(std::make_pair(id, newAcc));
        pthread_mutex_unlock(&open_account_lock);
        to_print = atm_id + " : New account id is " + id + " with password " + password;
        to_print += " and initial balance " + init;
    }
    print(to_print);
}
void make_VIP(int atm_id, int id,int pass)
{
    if (account_map.find(id) == account_map.end())

        //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->set_VIP();
}
void deposit(int atm_id, int id,int pass,int amount)
{
    //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->deposit(amount);
}
void withdraw(int atm_id, int id,int pass,int amount)
{
    //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->withdraw(amount);
}
void check_balance(int atm_id, int id,int pass)
{
    //TODO check password;
    //TODO
    /*    if (account_map.find(id) == account_map.end()){
        cerr << id <<" : wrong id" << endl;
    }*/
    account* selAcc = account_map.find(id)->second;
    selAcc->get_balance();
}
void transfer(int atm_id, int source, int pass, int target, int amount)
{
    //TODO check password;
    //TODO check account2  &1
    account* sourceAcc = account_map.find(source)->second;
    sourceAcc->withdraw(amount);
    account* targetAcc = account_map.find(target)->second;
    targetAcc->withdraw(amount);
}
void print(string str)
{
    pthread_mutex_lock(&write_to_log_lock);
    log_file << str << endl;
    pthread_mutex_unlock(&write_to_log_lock);
}

atm::atm(int id, char* input): id(id), input(input)
{}