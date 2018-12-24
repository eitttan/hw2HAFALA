//
// Created by user on 11/12/18.
//
#include "ATMs.h"


void* atm_thread (void* arg)
{
    int atm_id;
    string input;
    atm_id = ((atm*)arg)->id;
    input = ((atm*)arg)->input;
    std::ifstream infile(input);
    string line;
    int id, password, amount, t_id;

    while (!infile.eof())
    {
        std::getline(infile, line);
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
            usleep(atm_sleep);
        }
        else //empty line
            continue;
       // usleep(atm_sleep);
    }
    pthread_exit(NULL);
}

void open_account(int atm_id, int id, int password, int init)
{
    string to_print;
    pthread_mutex_lock(&open_account_lock);
    if (init < 0)
        return;
    if (account_map.find(id) != account_map.end())
    {
        pthread_mutex_unlock(&open_account_lock);
        to_print = "Error " + to_string(atm_id) + ": Your transaction failed - account with the same id exists" ;
    }
    else
    {
        account *newAcc = new account(id, password, init);
        account_map.insert(std::make_pair(id, newAcc));
        sleep(1);
        pthread_mutex_unlock(&open_account_lock);
        to_print = to_string(atm_id) + ": New account id is " + to_string(id) + " with password ";
        to_print += to_string(password) + " and initial balance " + to_string(init);
    }
    print_to_log(to_print);
}
void make_VIP(int atm_id, int id,int password)
{
    if (check_account(atm_id, id)) //valid account
    {
        account *selAcc = account_map.find(id)->second;
        if (selAcc->check_password(password))
            selAcc->set_VIP();
        else    //wrong password
        {
            string to_print;
            to_print = "Error " + to_string(atm_id) + ": Your transaction failed - password for account id ";
            to_print += to_string(id) + " is incorrect";
            print_to_log(to_print);
        }
    }
}
void deposit(int atm_id, int id,int password,int amount)
{
    string to_print;
    if (check_account(atm_id, id)) //valid account
    {
        account *selAcc = account_map.find(id)->second;
        if (selAcc->check_password(password))
        {
            int balance = selAcc->deposit(amount);
            to_print = to_string(atm_id) + ": Account " + to_string(id) + " new balance is " + to_string(balance);
            to_print += " after " + to_string(amount) + " $ was deposited";
        }
        else    //wrong password
        {
            to_print = "Error " + to_string(atm_id) + ": Your transaction failed - password for account id ";
            to_print += to_string(id) + " is incorrect";
        }
        print_to_log(to_print);
    }
}
void withdraw(int atm_id, int id,int password,int amount)
{
    string to_print;
    if (check_account(atm_id, id)) //valid account
    {
        account *selAcc = account_map.find(id)->second;
        if (selAcc->check_password(password))
        {
            int balance = selAcc->withdraw(amount);
            if (balance == -1)  //not enough money in account
            {
                to_print = "Error " + to_string(atm_id) + ": Your transaction failed - account id " +  to_string(id);
                to_print += " balance is lower than " + to_string(amount);
            }
            else
            {
                to_print = to_string(atm_id) + ": Account " + to_string(id) + " new balance is " + to_string(balance);
                to_print += " after " + to_string(amount) + " $ was withdrew";
            }
        }
        else    //wrong password
        {
            to_print = "Error " + to_string(atm_id) + ": Your transaction failed - password for account id ";
            to_print += to_string(id) + " is incorrect";
        }
        print_to_log(to_print);
    }
}
void check_balance(int atm_id, int id,int password)
{
    string to_print;
    int balance;
    if (check_account(atm_id, id)) //valid account
    {
        account *selAcc = account_map.find(id)->second;
        if (selAcc->check_password(password))
        {
            balance = selAcc->get_balance();
            to_print = to_string(atm_id) + ": Account " + to_string(id) + " balance is " + to_string(balance);
        }
        else    //wrong password
        {
            to_print = "Error " + to_string(atm_id) + ": Your transaction failed - password for account id ";
            to_print += to_string(id) + " is incorrect";
        }
        print_to_log(to_print);
    }
}
void transfer(int atm_id, int source, int password, int target, int amount)
{
    string to_print;
    int sourceBalance;
    int targetBalance;
    if (amount < 0)
        return;
    if (check_account(atm_id, source) && check_account(atm_id, target)) //both are valid accounts
    {
        account* first_lock;
        account* second_lock;
        account* sourceAcc = account_map.find(source)->second;
        account* targetAcc = account_map.find(target)->second;
        if (sourceAcc->check_password(password))
        {
            if (source < target)
            {
                first_lock = sourceAcc;
                second_lock = targetAcc;
            }
            else
            {
                first_lock = targetAcc;
                second_lock = sourceAcc;
            }
            first_lock->lock();
            second_lock->lock();
            sourceBalance = sourceAcc->transfer(-1*amount);
            if (sourceBalance == -1)  //not enough money in account
            {
                to_print = "Error " + to_string(atm_id) + ": Your transaction failed - account id ";
                to_print += to_string(source) + " balance is lower than " + to_string(amount);
            }
            else
            {
                targetBalance = targetAcc->transfer(amount);
                to_print = to_string(atm_id) + ": Transfer " + to_string(amount) + " from account ";
                to_print += to_string(source) + " to account " + to_string(target) + " new account balance is ";
                to_print += to_string(sourceBalance) + " new target account balance is " + to_string(targetBalance);
                sleep(1);
            }
            first_lock->unlock();
            second_lock->unlock();
        }
        else    //wrong password
        {
            to_print = "Error " + to_string(atm_id) + ": Your transaction failed - password for account id ";
            to_print += to_string(source) + " is incorrect";
        }
        print_to_log(to_print);
    }
}

void print_to_log(string str)
{
    pthread_mutex_lock(&write_to_log_lock);
   // log_file << to_string((clock()))<<" :" ;
    log_file << str << endl;
    pthread_mutex_unlock(&write_to_log_lock);
}
bool check_account(int atm_id, int id)
{
    if (account_map.find(id) == account_map.end())
    {
        string to_print;
        to_print = "Error " + to_string(atm_id) + ": Your transaction failed - account id " + to_string(id);
        to_print += " does not exist";
        print_to_log(to_print);
        return false;
    }
    return  true;
}



atm::atm(int id, string input): id(id), input(input)
{}
atm::atm(){}