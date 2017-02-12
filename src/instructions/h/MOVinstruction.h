/*
 * MOVinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef MOVINSTRUCTION_H_
#define MOVINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class MOV_instruction: public Instruction {
private:


	int dst; //dst:5
	int src; //src:5
	bool flag_l;
	// nu:8





public:
	MOV_instruction(int src=0,int dst=0, bool flag_l=false);

	MOV_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0,int dst=0,bool flag_l=false);
	~MOV_instruction();

	Elf32_Word read_instruction();
};



#endif /* MOVINSTRUCTION_H_ */
