#ifndef SHARED_H_
#define SHARED_H_

#define MAX_MODULES 100
#define MAX_LEVELS 10
#define MAX_EVENTS 100

struct Module {
    int moduleId;
    char moduleName[30];
    int memoryLevel;
    int cellNumber;
    int deletionFlag;
};

struct Level {
    int memoryLevel;
    int numberOfCells;
    int protectionFlag;
};

struct StatusEvent {
    int eventId;
    int moduleId;
    int newStatus;
    char date[11];  // "dd.mm.yyyy\0"
    char time[9];   // "hh:mm:ss\0"
};

extern struct Module modules[MAX_MODULES];
extern struct Level levels[MAX_LEVELS];
extern struct StatusEvent statusEvents[MAX_EVENTS];
extern int numModules;
extern int numLevels;
extern int numEvents;

// Функции для работы с индексами
void create_index(const char *filename, const int *data, int size);
int binary_search(const char *filename, int key);
void delete_index(const char *filename);

// Функции для работы с таблицами БД
void select_modules(struct Module *modules, int numModules);
void insert_module(struct Module *modules, int *numModules, struct Module newModule);
void update_module(struct Module *modules, int numModules, int moduleId, struct Module updatedModule);
void delete_module(struct Module *modules, int *numModules, int moduleId);

void select_levels(struct Level *levels, int numLevels);
void insert_level(struct Level *levels, int *numLevels, struct Level newLevel);
void update_level(struct Level *levels, int numLevels, int memoryLevel, struct Level updatedLevel);
void delete_level(struct Level *levels, int *numLevels, int memoryLevel);

void select_status_events(struct StatusEvent *statusEvents, int numEvents);
void insert_status_event(struct StatusEvent *statusEvents, int *numEvents, struct StatusEvent newEvent);
void update_status_event(struct StatusEvent *statusEvents, int numEvents, int eventId,
                         struct StatusEvent updatedEvent);
void delete_status_event(struct StatusEvent *statusEvents, int *numEvents, int eventId);

#endif /* SHARED_H_ */
