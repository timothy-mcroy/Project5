CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = main.o gear.o Game.o gameboard.o mapObject.o characterClass.o input.o

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o PandP

main.o: input.h gear.h Game.h gameboard.h mapObject.h characterClass.h
	$(CC) $(CFLAGS) main.cpp

gear.o: gear.h
	$(CC) $(CFLAGS) gear.cpp

Game.o: Game.h
	$(CC) $(CFLAGS) Game.cpp

gameboard.o: gameboard.h
	$(CC) $(CFLAGS) loadfile.cpp
    
mapObject.o: mapObject.h
	$(CC) $(CFLAGS) 

characterClass.o: characterClass.h
	$(CC) $(CFLAGS) 

input.o: input.h
	$(CC) $(CFLAGS)

clean:
	rm *.o PandP
