#pragma once
#include "account.h"

int validateName(const char name[]);
int validatePhone(const char phone[]);
int validateEmail(const char email[]);
int validateCNIC(const char cnic[]);
int validateDOB(const char dob[]);
void getCurrentDate(char date[]);
int updateAccount(const Account *account);
