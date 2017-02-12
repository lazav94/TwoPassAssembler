/*
 * INTinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef INTINSTRUCTION_H_
#define INTINSTRUCTION_H_

#include <string>
#include <iostream>
#include "Instruction.h"


using namespace std;

class Instruction;

class INT_instruction: public Instruction {
private:
	int src;
public:
	INT_instruction(int src=0);
	INT_instruction(string instruction, string name, string condition, bool psw_change,
				Elf32_Word op_code, int src = 0);
	~INT_instruction();

	Elf32_Word read_instruction();
};



#endif /* INTINSTRUCTION_H_ */
