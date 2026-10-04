#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

//  this section Find the index of an employee by ID; returns -1 if not found -- roswitha guys pls dont touch my section 
static int findEmployeeIndex(int id)
{
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Print a single employee record ---- done dont touch this section - roswitha
static void printEmployee(const Employee *emp)
{
    printf("----------------------------------------\n");
    printf("Employee ID        : %d\n", emp->id);
    printf("Name               : %s\n", emp->name);
    printf("Department         : %s\n", emp->department);
    printf("Basic Salary       : N$%.2f\n", emp->basicSalary);
    printf("Housing Allowance  : N$%.2f\n", emp->housingAllowance);
    printf("Transport Allowance: N$%.2f\n", emp->transportAllowance);
    printf("Total Salary       : N$%.2f\n", calculateSalary(emp));
    printf("----------------------------------------\n");
}

//  hey -- i fixed tis part Calculate the total monthly salary (basic + allowances)
double calculateSalary(const Employee *emp)
{
    return emp->basicSalary + emp->housingAllowance + emp->transportAllowance;
}

void addEmployee(void)
{
    Employee emp;
    int id;
    char buffer[NAME_LEN];

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Cannot add more employees. Maximum of %d reached.\n", MAX_EMPLOYEES);
        return;
    }

    // Validate ID: must be a positive whole number and unique --- works fine 
    for (;;) {
        if (!readPositiveInt("Enter employee ID: ", &id) || id <= 0) {
            printf("Invalid ID. IDs must be positive whole numbers. Try again.\n");
            continue;
        }
        if (findEmployeeIndex(id) != -1) {
            printf("ID %d is already in use. Try again.\n", id);
            continue;
        }
        break;
    }
    emp.id = id;

    //here this will  Validate name must not be empty -- !!! very imporant !! 
    for (;;) {
        readString("Enter full name: ", buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Name cannot be empty. Try again.\n");
    }
    strcpy(emp.name, buffer);

    //  same for  department
    for (;;) {
        readString("Enter department: ", buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Department cannot be empty. Try again.\n");
    }
    strcpy(emp.department, buffer);

    //  same for Validate salary fields but must be non-negative numbers -- roswitha : is it updated now -- paulus -- yes 
    for (;;) {
        if (readPositiveDouble("Enter basic salary (N$): ", &emp.basicSalary)) {
            break;
        }
        printf("Invalid salary. Salary cannot be negative or non-numeric. Try again.\n");
    }
    for (;;) {
        if (readPositiveDouble("Enter housing allowance (N$): ", &emp.housingAllowance)) {
            break;
        }
        printf("Invalid allowance. It must be a non-negative number. Try again.\n");
    }
    for (;;) {
        if (readPositiveDouble("Enter transport allowance (N$): ", &emp.transportAllowance)) {
            break;
        }
        printf("Invalid allowance. It must be a non-negative number. Try again.\n");
    }

    employees[employeeCount] = emp;
    employeeCount++;
    printf("Employee '%s' added successfully.\n", emp.name);
}

void displayEmployees(void)
{
    int i;

    if (employeeCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printf("\n---------- EMPLOYEE LIST ----------\n");
    for (i = 0; i < employeeCount; i++) {
        printEmployee(&employees[i]);
    }
    printf("Total employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    int choice, id, i, found;

    if (employeeCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printf("Search by:\n");
    printf("1. Employee ID\n");
    printf("2. Employee Name\n");
    if (!readInt("Enter choice: ", &choice)) {
        printf("Invalid choice.\n");
        return;
    }

    if (choice == 1) {
        if (!readInt("Enter employee ID:", &id)) {
            printf("Invalid ID.\n");
            return;
        }
        i = findEmployeeIndex(id);
        if (i == -1) {
            printf("No employee found with ID %d.\n", id);
        } else {
            printEmployee(&employees[i]);
        }
    } else if (choice == 2) {
        char name[NAME_LEN];
        found = 0;
        readString("Enter employee name:", name, sizeof(name));
        for (i = 0; i < employeeCount; i++) {
            if (strcmp(employees[i].name, name) == 0) {
                printEmployee(&employees[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("No employee named '%s' was found.\n", name);
        }
    } else {
        printf("Invalid search option.\n");
    }
}

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n---------- EMPLOYEE MANAGEMENT ----------\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Back to Main Menu\n");
         printf("-------------------------------------------\n");

        if (!readInt("Enter your choice: ", &choice)) {
            printf("Invalid input. Please enter a number from 1 to 4.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addEmployee();
                break;
             case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
        case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid menu choice. Please try again.\n");
        }
    } while (choice != 4);
}
