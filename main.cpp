#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

// Transaction structure
struct Transaction {
    string type;
    double amount;
};

// Account class
class Account {
public:
    int accountNumber;
    string ownerName;
    double balance;
    int pin;
    vector<Transaction> transactions;

    Account(int accNo, string name, double initialBalance, int pinCode)
        : accountNumber(accNo), ownerName(name), balance(initialBalance), pin(pinCode) {}

    void deposit(double amount) {
        balance += amount;
        transactions.push_back({"Deposit", amount});
        cout << "✅ Amount " << amount << " deposited successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "❌ Insufficient balance!\n";
        } else {
            balance -= amount;
            transactions.push_back({"Withdraw", amount});
            cout << "✅ Amount " << amount << " withdrawn successfully.\n";
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount > balance) {
            cout << "❌ Insufficient balance to transfer!\n";
        } else {
            balance -= amount;
            toAccount.balance += amount;
            transactions.push_back({"Transfer to " + to_string(toAccount.accountNumber), amount});
            toAccount.transactions.push_back({"Received from " + to_string(accountNumber), amount});
            cout << "✅ Amount " << amount << " transferred successfully to Account " << toAccount.accountNumber << ".\n";
        }
    }

    void displayInfo() const {
        cout << fixed << setprecision(2);
        cout << "\n--- Account Info ---\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Owner Name     : " << ownerName << "\n";
        cout << "Balance        : " << balance << "\n";
        cout << "--------------------\n";
    }
};

// Save accounts to file
void saveAccounts(const vector<Account> &accounts) {
    ofstream file("accounts.txt");
    if (!file.is_open()) {
        cout << "❌ Error saving file!\n";
        return;
    }
    for (auto &acc : accounts) {
        file << acc.accountNumber << "," << acc.ownerName << "," << acc.balance << "," << acc.pin << "\n";
    }
    file.close();
}

// Load accounts from file
void loadAccounts(vector<Account> &accounts, int &accountCounter) {
    ifstream file("accounts.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string accNoStr, name, balStr, pinStr;

        getline(ss, accNoStr, ',');
        getline(ss, name, ',');
        getline(ss, balStr, ',');
        getline(ss, pinStr, ',');

        int accNo = stoi(accNoStr);
        double balance = stod(balStr);
        int pin = stoi(pinStr);

        accounts.push_back(Account(accNo, name, balance, pin));
        if (accNo >= accountCounter)
            accountCounter = accNo + 1;
    }
    file.close();
}

// Find account by number and PIN
Account* findAccount(vector<Account> &accounts, int accNo, int pin) {
    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo && acc.pin == pin)
            return &acc;
    }
    return nullptr;
}

// Check if a PIN is already used
bool isPinUsed(const vector<Account> &accounts, int pin) {
    for (auto &acc : accounts)
        if (acc.pin == pin)
            return true;
    return false;
}

// Main function
int main() {
    system("chcp 65001 >nul"); // enable UTF-8 support
    vector<Account> accounts;
    int accountCounter = 1001;
    loadAccounts(accounts, accountCounter);

    int choice;
    cout << "=================================\n";
    cout << "     💰 CodeAlpha Banking System\n";
    cout << "         By: Mohammad Firoj\n";
    cout << "=================================\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Display Account Info\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double balance;
                int pin;
                cout << "Enter customer name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "Enter initial balance: ";
                cin >> balance;
                cout << "Create a 4-digit unique PIN: ";
                cin >> pin;

                if (isPinUsed(accounts, pin)) {
                    cout << "❌ This PIN is already used. Please choose another.\n";
                    break;
                }

                accounts.push_back(Account(accountCounter, name, balance, pin));
                cout << "✅ Account created successfully!\n";
                cout << "Your Account Number: " << accountCounter << "\n";
                accountCounter++;
                saveAccounts(accounts);
                break;
            }
            case 2: {
                int accNo, pin;
                double amount;
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter PIN: ";
                cin >> pin;

                Account *acc = findAccount(accounts, accNo, pin);
                if (!acc) {
                    cout << "❌ Invalid account number or PIN.\n";
                    break;
                }

                cout << "Enter deposit amount: ";
                cin >> amount;
                acc->deposit(amount);
                saveAccounts(accounts);
                break;
            }
            case 3: {
                int accNo, pin;
                double amount;
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter PIN: ";
                cin >> pin;

                Account *acc = findAccount(accounts, accNo, pin);
                if (!acc) {
                    cout << "❌ Invalid account number or PIN.\n";
                    break;
                }

                cout << "Enter withdrawal amount: ";
                cin >> amount;
                acc->withdraw(amount);
                saveAccounts(accounts);
                break;
            }
            case 4: {
                int fromAcc, toAcc, fromPin;
                double amount;
                cout << "Enter your account number: ";
                cin >> fromAcc;
                cout << "Enter your PIN: ";
                cin >> fromPin;

                Account *sender = findAccount(accounts, fromAcc, fromPin);
                if (!sender) {
                    cout << "❌ Invalid sender account or PIN.\n";
                    break;
                }

                cout << "Enter recipient account number: ";
                cin >> toAcc;

                Account *receiver = nullptr;
                for (auto &acc : accounts) {
                    if (acc.accountNumber == toAcc)
                        receiver = &acc;
                }

                if (!receiver) {
                    cout << "❌ Recipient account not found!\n";
                    break;
                }

                cout << "Enter amount to transfer: ";
                cin >> amount;
                sender->transfer(*receiver, amount);
                saveAccounts(accounts);
                break;
            }
            case 5: {
                int accNo, pin;
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter PIN: ";
                cin >> pin;

                Account *acc = findAccount(accounts, accNo, pin);
                if (!acc)
                    cout << "❌ Invalid account number or PIN.\n";
                else
                    acc->displayInfo();
                break;
            }
            case 6:
                cout << "👋 Exiting Secure Banking System. Thank you!\n";
                break;
            default:
                cout << "❌ Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
