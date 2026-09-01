#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "account.h"
#include "customer.h"
#include "utils.h"
//------------------------------------------------------
// Generate Account Number
int generateAccountNo(){
    FILE *fp = fopen("accounts.dat","rb");
    if(fp == NULL){
        return 10000001;
    }
    int largest = 0;
    Account temp;
    while(fread(&temp,sizeof(temp),1,fp) == 1){
        if(temp.accountNumber > largest){
            largest = temp.accountNumber;
        }
    }
    fclose(fp);
    return largest+1;
}
//-----------------------------------------------------
// save Account
int saveAccount(const Account *account){
    FILE *fp = fopen("accounts.dat","ab");
    if(fp == NULL){
        return 0;
    }
    size_t written = fwrite(account, sizeof(*account), 1, fp);
    fclose(fp);
    if(written == 1){
        return 1;
    }
    return 0;
}

//----------------------------------------------------------
// search account
int searchAccountByNumber(int accountNumber, Account *account){
    FILE *fp = fopen("accounts.dat","rb");
    if(fp == NULL){
        return 0;
    }
    Account record;
    while(fread(&record,sizeof(record),1,fp)== 1){
        if(record.accountNumber == accountNumber){
            *account = record;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

//-------------------------------------------------------------
// Display  Account
void displayAccount(const Account *account){
    printf("=================================================\n"
           "                ACCOUNT DETAILS\n"
           "=================================================\n");
    printf("%-20s : %d\n","Account Number", account->accountNumber);
    printf("%-20s : %d\n","Customer ID", account->customerID);
    printf("%-20s : %s\n","Account Type", account->accountType);
    printf("%-20s : %.2f\n","Balance", account->balance);
    printf("%-20s : %s\n","Status", account->status);
    printf("%-20s : %s\n","Password", account->password);
    printf("%-20s : %s\n","Opening Date", account->openedDate);
    printf("==================================================\n");
}
//---------------------------------------------------------------
// Input Account Data
void inputAccountData(Account *account){
    int choice;
    int valid = 0;
    char password[20];
    double initialDeposit;
    while(!valid){
        printf("Select Account Type: \n----------------------\n1- Savings\n2- Current\nchoice: ");
        scanf("%d",&choice);
        if(choice == 1){
            strcpy(account->accountType , SAVINGS_ACCOUNT);
            valid = 1;
        }else if(choice == 2){
            strcpy(account->accountType, CURRENT_ACCOUNT);
            valid = 1;
        }else{
            printf("Invalid choice. Try again:");
        }
    }
    valid = 0 ;
    while(!valid){
        printf("Enter Initial Deposit: ");
        scanf("%lf",&initialDeposit);
        if(initialDeposit >= MINIMUM_DEPOSIT){
            account->balance = initialDeposit ;
            valid = 1;
        }else{
            printf("Minimum opening deposit is 1000.0. Try again:");
        }
    }
    valid = 0;
    while(!valid){
        printf("Enter Password: ");
        scanf("%19s",password);
        if(validatePassword(password)){
            strcpy(account->password , password);
            valid = 1;
        }else{
            printf("Invalid password. Try again:");
        }
    }
}

//---------------------------------------------------------------
// Create Account
int createAccount(){
    Account account;
    int ID;
    printf("Enter Customer ID: ");
    scanf("%d",&ID);
    Customer accountHolder;
    int present = searchCustomerByID(ID,&accountHolder);
    if(!present){
        printf("Customer ID not found\n");
        return 0;
    }else{
        displayCustomer(&accountHolder);
        account.customerID = accountHolder.customerID;
        char choose;
        printf("Do you want to create Account.Y/N :");
        scanf(" %c",&choose); // space before %c skip the \n from the buffer left by scanf of ID
        if(choose == 'y' || choose == 'Y'){
            account.accountNumber = generateAccountNo();
            inputAccountData(&account);
            strcpy(account.status, STATUS_ACTIVE);
            getCurrentDate(account.openedDate);
            int saved = saveAccount(&account);
            if(saved){
                printf("Your account Number is: %d\n", account.accountNumber);
            }else{
                printf("Account could not saved");
            }
            return saved;

        }else {
            return 0;
        }
    }

}

//--------------------------------------------------
// Validate password
int validatePassword(const char password[]){
    int len = strlen(password);
    if(len < 6 || len >= 20){
        return 0;
    }
    if(strchr(password,' ') != NULL){
        return 0;
    }
    int digit = 0;
    int letter = 0;
    for (int i = 0 ; i < len ; i++){
        if(isalpha(password[i])){
            letter++;
        }else if(isdigit(password[i])){
            digit++;
        }
        if (digit >= 1 && letter >= 1){
            return 1;
        }
    }
    return 0;
}
//---------------------------------------------------
// Check balance
int checkBalance(){
    int accountNumber;
    Account account;
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    int exist = searchAccountByNumber(accountNumber , &account);
    if(exist){
        displayBalance(&account);
        return 1;
    }else{
        printf("Account not found.\n");
        return 0;
    }
}

//---------------------------------------------------------
// display balance
void displayBalance(const Account *account){
     printf("=================================================\n"
           "                ACCOUNT DETAILS\n"
           "=================================================\n");
    printf("%-20s : %d\n","Account Number", account->accountNumber);
    printf("%-20s : %s\n","Account Type", account->accountType);
    printf("%-20s : %.2f\n","Balance", account->balance);
    printf("%-20s : %s\n","Status", account->status);
    printf("==================================================\n");
}

//-------------------------------------------------------------------------
// change password
int changePassword(){
    int accountNumber;
    char password[20];
    char newPassword[20];
    char confirmPassword[20];
    Account account;
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    int exist = searchAccountByNumber(accountNumber , &account);
    if(strcmp(account.status, STATUS_ACTIVE) != 0){
    printf("Account is not active.\n");
    return 0;
    }
    if(exist){
        printf("Enter current password: ");
        scanf("%19s", password);
        if (strcmp(account.password,password) == 0){
            printf("Enter new password: ");
            scanf("%19s", newPassword);
            int valid = validatePassword(newPassword);
            if(valid){
                if(strcmp(password, newPassword) == 0){
                    printf("New password must be different from the current password.\n");
                    return 0;
                }
                printf("Confirm password: ");
                scanf("%19s", confirmPassword);
                if(strcmp(confirmPassword , newPassword ) == 0){
                    strcpy(account.password , newPassword);
                    int updated = updateAccount(&account);
                    if(!updated){
                        printf("Password could not be updated.");
                        return 0;
                    }
                    printf("Password changed successfully.");
                }else{
                    printf("Password not matched.");
                    return 0;
                }
            }else{
                printf("Invalid password.");
                return 0;
            }

        }else{
            printf("Incorrect password");
            return 0;
        }
    }else{
        printf("Account not found");
        return 0;
    }
    return 1;
}

int login(Account *account){
    int accountNumber;
    char password[20];
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    printf("Enter password: ");
    scanf("%19s", password);
    int exist = searchAccountByNumber(accountNumber , account);
    if(strcmp(account->status, STATUS_ACTIVE) != 0){
    printf("This account is closed.\n");
    return 0;
    }
    if(exist){
        if(strcmp(account->password, password) == 0){
            printf("Logged IN successfully");
        }else{
            printf("Incorrect password");
            return 0;
        }
    }else{
        printf("Account not found");
        return 0;
    }
    return 1;
}



