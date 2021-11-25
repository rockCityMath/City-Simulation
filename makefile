#Compiler Variables
CC=g++
CFLAGS := -std=c++11 -W


#Compile all Objects
output : init.o main.o grid.o cell.o sim.o residential.o industrial.o commercial.o
	$(CC) $(CFLAGS) init.o main.o grid.o cell.o sim.o residential.o industrial.o commercial.o -o output

#Source Objects
init.o : src/init.cpp include/init.h
	$(CC) -c src/init.cpp

main.o : src/main.cpp include/main.h include/grid.h include/cell.h include/init.h
	$(CC) -c src/main.cpp

grid.o : src/grid.cpp include/grid.h include/cell.h include/init.h
	$(CC) -c src/grid.cpp

cell.o : src/cell.cpp include/cell.h
	$(CC) -c src/cell.cpp

sim.o : src/sim.cpp include/grid.h
	$(CC) -c src/sim.cpp

residential.o : src/residential.cpp include/grid.h
	$(CC) -c src/residential.cpp

industrial.o : src/industrial.cpp include/grid.h
	$(CC) -c src/industrial.cpp

commercial.o : src/commercial.cpp include/grid.h
	$(CC) -c src/commercial.cpp

#Remove output file, .o files
clean:
	rm output *.o