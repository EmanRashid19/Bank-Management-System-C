#ifndef CUSTOMER_H// these are header gurds instead of theses three statements 
#define CUSTOMER_H// we can write #pragma once
typedef struct {
    int customerID;
    char firstName[20];
    char lastName[20];
    char cnic[16];
    char phone[12];
    char email[50];
    char address[100];
    char dateOfBirth[11];
    char createdAt[11];
}Customer;
#endif//

int generateCustomerID();
int isCNICExists(const char cnic[]);
int saveCustomer(const Customer *customer);
void inputCustomerData();
int createCustomer();
int searchCustomerByID(int customerID, Customer *customer);
void displayCustomer(const Customer *customer);