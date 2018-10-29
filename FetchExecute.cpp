//Lucas Manker
//FetchExecute.cpp

#include "FetchExecute.h"
#include <iostream>



using namespace std;

//constuctor----needs a filename to start the cycle
FetchExecute::FetchExecute(string filename) {
	memory.memWrite(filename);
	error = false;
	begin = false;
	end = false;
	setPC(0);
	setIR("0");
	setMBR("0");
	setMAR(0);
	setAC(0);
	setMQ(0);
}

//these functions access the registers
int FetchExecute::getPC(void) {
	return PC;
}
string FetchExecute::getIR(void) {
	return IR;
}
int FetchExecute::getMAR(void) {
	return MAR;
}
int FetchExecute::getAC(void) {
	return AC;
}
int FetchExecute::getMQ(void) {
	return MQ;
}
string FetchExecute::getMBR(void) {
	return MBR;
}
bool FetchExecute::getError(void) {
	return error;
}
bool FetchExecute::getBegin(void) {
	return begin;
}
bool FetchExecute::getEnd(void) {
	return end;
}


//functions to set registers
void FetchExecute::setPC(int val) {
	PC = val;
	return;
}
void FetchExecute::setIR(string val) {
	IR = val;
	return;
}
void FetchExecute::setMAR(int val) {
	MAR = val;
	return;
}

void FetchExecute::setAC(int val) {
	AC = val;
	return;
}
void FetchExecute::setMQ(int val) {
	MQ = val;
	return;
}
void FetchExecute::setMBR(string val) {
	MBR = val;
	return;
}
void FetchExecute::setError(void) {
	error = true;
	return;
}
void FetchExecute::setBegin(void) {
	begin = true;
	return;
}
void FetchExecute::setEnd(void) {
	end = true;
	return;
}

/*Fetch cycle:
Puts PC in MAR, decodes instructions then puts in MBR, increments PC, puts decoded instructions in IR.
After these steps, execute cycle starts.
*/
void FetchExecute::fetch(void) {
	while (!getEnd()) {
		setMAR(getPC());
		setMBR(memory.get(getMAR()));
		setPC(getPC() + 1);
		setIR(getMBR());
		decoder();
		if (begin) {
			postRec();
		}
	}
	return;
}

//finds out if there were 2 arguments or one (and if begin was entered), then executes
void FetchExecute::decoder(void) {
	string command = decode(getIR());
	regex patternTwo("(\\d+)\\s+(\\d+)");
	regex patternOne("(\\d+)");
	smatch result;
	if (command == "start") {
		preRec();
		setBegin();
		return;
	}
	else if (!begin) {
		return;
	}
	else {
		preRec();
		if (regex_match(command, result, patternTwo)) {
			string comm = result[1];
			string address = result[2];
			istringstream streamComm(comm);
			istringstream streamAdd(address);
			int varComm, varAdd;
			streamComm >> varComm;
			streamAdd >> varAdd;
			setMAR(varAdd);
			execute(varComm);
			return;
		}
		else if (regex_match(command, result, patternOne)) {
			istringstream stream(result[0]);
			int var;
			stream >> var;
			execute(var);
			return;
		}

	}
}


