#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "utils.h"

#define MAX_EMPLOYEES 100

typedef struct {
    int    id;
    char   name[NAME_LEN];
    char   department[DEPT_LEN];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
} Employee;

extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

void   employeeMenu(void);
void   addEmployee(void);
void   displayEmployees(void);
void   searchEmployee(void);
double calculateSalary(const Employee *emp);

#endif
