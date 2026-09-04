# 🏦 Bank Management System in C

A console-based Bank Management System developed in **C** as a programming project to practice core C programming concepts, modular programming, structures, pointers, file handling, validation, and Git/GitHub.

---

## 📌 About the Project

The Bank Management System is a menu-driven console application that allows users to manage basic banking information.

The project is divided into separate modules for:

- 👤 Customer Management
- 💳 Account Management
- 💰 Transaction Management

Each major module contains its own **header (`.h`) and source (`.c`) files**, making the project more organized and easier to maintain.

The system uses **file handling** to store and retrieve data so that information can persist between program executions.

---

## 🚀 Features

### 👤 Customer Management

- Create a new customer
- Generate a unique Customer ID
- Store customer information
- Search for customers by Customer ID
- Validate customer information
- Store customer records in a data file

### 💳 Account Management

- Create a bank account
- Generate a unique Account Number
- Associate an account with a customer
- Support different account types
- Store account balance
- Maintain account status
- Set account password
- Store account information in a data file

### 💰 Transaction Management

- Perform banking transactions
- Manage account balance
- Support deposit operations
- Support withdrawal operations
- Validate transaction-related input
- Maintain transaction information

---

## 🛠️ Technologies & Concepts Used

The project is developed using:

- **C Programming Language**
- Structures (`struct`)
- Functions
- Pointers
- Arrays
- Strings
- File Handling
- Header Files
- Multiple Source Files
- Preprocessor Macros
- Input Validation
- Modular Programming

---

## 📂 Project Structure

```text
Bank-Management-System/
│
├── main.c
│
├── customer.c
├── customer.h
│
├── account.c
├── account.h
│
├── transaction.c
├── transaction.h
│
├── README.md
├── .gitignore
│
├── customers.dat
├── accounts.dat
└── transactions.dat
