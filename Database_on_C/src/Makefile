CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OBJS = modules_db.o modules.o levels.o status_events.o

all: modules_db

build_db: modules_db

modules_db: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ../build/modules_db

modules_db.o: modules_db.c shared.h
	$(CC) $(CFLAGS) -c modules_db.c

modules.o: modules.c shared.h
	$(CC) $(CFLAGS) -c modules.c

levels.o: levels.c shared.h
	$(CC) $(CFLAGS) -c levels.c

status_events.o: status_events.c shared.h
	$(CC) $(CFLAGS) -c status_events.c

clean:
	rm -f *.o modules_db