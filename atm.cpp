#include"accountatm.h"

using namespace std;
vector<accountatm> list_accountatm;
int bank[501];

void input_data()
{
    ifstream file("accountatm.txt");
    if (file.is_open())
    {
        string id, password, money, numberwrong;
        while (getline(file, id, ':'))
        {
            getline(file, password, ':');
            getline(file, numberwrong, ':');
            getline(file, money, ':');
            accountatm p(id, password, stoi(money), stoi(numberwrong));
            list_accountatm.push_back(p);
        }
    file.close();
    }
    ifstream f("bank.txt");
    f>>bank[500];
    f>>bank[200];
    f>>bank[100];
    f>>bank[50];
    f>>bank[20];
    f>>bank[10];
}

void saveData()
{
    ofstream file("bank.txt");
    file<<bank[500]<<" "<<bank[200]<<" "<<bank[100]<<" "<<bank[50]<<" "<<bank[20]<<" "<< bank[10];
    file.close();
    ofstream f("accountatm.txt");
    for (accountatm x : list_accountatm)
    {
        f<<x.getid()<<":"<<x.getpassword()<<":"<<x.getaccount_balance()<<":"<<x.getnumberwrong()<<":";
    }
}

int readSelect(){
    int x = -1;
    while(x == -1){
        cin>>x;
    }
    return x;
}

