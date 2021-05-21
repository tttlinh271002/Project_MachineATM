#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class accountatm
{
private:
    string id;
    string password;
    int numberwrong, account_balance;
public:
    int moneywd;
    accountatm();
    accountatm(string id_, string password_, int money, int fail);
    ~accountatm();
    string getTimeNow();
    bool create(string id_);
    string getid() const { return id; }
    string getpassword() const { return password; }
    string getaccount_balance() const { return to_string(account_balance); }
    string getnumberwrong() const { return to_string(numberwrong); }
    bool login();
    void top_up(int bank[]);
    void change_password();
    int transfer_money();
    void receives_money(int moneyr);
    void withdraw(int bank[]);
    void check_balance();
    void write_history(string s);
    void print_history();
};

