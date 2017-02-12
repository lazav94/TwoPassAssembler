/*
 * INTinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "INTinstruction.h"

INT_instruction::INT_instruction(int src) {
	this->src = src;

}

INT_instruction::INT_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int src) :
		Instruction(instruction, name, condition, psw_change, op_code) {

	this->src = src;

}

INT_instruction::~INT_instruction() {

}

// memonic + one argument!
Elf32_Word INT_instruction::read_instruction() {
	vector<string> words;
	Format::get_words(instuction, words);

	try {

		int arg_pos = -1;
		for (unsigned int i = 0; i < words.size(); i++)
			if(Parser::is_memonic(words[i])){
				arg_pos = i;
				break;
			}
		if (arg_pos == -1)
			throw INSTRUCTION_NOT_FOUND;
		unsigned int arg_int = arg_pos + 1;

		if (words[arg_int] != "") {
			arg_int = stoi(words[arg_int]);
			if (arg_int > 15 || arg_int < 0)
				throw OUT_OF_BOUNDS;
			this->op_code |= arg_int << 20;

			return this->op_code;

		} else
			throw ARGUMENT_NOT_FOUND;

	} catch (int id) {
		cout << "Exception INT msg: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "INT " << exception_msgs[UNKNOWN_EXCEPTION]
				<< " Check INT instruction!" << endl;
	}
	return 0;

}