//instruction decoder, finding patterns then shipping off to IR
string FetchExecute::decode(string command) {
	regex patternOne("load MQ");
	regex patternTwo("load MQ,M\\((\\d+)\\)");
	regex patternThree("stor M\\((\\d+)\\)");
	regex patternFour("load M\\((\\d+)\\)");
	regex patternFive("load -M\\((\\d+)\\)");
	regex patternSix("load \\|M\\((\\d+)\\)\\|");
	regex patternSeven("load -\\|M\\((\\d+)\\)\\|");
	regex patternEight("halt");
	regex patternNine("begin");
	regex patternTen("[(-9)-9.]\.*");
	regex patternEleven("nop");
	regex patternTwelve("[a-z]");
	regex patternThirteen("jump M\\((\\d+)\\)");
	regex patternFourteen("jump[+] M\\((\\d+)\\)");
	regex patternFifteen("add M\\((\\d+)\\)");
	regex patternSixteen("add \\|M\\((\\d+)\\)\\|");
	regex patternSeventeen("sub M\\((\\d+)\\)");
	regex patternEighteen("sub \\|M\\((\\d+)\\)\\|");
	regex patternNineteen("mul M\\((\\d+)\\)");
	regex patternTwenty("div M\\((\\d+)\\)");
	regex patternTwentyone("lsh");
	regex patternTwentytwo("rsh");
	smatch result;
	if (regex_match(command, result, patternOne)) {
		return "1";
	}
	else if (regex_match(command, result, patternTwo)) {
		string retVal = result[1];
		return "2 " + retVal;
	}
	else if (regex_match(command, result, patternThree)) {
		string retVal = result[1];
		return "3 " + retVal;
	}
	else if (regex_match(command, result, patternFour)) {
		string retVal = result[1];
		string four = "4";
		return (four + " " + retVal);
	}
	else if (regex_match(command, result, patternFive)) {
		string retVal = result[1];
		return "5 " + retVal;
	}
	else if (regex_match(command, result, patternSix)) {
		string retVal = result[1];
		return "6 " + retVal;
	}
	else if (regex_match(command, result, patternSeven)) {
		string retVal = result[1];
		return "7 " + retVal;
	}
	else if (regex_match(command, result, patternEight)) {
		memory.setEnd(getPC());
		setEnd();
		return "0";
	}
	else if (regex_match(command, result, patternNine)) {
		return "start";
	}
	else if (regex_match(command, result, patternTen)) {
		return "0";
	}
	else if (regex_match(command, result, patternEleven)) {
		return "0";
	}
	else if (regex_match(command, result, patternTwelve)) {
		return "0";
	}
	else if (regex_match(command, result, patternThirteen)) {
		string retVal = result[1];
		return "8 " + retVal;
	}
	else if (regex_match(command, result, patternFourteen)) {
		string retVal = result[1];
		return "9 " + retVal;
	}
	else if (regex_match(command, result, patternFifteen)) {
		string retVal = result[1];
		return "10 " + retVal;
	}
	else if (regex_match(command, result, patternSixteen)) {
		string retVal = result[1];
		return "11 " + retVal;
	}
	else if (regex_match(command, result, patternSeventeen)) {
		string retVal = result[1];
		return "12 " + retVal;
	}
	else if (regex_match(command, result, patternEighteen)) {
		string retVal = result[1];
		return "13 " + retVal;
	}
	else if (regex_match(command, result, patternNineteen)) {
		string retVal = result[1];
		return "14 " + retVal;
	}
	else if (regex_match(command, result, patternTwenty)) {
		string retVal = result[1];
		return "15 " + retVal;
	}
	else if (regex_match(command, result, patternTwentyone)) {
		return "16";
	}
	else if (regex_match(command, result, patternTwentytwo)) {
		return "17";
	}
	else {
		cout << command << " incorrect syntax!" << endl;
		cout << "execution cancelled" << endl;
		exit(1);
	}
}

//figures out which instruction to execute
void FetchExecute::execute(int code) {
	switch (code) {
	case 1: loadMQ();
		break;
	case 2: loadMQX();
		break;
	case 3: store();
		break;
	case 4: loadMX();
		break;
	case 5: loadNegMX();
		break;
	case 6: loadABSMX();
		break;
	case 7: loadABSNegMX();
		break;
	case 8: jumpMX();
		break;
	case 9: jumpPlus();
		break;
	case 10: add();
		break;
	case 11: addABS();
		break;
	case 12: sub();
		break;
	case 13: subABS();
		break;
	case 14: mul();
		break;
	case 15: div();
		break;
	case 16: lSH();
		break;
	case 17: rSH();
		break;
	}
	return;
}
void FetchExecute::loadMQ(void) {
	setAC(getMQ());
	return;
}
void FetchExecute::loadMQX(void) {
	string temp = memory.get(getMAR());
	int val;
	istringstream stream(temp);
	stream >> val;
	setMQ(val);
	return;
}

