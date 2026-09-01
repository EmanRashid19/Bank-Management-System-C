#pragma once
typedef struct
{
    int accountNumber;
    int customerID;
    char accountType[20];
    double balance;
    char status[20];
    char password[20];
    char openedDate[11];
} Account;
#define MINIMUM_DEPOSIT 1000.0
#define STATUS_ACTIVE "Active"
#define STATUS_FROZEN "Frozen"
#define STATUS_CLOSED "Closed"
#define SAVINGS_ACCOUNT "Savings"
#define CURRENT_ACCOUNT "Current"
int generateAccountNo();
int createAccount();
void inputAccountData(Account *account);
int saveAccount(const Account *account);
int searchAccountByNumber(int accountNumber, Account *account);
void displayAccount(const Account *account);
int validatePassword(const char password[]);
int checkBalance();
void displayBalance(const Account *account);
int changePassword();
int login(Account *account);