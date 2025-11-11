Banking Management System (C++)

A simple, file-based Banking Management System built using C++. It demonstrates real-world banking operations such as account creation, deposits, withdrawals, fund transfers, and viewing account details. The project follows Object-Oriented Programming principles and uses persistent storage through a text file.

Overview

This system simulates basic banking functionalities with PIN-based authentication. It uses:

Classes and Objects

Vectors

File Handling

Transaction Logging

All account data is stored and retrieved from a local file (accounts.txt).

Key Features
1. Account Creation

Auto-generated unique account number

Accepts customer name and initial balance

Requires a 4-digit PIN

Stores data in accounts.txt

2. Deposit Money

Validates account number and PIN

Updates balance and transaction record

3. Withdraw Money

Validates account number and PIN

Checks available balance

Updates transaction record

4. Fund Transfer

Authenticates sender account

Allows transfer between two accounts

Records transactions for sender and receiver

5. View Account Information

Displays:

Account number

Owner name

Current balance

Data Storage Format

File: accounts.txt

Each account is stored as:

accountNumber,ownerName,balance,pin

Project Structure
Banking-System/
│
├── main.cpp
├── accounts.txt
└── README.md

Technologies Used

C++

Object-Oriented Programming

STL (Vectors)

File Input/Output

Exception Handling

Basic validation

How to Run
Compile:
g++ main.cpp -o banking_app

Execute:
./banking_app

Security Notes

This project is created for learning purposes only.

PIN is stored in plain text

No encryption

No database integration

In real systems, you should use:

Secure hashing (SHA-256, bcrypt)

Proper database storage

Authentication and access control

Input sanitization

Additional Notes

Output uses UTF-8 symbols

Validate user inputs to avoid runtime errors

Keep accounts.txt in the same directory as main.cpp

Author

Mohammad Firoj
CodeAlpha Internship Project
