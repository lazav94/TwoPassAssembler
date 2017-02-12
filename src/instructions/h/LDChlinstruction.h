/*
 * LDChlinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef LDChlINSTRUCTION_H_
#define LDChlINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class LDChl_instruction: public Instruction {
private:


	int dst; //dst:4
	int c;   //c:16
	bool flag_h;
	bool flag_ldc;
	// nu:3


public:
	LDChl_instruction(int dst=0,int c=0, bool flag_h=false, bool flag_ldc=false);

	LDChl_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int dst = 0,int c=0,bool flag_h=false,  bool flag_ldc=false);
	~LDChl_instruction();

	Elf32_Word read_instruction();
};



#endif /* LDChlINSTRUCTION_H_ */
