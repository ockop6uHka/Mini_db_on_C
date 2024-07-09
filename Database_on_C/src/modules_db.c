#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared.h"

void menu() {
    printf("\nPlease choose one operation:\n");
    printf("1. SELECT\n");
    printf("2. INSERT\n");
    printf("3. UPDATE\n");
    printf("4. DELETE\n");
    printf("5. Get all active additional modules (last module status is 1)\n");
    printf("6. Delete modules by ids\n");
    printf("7. Set protected mode for module by id\n");
    printf("8. Move module by id to specified memory level and cell\n");
    printf("9. Set protection flag of the specified memory level\n");
    printf("0. Exit\n");
    printf("> ");
}

void read_db_logs(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[100];
    int mode = 0;  // 0 - none, 1 - modules, 2 - levels, 3 - status events

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "MODULES")) {
            mode = 1;
            continue;
        } else if (strstr(line, "LEVELS")) {
            mode = 2;
            continue;
        } else if (strstr(line, "STATUS")) {
            mode = 3;
            continue;
        }

        switch (mode) {
            case 1: {
                struct Module newModule;
                sscanf(line, "%d %29s %d %d %d", &newModule.moduleId, newModule.moduleName,
                       &newModule.memoryLevel, &newModule.cellNumber, &newModule.deletionFlag);
                insert_module(modules, &numModules, newModule);
                break;
            }
            case 2: {
                struct Level newLevel;
                sscanf(line, "%d %d %d", &newLevel.memoryLevel, &newLevel.numberOfCells,
                       &newLevel.protectionFlag);
                insert_level(levels, &numLevels, newLevel);
                break;
            }
            case 3: {
                struct StatusEvent newEvent;
                sscanf(line, "%d %d %d %10s %8s", &newEvent.eventId, &newEvent.moduleId, &newEvent.newStatus,
                       newEvent.date, newEvent.time);
                insert_status_event(statusEvents, &numEvents, newEvent);
                break;
            }
            default:
                break;
        }
    }

    fclose(file);
}

int main() {
    char filename[] = "db_logs.txt";
    read_db_logs(filename);

    int choice;
    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int table_choice;
                printf("Please choose a table:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                printf("> ");
                scanf("%d", &table_choice);

                switch (table_choice) {
                    case 1:
                        select_modules(modules, numModules);
                        break;
                    case 2:
                        select_levels(levels, numLevels);
                        break;
                    case 3:
                        select_status_events(statusEvents, numEvents);
                        break;
                    default:
                        printf("Invalid table choice.\n");
                        break;
                }
                break;
            }
            case 2: {
                int table_choice;
                printf("Please choose a table to insert into:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                printf("> ");
                scanf("%d", &table_choice);

                switch (table_choice) {
                    case 1: {
                        struct Module newModule;
                        printf("Enter module details (Id Name MemoryLevel CellNumber DeletionFlag): ");
                        scanf("%d %29s %d %d %d", &newModule.moduleId, newModule.moduleName,
                              &newModule.memoryLevel, &newModule.cellNumber, &newModule.deletionFlag);
                        insert_module(modules, &numModules, newModule);
                        break;
                    }
                    case 2: {
                        struct Level newLevel;
                        printf("Enter level details (MemoryLevel NumberOfCells ProtectionFlag): ");
                        scanf("%d %d %d", &newLevel.memoryLevel, &newLevel.numberOfCells,
                              &newLevel.protectionFlag);
                        insert_level(levels, &numLevels, newLevel);
                        break;
                    }
                    case 3: {
                        struct StatusEvent newEvent;
                        printf(
                            "Enter status event details (EventId ModuleId NewStatus Date(DD.MM.YYYY) "
                            "Time(HH:MM:SS)): ");
                        scanf("%d %d %d %10s %8s", &newEvent.eventId, &newEvent.moduleId, &newEvent.newStatus,
                              newEvent.date, newEvent.time);
                        insert_status_event(statusEvents, &numEvents, newEvent);
                        break;
                    }
                    default:
                        printf("Invalid table choice.\n");
                        break;
                }
                break;
            }
            case 3: {
                int table_choice, id;
                printf("Please choose a table to update:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                printf("> ");
                scanf("%d", &table_choice);

                switch (table_choice) {
                    case 1: {
                        printf("Enter module Id to update: ");
                        scanf("%d", &id);
                        struct Module updatedModule;
                        printf(
                            "Enter updated module details (Id Name MemoryLevel CellNumber DeletionFlag): ");
                        scanf("%d %29s %d %d %d", &updatedModule.moduleId, updatedModule.moduleName,
                              &updatedModule.memoryLevel, &updatedModule.cellNumber,
                              &updatedModule.deletionFlag);
                        update_module(modules, numModules, id, updatedModule);
                        break;
                    }
                    case 2: {
                        printf("Enter level MemoryLevel to update: ");
                        scanf("%d", &id);
                        struct Level updatedLevel;
                        printf("Enter updated level details (MemoryLevel NumberOfCells ProtectionFlag): ");
                        scanf("%d %d %d", &updatedLevel.memoryLevel, &updatedLevel.numberOfCells,
                              &updatedLevel.protectionFlag);
                        update_level(levels, numLevels, id, updatedLevel);
                        break;
                    }
                    case 3: {
                        printf("Enter status event EventId to update: ");
                        scanf("%d", &id);
                        struct StatusEvent updatedEvent;
                        printf(
                            "Enter updated status event details (EventId ModuleId NewStatus Date(DD.MM.YYYY) "
                            "Time(HH:MM:SS)): ");
                        scanf("%d %d %d %10s %8s", &updatedEvent.eventId, &updatedEvent.moduleId,
                              &updatedEvent.newStatus, updatedEvent.date, updatedEvent.time);
                        update_status_event(statusEvents, numEvents, id, updatedEvent);
                        break;
                    }
                    default:
                        printf("Invalid table choice.\n");
                        break;
                }
                break;
            }
            case 4: {
                int table_choice, id;
                printf("Please choose a table to delete from:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                printf("> ");
                scanf("%d", &table_choice);

                switch (table_choice) {
                    case 1: {
                        printf("Enter module Id to delete: ");
                        scanf("%d", &id);
                        delete_module(modules, &numModules, id);
                        break;
                    }
                    case 2: {
                        printf("Enter level MemoryLevel to delete: ");
                        scanf("%d", &id);
                        delete_level(levels, &numLevels, id);
                        break;
                    }
                    case 3: {
                        printf("Enter status event EventId to delete: ");
                        scanf("%d", &id);
                        delete_status_event(statusEvents, &numEvents, id);
                        break;
                    }
                    default:
                        printf("Invalid table choice.\n");
                        break;
                }
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 9: {
                break;
            }
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 9.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
