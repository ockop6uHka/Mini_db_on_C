
#include <stdio.h>

#include "shared.h"

struct Level levels[MAX_LEVELS];
int numLevels = 0;

void select_levels(struct Level *levels, int numRecords) {
    printf("\n=============================\nLEVELS\n=============================\n");
    for (int i = 0; i < numRecords; ++i) {
        printf("%d %d %d\n", levels[i].memoryLevel, levels[i].numberOfCells, levels[i].protectionFlag);
    }
}

void insert_level(struct Level *levels, int *numRecords, struct Level newLevel) {
    if (*numRecords < MAX_LEVELS) {
        levels[*numRecords] = newLevel;
        (*numRecords)++;
        printf("Level inserted successfully.\n");
    } else {
        printf("Cannot insert level: Maximum capacity reached.\n");
    }
}

void update_level(struct Level *levels, int numRecords, int memoryLevel, struct Level updatedLevel) {
    int found = 0;
    for (int i = 0; i < numRecords; ++i) {
        if (levels[i].memoryLevel == memoryLevel) {
            levels[i] = updatedLevel;
            found = 1;
            printf("Level updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Level not found.\n");
    }
}

void delete_level(struct Level *levels, int *numRecords, int memoryLevel) {
    int found = 0;
    for (int i = 0; i < *numRecords; ++i) {
        if (levels[i].memoryLevel == memoryLevel) {
            levels[i] = levels[*numRecords - 1];
            (*numRecords)--;
            found = 1;
            printf("Level deleted successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Level not found.\n");
    }
}
