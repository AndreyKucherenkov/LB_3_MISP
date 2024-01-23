.PHONY: all clean test format

CXX=g++
OFLAGS=-O2 -Wall -DNDEBUG
LDFLAGS=-lUnitTest++ 

SOURCES=modBetaCipher.cpp modBetaCipher-test.cpp
HEADERS=modBetaCipher.h
EXECUTABLE=modBetaCipher-test


$(EXECUTABLE): $(SOURCES)
	$(CXX)  $(SOURCES)  -o $(EXECUTABLE) $(OFLAGS) $(LDFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE) 

format:
	astyle $(SOURCES) $(HEADERS)
clean:
	rm -f $(EXECUTABLE) *.orig
