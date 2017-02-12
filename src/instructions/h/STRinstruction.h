/*
 * STRinstruction.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef STRINSTRUCTION_H_
#define STRINSTRUCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "InstructionParser.h"
using namespace std;

class Instruction;

class STR_instruction: public Instruction {
private:


	int a; //a:5
	int r; //r:5
	int f; //f:3
	bool flag_STR;
	int imm; //imm:10


public:
	STR_instruction(int a=0,int r=0,int f=0,int imm= 0, bool flag_STR=false);

	STR_instruction(string instruction,string name, string condition, bool psw_change,
				Elf32_Word op_code, int a = 0,int r=0,int f=0,int imm=false,bool flag_STR=false);
	~STR_instruction();

	Elf32_Word read_instruction();
};



#endif /* STRINSTRUCTION_H_ */
