#include <bits/stdc++.h>
using namespace std;

class Bank
{
    string name;
    long long Acc_no;
    long long balance;
    int Age;
    static long long total_account;

public:
    void show_details();
    void Add_acc(string Name, long long bal, int age);
    void Del_acc();
    void Deposit(long long bal);
    void Withdraw(long long bal);
    string getName();
    Bank *search_by_acc(long long acc, vector<Bank> &vec);
};

string Bank::getName()
{
    return name;
}
void Bank ::show_details()
{
    cout << "\nYour account details are: " << endl;
    cout << "Account No: " << this->Acc_no << endl;
    cout << "Account Holder Name: " << this->name << endl;
    cout << "Age: " << this->Age << endl;
    cout << "Balance in your Account is: " << this->balance << endl;
}
void Bank::Add_acc(string Name, long long bal, int age)
{
    this->Acc_no = total_account++;
    this->name = Name;
    this->balance = bal;
    this->Age = age;
    cout << "\nAccount has been created";
    this->show_details();
}

void Bank::Del_acc()
{
    this->Acc_no = 0;
    this->Age = 0;
    this->name = "";
    this->balance = 0;
}
void Bank::Deposit(long long amount)
{
    this->balance += amount;
    cout << "Your New balance is: " << this->balance << "\n";
}
void Bank::Withdraw(long long amount){
    if(this->balance>=amount){
        this->balance-=amount;
        cout << "Your New balance is: " << this->balance << "\n";
    }
    else{
        cout<<"You do not have enough balance\n";
        cout<<"Your balance is: "<<this->balance<<"\n";
    }
}

long long Bank ::total_account = 1000;

Bank *Bank ::search_by_acc(long long acc, vector<Bank> &vec)
{
    Bank *ob;
    for (int i = 0; i < vec.size(); i++)
    {
        int id = vec[i].Acc_no;
        if (acc == id)
        {
            ob = &vec[i];
            return ob;
        }
    }

    return NULL;
}
class BankLoan
{
    long long acc_bl;
    long long loan_amt;
    long long income;
    long long emi;
    static int rate;

public:
    double score;
    void getScore();
    void takeInput(long long amt, long long inc, long long em, long long acc);
    long long get_acc();
    long long getAmount();
};
int BankLoan ::rate = 10;

void BankLoan ::getScore()
{
    double ratio = (1.0 * this->income) / (this->loan_amt);
    double time_val = ((12.0 * this->emi) - (0.01 * this->loan_amt * this->rate)) / (double)(this->loan_amt);
    this->score = 0.70 * ratio + 0.30 * time_val;
}

void BankLoan::takeInput(long long amt, long long inc, long long em, long long acc)
{
    this->acc_bl = acc;
    this->loan_amt = amt;
    this->income = inc;
    this->emi = em;
    this->getScore();
}

long long BankLoan::get_acc()
{
    return this->acc_bl;
}
long long BankLoan ::getAmount()
{
    return this->loan_amt;
}

bool Comp(BankLoan &A, BankLoan &B)
{
    return A.score > B.score;
}

int main()
{
    cout << "\tMenu " << endl;
    cout << "1. Add Account\n";
    cout << "2. Remove Account\n";
    cout << "3. Deposit\n";
    cout << "4. Withdrawal\n";
    cout << "5. Print Account detail\n";
    cout << "6. Loan Requests\n";
    cout << "7. Exit\n";
    vector<Bank> database;
    vector<BankLoan> loan_requests;
    int choice;
    do
    {
        cout << "\nChoose an option: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Bank ob;
            string name;
            int age;
            int balance;
            string c;
            cout << "Enter your Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter your Age: ";
            cin >> age;
            cout << "Enter the money you want to deposit: ";
            cin >> balance;
            ob.Add_acc(name, balance, age);
            database.push_back(ob);
            break;
        }

        case 2:
        {
            cout << "Enter your account no. ";
            long long acc;
            cin >> acc;
            Bank ob;
            Bank *acc_detail = ob.search_by_acc(acc, database);
            if(acc_detail){
                string Name=(acc_detail)->getName();
            (acc_detail)->Del_acc();
            cout << "\nAccount of "<<Name<<" has been deleted\n";
            }
            else{
                cout<<"No Account found with this account number\n";
            }
            break;
        }

        case 3:
        {   long long acc;
            long long amt;
            cout << "Enter account no. ";
            cin >> acc;
            Bank ob;
            Bank *acc_detail = ob.search_by_acc(acc, database);
            if(acc_detail){
                cout << "Enter the deposit amount: ";
                cin >> amt;
                (acc_detail)->Deposit(amt);
                break;
            }
            else 
            cout<<"No account with this account number\n";
            break;
        }

        case 4:
        {
            long long acc;
            long long amt;
            cout << "Enter account no. ";
            cin >> acc;
            Bank ob;
            Bank *acc_detail = ob.search_by_acc(acc, database);
            if(acc_detail){
                cout << "Enter the withdrawal amount: ";
                cin >> amt;
                (acc_detail)->Withdraw(amt);
                break;
            }
            else 
            cout<<"No account with this account number\n";
            break;
        }
        case 5:
        {
            cout << "Enter your Account No: ";
            long long a_no;
            cin >> a_no;
            Bank ob;
            Bank *acc_detail = ob.search_by_acc(a_no, database);
            if (acc_detail)
                acc_detail->show_details();
            else
                cout << "No account with this account number\n" << endl;
            break;
        }

        case 6:
        {
            int i=1;
            char c;
            cout<<"Any loan request?(y/n): ";
            cin>>c;
            while (c=='y')
            {   
                long long amt, income, emi;
                long long acc_no;
                string name;
                cout<<"\nLoan Request "<<i<<":\n";
                cout << "\nEnter account No. : ";
                cin >> acc_no;
                Bank ob;
                Bank *acc_detail = ob.search_by_acc(acc_no, database);
                if(acc_detail){
                    name = (acc_detail)->getName();
                    cout<<"Name of borrower: "<<name<<"\n";
                    cout << "Enter loan amount: ";
                    cin >> amt;
                    cout << "Enter income of the borrower: ";
                    cin >> income;
                    cout << "Enter EMI borrower can pay: ";
                    cin >> emi;
                    BankLoan A;
                    A.takeInput(amt, income, emi, acc_no);
                    loan_requests.push_back(A);
                    i++;
                }
                else{
                    cout<<"No account with this account number\n";
                }
                cout<<"Any other loan request?(y/n): ";
                cin>>c;
            }

            sort(loan_requests.begin(), loan_requests.end(), Comp);
            if(loan_requests.size() != 0){
            cout << "\nThe loan requests will be processed in the given order:\n";
            cout << "\nAcc_no\t\tname\t\tLoan amount\n";
            for (int j = 0; j < i; j++)
            {
                long long ac_no = loan_requests[j].get_acc();
                Bank ob;
                Bank *acc_detail = ob.search_by_acc(ac_no, database);
                string name = (acc_detail)->getName();
                long long Loan_amt = loan_requests[j].getAmount();
                cout << ac_no << "\t\t" << name << "\t\t" << Loan_amt << "\n";
            }
            
            }
            break;
        }

        case 7:
        {
            cout << "Exiting the program...";
            break;
        }
        default:
        {
            cout<<"Invalid Input\n";
        }
        }
    } while (choice != 7);

    return 0;
}