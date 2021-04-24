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
	

findcomp: driver.o PGMImageProcessor.o ConnectedComponent.o
	$(CC) driver.o ConnectedComponent.o PGMImageProcessor.o -o findcomp $(LIBS)

driver.o: $(SRCDIR)/driver.cpp 
	$(CC) -c $(SRCDIR)/driver.cpp

ConnectedComponent.o: $(SRCDIR)/ConnectedComponent.cpp
	$(CC) -c $(SRCDIR)/ConnectedComponent.cpp

PGMImageProcessor.o: $(SRCDIR)/PGMImageProcessor.cpp
	$(CC) -c $(SRCDIR)/PGMImageProcessor.cpp

clean:
	@rm -f *.o 
	@rm findcomp


install: 
	@mv $(BINDIR)/findcomp ~/bin