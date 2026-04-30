#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

class Bank
{
public:
    int accNo, pin;
    string name;
    float balance;
};

int getPIN()
{
    char ch;
    string pin = "";

    while (true)
    {
        ch = _getch();

        if (ch == 13) // Enter
            break;

        if (ch == 8) // Backspace
        {
            if (!pin.empty())
            {
                pin.pop_back();
                cout << "\b \b";
            }
        }
        else if (isdigit(ch))
        {
            pin += ch;
            cout << "*";
        }
    }

    cout << endl;
    return stoi(pin);
}

void addHistory(string text)
{
    ofstream file("history.txt", ios::app);
    file << text << endl;
    file.close();
}

void createAccount()
{
    Bank b, check;
    bool exists = false;

    cout << "\nEnter Account Number: ";
    cin >> b.accNo;
    cin.ignore();

    ifstream readFile("bank.txt");

    while (readFile >> check.accNo)
    {
        readFile.ignore();
        getline(readFile, check.name);
        readFile >> check.pin;
        readFile >> check.balance;

        if (check.accNo == b.accNo)
        {
            exists = true;
            break;
        }
    }

    readFile.close();

    if (exists)
    {
        cout << "\nAccount Number Already Exists!\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, b.name);

    cout << "Set 4-digit PIN: ";
    b.pin = getPIN();

    cout << "Enter Initial Balance: ";
    cin >> b.balance;

    ofstream file("bank.txt", ios::app);

    file << b.accNo << endl;
    file << b.name << endl;
    file << b.pin << endl;
    file << b.balance << endl;

    file.close();

    addHistory("New Account Created: " + b.name);

    cout << "\nAccount Created Successfully!\n";
}

void searchAccount()
{
    Bank b;
    int num, p;
    bool found = false;

    ifstream file("bank.txt");

    cout << "\nEnter Account Number: ";
    cin >> num;

    cout << "Enter PIN: ";
    p = getPIN();

    while (file >> b.accNo)
    {
        file.ignore();
        getline(file, b.name);
        file >> b.pin;
        file >> b.balance;

        if (b.accNo == num && b.pin == p)
        {
            found = true;
            cout << "\nAccount Found\n";
            cout << "Account Number: " << b.accNo << endl;
            cout << "Name: " << b.name << endl;
            cout << "Balance: " << b.balance << endl;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found / Invalid PIN\n";

    file.close();
}

void depositMoney()
{
    Bank b;
    int num, p;
    float amt;
    bool found = false;

    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Account Number: ";
    cin >> num;

    cout << "Enter PIN: ";
    p = getPIN();

    cout << "Enter Deposit Amount: ";
    cin >> amt;

    while (file >> b.accNo)
    {
        file.ignore();
        getline(file, b.name);
        file >> b.pin;
        file >> b.balance;

        if (!found && b.accNo == num && b.pin == p)
        {
            found = true;
            b.balance += amt;
            addHistory("Deposited Rs." + to_string((int)amt) + " to " + b.name);
            cout << "\nDeposit Successful!\n";
        }

        temp << b.accNo << endl;
        temp << b.name << endl;
        temp << b.pin << endl;
        temp << b.balance << endl;
    }

    if (!found)
        cout << "\nAccount Not Found / Invalid PIN\n";

    file.close();
    temp.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
}

void withdrawMoney()
{
    Bank b;
    int num, p;
    float amt;
    bool found = false;

    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter Account Number: ";
    cin >> num;

    cout << "Enter PIN: ";
    p = getPIN();

    cout << "Enter Withdraw Amount: ";
    cin >> amt;

    while (file >> b.accNo)
    {
        file.ignore();
        getline(file, b.name);
        file >> b.pin;
        file >> b.balance;

        if (!found && b.accNo == num && b.pin == p)
        {
            found = true;

            if (amt <= b.balance)
            {
                b.balance -= amt;
                addHistory("Withdrawn Rs." + to_string((int)amt) + " from " + b.name);
                cout << "\nWithdraw Successful!\n";
            }
            else
            {
                cout << "\nInsufficient Balance!\n";
            }
        }

        temp << b.accNo << endl;
        temp << b.name << endl;
        temp << b.pin << endl;
        temp << b.balance << endl;
    }

    if (!found)
        cout << "\nAccount Not Found / Invalid PIN\n";

    file.close();
    temp.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
}

void bankHistory()
{
    ifstream file("history.txt");
    string line;

    cout << "\n====== BANK HISTORY ======\n";

    while (getline(file, line))
        cout << line << endl;

    file.close();
}

void individualHistory()
{
    string name;
    string line;

    cin.ignore();
    cout << "\nEnter Account Holder Name: ";
    getline(cin, name);

    ifstream file("history.txt");

    cout << "\n====== INDIVIDUAL HISTORY ======\n";

    while (getline(file, line))
    {
        if (line.find(name) != string::npos)
            cout << line << endl;
    }

    file.close();
}

void showHistoryMenu()
{
    int ch;

    cout << "\n1. Bank History";
    cout << "\n2. Individual Account History";
    cout << "\nEnter Choice: ";
    cin >> ch;

    if (ch == 1)
        bankHistory();
    else if (ch == 2)
        individualHistory();
    else
        cout << "\nInvalid Choice!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n====== BANKING SYSTEM ======\n";
        cout << "1. Create Account\n";
        cout << "2. Search Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transaction History\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            searchAccount();
            break;
        case 3:
            depositMoney();
            break;
        case 4:
            withdrawMoney();
            break;
        case 5:
            showHistoryMenu();
            break;
        case 6:
            cout << "\nThank You!\n";
            break;
        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
