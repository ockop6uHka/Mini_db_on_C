
#include <stdio.h>

#include "shared.h"

struct Module modules[MAX_MODULES];
int numModules = 0;

void select_modules(struct Module *modules, int numRecords) {
    printf("\n=============================\nMODULES\n=============================\n");
    for (int i = 0; i < numRecords; ++i) {
        printf("%d %s %d %d %d\n", modules[i].moduleId, modules[i].moduleName, modules[i].memoryLevel,
               modules[i].cellNumber, modules[i].deletionFlag);
    }
}

void insert_module(struct Module *modules, int *numRecords, struct Module newModule) {
    if (*numRecords < MAX_MODULES) {
        modules[*numRecords] = newModule;
        (*numRecords)++;
        printf("Module inserted successfully.\n");
    } else {
        printf("Cannot insert module: Maximum capacity reached.\n");
    }
}

void update_module(struct Module *modules, int numRecords, int moduleId, struct Module updatedModule) {
    int found = 0;
    for (int i = 0; i < numRecords; ++i) {
        if (modules[i].moduleId == moduleId) {
            modules[i] = updatedModule;
            found = 1;
            printf("Module updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Module not found.\n");
    }
}

void delete_module(struct Module *modules, int *numRecords, int moduleId) {
    int found = 0;
    for (int i = 0; i < *numRecords; ++i) {
        if (modules[i].moduleId == moduleId) {
            modules[i] = modules[*numRecords - 1];
            (*numRecords)--;
            found = 1;
            printf("Module deleted successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Module not found.\n");
    }
}
