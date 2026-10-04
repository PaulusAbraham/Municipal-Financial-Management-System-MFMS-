#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

static int findSupplierIndex(int id)
{
    int i;
    for (i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) {
            return i;
        }
    }
    return -1;
}

static void printSupplier(const Supplier *s)
{
    printf("----------------------------------------\n");
    printf("Supplier ID : %d\n", s->id);
    printf("Name        : %s\n", s->name);
    printf("Email       : %s\n", s->email);
    printf("Telephone   : %s\n", s->phone);
    printf("Town        : %s\n", s->town);
    printf("----------------------------------------\n");
}

void addSupplier(void)
{
    Supplier s;
    int id;
    char buffer[EMAIL_LEN];

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Cannot add more suppliers. Maximum of %d reached.\n", MAX_SUPPLIERS);
        return;
    }

    for (;;) {
        if (!readPositiveInt("Enter supplier ID: ", &id) || id <= 0) {
            printf("Invalid ID. IDs must be positive whole numbers. Try again.\n");
            continue;
        }
        if (findSupplierIndex(id) != -1) {
            printf("ID %d is already in use. Try again.\n", id);
            continue;
        }
        break;
    }
    s.id = id;

    for (;;) {
        readString("Enter supplier name: ", buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Name cannot be empty. Try again.\n");
    }
    strcpy(s.name, buffer);

    // Basic email validation: it must contain an '@' character
    for (;;) {
        readString("Enter email address: ", buffer, sizeof(buffer));
        if (strlen(buffer) == 0) {
            printf("Email cannot be empty. Try again.\n");
            continue;
        }
        if (strchr(buffer, '@') == NULL) {
            printf("Invalid email. It must contain '@'. Try again.\n");
            continue;
        }
        break;
    }
    strcpy(s.email, buffer);

    for (;;) {
        readString("Enter telephone number: ", buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Telephone number cannot be empty. Try again.\n");
    }
    strcpy(s.phone, buffer);

    for (;;) {
        readString("Enter town/location: ", buffer, sizeof(TOWN_LEN));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Town cannot be empty. Try again.\n");
    }
    strcpy(s.town, buffer);

    suppliers[supplierCount] = s;
    supplierCount++;
    printf("Supplier '%s' added successfully.\n", s.name);
}

void displaySuppliers(void)
{
    int i;

    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("\n---------------- SUPPLIER LIST -----------------\n");
    for (i = 0; i < supplierCount; i++) {
        printSupplier(&suppliers[i]);
    }
    printf("Total suppliers: %d\n", supplierCount);
}

void searchSupplier(void)
{
    int choice, id, i, found;
    char term[NAME_LEN];

    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("Search by:\n");
    printf("1. Supplier ID\n");
    printf("2. Supplier Name\n");
    printf("3. Town/Location\n");
    if (!readInt("Enter choice: ", &choice)) {
        printf("Invalid choice.\n");
        return;
    }

    if (choice == 1) {
        if (!readInt("Enter supplier ID:", &id)) {
            printf("Invalid ID.\n");
            return;
        }
        i = findSupplierIndex(id);
        if (i == -1) {
            printf("No supplier found with ID %d.\n", id);
        } else {
            printSupplier(&suppliers[i]);
        }
    } else if (choice == 2 || choice == 3) {
        found = 0;
        readString("Enter search term: ", term, sizeof(term));
        for (i = 0; i < supplierCount; i++) {
            const char *field = (choice == 2) ? suppliers[i].name : suppliers[i].town;
            if (strcmp(field, term) == 0) {
                printSupplier(&suppliers[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("No matching supplier found for '%s'.\n", term);
        }
    } else {
        printf("Invalid search option.\n");
    }
}

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n---------- SUPPLIER MANAGEMENT ----------\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        printf("------------------------------------------\n");

        if (!readInt("Enter your choice: ", &choice)) {
            printf("Invalid input. Please enter a number from 1 to 4.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplier();
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid menu choice. Please try again.\n");
        }
    } while (choice != 4);
}
