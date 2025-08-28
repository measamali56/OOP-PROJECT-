#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Account {
protected:
    int accountId;
    string username;
    double balance;

public:
    Account(int id, string uname, double bal) : accountId(id), username(uname), balance(bal) {}

    int getAccountId() { return accountId; }
    string getUsername() { return username; }
    double getBalance() { return balance; }

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: $" << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        }
    }
};
class BankAccount : public Account {
private:
    string password;

public:
    BankAccount(int id, string uname, string pwd, double bal) : Account(id, uname, bal), password(pwd) {}

    string getPassword() { return password; }

    void transfer(BankAccount &receiver, double amount) {
        if (amount > balance) {
            cout << "Insufficient funds for transfer!" << endl;
        } else {
            balance -= amount;
            receiver.balance += amount;
            cout << "Transferred $" << amount << " to " << receiver.getUsername() << endl;
            cout << "Your new balance: $" << balance << endl;
        }
    }
};
class Bank {
private:
    vector<BankAccount> accounts;
    BankAccount* loggedInAccount = nullptr;

    BankAccount* findAccountById(int id) {
        for (auto &acc : accounts) {
            if (acc.getAccountId() == id) return &acc;
        }
        return nullptr;
    }

public:
    void signup() {
        int id;
        string name, pass;
        double bal;
        cout << "Enter account ID: ";
        cin >> id;
        cout << "Enter username: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> pass;
        cout << "Enter initial balance: $";
        cin >> bal;
        accounts.push_back(BankAccount(id, name, pass, bal));
        cout << "Account created successfully!\n";
    }

    void login() {
        int id;
        string pass;
        cout << "Enter account ID: ";
        cin >> id;
        cout << "Enter password: ";
        cin >> pass;
        for (auto &acc : accounts) {
            if (acc.getAccountId() == id && acc.getPassword() == pass) {
                loggedInAccount = &acc;
                cout << "Login successful! Welcome, " << acc.getUsername() << ".\n";
                return;
            }
        }
        cout << "Invalid ID or password.\n";
    }

    void logout() {
        if (loggedInAccount) {
            cout << "Logged out successfully.\n";
            loggedInAccount = nullptr;
        }
    }

    void showMenu() {
        int choice;
        while (loggedInAccount) {
            cout << "\n--- ATM Menu ---\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Transfer\n";
            cout << "4. Balance Inquiry\n";
            cout << "5. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                double amt;
                cout << "Enter deposit amount: ";
                cin >> amt;
                loggedInAccount->deposit(amt);
            }
            else if (choice == 2) {
                double amt;
                cout << "Enter withdraw amount: ";
                cin >> amt;
                loggedInAccount->withdraw(amt);
            }
            else if (choice == 3) {
                int id;
                double amt;
                cout << "Enter receiver account ID: ";
                cin >> id;
                BankAccount* receiver = findAccountById(id);
                if (receiver) {
                    cout << "Enter transfer amount: ";
                    cin >> amt;
                    loggedInAccount->transfer(*receiver, amt);
                } else {
                    cout << "Receiver account not found.\n";
                }
            }
            else if (choice == 4) {
                cout << "Current Balance: $" << loggedInAccount->getBalance() << endl;
            }
            else if (choice == 5) {
                logout();
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
    }
};

int main() {
    Bank b1;
    int choice;

    while (true) {
        cout << "\n--- Welcome to Simple ATM ---\n";
        cout << "1. Signup\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) b1.signup();
        else if (choice == 2) {
            b1.login();
            b1.showMenu();
        }
        else if (choice == 3) {
            cout << "Thank you for using ATM!\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
