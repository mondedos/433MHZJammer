all: fetch merge merge

fetch:
	git fetch origin 

merge:
	git merge origin/master 

comp_main:
	$(CXX)  -Wall -o Jammer main.c -lwiringPi -lpthread

clean:
	$(RM) *.o main.o
