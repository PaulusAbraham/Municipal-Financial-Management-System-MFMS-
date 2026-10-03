#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "assets.h"

/* ================= Shared data (parallel arrays) ================= */
/* Element i of every array describes the SAME asset. */
char assetID[MAX_ASSETS][ID_LEN];
char assetName[MAX_ASSETS][NAME_LEN];
char assetType[MAX_ASSETS][TYPE_LEN];
float assetPurchaseValue[MAX_ASSETS];
char assetDepartment[MAX_ASSETS][DEPARTMENT_LEN];
char assetCondition[MAX_ASSETS][CONDITION_LEN];
int assetCount = 0;

/* ================= Internal helper functions =================

static void readNonEmptyString(const char *prompt, char dest[], int size)
{
    int valid = 0;

    while (!valid)
    {
        printf("%s", prompt);

        if (fgets(dest, size, stdin) == NULL)
        {
            /* Input stream problem: treat as empty and retry */
            clearerr(stdin);
            dest[0] = '\0';
        }

        /* Remove the trailing newline left by fgets */
        dest[strcspn(dest, "\n")] = '\0';

        /* strlen() checks for empty input */
        if (strlen(dest) == 0)
        {
            printf("Error: value cannot be empty. Please try again.\n");
        }
        else
        {
            valid = 1;
        }
    }
}

static float readNonNegativeFloat(const char *prompt)
{
    float value = -1.0f;
    int scanned = 0;

    while (1)
    {
        printf("%s", prompt);
        scanned = scanf("%f", &value);

        /* Clear whatever is left in the input buffer */
        while (getchar() != '\n')
            ;

        if (scanned != 1)
        {
            printf("Error: please enter a numeric value.\n");
        }
        else if (value < 0.0f)
        {
           
            printf("Error: value cannot be negative. Please try again.\n");
        }
        else
        {
            return value;
        }
    }
}

static void toLowerCase(char text[])
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        text[i] = (char)tolower((unsigned char)text[i]);
    }
}

static void readCondition(char dest[])
{
    char lower[CONDITION_LEN];

    while (1)
    {
        readNonEmptyString("Condition (Good/Fair/Poor): ", dest,  CONDITION_LEN);

        strcpy(lower, dest);   
        toLowerCase(lower);

        
        if (strcmp(lower, "good") == 0)
        {
            strcpy(dest, "Good");
            return;
        }
        else if (strcmp(lower, "fair") == 0)
        {
            strcpy(dest, "Fair");
            return;
        }
        else if (strcmp(lower, "poor") == 0)
        {
            strcpy(dest, "Poor");
            return;
        }

        printf("Error: condition must be Good, Fair or Poor.\n");
    }
}

static void printAssetRow(int index)
{
    printf("%-10s %-25s %-12s N$%-12.2f %-15s %-6s\n",
           assetID[index],
           assetName[index],
           assetType[index],
           assetPurchaseValue[index],
           assetDepartment[index],
           assetCondition[index]);
}

static void printTableHeader(void)
{
    printf("%-10s %-25s %-12s %-14s %-15s %-6s\n",
           "Asset ID", "Name", "Type", "Value", "Department", "Cond.");
    printf("-------------------------------------------------------------------------------\n");
}


int findAssetByID(const char id[])
{
    int i;
    for (i = 0; i < assetCount; i++)
    {
        
        if (strcmp(assetID[i], id) == 0)
        {
            return i;
        }
    }
    return -1;   /* not found */
}

void addAsset(void)
{
    char newID[ID_LEN];

    printf("\n--- Add New Asset ---\n");

    if (assetCount >= MAX_ASSETS)
    {
        printf("The asset register is full (maximum %d assets).\n", MAX_ASSETS);
        return;
    }

    
    while (1)
    {
        readNonEmptyString("Asset ID (e.g. AST-001): ", newID, ID_LEN);

        if (findAssetByID(newID) != -1)
        {
            printf("Error: an asset with ID '%s' already exists.\n", newID);
        }
        else
        {
            break;
        }
    }

   
    strcpy(assetID[assetCount], newID);
    readNonEmptyString("Asset name (e.g. Toyota Hilux LDV): ",
                       assetName[assetCount], NAME_LEN);
    readNonEmptyString("Asset type (Vehicle/Computer/Building/Equipment/Furniture): ",
                       assetType[assetCount], TYPE_LEN);
    assetPurchaseValue[assetCount] = readNonNegativeFloat("Purchase value (N$): ");
    readNonEmptyString("Department: ",
                       assetDepartment[assetCount], DEPARTMENT_LEN);
    readCondition(assetCondition[assetCount]);

    assetCount++;
    printf("Asset '%s' registered successfully. Total assets: %d\n",
           newID, assetCount);
}

