#Marcel Zama 
# 28/10/2023
#MakeFile for Wator working Parallel version

CXX = g++
CPPFILES= Parallel.cpp
CPPFLAGS= -Wall -fopenmp
LDFLAGS = -lgomp -lsfml-graphics -lsfml-window -lsfml-system
EXE= Parallel

SRCS=Parallel.cpp
OBJS=$(subst .cc,.o,$(SRCS))

#This rule says that each .o file depends on a .cpp file of the same name
#%.o: %.cpp
#	$(CC) -c -o $@ $< $(CPPFLAGS) $(DEBUGFLAGS)

ALL:  $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)


#this is customary and just deletes all .o files
CLEAN:
	rm *.o
