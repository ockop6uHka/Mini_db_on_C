
#ifndef LEVELS_H
#define LEVELS_H

#include "shared.h"

#define MAX_LEVELS 10

struct Level {
    int memoryLevel;
    int numberOfCells;
    int protectionFlag;
};

void select_levels(struct Level *levels, int numRecords);
void insert_level(struct Level *levels, int *numRecords, struct Level newLevel);
void update_level(struct Level *levels, int numRecords, int memoryLevel, struct Level updatedLevel);
void delete_level(struct Level *levels, int *numRecords, int memoryLevel);

#endif
