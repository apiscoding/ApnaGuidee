#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Base class for Account
class Account {
protected:
    string accountHolder;
    int accountNumber;
    double balance;
    static int nextAccountNumber;

public:
    Account(string holder, double initialBalance)
        : accountHolder(holder), balance(initialBalance) {
        accountNumber = nextAccountNumber++;
    }

    virtual ~Account() {}

    int getAccountNumber() const {
        return accountNumber;
    }

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "Insufficient balance.\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const = 0;
};

int Account::nextAccountNumber = 1000;

// Derived class for SavingsAccount
class SavingsAccount : public Account {
    double interestRate;
public:
    SavingsAccount(string holder, double initialBalance, double rate)
        : Account(holder, initialBalance), interestRate(rate) {}

    void applyInterest() {
        balance += balance * interestRate;
    }

    void displayAccountInfo() const override {
        cout << "Savings Account\n";
        cout << "Account Holder: " << accountHolder << "\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Balance: $" << balance << "\n";
        cout << "Interest Rate: " << interestRate * 100 << "%\n";
    }
};

// Derived class for CheckingAccount
class CheckingAccount : public Account {
    double overdraftLimit;
public:
    CheckingAccount(string holder, double initialBalance, double limit)
        : Account(holder, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
        } else {
            cout << "Overdraft limit exceeded.\n";
        }
    }

    void displayAccountInfo() const override {
        cout << "Checking Account\n";
        cout << "Account Holder: " << accountHolder << "\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Balance: $" << balance << "\n";
        cout << "Overdraft Limit: $" << overdraftLimit << "\n";
    }
};

// Banking system management
class BankingSystem {
    vector<unique_ptr<Account>> accounts;

public:
    void openSavingsAccount(const string& holder, double initialBalance, double interestRate) {
        accounts.push_back(make_unique<SavingsAccount>(holder, initialBalance, interestRate));
    }

    void openCheckingAccount(const string& holder, double initialBalance, double overdraftLimit) {
        accounts.push_back(make_unique<CheckingAccount>(holder, initialBalance, overdraftLimit));
    }

    Account* getAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account.get();
            }
        }
        return nullptr;
    }

    void displayAllAccounts() const {
        for (const auto& account : accounts) {
            account->displayAccountInfo();
            cout << "------------------------\n";
        }
    }
};

// Main function
int main() {
    BankingSystem system;
    int choice;

    do {
        cout << "Banking System Menu:\n";
        cout << "1. Open Savings Account\n";
        cout << "2. Open Checking Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Display All Accounts\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string holder;
            double initialBalance, interestRate;
            cout << "Enter account holder name: ";
            cin >> holder;
            cout << "Enter initial balance: ";
            cin >> initialBalance;
            cout << "Enter interest rate (as a decimal, e.g., 0.05 for 5%): ";
            cin >> interestRate;
            system.openSavingsAccount(holder, initialBalance, interestRate);
            break;
        }
        case 2: {
            string holder;
            double initialBalance, overdraftLimit;
            cout << "Enter account holder name: ";
            cin >> holder;
            cout << "Enter initial balance: ";
            cin >> initialBalance;
            cout << "Enter overdraft limit: ";
            cin >> overdraftLimit;
            system.openCheckingAccount(holder, initialBalance, overdraftLimit);
            break;
        }
        case 3: {
            int accountNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            Account* account = system.getAccount(accountNumber);
            if (account) {
                account->deposit(amount);
            } else {
                cout << "Account not found.\n";
            }
            break;
        }
        case 4: {
            int accountNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            Account* account = system.getAccount(accountNumber);
            if (account) {
                account->withdraw(amount);
            } else {
                cout << "Account not found.\n";
            }
            break;
        }
        case 5: {
            int accountNumber;
            cout << "Enter account number: ";
            cin >> accountNumber;
            Account* account = system.getAccount(accountNumber);
            if (account) {
                cout << "Balance: $" << account->getBalance() << "\n";
            } else {
                cout << "Account not found.\n";
            }
            break;
        }
        case 6:
            system.displayAllAccounts();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
