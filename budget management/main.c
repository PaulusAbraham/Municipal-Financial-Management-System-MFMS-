#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void budgetMenu();

int main()
{
    budgetMenu();
    return 0;
}

char names[30][50];
float allocated[30];
float spent[30];
int count = 0;

void addDepartment();
void recordExpenditure();
void displayBudgets();
void showOverBudget();
void showBudgetTotals();
int findDepartment(char name[]);
float calculateBudget(float budget, float expenditure);
int isWithinBudget(float budget, float expenditure);
float readAmount();

void budgetMenu()
{
    int choice;

    do
    {
        printf("\n--- BUDGET MANAGEMENT ---\n");
        printf("1. Add department budget\n");
        printf("2. Record expenditure\n");
        printf("3. Display budgets\n");
        printf("4. Show departments over budget\n");
        printf("5. Show budget totals\n");
        printf("6. Back\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            if (feof(stdin))
            {
                choice = 6;
            }
            else
            {
                choice = 0;
                scanf("%*[^\n]");
            }
        }

        switch (choice)
        {
            case 1:
                addDepartment();
                break;
            case 2:
                recordExpenditure();
                break;
            case 3:
                displayBudgets();
                break;
            case 4:
                showOverBudget();
                break;
            case 5:
                showBudgetTotals();
                break;
            case 6:
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 6);
}

float readAmount()
{
    float amount;

    if (scanf("%f", &amount) != 1)
    {
        if (feof(stdin))
        {
            exit(0);
        }

        scanf("%*[^\n]");
        return -1;
    }

    return amount;
}

int findDepartment(char name[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            return i;
        }
    }

    return -1;
}

float calculateBudget(float budget, float expenditure)
{
    return budget - expenditure;
}

int isWithinBudget(float budget, float expenditure)
{
    if (expenditure <= budget)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void addDepartment()
{
    char name[50] = "";
    float amount;

    if (count >= 30)
    {
        printf("Department list is full.\n");
    }
    else
    {
        printf("Enter department name: ");
        scanf(" %49[^\n]", name);

        if (strlen(name) == 0)
        {
            printf("Department name cannot be empty.\n");
        }
        else if (findDepartment(name) != -1)
        {
            printf("That department already exists.\n");
        }
        else
        {
            do
            {
                printf("Enter allocated budget (N$): ");
                amount = readAmount();

                if (amount < 0)
                {
                    printf("Budget must be a number that is not negative.\n");
                }
            } while (amount < 0);

            strcpy(names[count], name);
            allocated[count] = amount;
            spent[count] = 0;
            count++;

            printf("Department budget saved.\n");
        }
    }
}

void recordExpenditure()
{
    char name[50] = "";
    float amount;
    int position;

    printf("Enter department name: ");
    scanf(" %49[^\n]", name);

    position = findDepartment(name);

    if (position == -1)
    {
        printf("Department not found.\n");
    }
    else
    {
        do
        {
            printf("Enter expenditure (N$): ");
            amount = readAmount();

            if (amount < 0)
            {
                printf("Expenditure must be a number that is not negative.\n");
            }
        } while (amount < 0);

        spent[position] = spent[position] + amount;
        printf("Expenditure recorded.\n");
    }
}

void displayBudgets()
{
    if (count == 0)
    {
        printf("No budgets captured yet.\n");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("\nDepartment      : %s\n", names[i]);
            printf("Allocated Budget: N$%.2f\n", allocated[i]);
            printf("Expenditure     : N$%.2f\n", spent[i]);
            printf("Remaining Budget: N$%.2f\n", calculateBudget(allocated[i], spent[i]));

            if (isWithinBudget(allocated[i], spent[i]) == 1)
            {
                printf("Status          : WITHIN BUDGET\n");
            }
            else
            {
                printf("Status          : OVER BUDGET\n");
            }
        }
    }
}

void showOverBudget()
{
    int found = 0;

    printf("\nDepartments over budget:\n");

    for (int i = 0; i < count; i++)
    {
        if (isWithinBudget(allocated[i], spent[i]) == 0)
        {
            printf("%s\n", names[i]);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("None.\n");
    }
}

void showBudgetTotals()
{
    float totalAllocated = 0;
    float totalSpent = 0;

    for (int i = 0; i < count; i++)
    {
        totalAllocated = totalAllocated + allocated[i];
        totalSpent = totalSpent + spent[i];
    }

    printf("\nTotal Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure     : N$%.2f\n", totalSpent);
    printf("Total Remaining Budget: N$%.2f\n", calculateBudget(totalAllocated, totalSpent));
}
 
