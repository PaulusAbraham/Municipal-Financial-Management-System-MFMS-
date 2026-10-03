#include <stdio.h>
#include <string.h>

int main(void) {
    char municipality[100];
    char mayor[100];
    int population;

    printf("========================================\n");
    printf("  MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n\n");
    printf("Welcome to Windhoek Municipality\n\n");

    printf("Enter Municipality Name: ");
    fgets(municipality, sizeof(municipality), stdin);
    municipality[strcspn(municipality, "\n")] = '\0';

    printf("Enter Mayor's Name: ");
    fgets(mayor, sizeof(mayor), stdin);
    mayor[strcspn(mayor, "\n")] = '\0';

    printf("Enter Population: ");
    scanf("%d", &population);

    printf("\n========================================\n");
    printf("         MUNICIPALITY REPORT\n");
    printf("========================================\n");
    printf("%-20s: %s\n", "Municipality Name", municipality);
    printf("%-20s: %s\n", "Mayor's Name", mayor);
    printf("%-20s: %d\n", "Population", population);
    printf("========================================\n");

    return 0;
}