void displayAssets(void)
{
    int i;

    printf("\n--- Municipal Asset Register ---\n");

    if (assetCount == 0)
    {
        printf("No assets have been registered yet.\n");
        return;
    }

    printTableHeader();
    for (i = 0; i < assetCount; i++)
    {
        printAssetRow(i);
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("Total assets: %d   Total purchase value: N$%.2f\n",
           assetCount, totalAssetValue());
}

void searchAsset(void)
{
    int choice;
    int i;
    int found;

    printf("\n--- Search Assets ---\n");
    printf("1. Search by Asset ID\n");
    printf("2. Search by name or type (keyword)\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid choice. Returning to the asset menu.\n");
        return;
    }
    while (getchar() != '\n')
        ;   /* clear input buffer */

    switch (choice)
    {
        case 1:
        {
            char id[ID_LEN];
            int index;

            readNonEmptyString("Enter Asset ID to search for: ", id, ID_LEN);
            index = findAssetByID(id);

            if (index == -1)
            {
                printf("No asset found with ID '%s'.\n", id);
            }
            else
            {
                printf("\nAsset found:\n");
                printTableHeader();
                printAssetRow(index);
            }
            break;
        }

        case 2:
        {
            char keyword[NAME_LEN];
            char lowerKeyword[NAME_LEN];
            char lowerName[NAME_LEN];
            char lowerType[TYPE_LEN];

            readNonEmptyString("Enter a keyword (e.g. computer): ",
                               keyword, NAME_LEN);
            strcpy(lowerKeyword, keyword);
            toLowerCase(lowerKeyword);

            found = 0;
            printf("\nMatching assets:\n");

            for (i = 0; i < assetCount; i++)
            {
                /* Copy to scratch strings so the originals stay intact */
                strcpy(lowerName, assetName[i]);
                strcpy(lowerType, assetType[i]);
                toLowerCase(lowerName);
                toLowerCase(lowerType);

                
                if (strstr(lowerName, lowerKeyword) != NULL ||
                    strstr(lowerType, lowerKeyword) != NULL)
                {
                    if (!found)
                    {
                        printTableHeader();
                    }
                    printAssetRow(i);
                    found++;
                }
            }

            if (found == 0)
            {
                printf("No assets matched the keyword '%s'.\n", keyword);
            }
            else
            {
                printf("%d asset(s) matched.\n", found);
            }
            break;
        }

        default:
            printf("Invalid choice. Returning to the asset menu.\n");
            break;
    }
}

int getAssetCount(void)
{
    return assetCount;
}

float totalAssetValue(void)
{
    float total = 0.0f;
    int i;

    for (i = 0; i < assetCount; i++)
    {
        total += assetPurchaseValue[i];
    }
    return total;
}

void assetReport(void)
{
    int i;
    int good = 0, fair = 0, poor = 0;

    printf("\n--- Asset Report ---\n");
    printf("Total registered assets : %d\n", assetCount);
    printf("Total purchase value    : N$%.2f\n", totalAssetValue());

    if (assetCount > 0)
    {
        for (i = 0; i < assetCount; i++)
        {
            
            if (strcmp(assetCondition[i], "Good") == 0)
                good++;
            else if (strcmp(assetCondition[i], "Fair") == 0)
                fair++;
            else if (strcmp(assetCondition[i], "Poor") == 0)
                poor++;
        }

        printf("Average purchase value  : N$%.2f\n",
               totalAssetValue() / assetCount);
        printf("Condition - Good: %d  Fair: %d  Poor: %d\n", good, fair, poor);
    }
}

void assetMenu(void)
{
    int choice = 0;

    while (choice != 4)
    {
        printf("\n========================================\n");
        printf("         ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add an asset\n");
        printf("2. Display all assets\n");
        printf("3. Search for an asset\n");
        printf("4. Return to main menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            continue;
        }
        while (getchar() != '\n')
            ;   /* clear input buffer */

        switch (choice)
        {
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
                printf("Returning to the main menu...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }
    }
}

