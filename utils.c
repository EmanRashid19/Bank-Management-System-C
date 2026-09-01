#include "utils.h"
#include "account.h"
#include "account.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
// validate Name
int validateName(const char name[]){
    if(name[0] == '\0'){
        return 0;
    }
    for(int i = 0  ; name[i] != '\0' ; i++){
        char ch = name[i];
        if(!isalpha(ch)){
            return 0;
        }
    }
    
    return 1;
}
//-------------------------------------------------------
//Va;lidate phone

int validatePhone(const char phone[]){
    int l = strlen(phone);
    if( l != 11 || phone[0] != '0' || phone[1] != '3'){
        return 0;
    }
    char group = phone[2];
    char code = phone[3];
    int validPrefix = 0;
    if(group >= '0' && group <= '5'){
        if(group != '5'){
            if(code >= '0' && code <= '9'){
                validPrefix = 1;
            }
        }else{
            if(code >= '5' && code <= '7'){
                validPrefix = 1;
            }
        }
    }
    if (!validPrefix){
        return 0;
    }
    
    for(int i = 0 ;phone[i] != '\0' ; i++){
        if(!isdigit(phone[i])){
            return 0;
        }
    }
    

    return 1;
}
//----------------------------------------------------------------
// Validate email
int validateEmail(const char email[]){
    int len = strlen(email);
    if(len == 0){
        return 0;
    }
    int atCount = 0;
    int atPosition = -1;
    int dotPosition = -1;
    for(int i = 0 ; i < len ; i++){
        char temp = email[i];
        if(temp == '@'){
            atCount++;
            atPosition = i;
        }
        if( temp == '.'){
            dotPosition = i;
        }
    }
    if (atPosition == 0 || atPosition == len-1 || dotPosition == 0 || dotPosition == len-1){
        return 0;
    }
    if (atCount != 1){
        return 0;
    }
    if (dotPosition < atPosition || dotPosition == atPosition+1){
        return 0;
    }
    return 1;
}

//--------------------------------------------------------------------------------
// validate CNIC
int validateCNIC(const char cnic[]){
    int len = strlen(cnic);
    if(len != 15){
        return 0;
    }
    if(cnic[5] != '-' || cnic[13] != '-'){
        return 0;
    }
    for(int i = 0 ; i < len ; i++ ){
        if(i == 5 || i == 13){
            continue;
        }else if(!isdigit(cnic[i])){
            return 0;
        }
    }
    return 1;
}

//-------------------------------------------------------------------
//Get current Date function
void getCurrentDate(char date[]){
    time_t now ;
    time(&now);
    struct tm *current = localtime(&now);
    strftime(date,11,"%Y-%m-%d",current);
}
//---------------------------------------------------------------------
// VAlidate DOB
int validateDOB(const char dob[]){
    int len = strlen(dob);
    if(len == 0){
        return 0;
    }
    if(dob[4] != '-' || dob[7] != '-'){
        return 0;
    }
}

//----------------------------------------------------------------------
// Update account
int updateAccount(const Account *account){
    FILE *fp = fopen("accounts.dat","rb+");
    if (fp == NULL){
        return 0; 
    }
    Account temp;
    while(fread(&temp,sizeof(temp),1,fp) == 1){
        if(temp.accountNumber == account->accountNumber){
            fseek(fp,-sizeof(temp),SEEK_CUR);
            size_t written = fwrite(account,sizeof(*account),1,fp);
            if(written){
                fclose(fp);
                return 1;
            }
            return 0;
        }
    }
    fclose(fp);
    printf("Account not Found.\n");
    return 0;
}

//-----------------------------------------------------------------------
