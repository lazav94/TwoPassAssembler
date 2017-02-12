/*
 * Instruction.cpp
 *
 *  Created on: Aug 9, 2016
 *      Author: laza
 */

#include "Instruction.h"




Instruction::Instruction() {
	this->op_code = START_INSTRUCTION;
	this->psw_change = false;
}

Instruction::Instruction(string& s) {
	this->op_code = START_INSTRUCTION;

	this->instuction = s;

	this->psw_change = Parser::have_psw_change(s);

	this->condition = Parser::get_condition(s);
	this->name = Parser::get_memonic_from_instruction(s);

}
Instruction::Instruction(string instruction,string name, string condition, bool psw_change,
		Elf32_Word op_code) {
	this->instuction = instruction;
	this->name = name;
	this->condition = condition;
	this->psw_change = psw_change;
	this->op_code = op_code;

}

Instruction::~Instruction() {

}



void Instruction::parse_line(string line) {
	vector<string> words;
	Format::get_words(line, words);

	Instruction instruction;

	for (unsigned int i = 0; i < words.size(); i++) {
		if (Parser::is_label(words[i])) {

		} else if (Parser::is_memonic(words[i])) {

			Parser::parse_memonic(words[i]);
			//Instiction = make_instruction(words[i])
			//instruction = read_instruction(line)

		} else {

		}
	}
}





