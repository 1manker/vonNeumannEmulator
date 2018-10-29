//Lucas Manker
//Memory.h

#ifndef _MEMORY_H
#define _MEMORY_H

#include <string>


using namespace std;

class Memory {
private:
	string mem[1000];
	int end;
	int begin;
public:
	Memory();
	string get(int index);
	void set(string entry, int index);
	void memWrite(string fileName);
	void print(void);
	void setEnd(int val);
	void setBegin(int val);
};


#endif
