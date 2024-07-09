// status_events.h

#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include "shared.h"

#define MAX_EVENTS 100

struct StatusEvent {
    int eventId;
    int moduleId;
    int newStatus;
    char date[11];  // dd.mm.yyyy\0 format
    char time[9];   // hh:mm:ss\0 format
};

void select_status_events(struct StatusEvent *events, int numRecords);
void insert_status_event(struct StatusEvent *events, int *numRecords, struct StatusEvent newEvent);
void update_status_event(struct StatusEvent *events, int numRecords, int eventId,
                         struct StatusEvent updatedEvent);
void delete_status_event(struct StatusEvent *events, int *numRecords, int eventId);

#endif  // STATUS_EVENTS_H
