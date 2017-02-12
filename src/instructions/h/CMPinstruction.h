/*
 * CMPinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef CMPINSTRUCTION_H_
#define CMPINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class CMP_instruction: public Instruction {
private:


	int dst; //dst:5
	int src; //src:5
	int imm; //imm:18
	bool flag;
	// nu:13

	//immed_flag == 0 => dst:5 src:5 flag:1 nu:13 = 24
	//immed_flat == 1 => dst:5 falg:1 imm:18      = 24



public:
	CMP_instruction(int src=0,int dst=0,int imm= 0, bool flag=false);

	CMP_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0,int dst=0,int imm=false,bool flag=false);
	~CMP_instruction();

	Elf32_Word read_instruction();
};



#endif /* CMPINSTRUCTION_H_ */