int main()
{
    MENU:
    string id,password;
    input_data();

    while(true)
    {
        int select=0;
        system("cls");
        cout<<"            >>>>>>>>>>>>>>>>>> ATM <<<<<<<<<<<<<<<<<<"<<endl;
        cout<<"\n1.Login"<<endl
            <<"2.Create Account"<<endl;
        cout<<"Answer: ";
        cin>>select;
        if (select==1)
        {
            system("cls");
            cout<<"           >>>>>>>>>>>>>>>>> LOGIN <<<<<<<<<<<<<<<<<"<<endl;
            cout<<"\nID: ";
            cin>>id;
            bool checklogin=false;
            for(int i=0;i<list_accountatm.size(); i++)
            {
                if (id==list_accountatm.at(i).getid())
                {
                    checklogin = true;
                    if (list_accountatm.at(i).login())
                    {
                        accountatm* CurrentAccount = &list_accountatm.at(i);
                        cout<<"\nWould you like to continue with the transaction"
                            <<"\n7.Continue                    8.Back"<<endl
                            <<"Answer: ";
                        int s3;
                        cin>>s3;
                        if(s3==7) goto DS;
                        if(s3==8) goto MENU;
                    DS:
                        int choose = 0;
                        system("cls");
                        /*cout<<"\nNgôn ngữ";
                        cout<< "\n1.Tiếng việt\2.English";
                        if (choose==1)
                        else if (choose==2)*/
                        cout<<"             Please select your Transaction"<<endl;
                        cout<<"\n1.Top up"<<"                                  "<<"2.Change password"<<endl;
                        cout<<"3.Transfer money"<<"                          "<<"4.Withdraw"<<endl;
                        cout<<"5.Check balance"<<"                           "<<"6.History"<<endl;
                        cout<<"Answer: ";
                        cin>>choose;
                        system("cls");
                        if (choose==1)
                        {
                            cout<<"          >>>>>>>>>>>>>>>>>> TOP UP <<<<<<<<<<<<<<<<<<"<<endl;
                            CurrentAccount->top_up(bank);
                        }
                        else if (choose==2)
                        {
                            cout<<"        >>>>>>>>>>>>>>>> CHANGE PASSWORD <<<<<<<<<<<<<<<<"<<endl;
                            CurrentAccount->change_password();
                        }
                        else if (choose==3)
                        {
                            cout<<"          >>>>>>>>>>>>>> TRANSFER MONEY <<<<<<<<<<<<<<"<<endl;
                            string recipient_id;
                            cout << "\nFill in recipient ID: ";
                            cin >> recipient_id;
                            int che=false;
                            for(int j=0;j<list_accountatm.size();j++)
                            {
                                if (list_accountatm.at(j).getid() == recipient_id)
                                {
                                    list_accountatm.at(j).receives_money(CurrentAccount->transfer_money());
                                    che=true;
                                    break;
                                }
                            }
                            if (che=false) cout<<"\nAccount does not exist"<<endl;
                        }
                        else if (choose==4)
                        {
                            cout<<"         >>>>>>>>>>>>>>>>>> WITHDRAW <<<<<<<<<<<<<<<<<<"<<endl;
                            int ch;
                            cout<<"\nChoose Withdraw Amount "<<endl;
                            cout<<"1.10000"<<"       "<<"2.5000"<<endl;
                            cout<<"3.4000"<<"        "<<"4.2000"<<endl;
                            cout<<"5.1000"<<"        "<<"6.Other"<<endl;
                            cin>>ch;
                            if(ch==1)
                            {
                                CurrentAccount->moneywd=10000;
                                CurrentAccount->withdraw(bank);
                            }
                            if(ch==2)
                            {
                                CurrentAccount->moneywd=5000;
                                CurrentAccount->withdraw(bank);
                            }
                            if(ch==3)
                            {
                                CurrentAccount->moneywd=4000;
                                CurrentAccount->withdraw(bank);
                            }
                            if(ch==4)
                            {
                                CurrentAccount->moneywd=2000;
                                CurrentAccount->withdraw(bank);
                            }
                            if(ch==5)
                            {
                                CurrentAccount->moneywd=1000;
                                CurrentAccount->withdraw(bank);
                            }
                            if(ch==6)
                            {
                                cout<<"The Withdraw Amount: ";
                                cin>>CurrentAccount->moneywd;
                                CurrentAccount->withdraw(bank);
                            }
                        }
                        else if (choose==5)
                        {
                            cout<<"        >>>>>>>>>>>>>>>> CHECK BALANCE <<<<<<<<<<<<<<<<"<<endl;
                            CurrentAccount->check_balance();
                        }
                        else if (choose==6)
                        {
                            cout<<"         >>>>>>>>>>>>>>>>>> HISTORY <<<<<<<<<<<<<<<<<<"<<endl
                                <<endl;
                            CurrentAccount->print_history();
                        }

                    saveData();
                    cout<<"\nDo you perform another transaction?"<<endl;
                    cout<<"10.YES               11.NO"<<endl;
                    cout<<"Answer: ";
                    int s1 = readSelect();
                        if(s1==10) goto DS;
                        else if (s1==11) goto MENU;
                    }
                    else
                    {
                        int s2;
                        cout<<"\n0.Exit"<<endl
                            <<"Answer: ";
                        cin>>s2;
                        if(s2==0) goto MENU;
                    }
                }
            }
            if (!checklogin)
            {
                int s2;
                cout << "\nAccount does not exist"<<endl;
                cout<<"\n0.Exit"<<endl
                    <<"Answer: ";
                cin>>s2;
                if(s2==0) goto MENU;
            }
        }
        else if (select==2)
        {
            system("cls");
            cout<<"       >>>>>>>>>>>>>>>> 2.CREATE ACCOUNT <<<<<<<<<<<<<<<<"<<endl;
            string id;
            cout<<"\nID: ";
            cin>>id;
            bool exist=false;
            for(auto x : list_accountatm){
                if(x.getid() == id) exist = true;
            }
            if(!exist)
            {
                accountatm p;
                if (p.create(id))
                {
                    list_accountatm.push_back(p);
                    cout << "\nAccount successfully create"<<endl;
                }
                else cout << "\nError"<<endl;
            }
            else cout<<"\nAccount exist!"<<endl;
        saveData();
        cout<<"\n0.Exit"<<endl
            <<"Answer: ";
        int s2;
        cin>>s2;
        if(s2==0) goto MENU;
        }
        saveData();
        int x = 0;
        while (!x)
        {
            cin >> x;
        }
    }
    return 0;
}

