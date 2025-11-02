#include <stdio.h>
#include <string.h>

#define MAX_TRANSACTIONS 100
#define MAX_LENGTH 100

// Structure to store transaction
struct Transaction {
    int id;
    char description[MAX_LENGTH];
    float amount;
    int type; // 1 for income, 2 for expense
    char category[MAX_LENGTH];
};

// Global variables
struct Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;
int currentType = 1; // 1 = income, 2 = expense

// Function declarations
void displayMenu();
void setType();
void showCategories();
void addTransaction();
void deleteTransaction();
void displayTransactions();
void displayStats();

int main() {
    int choice;
    
    printf("========================================\n");
    printf("    FINANCE TRACKER - C PROGRAM\n");
    printf("========================================\n\n");
    
    while(1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                displayTransactions();
                break;
            case 3:
                deleteTransaction();
                break;
            case 4:
                displayStats();
                break;
            case 5:
                setType();
                break;
            case 6:
                printf("\nThank you for using Finance Tracker!\n");
                return 0;
            default:
                printf("\nInvalid choice!\n");
        }
        
        printf("\n");
    }
    
    return 0;
}

// Display menu
void displayMenu() {
    printf("\n========================================\n");
    
    switch(currentType) {
        case 1:
            printf("Current Mode: INCOME\n");
            break;
        case 2:
            printf("Current Mode: EXPENSE\n");
            break;
    }
    
    printf("========================================\n");
    printf("1. Add Transaction\n");
    printf("2. View All Transactions\n");
    printf("3. Delete Transaction\n");
    printf("4. View Statistics\n");
    printf("5. Change Type (Income/Expense)\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

// Change type
void setType() {
    int choice;
    
    printf("\n--- Change Type ---\n");
    printf("1. Income\n");
    printf("2. Expense\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            currentType = 1;
            printf("Type changed to: Income\n");
            break;
        case 2:
            currentType = 2;
            printf("Type changed to: Expense\n");
            break;
        default:
            printf("Invalid choice!\n");
    }
}

// Show categories
void showCategories() {
    printf("\nSelect Category:\n");
    
    switch(currentType) {
        case 2: // Expense
            printf("1. Food\n");
            printf("2. Transport\n");
            printf("3. Shopping\n");
            printf("4. Bills\n");
            printf("5. Entertainment\n");
            printf("6. Health\n");
            printf("7. Other\n");
            break;
        case 1: // Income
            printf("1. Salary\n");
            printf("2. Business\n");
            printf("3. Investment\n");
            printf("4. Gift\n");
            printf("5. Other\n");
            break;
    }
}

// Add transaction
void addTransaction() {
    if(transactionCount >= MAX_TRANSACTIONS) {
        printf("\nTransaction limit reached!\n");
        return;
    }
    
    int categoryChoice;
    
    printf("\n--- Add Transaction ---\n");
    
    switch(currentType) {
        case 1:
            printf("Type: Income\n");
            break;
        case 2:
            printf("Type: Expense\n");
            break;
    }
    
    // Get description
    printf("\nEnter description: ");
    scanf(" %[^\n]", transactions[transactionCount].description);
    
    // Get amount
    printf("Enter amount (Rs): ");
    scanf("%f", &transactions[transactionCount].amount);
    
    // Get category
    showCategories();
    printf("Enter choice: ");
    scanf("%d", &categoryChoice);
    
    // Set category based on choice and type
    switch(currentType) {
        case 2: // Expense
            switch(categoryChoice) {
                case 1:
                    strcpy(transactions[transactionCount].category, "Food");
                    break;
                case 2:
                    strcpy(transactions[transactionCount].category, "Transport");
                    break;
                case 3:
                    strcpy(transactions[transactionCount].category, "Shopping");
                    break;
                case 4:
                    strcpy(transactions[transactionCount].category, "Bills");
                    break;
                case 5:
                    strcpy(transactions[transactionCount].category, "Entertainment");
                    break;
                case 6:
                    strcpy(transactions[transactionCount].category, "Health");
                    break;
                case 7:
                    strcpy(transactions[transactionCount].category, "Other");
                    break;
                default:
                    printf("Invalid category!\n");
                    return;
            }
            break;
            
        case 1: // Income
            switch(categoryChoice) {
                case 1:
                    strcpy(transactions[transactionCount].category, "Salary");
                    break;
                case 2:
                    strcpy(transactions[transactionCount].category, "Business");
                    break;
                case 3:
                    strcpy(transactions[transactionCount].category, "Investment");
                    break;
                case 4:
                    strcpy(transactions[transactionCount].category, "Gift");
                    break;
                case 5:
                    strcpy(transactions[transactionCount].category, "Other");
                    break;
                default:
                    printf("Invalid category!\n");
                    return;
            }
            break;
    }
    
    // Set transaction data
    transactions[transactionCount].type = currentType;
    transactions[transactionCount].id = transactionCount + 1;
    
    transactionCount++;
    printf("\nTransaction added successfully!\n");
}

// Delete transaction
void deleteTransaction() {
    if(transactionCount == 0) {
        printf("\nNo transactions to delete!\n");
        return;
    }
    
    int id;
    int found = 0;
    
    printf("\n--- Delete Transaction ---\n");
    displayTransactions();
    
    printf("\nEnter transaction ID to delete: ");
    scanf("%d", &id);
    
    for(int i = 0; i < transactionCount; i++) {
        if(transactions[i].id == id) {
            found = 1;
            
            // Shift all transactions
            for(int j = i; j < transactionCount - 1; j++) {
                transactions[j] = transactions[j + 1];
            }
            
            transactionCount--;
            printf("\nTransaction deleted successfully!\n");
            break;
        }
    }
    
    if(found == 0) {
        printf("\nTransaction not found!\n");
    }
}

// Display all transactions
void displayTransactions() {
    if(transactionCount == 0) {
        printf("\nNo transactions yet!\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("         ALL TRANSACTIONS\n");
    printf("========================================\n");
    
    for(int i = 0; i < transactionCount; i++) {
        printf("\nID: %d\n", transactions[i].id);
        printf("Description: %s\n", transactions[i].description);
        printf("Amount: Rs %.0f\n", transactions[i].amount);
        
        switch(transactions[i].type) {
            case 1:
                printf("Type: Income\n");
                break;
            case 2:
                printf("Type: Expense\n");
                break;
        }
        
        printf("Category: %s\n", transactions[i].category);
        printf("----------------------------------------\n");
    }
}

// Display statistics
void displayStats() {
    float totalIncome = 0;
    float totalExpense = 0;
    float balance = 0;
    
    // Calculate totals
    for(int i = 0; i < transactionCount; i++) {
        switch(transactions[i].type) {
            case 1: // Income
                totalIncome = totalIncome + transactions[i].amount;
                break;
            case 2: // Expense
                totalExpense = totalExpense + transactions[i].amount;
                break;
        }
    }
    
    balance = totalIncome - totalExpense;
    
    printf("\n========================================\n");
    printf("           STATISTICS\n");
    printf("========================================\n");
    printf("Total Income:   Rs %.0f\n", totalIncome);
    printf("Total Expense:  Rs %.0f\n", totalExpense);
    printf("Balance:        Rs %.0f\n", balance);
    printf("========================================\n");
    printf("Total Transactions: %d\n", transactionCount);
}