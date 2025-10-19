/*
 * ============================================
 * VERSION 1: BASIC ATM (2021 - Original Code)
 * ============================================
 * Simple ATM with basic functions
 * Written when learning C programming
 * Uses simple logic and basic features
 */

#include <stdio.h>
#include <stdlib.h>

// Simple global variables
float balance = 5000.00;
int pin = 1234;

// Function declarations
void menu();
void checkBalance();
void deposit();
void withdraw();

int main() {
    int inputPin;
    int choice;
    
    // Simple PIN check
    printf("*** WELCOME TO ATM ***\n");
    printf("Enter PIN: ");
    scanf("%d", &inputPin);
    
    if(inputPin != pin) {
        printf("Wrong PIN!\n");
        return 0;
    }
    
    printf("PIN Correct!\n\n");
    
    // Main loop
    while(1) {
        menu();
        scanf("%d", &choice);
        
        if(choice == 1) {
            checkBalance();
        }
        else if(choice == 2) {
            deposit();
        }
        else if(choice == 3) {
            withdraw();
        }
        else if(choice == 4) {
            printf("Thank you!\n");
            break;
        }
        else {
            printf("Wrong choice!\n");
        }
    }
    
    return 0;
}

// Show menu
void menu() {
    printf("\n=== ATM MENU ===\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Exit\n");
    printf("Choice: ");
}

// Check balance function
void checkBalance() {
    printf("\nYour balance: $%.2f\n", balance);
}

// Deposit money
void deposit() {
    float amount;
    printf("\nEnter amount: $");
    scanf("%f", &amount);
    
    if(amount > 0) {
        balance = balance + amount;
        printf("Deposit successful!\n");
        printf("New balance: $%.2f\n", balance);
    }
    else {
        printf("Invalid amount!\n");
    }
}

// Withdraw money
void withdraw() {
    float amount;
    printf("\nEnter amount: $");
    scanf("%f", &amount);
    
    if(amount > balance) {
        printf("Not enough money!\n");
    }
    else if(amount <= 0) {
        printf("Invalid amount!\n");
    }
    else {
        balance = balance - amount;
        printf("Withdrawal successful!\n");
        printf("Remaining balance: $%.2f\n", balance);
    }
}
