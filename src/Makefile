CC=g++ # compilador
CFLAGS=-Wall -Wextra # compiler flags
EXEC=./tp03 # nome do executavel

# === REGRAS =====

$(EXEC): main.cpp metro.o
	$(CC) $(CFLAGS) main.cpp metro.o -o $(EXEC)

main.o: main.cpp
	g++ -c main.cpp

metro.o: metro.cpp headers/metro.h
	g++ -c metro.cpp

clean:
	rm -rf main.o metro.o