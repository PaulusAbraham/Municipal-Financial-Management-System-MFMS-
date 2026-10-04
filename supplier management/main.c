#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_SUPPLIERS 100
#define ID_LEN        10
#define NAME_LEN      50
#define EMAIL_LEN     50
#define PHONE_LEN     20
#define TOWN_LEN      30
#define CONTACT_LEN   (EMAIL_LEN + PHONE_LEN + 4)

void supplierMenu(void);         
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);


int         getSupplierCount(void);
const char *getSupplierId(int index);
const char *getSupplierName(int index);
const char *getSupplierEmail(int index);
const char *getSupplierPhone(int index);
const char *getSupplierTown(int index);
void        getSupplierContact(int index, char contact[]);  



#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


static char supplierId[MAX_SUPPLIERS][ID_LEN];
static char supplierName[MAX_SUPPLIERS][NAME_LEN];
static char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
static char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
static char supplierTown[MAX_SUPPLIERS][TOWN_LEN];
static int  supplierCount = 0;


static void readLine(const char *prompt, char *buf, int size)
{
    int c, start = 0, end;

    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {  
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
    end = (int)strlen(buf);
    if (end > 0 && buf[end - 1] == '\n') {
        buf[--end] = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF) { }  
    }
    while (end > 0 && isspace((unsigned char)buf[end - 1])) buf[--end] = '\0';
    while (buf[start] != '\0' && isspace((unsigned char)buf[start])) start++;
    if (start > 0) memmove(buf, buf + start, strlen(buf + start) + 1);
}

static int readChoice(const char *prompt)
{
    char line[20];
    int choice;

    readLine(prompt, line, sizeof line);
    if (sscanf(line, "%d", &choice) != 1) return -1;   
    return choice;
}

static int hasSpace(const char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        if (isspace((unsigned char)s[i])) return 1;
    return 0;
}


static int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    const char *dot;

    if (strlen(email) < 5 || hasSpace(email) || at == NULL || at == email)
        return 0;
    if (strchr(at + 1, '@') != NULL) return 0;
    dot = strrchr(at, '.');
    return (dot != NULL && dot > at + 1 && dot[1] != '\0');
}


static int isValidPhone(const char *phone)
{
    int i, digits = 0;

    for (i = 0; phone[i] != '\0'; i++) {
        if (isdigit((unsigned char)phone[i])) digits++;
        else if (phone[i] != ' ' && phone[i] != '+' && phone[i] != '-') return 0;
    }
    return (digits >= 7 && digits <= 15);
}


static int findSupplierById(const char *id)
{
    int i;
    for (i = 0; i < supplierCount; i++)
        if (strcmp(supplierId[i], id) == 0) return i;
    return -1;
}

static void toLowerCopy(char *dest, const char *src)
{
    int i;
    for (i = 0; src[i] != '\0'; i++) dest[i] = (char)tolower((unsigned char)src[i]);
    dest[i] = '\0';
}


static int containsIgnoreCase(const char *text, const char *part)
{
    char t[NAME_LEN], p[NAME_LEN];
    toLowerCopy(t, text);
    toLowerCopy(p, part);
    return strstr(t, p) != NULL;
}

