#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "account.h"
#include "utils.h"
// Withdraw money
int withdrawMoney(){
    Account account;
    int accountNumber;
    double withdrawAmount;
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    int exist = searchAccountByNumber(accountNumber, &account);
    if(exist){
        if(strcmp(account.status, STATUS_ACTIVE) == 0){
            displayAccount(&account);
            printf("Enter Withdrawal Amount: ");
            scanf("%lf", &withdrawAmount);
            if(withdrawAmount > 0 && withdrawAmount <= account.balance){
                account.balance -= withdrawAmount;
                int updated = updateAccount(&account);
                if(updated){
                    printf("Withdrawal successful");
                    printf("New Balance: %.2lf",account.balance);
                    return 1;
                }else{
                    printf("Error occured");
                    return 0;
                }
            }else{
                printf("Invalid Amount.\n Amount must not be zero or exceed the available balance.");
                return 0;
            }

        }else{
            printf("Sorry! Your Account Status is: %s\n Transaction can't be completed", account.status);
            return 0;
        }
    }else{
        printf("Account not found. ");
        return 0;
    }
}
//--------------------------------------------------------------------------
// deposit money
int depositMoney(){
    Account account;
    int accountNumber;
    double depositAmount;
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    int exist = searchAccountByNumber(accountNumber, &account);
    if(exist){
        if(strcmp(account.status, STATUS_ACTIVE) == 0){
            displayAccount(&account);
            printf("Enter Deposit Amount: ");
            scanf("%lf", &depositAmount);
            if(depositAmount > 0){
                account.balance += depositAmount;
                int updated = updateAccount(&account);
                if(updated){
                    printf("Deposit successful");
                    printf("New Balance: %.2lf",account.balance);
                    return 1;
                }else{
                    printf("Error occured");
                    return 0;
                }
            }else{
                printf("Invalid Amount");
                return 0;
            }

        }else{
            printf("Sorry! Your Account Status is: %s\n Transaction can't be completed", account.status);
            return 0;
        }
    }else{
        printf("Account not found. ");
        return 0;
    }
}

//----------------------------------------------------------------------------
// transfer Money
int transferMoney(){
    Account senderAccount;
    Account receiverAccount;
    int senderAccountNumber;
    int receiverAccountNumber;
    int exist;
    double transferAmount;
    int updated;

    printf("Enter your account number:");
    scanf("%d",&senderAccountNumber);
    exist = searchAccountByNumber(senderAccountNumber, &senderAccount );
    if(exist){
        printf("Enter receiver account Number:");
        scanf("%d",&receiverAccount);
        if(senderAccountNumber == receiverAccountNumber){
            return 0;
        }
        exist = searchAccountByNumber(receiverAccountNumber, &receiverAccount);
        if(exist){
            if(strcmp(senderAccount.status, STATUS_ACTIVE) == 0 && strcmp(receiverAccount.status , STATUS_ACTIVE) == 0){

                printf("Enter Amount to transfer: ");
                scanf("%lf", &transferAmount);
                if(senderAccount.balance >= transferAmount && transferAmount > 0){
                    senderAccount.balance -= transferAmount;
                    receiverAccount.balance += transferAmount;
                    updated = updateAccount(&senderAccount);
                    if(updated){
                        updated = updateAccount(&receiverAccount);
                        if(!updated){
                            printf("Updation unsuccessful");
                            return 0;
                        }
                    }else{
                        printf("updation unsuccesful");
                        return 0;
                    }
    
                }
            }else{
                printf("Sender Account Status : %s \n Receiver Account Status : %s", senderAccount.status, receiverAccount.status);
                return 0;
            }
        }else{
            printf("Receiver Account not found.");
            return 0;
        }
    }else{
        printf("Sender Account not found.");
        return 0;
    }
    printf("Transfer successful.\n");
    printf("Transferred Amount : %.2lf\n", transferAmount);
    printf("Sender Balance     : %.2lf\n", senderAccount.balance);
    return 1;
}

//-----------------------------------------------------------------------
// close Account
int closeAccount(){
    int accountNumber;
    int choice;
    Account account;
    int again = 1;
    int success;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    int exist = searchAccountByNumber(accountNumber,&account);
    if(exist){
        if(strcmp(account.status,STATUS_ACTIVE) == 0){
            if(account.balance > 0.0){
                while(again){
                    printf("Your account balance = %.2lf", account.balance);
                    printf("1- Withdraw all amount \n2- Transfer to another account");
                    scanf("%d",&choice);
                    switch (choice){
                    case 1:
                        success = withdrawMoney();
                        if(!success){
                            return 0;
                        }
                        searchAccountByNumber(accountNumber,&account);
                        if(account.balance != 0.0){
                            continue;
                        }
                        again = 0;
                        break;
                    
                    case 2:
                        success = transferMoney();
                        if(!success){
                            return 0;
                        }
                        searchAccountByNumber(accountNumber,&account);
                        if(account.balance != 0.0){
                            continue;
                        }
                        again = 0;
                        break;
    
                    default:
                        printf("Invalid choice.Try again");
                    }         
                }

                if(account.balance == 0.0){
                    printf("Please confirm. You want to close account. Y/N");
                    char choose;
                    scanf(" %c",&choose);
                    if(choose == 'Y' || choose == 'y'){
                        strcpy(account.status,STATUS_CLOSED);
                    }else{
                        return 0;
                    }
                        
                }else{
                    printf("Account can't be closed bcz balance is not zero.");
                    return 0;
                }
            }else{
                strcpy(account.status,STATUS_CLOSED);
            }
        }else{
            printf("Account already closed.");
            return 0;
        }
    }else{
        printf("Account not found");
        return 0;
    }
    int updated = updateAccount(&account);
    if (updated){
        printf("account closed successfully");
        return 1;
    }else{
        return 0;
    }
}
