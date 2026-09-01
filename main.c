#include <stdio.h>
#include "customer.h"
#include "account.h"
#include "transaction.h"

void customerManagement();
void accountManagement();
void bankOperations();
// Main menu
int main(){
    int choice;

    while(1){
        printf("=======================================\n"
               "        BANK MANAGEMENT SYSTEM         \n"
               "=======================================\n");
        printf("1. Customer Managment\n2. Account Managemant\n3. Banking Operations\n4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            customerManagement();
            break;
        case 2: 
            accountManagement();
            break;
        case 3:
            bankOperations();
            break;
        case 4:
            printf("Exited successfully");
            return 0 ;

        default:
            printf("Invalid choice try again.");
            continue;
        }
    }
    return 0;
}

// custommer management

void customerManagement(){
    int choice;
    int created;
    int exist;
    int customerID;
    Customer customer;
    while(1){
        printf("=======================================\n"
               "          CUSTOMER MANAGEMENT          \n"
               "=======================================\n");
        printf("1. Create Customer\n2. Search Customer\n3. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            created = createCustomer();
            if(created){
                printf("\nCustomer created successfully.\n");
            }else{
                printf("An error occured. Customer not created.");
            }
            break;
        case 2: 
            printf("Enter customer ID: ");
            scanf("%d", &customerID);
            exist = searchCustomerByID(customerID, &customer);
            if(exist){
                displayCustomer(&customer);
            }else{
                printf("Customer not found.");
            }
            break;
        case 3:
            return;  

        default:
            printf("Invalid choice try again.");
            continue;
        }
    }
}

//-----------------------------------------------
// account management
void accountManagement(){
    int choice;
    int created;
    int accountNumber;
    int exist;
    int checked;
    Account account;
    while(1){
        printf("=======================================\n"
               "          ACCOUNT MANAGEMENT          \n"
               "=======================================\n");
        printf("1. Create Account\n2. Search Account\n3. Check Balance\n4. Change password \n5. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                created = createAccount();
                if(created){
                    printf("Account created successfully\n");
                }else{
                    printf("Account could not be created\n");
                }
                break;
            case 2:
                printf("Enter Account Number: ");
                scanf("%d", &accountNumber);
                exist = searchAccountByNumber(accountNumber, &account);
                if(exist){
                    displayAccount(&account);
                }else{
                    printf("Account not found.\n");
                }
                break;
            case 3:
                checked = checkBalance();
                if(!checked){
                    printf("An error occured");
                }
                break;
            case 4:
                changePassword();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice.Try again: ");
                continue;
        }
    }

}

//--------------------------------------------------------
// bank operations
void bankOperations(){
    int choice;
    while(1){
        printf("=======================================\n"
               "             BANK OPERATIONS           \n"
               "=======================================\n");
        printf("1. Deposit Money\n2. Withdraw Money\n3. Tranfer Money\n4. Close Account \n5. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                depositMoney();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                transferMoney();
                break;
            case 4:
                closeAccount();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice.Try Again:");
                continue;
        }
    }

}
