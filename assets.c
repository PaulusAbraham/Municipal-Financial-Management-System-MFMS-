#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

static int findAssetIndex(int id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            return i;
        }
    }
    return -1;
}

static void printAsset(const Asset *a)
{
    printf("----------------------------------------\n");
    printf("Asset ID       : %d\n", a->id);
    printf("Name           : %s\n", a->name);
    printf("Type           : %s\n", a->type);
    printf("Purchase Value : N$%.2f\n", a->purchaseValue);
    printf("Department     : %s\n", a->department);
    printf("Condition      : %s\n", a->condition);
    printf("----------------------------------------\n");
}

//Let the user pick a condition from a fixed list 
static void chooseCondition(char *condition)
{
    int choice;

    for (;;) {
        printf("Condition:\n");
        printf("1. Excellent\n");
        printf("2. Good\n");
        printf("3. Fair\n");
        printf("4. Poor\n");
        if (readInt("Enter choice (1-4): ", &choice)) {
            switch (choice) {
                case 1:
                    strcpy(condition, "Excellent");
                    return;
                case 2:
                    strcpy(condition, "Good");
                    return;
                case 3:
                    strcpy(condition, "Fair");
                    return;
                case 4:
                    strcpy(condition, "Poor");
                    return;
                default:
                    printf("Invalid choice. Please choose a number from 1 to 4.\n");
            }
        } else {
            printf("Invalid choice. Please choose a number from 1 to 4.\n");
        }
    }
}

void addAsset(void)
{
    Asset a;
    int id;
    char buffer[NAME_LEN];

    if (assetCount >= MAX_ASSETS) {
        printf("Cannot add more assets. Maximum of %d reached.\n", MAX_ASSETS);
        return;
    }

    for (;;) {
        if (!readPositiveInt("Enter asset ID: ", &id) || id <= 0) {
            printf("Invalid ID. IDs must be positive whole numbers. Try again.\n");
            continue;
        }
        if (findAssetIndex(id) != -1) {
            printf("ID %d is already in use. Try again.\n", id);
            continue;
        }
        break;
    }
    a.id = id;

    for (;;) {
        readString("Enter asset name: ", buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Name cannot be empty. Try again.\n");
    }
    strcpy(a.name, buffer);

    for (;;) {
        readString("Enter asset type (e.g. Vehicle, Computer, Building): ",
                   buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Type cannot be empty. Try again.\n");
    }
    strcpy(a.type, buffer);

    for (;;) {
        if (readPositiveDouble("Enter purchase value (N$): ", &a.purchaseValue)) {
            break;
        }
        printf("Invalid value. The purchase value cannot be negative. Try again.\n");
    }

    for (;;) {
        readString("Enter department: ", buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Department cannot be empty. Try again.\n");
    }
    strcpy(a.department, buffer);

    chooseCondition(a.condition);

    assets[assetCount] = a;
    assetCount++;
    printf("Asset '%s' added successfully.\n", a.name);
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    printf("\n................ ASSET LIST .................\n");
    for (i = 0; i < assetCount; i++) {
        printAsset(&assets[i]);
    }
    printf("Total assets: %d\n", assetCount);
}

void searchAsset(void)
{
    int choice, id, i, found;
    char term[NAME_LEN];

    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    printf("Search by:\n");
    printf("1. Asset ID\n");
    printf("2. Asset Name\n");
    printf("3. Asset Type\n");
    if (!readInt("Enter choice: ", &choice)) {
        printf("Invalid choice.\n");
        return;
    }

    if (choice == 1) {
        if (!readInt("Enter asset ID: ", &id)) {
            printf("Invalid ID.\n");
            return;
        }
        i = findAssetIndex(id);
        if (i == -1) {
            printf("No asset found with ID %d.\n", id);
        } else {
            printAsset(&assets[i]);
        }
    } else if (choice == 2 || choice == 3) {
        found = 0;
        readString("Enter search term: ", term, sizeof(term));
        for (i = 0; i < assetCount; i++) {
            const char *field = (choice == 2) ? assets[i].name : assets[i].type;
            if (strcmp(field, term) == 0) {
                printAsset(&assets[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("No matching asset found for '%s'.\n", term);
        }
    } else {
        printf("Invalid search option.\n");
    }
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n---------- ASSET MANAGEMENT ----------\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("------------------------------------------\n");

        if (!readInt("Enter your choice: ", &choice)) {
            printf("Invalid input. Please enter a number from 1 to 4.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addAsset();
                break;
            case 2:
                displayAssets();
                break;
            case 3:
                searchAsset();
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid menu choice. Please try again.\n");
        }
    } while (choice != 4);
}

