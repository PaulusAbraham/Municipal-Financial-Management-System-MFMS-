#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void employeeReport(void)
{
    int i;
    double total, average, highest, lowest, salary;

    if (employeeCount == 0) {
        printf("\n---- EMPLOYEE REPORT ----\n");
        printf("No employees registered yet.\n");
        return;
    }

    highest = lowest = calculateSalary(&employees[0]);
    total = 0.0;
    for (i = 0; i < employeeCount; i++) {
        salary = calculateSalary(&employees[i]);
        total += salary;
        if (salary > highest) {
            highest = salary;
        }
        if (salary < lowest) {
            lowest = salary;
        }
    }
    average = total / employeeCount;

    printf("\n---- EMPLOYEE REPORT ----\n");
    printf("Total Employees : %d\n", employeeCount);
    printf("Average Salary  : N$%.2f\n", average);
    printf("Highest Salary  : N$%.2f\n", highest);
    printf("Lowest Salary   : N$%.2f\n", lowest);
}

void budgetReport(void)
{
    int i, exceeded;
    double totalAllocated, totalExpenditure, totalRemaining;

    printf("\n---- BUDGET REPORT ----\n");
    if (budgetCount == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }

    totalAllocated = totalExpenditure = totalRemaining = 0.0;
    exceeded = 0;
    for (i = 0; i < budgetCount; i++) {
        totalAllocated += budgets[i].allocated;
        totalExpenditure += budgets[i].expenditure;
        totalRemaining += calculateRemaining(&budgets[i]);
        if (isOverBudget(&budgets[i])) {
            exceeded++;
        }
    }

    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalExpenditure);
    printf("Total Remaining Budget : N$%.2f\n", totalRemaining);
    printf("Departments Exceeding Budget: %d\n", exceeded);
    if (exceeded > 0) {
        for (i = 0; i < budgetCount; i++) {
            if (isOverBudget(&budgets[i])) {
                printf("  - %s (over by N$%.2f)\n",
                       budgets[i].department,
                       budgets[i].expenditure - budgets[i].allocated);
            }
        }
    }
}

void supplierReport(void)
{
    int i;

    printf("\n---- SUPPLIER REPORT ----\n");
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("Total Suppliers: %d\n", supplierCount);
    for (i = 0; i < supplierCount; i++) {
        printf("%d | %s | %s | %s | %s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].phone,
               suppliers[i].town);
    }
}

void assetReport(void)
{
    int i;
    double totalValue;

    printf("\n---- ASSET REPORT ----\n");
    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    totalValue = 0.0;
    for (i = 0; i < assetCount; i++) {
        totalValue += assets[i].purchaseValue;
    }

    printf("Total Assets        : %d\n", assetCount);
    printf("Total Purchase Value: N$%.2f\n", totalValue);
    for (i = 0; i < assetCount; i++) {
        printf("%d | %s | %s | N$%.2f | %s | %s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
}

void fullReport(void)
{
    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();
}

void reportsMenu(void)
{
    int choice;

    do {
        printf("\n---------- REPORTS ----------\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Full Report (All)\n");
        printf("6. Back to Main Menu\n");
        printf("-------------------------------\n");

        if (!readInt("Enter your choice: ", &choice)) {
            printf("Invalid input. Please enter a number from 1 to 6.\n");
            continue;
        }

        switch (choice) {
            case 1:
                employeeReport();
                break;
            case 2:
                budgetReport();
                break;
            case 3:
                supplierReport();
                break;
            case 4:
                assetReport();
                break;
            case 5:
                fullReport();
                break;
            case 6:
                printf("Returning to main menu--\n");
                break;
            default:
                printf("Invalid menu choice. Please try again.\n");
        }
    } while (choice != 6);
}
