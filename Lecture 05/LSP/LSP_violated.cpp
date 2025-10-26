#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Interfaces
class DepositOnly {
public:
    virtual void deposit(double amount) = 0;
};

class Withdrawable {
public:
    virtual void withdraw(double amount) = 0;
};

// Accounts
class SavingAccount : public DepositOnly, public Withdrawable {
private:
    double balance;

public:
    SavingAccount() { balance = 0; }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " in Savings Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Savings Account. New Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds in Savings Account!\n";
        }
    }
};

class CurrentAccount : public DepositOnly, public Withdrawable {
private:
    double balance;

public:
    CurrentAccount() { balance = 0; }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " in Current Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Current Account. New Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds in Current Account!\n";
        }
    }
};

class FixedTermAccount : public DepositOnly {
private:
    double balance;

public:
    FixedTermAccount() { balance = 0; }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " in Fixed Term Account. New Balance: " << balance << endl;
    }

    // Withdraw removed, FixedTermAccount cannot withdraw
};

// BankClient
class BankClient {
private:
    vector<DepositOnly*> depositAccounts;
    vector<Withdrawable*> withdrawAccounts;

public:
    BankClient(vector<DepositOnly*> deposits, vector<Withdrawable*> withdraws) {
        this->depositAccounts = deposits;
        this->withdrawAccounts = withdraws;
    }

    void processTransactions() {
        // Deposit for all accounts
        for (DepositOnly* acc : depositAccounts) {
            acc->deposit(1000);
        }

        // Withdraw for withdrawable accounts only
        for (Withdrawable* acc : withdrawAccounts) {
            acc->withdraw(500);
        }
    }
};

int main() {
    vector<DepositOnly*> depositAccounts;
    vector<Withdrawable*> withdrawAccounts;

    SavingAccount* sa = new SavingAccount();
    CurrentAccount* ca = new CurrentAccount();
    FixedTermAccount* fta = new FixedTermAccount();

    depositAccounts.push_back(sa);
    depositAccounts.push_back(ca);
    depositAccounts.push_back(fta);

    withdrawAccounts.push_back(sa);
    withdrawAccounts.push_back(ca);
    // FixedTermAccount not added to withdrawAccounts

    BankClient* client = new BankClient(depositAccounts, withdrawAccounts);
    client->processTransactions(); // No exception now

    return 0;
}
