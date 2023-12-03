#Marcel Zama 
# 24/10/2023
#MakeFile for Wator working Sequencially version
#GitHub repository: https://github.com/MarcelZama/Wa-Tor-Problem/tree/main

CXX = g++
CPPFILES= Sequencially.cpp
CPPFLAGS= -Wall -fopenmp
LDFLAGS = -lgomp -lsfml-graphics -lsfml-window -lsfml-system
EXE= Sequencially

SRCS=Sequencially.cpp
OBJS=$(subst .cc,.o,$(SRCS))

#This rule says that each .o file depends on a .cpp file of the same name
#%.o: %.cpp
#	$(CC) -c -o $@ $< $(CPPFLAGS) $(DEBUGFLAGS)

ALL:  $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)


#this is customary and just deletes all .o files
CLEAN:
	rm *.o
