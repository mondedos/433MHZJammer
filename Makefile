all: main.o
	$(CXX) main.o -o Jammer
	
main.o: main.c
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi
	
	

clean:
	$(RM) *.o main.o