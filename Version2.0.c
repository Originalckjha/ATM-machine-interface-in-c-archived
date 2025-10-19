/*
 * ============================================
 * VERSION 2: REFINED ATM (2025 - AI Enhanced)
 * ============================================
 * Enhanced version with Claude AI assistance
 * Added: Better validation, security features,
 * multiple attempts, transaction history,
 * PIN change, receipts, and professional UI
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 3
#define MAX_TRANSACTIONS 100
#define MIN_PIN_LENGTH 4

// Structure to store transaction history
typedef struct {
    char type[20];
    float amount;
    float balanceAfter;
    char timestamp[26];
} Transaction;

// Global variables with better organization
float balance = 5000.00;
char currentPIN[10] = "1234";
Transaction history[MAX_TRANSACTIONS];
int transactionCount = 0;

// Enhanced function declarations
int authenticateUser();
void displayMainMenu();
void checkBalance();
void depositMoney();
void withdrawMoney();
void changePIN();
void viewTransactionHistory();
void printReceipt(char operation[], float amount);
void addTransaction(char type[], float amount);
void getCurrentTime(char* buffer);
void clearInputBuffer();
void pauseScreen();

int main() {
    int choice;
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║   WELCOME TO SECURE ATM SYSTEM 2025   ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    // Enhanced authentication with multiple attempts
    if (!authenticateUser()) {
        printf("\n⚠️  SECURITY ALERT: Too many failed attempts.\n");
        printf("Card has been temporarily blocked.\n");
        return 1;
    }
    
    printf("\n✓ Authentication Successful!\n");
    pauseScreen();
    
    // Main program loop
    while (1) {
        displayMainMenu();
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\n❌ Invalid input! Please enter a number.\n");
            pauseScreen();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                changePIN();
                break;
            case 5:
                viewTransactionHistory();
                break;
            case 6:
                printf("\n╔════════════════════════════════════════╗\n");
                printf("║     Thank you for using our ATM!      ║\n");
                printf("║         Have a wonderful day!         ║\n");
                printf("╚════════════════════════════════════════╝\n");
                return 0;
            default:
                printf("\n❌ Invalid choice! Please select 1-6.\n");
        }
        
        pauseScreen();
    }
    
    return 0;
}

// Enhanced authentication with security features
int authenticateUser() {
    char enteredPIN[10];
    int attempts = 0;
    
    while (attempts < MAX_ATTEMPTS) {
        printf("🔐 Enter your PIN: ");
        scanf("%s", enteredPIN);
        clearInputBuffer();
        
        if (strcmp(enteredPIN, currentPIN) == 0) {
            return 1;
        } else {
            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                printf("❌ Incorrect PIN! %d attempt(s) remaining.\n\n", 
                       MAX_ATTEMPTS - attempts);
            }
        }
    }
    
    return 0;
}

// Professional menu display
void displayMainMenu() {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║            ATM MAIN MENU              ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║  1. 💰 Check Balance                   ║\n");
    printf("║  2. 📥 Deposit Money                   ║\n");
    printf("║  3. 📤 Withdraw Money                  ║\n");
    printf("║  4. 🔑 Change PIN                      ║\n");
    printf("║  5. 📊 Transaction History             ║\n");
    printf("║  6. 🚪 Exit                            ║\n");
    printf("╚════════════════════════════════════════╝\n");
}

// Enhanced balance check with receipt option
void checkBalance() {
    char wantReceipt;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║          BALANCE INQUIRY              ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║  Current Balance: $%-18.2f ║\n", balance);
    printf("╚════════════════════════════════════════╝\n");
    
    addTransaction("Balance Check", 0.00);
    
    printf("\n📄 Print receipt? (y/n): ");
    scanf(" %c", &wantReceipt);
    clearInputBuffer();
    
    if (wantReceipt == 'y' || wantReceipt == 'Y') {
        printReceipt("Balance Inquiry", 0.00);
    }
}

// Enhanced deposit with better validation
void depositMoney() {
    float amount;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║            DEPOSIT MONEY              ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\nCurrent Balance: $%.2f\n", balance);
    printf("Enter deposit amount: $");
    
    if (scanf("%f", &amount) != 1) {
        clearInputBuffer();
        printf("\n❌ Invalid input!\n");
        return;
    }
    clearInputBuffer();
    
    // Validation checks
    if (amount <= 0) {
        printf("\n❌ Amount must be positive!\n");
        return;
    }
    
    if (amount > 10000) {
        printf("\n❌ Maximum deposit limit: $10,000 per transaction.\n");
        return;
    }
    
    // Process deposit
    balance += amount;
    addTransaction("Deposit", amount);
    
    printf("\n✓ Deposit Successful!\n");
    printf("Amount Deposited: $%.2f\n", amount);
    printf("New Balance: $%.2f\n", balance);
    
    printReceipt("Deposit", amount);
}

// Enhanced withdrawal with multiple checks
void withdrawMoney() {
    float amount;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║           WITHDRAW MONEY              ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\nAvailable Balance: $%.2f\n", balance);
    printf("Enter withdrawal amount: $");
    
    if (scanf("%f", &amount) != 1) {
        clearInputBuffer();
        printf("\n❌ Invalid input!\n");
        return;
    }
    clearInputBuffer();
    
    // Validation checks
    if (amount <= 0) {
        printf("\n❌ Amount must be positive!\n");
        return;
    }
    
    if (amount > balance) {
        printf("\n❌ Insufficient funds!\n");
        printf("Your balance: $%.2f\n", balance);
        return;
    }
    
    if (amount > 1000) {
        printf("\n❌ Maximum withdrawal limit: $1,000 per transaction.\n");
        return;
    }
    
    // Process withdrawal
    balance -= amount;
    addTransaction("Withdrawal", amount);
    
    printf("\n✓ Withdrawal Successful!\n");
    printf("Amount Withdrawn: $%.2f\n", amount);
    printf("Remaining Balance: $%.2f\n", balance);
    printf("\n💵 Please collect your cash.\n");
    
    printReceipt("Withdrawal", amount);
}

// Secure PIN change feature
void changePIN() {
    char oldPIN[10], newPIN[10], confirmPIN[10];
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║             CHANGE PIN                ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    printf("\nEnter current PIN: ");
    scanf("%s", oldPIN);
    clearInputBuffer();
    
    if (strcmp(oldPIN, currentPIN) != 0) {
        printf("\n❌ Incorrect current PIN!\n");
        return;
    }
    
    printf("Enter new PIN (4-6 digits): ");
    scanf("%s", newPIN);
    clearInputBuffer();
    
    if (strlen(newPIN) < MIN_PIN_LENGTH || strlen(newPIN) > 6) {
        printf("\n❌ PIN must be 4-6 digits!\n");
        return;
    }
    
    printf("Confirm new PIN: ");
    scanf("%s", confirmPIN);
    clearInputBuffer();
    
    if (strcmp(newPIN, confirmPIN) == 0) {
        strcpy(currentPIN, newPIN);
        addTransaction("PIN Changed", 0.00);
        printf("\n✓ PIN changed successfully!\n");
        printf("🔒 Please remember your new PIN.\n");
    } else {
        printf("\n❌ PINs do not match!\n");
    }
}

// New feature: Transaction history
void viewTransactionHistory() {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║        TRANSACTION HISTORY            ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    if (transactionCount == 0) {
        printf("No transactions yet.\n");
        return;
    }
    
    printf("%-4s %-18s %-12s %-12s\n", "No.", "Type", "Amount", "Balance");
    printf("────────────────────────────────────────────────\n");
    
    for (int i = 0; i < transactionCount; i++) {
        printf("%-4d %-18s $%-11.2f $%-11.2f\n", 
               i + 1, 
               history[i].type, 
               history[i].amount, 
               history[i].balanceAfter);
    }
}

// Enhanced receipt printing
void printReceipt(char operation[], float amount) {
    char timeStr[26];
    getCurrentTime(timeStr);
    
    printf("\n┌────────────────────────────────────────┐\n");
    printf("│          TRANSACTION RECEIPT          │\n");
    printf("├────────────────────────────────────────┤\n");
    printf("│ Operation: %-27s │\n", operation);
    
    if (amount > 0) {
        printf("│ Amount: $%-29.2f │\n", amount);
    }
    
    printf("│ Balance: $%-28.2f │\n", balance);
    printf("│ Transaction #: %-23d │\n", transactionCount);
    printf("│ Time: %-32s │\n", timeStr);
    printf("└────────────────────────────────────────┘\n");
    printf("      Thank you for banking with us!      \n");
    printf("──────────────────────────────────────────\n");
}

// Add transaction to history
void addTransaction(char type[], float amount) {
    if (transactionCount < MAX_TRANSACTIONS) {
        strcpy(history[transactionCount].type, type);
        history[transactionCount].amount = amount;
        history[transactionCount].balanceAfter = balance;
        getCurrentTime(history[transactionCount].timestamp);
        transactionCount++;
    }
}

// Get current time as string
void getCurrentTime(char* buffer) {
    time_t rawtime;
    struct tm* timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", timeinfo);
}

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Pause screen
void pauseScreen() {
    printf("\nPress Enter to 
