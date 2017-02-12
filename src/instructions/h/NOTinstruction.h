/*
 * NOTinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef NOTINSTRUCTION_H_
#define NOTINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class NOT_instruction: public Instruction {
private:


	int dst; //dst:5
	int src; //src:5


	//immed_flag == 0 => dst:5 src:5  nu:14 = 24




public:
	NOT_instruction(int src=0,int dst=0);

	NOT_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0,int dst=0);
	~NOT_instruction();

	Elf32_Word read_instruction();
};



#endif /* NOTINSTRUCTION_H_ */
