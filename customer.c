#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "utils.h"
#include "account.h"
//----------------------------------------------------------
// costumer ID generation
int generateCustomerID(){
    int largestID = 0;

    FILE *fp = fopen("customers.dat","rb");
    if(fp == NULL){
        return 1001;
    }
    
    Customer temp;
    while(fread(&temp,sizeof(temp),1,fp) == 1){
        if(temp.customerID > largestID){
            largestID = temp.customerID;
        }
    }
    fclose(fp);
    return largestID +1;
}
//------------------------------------------------------
// Check duplicate CNIC
int isCNICExists(const char cnic[]){
    FILE *fp = fopen("customers.dat","rb");
    int found = 0;
    if (fp == NULL){
        return found;
    }
    Customer temp;
    while(fread(&temp,sizeof(temp),1,fp) == 1){
        if(strcmp(temp.cnic,cnic) == 0 ){
            found = 1;  // already exist
            break;
        }
    }
    fclose(fp);
    return found;
}
//-------------------------------------------------------------
//To Save Customer
int saveCustomer(const Customer *customer){
    FILE *fp = fopen("customers.dat","ab");
    if(fp == NULL){
        return 0;
    }
    size_t written = fwrite(customer, sizeof(*customer), 1, fp);
    fclose(fp);
    if(written == 1){
        return 1;
    }
    return 0;

}


//---------------------------------------------------------------
// input customer Data
void inputCustomerData(Customer *customer){
    char first_name[20];
    char last_name[20];
    char cnic[16];
    char phone[12];
    char email[50];
    char dateOfBirth[11];
    char address[100];
    int valid = 0;
    while(!valid){
        printf("Enter First Name: ");
        scanf("%19s",first_name);
        valid = validateName(first_name);
        if(valid == 0){
            printf("Invalid name.Please Enter Again: \n");
        }else{
            strcpy( customer->firstName , first_name);
           
        }
    }
    valid = 0;
    while(!valid){
        printf("Enter Last Name: ");
        scanf("%19s",last_name);
        valid = validateName(last_name);
        if(valid == 0){
            printf("Invalid name.Please Enter Again: \n");
        }else{
            strcpy( customer->lastName , last_name);
           
        }
    }
    valid = 0;
    while(!valid){
        printf("Enter CNIC: ");
        scanf("%15s",cnic);
        valid = validateCNIC(cnic);
        if(valid == 0){
            printf("Invalid CNIC.Please Enter Again: \n");
        }else{
            int exist = isCNICExists(cnic);
            if(exist){
                printf("CNIC already exist.Please enter again:");
                valid = 0 ;
            }else{
            strcpy( customer->cnic , cnic);   
            }
        }
    }
    valid = 0;
    while(!valid){
        printf("Enter phone number: ");
        scanf("%11s",phone);
        valid = validatePhone(phone);
        if(valid == 0){
            printf("Invalid Phone Number.Please Enter Again");
        }else{
            strcpy( customer->phone , phone);
           
        }
    }
    valid = 0;
    while(!valid){
        printf("Enter email: ");
        scanf("%49s",email);
        valid = validateEmail(email);
        if(valid == 0){
            printf("Invalid Email.Please Enter Again");
        }else{
            strcpy( customer->email , email);
           
        }
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    valid = 0;
    while(!valid){
        printf("Enter address: ");
        fgets(address,sizeof(address),stdin);
        address[strcspn(address,"\n")] = '\0';
        if(strlen(address) == 0){
            valid = 0;
            printf("Invalid address.Please Enter Again");
        }else{
            valid = 1;
            strcpy( customer->address , address);
        }
           
    }
    
    valid = 0;
    while(!valid){
        printf("Enter Date of Birth YYYY-MM-DD: ");
        scanf("%10s",dateOfBirth);
        valid = validateDOB(dateOfBirth);
        if(valid == 0){
            printf("Invalid DOB.Please Enter Again");
        }else{
            strcpy( customer->dateOfBirth , dateOfBirth);
           
        }
    }
}

//--------------------------------------------------------------
// Create customer
int createCustomer(){
    Customer customer;
    customer.customerID = generateCustomerID();
    inputCustomerData(&customer);    
    getCurrentDate(customer.createdAt);
    printf("Customer ID: %d", customer.customerID);
    return saveCustomer(&customer);
}

//----------------------------------------------------------------
// Searching customer by  ID
int searchCustomerByID(int customerID, Customer *customer){
    FILE *fp = fopen("customers.dat","rb");
    if(fp == NULL){
        return 0;
    }
    Customer temp;
    while(fread(&temp,sizeof(temp),1,fp) == 1){
        if(temp.customerID == customerID){
            *customer = temp ;
            fclose(fp);
            return 1;    
        }
    }
    fclose(fp);
    return 0;
}
//------------------------------------------------------------------
// Display customer
void displayCustomer(const Customer *customer){
    printf("=================================================\n"
           "                CUSTOMER DETAILS\n"
           "=================================================\n");
    printf("%-20s : %d\n","Customer ID", customer->customerID);
    printf("%-20s : %s\n","First Name", customer->firstName);
    printf("%-20s : %s\n","Last Name", customer->lastName);
    printf("%-20s : %s\n","CNIC", customer->cnic);
    printf("%-20s : %s\n","Phone", customer->phone);
    printf("%-20s : %s\n","Email", customer->email);
    printf("%-20s : %s\n","Address", customer->address);
    printf("%-20s : %s\n","Date of Birth", customer->dateOfBirth);
    printf("%-20s : %s\n","Date of creation", customer->createdAt);
    printf("==================================================\n");
}