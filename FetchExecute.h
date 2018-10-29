//Lucas Manker
//FetchExecute.h
#ifndef _FETCHEXECUTE_H
#define _FETCHEXECUTE_H

#include <string>
#include <sstream>
#include "Memory.h"
#include <cmath>
#include <regex>

using namespace std;

class FetchExecute {
private:
	int PC;
	string IR;
	int MAR;
	string MBR;
	int AC;
	int MQ;
	bool error;
	bool begin;
	bool end;
public:
	FetchExecute(string filename);

	Memory memory;
	vector<string> progExe;

	int getPC(void);
	string getIR(void);
	int getMAR(void);
	int getAC(void);
	int getMQ(void);
	string getMBR(void);
	bool getError(void);
	bool getBegin(void);
	bool getEnd(void);

	void setPC(int val);
	void setIR(string val);
	void setMAR(int val);
	void setAC(int val);
	void setMQ(int val);
	void setMBR(string val);
	void setError(void);
	void setBegin(void);
	void setEnd(void);

	void fetch(void);
	void decoder(void);
	string decode(string command);

	void execute(int code);
	void loadMQ(void);
	void loadMQX(void);
	void store(void);
	void loadMX(void);
	void loadNegMX(void);
	void loadABSMX(void);
	void loadABSNegMX(void);
	void jumpMX(void);
	void jumpPlus(void);
	void add(void);
	void addABS(void);
	void sub(void);
	void subABS(void);
	void mul(void);
	void div(void);
	void lSH(void);
	void rSH(void);

	void preRec(void);
	void postRec(void);
	void exePrint(void);
};

#endif