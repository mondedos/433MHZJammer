all: 
	$(CXX)  -Wall -o Jammer main.c -lwiringPi -lpthread

clean:
	$(RM) *.o main.o