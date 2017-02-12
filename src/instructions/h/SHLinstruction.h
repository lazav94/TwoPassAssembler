/*
 * SHLinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef SHLINSTRUCTION_H_
#define SHLINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class SHL_instruction: public Instruction {
private:


	int dst; //dst:5
	int src; //src:5
	int imm; //imm:5
	bool flag_l;
	// nu:8





public:
	SHL_instruction(int src=0,int dst=0,int imm= 0, bool flag_l=false);

	SHL_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0,int dst=0,int imm=false,bool flag_l=false);
	~SHL_instruction();

	Elf32_Word read_instruction();
};



#endif /* SHLINSTRUCTION_H_ */
