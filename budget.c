#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"

Budget budgets[MAX_BUDGETS];
int budgetCount = 0;

// Return the array index of a department's budget, or -1 :: ano is this accunting 
static int findBudgetIndex(const char *department)
{
    int i;
    for (i = 0; i < budgetCount; i++) {
        if (strcmp(budgets[i].department, department) == 0) {
            return i;
        }
    }
    return -1;
}

// Remaining budget = allocated - expenditure. guys please correct my formula if wrong 
double calculateRemaining(const Budget *b)
{
    return b->allocated - b->expenditure;
}

int isOverBudget(const Budget *b)
{
    return b->expenditure > b->allocated;
}

void enterBudget(void)
{
    Budget b;
    char buffer[DEPT_LEN];

    if (budgetCount >= MAX_BUDGETS) {
        printf("Cannot add more budgets. Maximum of %d reached.\n", MAX_BUDGETS);
        return;
    }

    for (;;) {
        readString("Enter department name: ", buffer, sizeof(buffer));
        if (strlen(buffer) == 0) {
            printf("Department cannot be empty. Try again.\n");
            continue;
        }
        if (findBudgetIndex(buffer) != -1) {
            printf("A budget for '%s' already exists.\n", buffer);
            return;
        }
        break;
    }
    strcpy(b.department, buffer);

    b.expenditure = 0.0;
    for (;;) {
        if (readPositiveDouble("Enter allocated budget (N$): ", &b.allocated)
                && b.allocated > 0.0) {
            break;
        }
        printf("Invalid budget. The allocated budget must be a positive number. Try again.\n");
    }

    budgets[budgetCount] = b;
    budgetCount++;
    printf("Budget for '%s' recorded.\n", b.department);
}

void recordExpenditure(void)
{
    char department[DEPT_LEN];
    int index;
    double amount;

    readString("Enter department name: ", department, sizeof(department));
    index = findBudgetIndex(department);
    if (index == -1) {
        printf("No budget found for department '%s'.\n", department);
        return;
    }

    for (;;) {
        if (readPositiveDouble("Enter expenditure amount (N$): ", &amount)
                && amount > 0.0) {
            break;
        }
        printf("Invalid amount. Expenditure must be a positive number. Try again.\n");
    }

    budgets[index].expenditure += amount;
    printf("Expenditure recorded. '%s' has now spent N$%.2f\n",
           department, budgets[index].expenditure);
}

void displayBudgets(void)
{
    int i;

    if (budgetCount == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }

    printf("\n---------------- BUDGET INFORMATION -----------------\n");
    for (i = 0; i < budgetCount; i++) {
        printf("Department: %s\n", budgets[i].department);
        printf("Allocated Budget : N$%.2f\n", budgets[i].allocated);
        printf("Expenditure      : N$%.2f\n", budgets[i].expenditure);
        printf("Remaining Budget : N$%.2f\n", calculateRemaining(&budgets[i]));
        if (isOverBudget(&budgets[i])) {
            printf("Status: OVER BUDGET by N$%.2f\n", budgets[i].expenditure - budgets[i].allocated);
        } else {
            printf("Status: WITHIN BUDGET\n");
        }
        printf("----------------------------------------------------\n");
    }
}

void displayExceededDepartments(void)
{
    int i, any;

    if (budgetCount == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }

    any = 0;
    printf("\n------- DEPARTMENTS EXCEEDING BUDGET ----------\n");
    for (i = 0; i < budgetCount; i++) {
        if (isOverBudget(&budgets[i])) {
            printf("%s exceeded its budget by N$%.2f\n",
                   budgets[i].department,
                   budgets[i].expenditure - budgets[i].allocated);
            any = 1;
        }
    }
    if (!any) {
        printf("All departments are within their budgets.\n");
    }
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n---------- BUDGET MANAGEMENT ----------\n");
        printf("1. Enter Departmental Budget\n");
        printf("2. Record Expenditure\n");
        printf("3. Display Budget Information\n");
        printf("4. Show Departments Exceeding Budget\n");
        printf("5. Back to Main Menu\n");
        printf("------------------------------------------\n");

        if (!readInt("Enter your choice: ", &choice)) {
            printf("Invalid input. Please enter a number from 1 to 5.\n");
            continue;
        }

        switch (choice) {
            case 1:
                enterBudget();
                break;
            case 2:
                recordExpenditure();
                break;
            case 3:
                displayBudgets();
                break;
            case 4:
                displayExceededDepartments();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid menu choice. Please try again.\n");
        }
    } while (choice != 5);
}
