#/******************************************************************
#Title:            makefile
#Author:           Erin Williams
#Date Created:     4/30/2017
#Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
#Professor:        Aarsh Vora
#Purpose:          Assignment #3
#Description:      Makefile for Project 3
#*******************************************************************/

CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall

SOURCES = main.cpp trienode.cpp trie.cpp dictionary.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE_NAME = Project3

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)
