#include "accountatm.h"
#include<ctime>
#include<time.h>
#include<conio.h>

accountatm::accountatm()
{
    account_balance=0;
    ofstream file(id+".txt");
    file<<getTimeNow()<<endl<<"Congratulations, you successfully login"<<endl;
    file.close();
    numberwrong = 0;
}

accountatm::accountatm(string id_, string password_, int money, int fail)
{
    id = id_;
    password = password_;
    account_balance = money;
    numberwrong = fail;
}

accountatm::~accountatm()
{
}

string accountatm::getTimeNow()
{
    time_t rawtime;
    time(&rawtime);
    string tme = ctime(&rawtime);
    tme.erase(tme.length() - 1, 1);
    return tme;
}

bool accountatm::create(string id_)
{
    id = id_;
    cout<<"Password: ";
    cin>>password;

    fstream file;
    file.open("accountatm.txt", ios::app);
    if (file.is_open())
        {
        file<<id<<":"<<password<<":"<<account_balance<<":"<<numberwrong<<":";
        file.close();
        }
    return 1;
}

bool accountatm::login()
{
    string pass;
    if (numberwrong<5)
    {
        cout<<"Password: ";
        cin>>pass;
        if (pass==password)
        {
            numberwrong=0;
            write_history("Login Successfully");
            cout<<"\nCongratulations, you successfully log in"<<endl;
            return 1;
        }
        else
        {
            numberwrong+=1;
            write_history("Login Error");
            cout<<"\nIncorrect Password"<<endl;
            return 0;
        }
    }
    else
    {
        cout<<" Your Account is locked ";
        return 0;
    }
}

void accountatm::top_up(int bank[])
{
    int moneytu=0,K50=0,K20=0,K10=0,K5=0,K2=0,K1=0;
        int amount=0;
        cout<<"\nDenominations: 500"<<endl;
        cout<<"Fill in Amount: ";
        cin>>K50;
        cout<<"\nDenominations: 200"<<endl;
        cout<<"Fill in Amount: ";
        cin>>K20;
        cout<<"\nDenominations: 100"<<endl;
        cout<<"Fill in Amount: ";
        cin>>K10;
        cout<<"\nDenominations: 50"<<endl;
        cout<<"Fill in Amount: ";
        cin>>K5;
        cout<<"\nDenominations: 20"<<endl;
        cout<<"Fill in Amount: ";
        cin>>K2;
        cout<<"\nDenominations: 10"<<endl;
        cout<<"Fill in Amount: ";
        cin>>K1;
        moneytu = 500*K50 + 200*K20 + 100*K10 + 50*K5 + 20*K2 + 10*K1;
        bank[500]+= K50;
        bank[200]+= K20;
        bank[100]+= K10;
        bank[50]+= K5;
        bank[20]+= K2;
        bank[10]+= K1;

    if(account_balance+=moneytu)
    {
        cout<<"\nPay in Successfully: "<<moneytu<<endl;
        write_history("Pay in Successfully + " + to_string(moneytu));
    }
    else
        cout<<"\nPay in Unsuccessfully"<<endl;
}

void accountatm::change_password()
{
    string old,new1,new2;
    cout << "\nOld password: ";
    cin >> old;
    if (old==password)
    {
        cout<<"New password: ";
        cin >> new1;
        if (new1 != password)
        {
            cout <<"Enter new password: ";
            cin >> new2;
            if (new1 == new2)
            {
                password = new1;
                cout <<"\nChange password successfully"<<endl;
                write_history("Change password");
            }
            else cout<<"\nNew password does not match"<<endl;
        }
        else cout<<"\nNew password needs to match old password"<<endl;
    }
    else cout<<"\nOld password is not correct"<<endl;

}

int accountatm::transfer_money()
{
    int moneytf=0;
    cout<<"Account_balance: "<<account_balance;
    cout<<"\nFill in Transfer Amount: ";
    cin>>moneytf;
    if (moneytf<=account_balance && moneytf!=0)
    {
        account_balance-=moneytf;
        cout<<"\nTransfer Successfully"<<endl;
        write_history("Transfer Successfully - " + to_string(moneytf));
        return moneytf;
    }
    else if(moneytf==0)
    {
        cout<<"\nTransaction fail"<<endl;
        return 0;
    }
    else
    {
        cout<<"\nInsufficient Balance"<<endl;
        return 0;
    }
}

void accountatm::receives_money(int moneyr)
{
    account_balance+=moneyr;
    write_history("Receive Successfully + " + to_string(moneyr));
}

void accountatm::withdraw(int bank[])
{
    int K500=0,K200=0,K100=0,K50=0,K20=0,K10=0;
    int md=moneywd;
    if (moneywd<=(account_balance-50) && moneywd%10==0)
    {
        while(moneywd>=500 && bank[500]>0)
        {
            moneywd-=500;
            K500++;
            bank[500]--;
        }
        while(moneywd>=200 && bank[200]>0)
        {
            moneywd-=200;
            K200++;
            bank[200]--;
        }
        while(moneywd>=100 && bank[100]>0)
        {
            moneywd-=100;
            K100++;
            bank[100]--;
        }
        while(moneywd>=50 && bank[50]>0)
        {
            moneywd-=50;
            K50++;
            bank[50]--;
        }
        while(moneywd>=20 && bank[20]>0)
        {
            moneywd-=20;
            K20++;
            bank[20]--;
        }
        while(moneywd>=10 && bank[10]>0)
        {
            moneywd-=10;
            K10++;
            bank[10]--;
        }
        if (moneywd==0)
        {
            account_balance-=md;
            cout<<"\nWithdraw Successfully"<<endl;
            write_history("Withdraw Successfully - " + to_string(md));
        }
        else
            cout<<"\nWithdraw Unsuccessfully"<<endl;
    }
    else if (moneywd<=(account_balance-50) && moneywd%10!=0)
    {
        cout<<"\nWithdraw unsuccessfully"<<endl;
    }
    else
    {
        cout<<"\nInsufficient Balance"<<endl;
    }
}

void accountatm::check_balance()
{
    cout<<"\nAccount Balance: "<<account_balance<<endl;
    write_history("Check Account Balance");
}
void accountatm::write_history(string s)
{
    fstream file(id+".txt", ios::app);
    file<<getTimeNow()<<endl<<s<<endl<<"---------------"<<endl;
}

void accountatm::print_history()
{
    ifstream file(id+".txt");
    while (!file.eof())
    {
        string s;
        getline(file, s);
        cout<<s<<endl;
    }
    file.close();
}
