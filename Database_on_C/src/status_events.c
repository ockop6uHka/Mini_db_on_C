// status_events.c

#include <stdio.h>

#include "shared.h"

struct StatusEvent statusEvents[MAX_EVENTS];
int numEvents = 0;

void select_status_events(struct StatusEvent *events, int numRecords) {
    printf("\n=============================\nSTATUS_EVENTS\n=============================\n");
    for (int i = 0; i < numRecords; ++i) {
        printf("%d %d %d %s %s\n", events[i].eventId, events[i].moduleId, events[i].newStatus, events[i].date,
               events[i].time);
    }
}

void insert_status_event(struct StatusEvent *events, int *numRecords, struct StatusEvent newEvent) {
    if (*numRecords < MAX_EVENTS) {
        events[*numRecords] = newEvent;
        (*numRecords)++;
        printf("Status event inserted successfully.\n");
    } else {
        printf("Cannot insert status event: Maximum capacity reached.\n");
    }
}

void update_status_event(struct StatusEvent *events, int numRecords, int eventId,
                         struct StatusEvent updatedEvent) {
    int found = 0;
    for (int i = 0; i < numRecords; ++i) {
        if (events[i].eventId == eventId) {
            events[i] = updatedEvent;
            found = 1;
            printf("Status event updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Status event not found.\n");
    }
}

void delete_status_event(struct StatusEvent *events, int *numRecords, int eventId) {
    int found = 0;
    for (int i = 0; i < *numRecords; ++i) {
        if (events[i].eventId == eventId) {
            events[i] = events[*numRecords - 1];
            (*numRecords)--;
            found = 1;
            printf("Status event deleted successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Status event not found.\n");
    }
}
