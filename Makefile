all: main.o
	$(CXX) main.o -o Jammer
	
main.o: main.c
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.c -o main.o -lwiringPi
	
	

clean:
	$(RM) *.o main.o