//stores whatever is in the AC into the address in MAR
void FetchExecute::store(void) {
	int temp = getAC();
	string convert = to_string(temp);
	memory.set(convert, getMAR());
	return;
}

//loads whatever the MAR is at into the AC
void FetchExecute::loadMX(void) {
	string temp = memory.get(getMAR());
	int val;
	istringstream stream(temp);
	stream >> val;
	setAC(val);
	return;
}

//loads whatever the MAR is at, then makes it negative, then puts into AC
void FetchExecute::loadNegMX(void) {
	string temp = memory.get(getMAR());
	int val;
	istringstream stream(temp);
	stream >> val;
	val *= (-1);
	setAC(val);
	return;
}

//loads whatever the MAR is at, takes the absolute value, puts in AC
void FetchExecute::loadABSMX(void) {
	string temp = memory.get(getMAR());
	int val;
	istringstream stream(temp);
	stream >> val;
	val = abs(val);
	setAC(val);
	return;
}

//loads whatever the MAR is at, takes the absolute value, makes it negative, puts in AC
void FetchExecute::loadABSNegMX(void) {
	string temp = memory.get(getMAR());
	int val;
	istringstream stream(temp);
	stream >> val;
	val = abs(val);
	val *= (-1);
	setAC(val);
	return;
}

void FetchExecute::jumpMX(void) {
	setPC(getMAR());
	return;
}
void FetchExecute::jumpPlus(void) {
	if (getAC() >= 0) {
		setPC(getMAR());
	}
	return;
}
void FetchExecute::add(void) {
	string temp = memory.get(getMAR());
	int val = 0;
	istringstream stream(temp);
	stream >> val;
	setAC(getAC() + val);
	return;
}
void FetchExecute::addABS(void) {
	string temp = memory.get(getMAR());
	int val = 0;
	istringstream stream(temp);
	stream >> val;
	val = abs(val);
	setAC(getAC() + val);
	return;
}
void FetchExecute::sub(void) {
	string temp = memory.get(getMAR());
	int val = 0;
	istringstream stream(temp);
	stream >> val;
	setAC(getAC() - val);
	return;
}
void FetchExecute::subABS(void) {
	string temp = memory.get(getMAR());
	int val = 0;
	istringstream stream(temp);
	stream >> val;
	val = abs(val);
	setAC(getAC() - val);
	return;
}
void FetchExecute::mul(void) {
	string temp = memory.get(getMAR());
	int val = 0;
	istringstream stream(temp);
	stream >> val;
	setAC(getMQ() * val);
	return;
}
void FetchExecute::div(void) {
	string temp = memory.get(getMAR());
	int val = 0;
	istringstream stream(temp);
	stream >> val;
	setMQ(getAC() / val);
	setAC(getAC() % val);
	return;
}
void FetchExecute::lSH(void) {
	int val = getAC();
	val <<= 1;
	setAC(val);
	return;
}
void FetchExecute::rSH(void) {
	int val = getAC();
	val >>= 1;
	setAC(val);
	return;
}

void FetchExecute::preRec(void) {
	int pcTemp = (getPC()-1);
	string pc = to_string(pcTemp);
	string ir = getIR();
	string combo = "PC = " + pc + " IR = " + ir;
	progExe.push_back(combo);
	return;
}
void FetchExecute::postRec(void) {
	int pcTemp = getPC();
	string pc = to_string(pcTemp);
	int acTemp = getAC();
	string ac = to_string(acTemp);
	int mqTemp = getMQ();
	string mq = to_string(mqTemp);
	string combo = "PC = " + pc + " AC = " + ac + " MQ = " + mq;
	progExe.push_back(combo);
	return;
}
void FetchExecute::exePrint(void) {
	cout << "                   EXECUTION OF PROGRAM                   " << endl;
	int lineBreak(1);
	for (int i = 0; i < progExe.size(); i++) {
		cout << progExe[i] << endl;
		if (lineBreak % 2 == 0) {
			cout << "-----------------------------------------------------------------" << endl;
		}
		lineBreak++;
	}
	return;
}

