/*
 * ADDinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef ADDINSTRUCTION_H_
#define ADDINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class ADD_instruction: public Instruction {
private:


	int dst; //dst:5
	int src; //src:5
	int imm; //imm:18
	bool flag;
	// nu:13

	//immed_flag == 0 => dst:5 src:5 flag:1 nu:13 = 24
	//immed_flat == 1 => dst:5 falg:1 imm:18      = 24



public:
	ADD_instruction(int src=0,int dst=0,int imm= 0, bool flag=false);

	ADD_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0,int dst=0,int imm=false,bool flag=false);
	~ADD_instruction();


	Elf32_Word read_instruction();
};



#endif /* ADDINSTRUCTION_H_ */
