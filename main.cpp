#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class account
{
public:
    string account_holder;
    string joint_holder;
    int balance;
    string account_type;
    string pin;
    long long account_number;
    static long long next_account_number;

    // Constructors
    account(string accholdername, int bal, string typeofacc, string pc)
        : account_holder(accholdername), balance(bal), account_type(typeofacc), pin(pc)
    {
        account_number = next_account_number++;
    }

    account(string accholdername, string jointholdername, int bal, string typeofacc, string pc)
        : account_holder(accholdername), joint_holder(jointholdername), balance(bal), account_type(typeofacc), pin(pc)
    {
        account_number = next_account_number++;
    }
};

long long account::next_account_number = 100000;
vector<account> accts;

void display_details(long long accnum)
{
    for (const auto &it : accts)
    {
        if (it.account_number == accnum)
        {
            cout << "\nAccount Details:\n";
            cout << "Account Number: " << it.account_number << "\n";
            cout << "Account Holder: " << it.account_holder << "\n";
            if (!it.joint_holder.empty())
            {
                cout << "Joint Holder: " << it.joint_holder << "\n";
            }
            cout << "Account Type: " << it.account_type << "\n";
            cout << "Balance: " << it.balance << "\n";
            return;
        }
    }
    cout << "Account not found!\n";
}

bool create_account()
{
    system("cls");
    string accholder_name, joint_holder, pin, typeofacc;
    int choice, balance;

    cout << "\nENTER YOUR DETAILS HERE : ";
    cout << "\nName of Account Holder : ";
    cin >> accholder_name;

    cout << "\nDo you want a joint account? (YES/NO): ";
    cin >> joint_holder;

    cout << "\nEnter the pin: ";
    cin >> pin;

    cout << "\nEnter the type of account: \n1 - Savings Account\n2 - Current Account\nEnter your choice: ";
    cin >> choice;
    typeofacc = (choice == 1) ? "Savings" : "Current";

    cout << "\nEnter initial balance: ";
    cin >> balance;

    if (typeofacc == "Current" && balance < 10000)
    {
        cout << "INSUFFICIENT BALANCE FOR CURRENT ACCOUNT!";
        return false;
    }

    if (joint_holder == "YES")
    {
        cout << "Enter Joint Holder Name: ";
        cin >> joint_holder;
        accts.emplace_back(accholder_name, joint_holder, balance, typeofacc, pin);
    }
    else
    {
        accts.emplace_back(accholder_name, balance, typeofacc, pin);
    }

    cout << "ACCOUNT CREATED SUCCESSFULLY!";
    display_details(accts.back().account_number);
    return true;
}

bool change_pin()
{
    long long accnum;
    cout << "Enter your account number: ";
    cin >> accnum;

    for (auto &it : accts)
    {
        if (it.account_number == accnum)
        {
            string newpin, oldpin;
            cout << "Enter old pin: ";
            cin >> oldpin;
            if (oldpin == it.pin)
            {
                cout << "Enter new pin: ";
                cin >> newpin;
                it.pin = newpin;
                cout << "Pin updated successfully!";
                return true;
            }
            else
            {
                cout << "Invalid Pin. Try Again";
                return false;
            }
        }
    }
    cout << "Account not found!";
    return false;
}

bool withdraw_from_account()
{
    long long accnum;
    cout << "Enter your account number: ";
    cin >> accnum;

    for (auto &it : accts)
    {
        if (it.account_number == accnum)
        {
            string pinInput;
            cout << "Enter pin: ";
            cin >> pinInput;
            if (pinInput == it.pin)
            {
                int withdrawal_amount;
                cout << "Enter the amount to withdraw: ";
                cin >> withdrawal_amount;
                if (it.balance >= withdrawal_amount)
                {
                    it.balance -= withdrawal_amount;
                    cout << "Withdrawal successful! Updated balance: " << it.balance;
                    return true;
                }
                else
                {
                    cout << "Insufficient Balance!";
                    return false;
                }
            }
            else
            {
                cout << "Invalid Pin!";
                return false;
            }
        }
    }
    cout << "Account not found!";
    return false;
}

bool close_account()
{
    long long accnum;
    cout << "Enter your account number: ";
    cin >> accnum;

    auto it = remove_if(accts.begin(), accts.end(),
                        [accnum](const account &acc)
                        { return acc.account_number == accnum; });
    if (it != accts.end())
    {
        accts.erase(it, accts.end());
        cout << "Account closed successfully!";
        return true;
    }
    cout << "Account not found!";
    return false;
}

int main()
{
    int choice;
    do
    {
        cout << "\nBanking System Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Change Pin\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Close Account\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            change_pin();
            break;
        case 3:
            withdraw_from_account();
            break;
        case 4:
            close_account();
            break;
        case 5:
            cout << "Exiting...";
            break;
        default:
            cout << "Invalid option! Try again.";
        }
    } while (choice != 5);
    return 0;
}