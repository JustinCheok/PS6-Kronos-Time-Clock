CC = g++
CFLAGS = -std=c++11 -c -g -Og -Wall -Werror -pedantic -std=c++11 -l boost_unit_test_framework -o2 -lboost_regex -lboost_date_time
OBJ = main.o 
DEPS = main.cpp 
LIBS = -lboost_regex -lboost_date_time
EXE = ps6

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
	
clean:
	rm $(OBJ) $(EXE)
