/*
 * CALLinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef CALLINSTRUCTION_H_
#define CALLINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class CALL_instruction: public Instruction {
private:


	int dst; //dst:5
	int imm; //imm:19


public:
	CALL_instruction(int dst=0,int imm= 0);

	CALL_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int dst=0,int imm=false);
	~CALL_instruction();

	Elf32_Word read_instruction();
};



#endif /* CALLINSTRUCTION_H_ */
