#include <stdio.h>
#include "reports.h"
#include "budgets.h"
#include "assets.h"
#include "suppliers.h"
#include "employees.h"

void employeeReport(void);
void budgetReport(void);
void supplierReport(void);
void assetReport(void);

int getSupplierCount(void);
const char *getSupplierName(int index);
char *getSupplierTown(int index);

void displayReports(void)
{
    char choice[10];
   
    do {
        printf("\n========================================\n");
        printf("           REPORTS MODULE           \n");
        printf("         Developed by: MM :-)              \n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Exit\n");
        printf("========================================\n");
        printf("Enter your choice please: ");

        fgets(choice, sizeof(choice), stdin);

        if (choice[0] == '1')
        {
            employeeReport();
        }
        else if (choice[0] == '2')
        {
            budgetReport();
        }
        else if (choice[0] == '3')
        {
            supplierReport();
        }
        else if (choice[0] == '4')
        {
            assetReport();
        }
        else if (choice[0] == '5')
        {
            printf("Leaving reports menu...\n");
        }
        else
        {
            printf("Oopsies. Please try again.\n");
        }

    } while (choice[0] != '5');
}
void employeeReport(void)
{
    printf("\n============================\n");
    printf("        EMPLOYEE REPORT\n");
    printf("============================\n");

    printf("Total number of employees\n");
    printf("Average salary\n");
    printf("Highest salary\n");
    printf("Lowest salary\n");
}

void budgetReport(void)
{
    int i;
    float totalAllocated = 0;
    float totalSpent = 0;
    float remaining;

    printf("\n========================\n");
    printf("        BUDGET REPORT\n");
    printf("========================\n");

    for (i = 0; i < count; i++)
    {
        totalAllocated = totalAllocated + allocated[i];
        totalSpent = totalSpent + spent[i];
    }

    remaining = totalAllocated - totalSpent;

    printf("Total allocated budget : %.2f\n", totalAllocated);
    printf("Total expenditure      : %.2f\n", totalSpent);
    printf("Remaining budget       : %.2f\n", remaining);

    printf("\nDepartments exceeding budget:\n");

    for (i = 0; i < count; i++)
    {
        if (spent[i] > allocated[i])
        {
            printf("- %s\n", names[i]);
        }
    }
}

void supplierReport(void)
{
    int i;
    int total;

    printf("\n========================\n");
    printf("       SUPPLIER REPORT\n");
    printf("========================\n");

    total = getSupplierCount();

    printf("Total registered suppliers: %d\n", total);

    printf("\nSupplier List:\n");

    for (i = 0; i < total; i++)
    {
        printf("%d. %s - %s\n",
               i + 1,
               getSupplierName(i),
               getSupplierTown(i));
    }
}

void assetReport(void)
{
    int i;
    float totalValue = 0;

    printf("\n========================\n");
    printf("         ASSET REPORT\n");
    printf("========================\n");

    printf("Total registered assets: %d\n", assetCount);

    for (i = 0; i < assetCount; i++)
    {
        totalValue = totalValue + assetPurchaseValue[i];
    }

    printf("Total asset value: %.2f\n", totalValue);

    printf("\nAsset List:\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("%d. %s - %s - %.2f\n",
               i + 1,
               assetName[i],
               assetDepartment[i],
               assetPurchaseValue[i]);
    }
}