/*
 * OUTinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef OUTOUTSTRUCTION_H_
#define OUTOUTSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class OUT_instruction: public Instruction {
private:


	int dst; //dst:4
	int src; //src:4
	bool flag;
	// nu:15




public:
	OUT_instruction(int src=0,int dst=0,bool flag=false);

	OUT_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0,int dst=0, bool flag=false);
	~OUT_instruction();

	Elf32_Word read_instruction();
};



#endif /* OUTOUTSTRUCTION_H_ */
