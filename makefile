# Makefile for creating the 'Bank' program
CCC = g++
CXXFLAGS = -g -Wall -pthread -std=c++11 -pedantic
CXXLINK = $(CCC)
OBJS = main.o bank.o ATMs.o account.o
RM = rm -f

All:Bank

# Link the final executable
Bank : $(OBJS)
	$(CXXLINK) $(CXXFLAGS) -o Bank $(OBJS)


# Compile main.c to create main.o
main.o: main.cpp ATMs.h account.h
bank.o: bank.cpp ATMs.h account.h
ATMs.o: ATMs.cpp ATMs.h account.h
account.o: account.cpp account.h

# Cleaning old files before new make
clean:
	$(RM) Bank *.o *.bak *~ "#"* core log.txt