static void printHeader(void)
{
    printf("\n%-8s %-22s %-26s %-16s %-14s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printf("---------------------------------------------------------------------------------\n");
}

static void printSupplierRow(int i)
{
    printf("%-8s %-22.22s %-26.26s %-16s %-14.14s\n",
           supplierId[i], supplierName[i], supplierEmail[i],
           supplierPhone[i], supplierTown[i]);
}



void addSupplier(void)
{
    char id[ID_LEN], name[NAME_LEN], email[EMAIL_LEN], phone[PHONE_LEN], town[TOWN_LEN];

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("\nSupplier list is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }
    printf("\n--- ADD SUPPLIER ---\n");

    for (;;) {                                  
        readLine("Supplier ID (e.g. S001): ", id, sizeof id);
        if (strlen(id) == 0)            printf("ID cannot be empty.\n");
        else if (hasSpace(id))          printf("ID cannot contain spaces.\n");
        else if (findSupplierById(id) != -1) printf("That ID already exists.\n");
        else break;
    }
    for (;;) {                                  
        readLine("Supplier name: ", name, sizeof name);
        if (strlen(name) > 0) break;
        printf("Name cannot be empty.\n");
    }
    for (;;) {                                  
        readLine("Email: ", email, sizeof email);
        if (isValidEmail(email)) break;
        printf("Invalid email (example: info@company.com.na).\n");
    }
    for (;;) {                                   
        readLine("Telephone: ", phone, sizeof phone);
        if (isValidPhone(phone)) break;
        printf("Invalid number (7-15 digits; only digits, space, + and - allowed).\n");
    }
    for (;;) {                                   
        readLine("Town/Location: ", town, sizeof town);
        if (strlen(town) > 0) break;
        printf("Town cannot be empty.\n");
    }

    strcpy(supplierId[supplierCount],    id);
    strcpy(supplierName[supplierCount],  name);
    strcpy(supplierEmail[supplierCount], email);
    strcpy(supplierPhone[supplierCount], phone);
    strcpy(supplierTown[supplierCount],  town);
    supplierCount++;

    printf("\nSupplier '%s' added successfully.\n", name);
}

void displaySuppliers(void)
{
    int i;

    printf("\n--- ALL SUPPLIERS ---\n");
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }
    printHeader();
    for (i = 0; i < supplierCount; i++) printSupplierRow(i);
    printf("\nTotal suppliers: %d\n", supplierCount);
}

void searchSupplier(void)
{
    char key[NAME_LEN];
    int choice, i, found = 0;

    if (supplierCount == 0) {
        printf("\nNo suppliers registered yet.\n");
        return;
    }
    printf("\n--- SEARCH SUPPLIER ---\n");
    printf("1. By Supplier ID\n2. By Name (partial match)\n3. By Town\n");
    choice = readChoice("Choice: ");
    if (choice < 1 || choice > 3) {
        printf("Invalid search option.\n");
        return;
    }
    readLine("Search for: ", key, sizeof key);
    if (strlen(key) == 0) {
        printf("Search text cannot be empty.\n");
        return;
    }

    for (i = 0; i < supplierCount; i++) {
        int match = 0;
        if (choice == 1) match = (strcmp(supplierId[i], key) == 0);
        else if (choice == 2) match = containsIgnoreCase(supplierName[i], key);
        else match = containsIgnoreCase(supplierTown[i], key);

        if (match) {
            if (!found) printHeader();
            printSupplierRow(i);
            found++;
        }
    }
    if (found == 0) printf("No supplier found matching '%s'.\n", key);
    else printf("\n%d supplier(s) found.\n", found);
}

void compareSuppliers(void)
{
    char id1[ID_LEN], id2[ID_LEN];
    int a, b;

    printf("\n--- COMPARE TWO SUPPLIERS ---\n");
    if (supplierCount < 2) {
        printf("You need at least 2 suppliers to compare.\n");
        return;
    }
    readLine("First supplier ID: ", id1, sizeof id1);
    readLine("Second supplier ID: ", id2, sizeof id2);
    a = findSupplierById(id1);
    b = findSupplierById(id2);

    if (a == -1 || b == -1) {
        printf("One or both supplier IDs were not found.\n");
        return;
    }
    if (a == b) {
        printf("Please enter two different suppliers.\n");
        return;
    }

    printHeader();
    printSupplierRow(a);
    printSupplierRow(b);
    printf("\nComparison:\n");
    printf("  Same town?  %s\n", strcmp(supplierTown[a], supplierTown[b]) == 0 ? "YES" : "NO");
    printf("  Same email domain? %s\n",
           strcmp(strchr(supplierEmail[a], '@'), strchr(supplierEmail[b], '@')) == 0 ? "YES" : "NO");
    printf("  Name length: %s = %d chars, %s = %d chars\n",
           supplierName[a], (int)strlen(supplierName[a]),
           supplierName[b], (int)strlen(supplierName[b]));
    printf("  Alphabetical order: %s comes first\n",
           strcmp(supplierName[a], supplierName[b]) <= 0 ? supplierName[a] : supplierName[b]);
}

int getSupplierCount(void)
{
    return supplierCount;
}



static int validIndex(int index)
{
    return (index >= 0 && index < supplierCount);
}

const char *getSupplierId(int index)    { return validIndex(index) ? supplierId[index]    : ""; }
const char *getSupplierName(int index)  { return validIndex(index) ? supplierName[index]  : ""; }
const char *getSupplierEmail(int index) { return validIndex(index) ? supplierEmail[index] : ""; }
const char *getSupplierPhone(int index) { return validIndex(index) ? supplierPhone[index] : ""; }
const char *getSupplierTown(int index)  { return validIndex(index) ? supplierTown[index]  : ""; }


void getSupplierContact(int index, char contact[])
{
    if (!validIndex(index)) {
        contact[0] = '\0';
        return;
    }
    strcpy(contact, supplierEmail[index]);
    strcat(contact, " | ");
    strcat(contact, supplierPhone[index]);
}

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("          SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Compare Two Suppliers\n");
        printf("5. Back to Main Menu\n");
        choice = readChoice("Enter your choice: ");

        switch (choice) {
            case 1: addSupplier();      break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier();   break;
            case 4: compareSuppliers(); break;
            case 5: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Please enter 1-5.\n");
        }
    } while (choice != 5);
}


int main(void)
{
    int i; char c[CONTACT_LEN];
    supplierMenu();
    printf("Count: %d\n", getSupplierCount());
    for (i = 0; i < getSupplierCount(); i++) {
        getSupplierContact(i, c);
        printf("%s | %s | %s | %s\n", getSupplierId(i), getSupplierName(i), getSupplierTown(i), c);
    }
    return 0;
}
