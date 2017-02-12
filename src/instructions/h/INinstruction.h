/*
 * INinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef ININSTRUCTION_H_
#define ININSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class IN_instruction: public Instruction {
private:


	int dst; //dst:4
	int src; //src:4
	bool flag;
	// nu:15




public:
	IN_instruction(int src=0,int dst=0,bool flag=false);

	IN_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0,int dst=0, bool flag=false);
	~IN_instruction();

	Elf32_Word read_instruction();
};



#endif /* ININSTRUCTION_H_ */
