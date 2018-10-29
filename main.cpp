//Lucas Manker
//Homework 8
//due 4/27/18

#include <iostream>
#include <fstream>
#include <string>
#include "FetchExecute.h"

using namespace std;


bool fileCheck(fstream &stream);

//main----takes in the file as an argument, fizzles if no filepath was entered
int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Specify a file path" << endl;
		return 1;
	}
	fstream stream;
	stream.open(argv[1]);
	bool isOpen = fileCheck(stream);

	if (!isOpen) {
		cout << "Bad file path" << endl;
		return 1;
	}
	stream.close();
	FetchExecute cycle(argv[1]);
	cycle.fetch();
	cycle.exePrint();
	cycle.memory.print();
	return 0;
}



//checks to make sure the file path was correct
bool fileCheck(fstream& stream) {
	if (stream.is_open()) {
		return true;
	}
	else {
		return false;
	}
}