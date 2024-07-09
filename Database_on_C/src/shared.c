#include "shared.h"

#include <stdio.h>
#include <string.h>

struct Module modules[MAX_MODULES];
struct Level levels[MAX_LEVELS];
struct StatusEvent statusEvents[MAX_EVENTS];
int numModules = 0;
int numLevels = 0;
int numEvents = 0;

void create_index(const char *filename, const int *data, int size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening index file");
        return;
    }
    fwrite(data, sizeof(int), size, file);
    fclose(file);
}

int binary_search(const char *filename, int key) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening index file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int left = 0;
    int right = (int)(size / sizeof(int)) - 1;
    int mid, found = -1;

    while (left <= right) {
        mid = left + (right - left) / 2;
        fseek(file, mid * sizeof(int), SEEK_SET);
        int value;
        fread(&value, sizeof(int), 1, file);

        if (value == key) {
            found = mid;
            break;
        } else if (value < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    fclose(file);
    return found;
}

void delete_index(const char *filename) {
    if (remove(filename) != 0) {
        perror("Error deleting index file");
    }
}

void select_modules(struct Module *modules, int numModules) {
    printf("\n=============================\nMODULES\n=============================\n");
    for (int i = 0; i < numModules; ++i) {
        printf("%d %s %d %d %d\n", modules[i].moduleId, modules[i].moduleName, modules[i].memoryLevel,
               modules[i].cellNumber, modules[i].deletionFlag);
    }
}

void insert_module(struct Module *modules, int *numModules, struct Module newModule) {
    if (*numModules < MAX_MODULES) {
        modules[(*numModules)++] = newModule;
        printf("Module inserted successfully.\n");
    } else {
        printf("Cannot insert module: maximum capacity reached.\n");
    }
}

void update_module(struct Module *modules, int numModules, int moduleId, struct Module updatedModule) {
    for (int i = 0; i < numModules; ++i) {
        if (modules[i].moduleId == moduleId) {
            modules[i] = updatedModule;
            printf("Module updated successfully.\n");
            return;
        }
    }
    printf("Module with ID %d not found.\n", moduleId);
}

void delete_module(struct Module *modules, int *numModules, int moduleId) {
    for (int i = 0; i < *numModules; ++i) {
        if (modules[i].moduleId == moduleId) {
            for (int j = i; j < *numModules - 1; ++j) {
                modules[j] = modules[j + 1];
            }
            (*numModules)--;
            printf("Module deleted successfully.\n");
            return;
        }
    }
    printf("Module with ID %d not found.\n", moduleId);
}

void select_levels(struct Level *levels, int numLevels) {
    printf("\n=============================\nLEVELS\n=============================\n");
    for (int i = 0; i < numLevels; ++i) {
        printf("%d %d %d\n", levels[i].memoryLevel, levels[i].numberOfCells, levels[i].protectionFlag);
    }
}

void insert_level(struct Level *levels, int *numLevels, struct Level newLevel) {
    if (*numLevels < MAX_LEVELS) {
        levels[(*numLevels)++] = newLevel;
        printf("Level inserted successfully.\n");
    } else {
        printf("Cannot insert level: maximum capacity reached.\n");
    }
}

void update_level(struct Level *levels, int numLevels, int memoryLevel, struct Level updatedLevel) {
    for (int i = 0; i < numLevels; ++i) {
        if (levels[i].memoryLevel == memoryLevel) {
            levels[i] = updatedLevel;
            printf("Level updated successfully.\n");
            return;
        }
    }
    printf("Memory level %d not found.\n", memoryLevel);
}

void delete_level(struct Level *levels, int *numLevels, int memoryLevel) {
    for (int i = 0; i < *numLevels; ++i) {
        if (levels[i].memoryLevel == memoryLevel) {
            for (int j = i; j < *numLevels - 1; ++j) {
                levels[j] = levels[j + 1];
            }
            (*numLevels)--;
            printf("Level deleted successfully.\n");
            return;
        }
    }
    printf("Memory level %d not found.\n", memoryLevel);
}

void select_status_events(struct StatusEvent *statusEvents, int numEvents) {
    printf("\n=============================\nSTATUS_EVENTS\n=============================\n");
    for (int i = 0; i < numEvents; ++i) {
        printf("%d %d %d %s %s\n", statusEvents[i].eventId, statusEvents[i].moduleId,
               statusEvents[i].newStatus, statusEvents[i].date, statusEvents[i].time);
    }
}

void insert_status_event(struct StatusEvent *statusEvents, int *numEvents, struct StatusEvent newEvent) {
    if (*numEvents < MAX_EVENTS) {
        statusEvents[(*numEvents)++] = newEvent;
        printf("Status event inserted successfully.\n");
    } else {
        printf("Cannot insert status event: maximum capacity reached.\n");
    }
}

void update_status_event(struct StatusEvent *statusEvents, int numEvents, int eventId,
                         struct StatusEvent updatedEvent) {
    for (int i = 0; i < numEvents; ++i) {
        if (statusEvents[i].eventId == eventId) {
            statusEvents[i] = updatedEvent;
            printf("Status event updated successfully.\n");
            return;
        }
    }
    printf("Status event with ID %d not found.\n", eventId);
}

void delete_status_event(struct StatusEvent *statusEvents, int *numEvents, int eventId) {
    for (int i = 0; i < *numEvents; ++i) {
        if (statusEvents[i].eventId == eventId) {
            for (int j = i; j < *numEvents - 1; ++j) {
                statusEvents[j] = statusEvents[j + 1];
            }
            (*numEvents)--;
            printf("Status event deleted successfully.\n");
            return;
        }
    }
    printf("Status event with ID %d not found.\n", eventId);
}
