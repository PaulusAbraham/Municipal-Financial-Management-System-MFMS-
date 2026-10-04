#include <stdio.h>
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

//  THIS Function is  to display the main menu _ very important : Paulus 
void displayMainMenu(void)
{
    printf("\n------------------------------------------\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("------------------------------------------\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("------------------------------------------\n");
}

int main(void)
{
    int choice;

    do {
        displayMainMenu();

        if (!readInt("Enter your choice:", &choice)) {
            printf("Invalid input. Please enter a number between 1 and 6.\n");
            continue;
        }

        switch (choice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                supplierMenu();
                break;
            case 4:
                assetMenu();
                break;
            case 5:
                reportsMenu();
                break;
            case 6:
                printf("Thank you for using the MFMS :). !!Goodbye!!\n");
                break;
            default:
                printf("Invalid choice. Please choose a number that is between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
