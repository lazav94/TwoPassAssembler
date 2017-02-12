/*
 * Instruction.h
 *
 *  Created on: Aug 9, 2016
 *      Author: laza
 */

#ifndef PARSING_INSTRUCTION_H_
#define PARSING_INSTRUCTION_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>

#include "Parser.h"
#include "definitions.h"

using namespace std;



class Instruction {
protected:

	string instuction;

	string name;
	string condition;
	bool psw_change;   // 1 bit for psw change flag

	Elf32_Word op_code;

public:
	Instruction();
	//Instruction& operator=(const Instruction&);
	Instruction(string& s);
	Instruction(string instruction,string name, string condition, bool psw_change,
			Elf32_Word op_code = UNDEF_INSTRUCTION);
	virtual ~Instruction();

	Elf32_Word getOpCode() {
		return op_code;
	}
	void setOpCode(Elf32_Word op_code) {
		this->op_code = op_code;
	}

	virtual void first_pass() {
	}
	virtual void second_pass(){

	}
//Change~!
	static void parse_line(string line);

	virtual Elf32_Word read_instruction(){
		return 0;
	}
	//static int read_register(string &s);
	//static int read_immed(string &s);
	//



};

#endif /* PARSING_INSTRUCTION_H_ */
