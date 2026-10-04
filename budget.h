#ifndef BUDGET_H
#define BUDGET_H

#include "utils.h"

#define MAX_BUDGETS 50

typedef struct {
    char   department[DEPT_LEN];
    double allocated;
    double expenditure;
} Budget;

extern Budget budgets[MAX_BUDGETS];
extern int budgetCount;

void   budgetMenu(void);
void   enterBudget(void);
void   recordExpenditure(void);
void   displayBudgets(void);
double calculateRemaining(const Budget *b);
int    isOverBudget(const Budget *b);
void   displayExceededDepartments(void);

#endif
