# Makefile for Project 01: Strands
# Author: Fernando Tello
# CPSC1070 - Spring 2024
# Project 01: Strands

CC = gcc
CFLAGS = -Wall

EXECUTABLE = strands.exe
MAIN = main.c

# Includes the file containing SOURCES and HEADERS
include defs.mk

$(EXECUTABLE): $(MAIN) $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(MAIN) $(SOURCES)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
