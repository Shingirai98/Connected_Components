# ------------------------------------------
# Makefile
# Shingirai Denver Maburutse
# Date: 05/04/2021
# ------------------------------------------

CC = g++
LIBS = -lm
SRCDIR = src
BINDIR = bin
OBJDIR = obj

#$(BINDIR)/frames: $(OBJDIR)/driver.o $(OBJDIR)/FrameSequence.o
	

findcomp:  ConnectedComponent.o PGMImageProcessor.o driver.o
	$(CC)  ConnectedComponent.o PGMImageProcessor.o driver.o -o findcomp $(LIBS) -std=c++2a

driver.o: $(SRCDIR)/driver.cpp 
	$(CC) -c $(SRCDIR)/driver.cpp

PGMImageProcessor.o: $(SRCDIR)/PGMImageProcessor.cpp
	$(CC) -c $(SRCDIR)/PGMImageProcessor.cpp

ConnectedComponent.o: $(SRCDIR)/ConnectedComponent.cpp
	$(CC) -c $(SRCDIR)/ConnectedComponent.cpp



clean:
	@rm -f *.o 
	@rm findcomp
	

run:
	./findcomp -s 3 153468 -t 200 -p -w out.pgm ./images/chess.pgm

install: 
	@mv $(BINDIR)/findcomp ~/bin