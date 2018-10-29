//Lucas Manker
//Memory.cpp

#include "MEMORY.H"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

//fills 1000 blocks of an array with "nop"
Memory::Memory() {
	end = 0;
	for (int i = 0; i < 1000; i++) {
		mem[i] = "nop";
	}
}

//gets whatever is at the array block
string Memory::get(int index) {
	return mem[index];
}

//changes the value at an array block
void Memory::set(string entry, int index) {
	mem[index] = entry;
	return;
}
void Memory::setEnd(int val) {
	end = val;
	return;
}

void Memory::setBegin(int val) {
	end = val;
	return;
}

//reads in the lines of a file, writes these strings to memory
void Memory::memWrite(string fileName) {
	string temp;
	ifstream stream;
	regex pattern("(\\d+)(\\s)(.*)");
	smatch result;
	stream.open(fileName);
	if (!stream.is_open()) {
		cout << "could not write to memory" << endl;
		return;
	}
	while(getline(stream, temp)) {
		if (regex_match(temp, result, pattern)) {
			istringstream stream(result[0]);
			int val;
			stream >> val;
			set(result[3], val);
		}
	}
	stream.close();
	return;
}

void Memory::print(void) {
	cout << "                MEMORY                    " << endl;
	int i(0);
	while (i < end) {
		cout << i << " "<< mem[i] << endl;
		i++;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
}