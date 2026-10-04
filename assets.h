#ifndef ASSETS_H
#define ASSETS_H

#include "utils.h"

#define MAX_ASSETS 200
#define TYPE_LEN 30
#define CONDITION_LEN 20

typedef struct {
    int    id;
    char   name[NAME_LEN];
    char   type[TYPE_LEN];
    double purchaseValue;
    char   department[DEPT_LEN];
    char   condition[CONDITION_LEN];
} Asset;

extern Asset assets[MAX_ASSETS];
extern int assetCount;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);

#endif
