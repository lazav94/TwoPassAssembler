/*
 * INinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "INinstruction.h"

IN_instruction::IN_instruction(int src, int dst, bool flag) {
	this->src = src;
	this->dst = dst;
	this->flag = flag;

}

IN_instruction::IN_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int src, int dst,
		bool flag) :
		Instruction(instruction, name, condition, psw_change, op_code) {

	this->src = src;
	this->dst = dst;
	this->flag = flag;

}

IN_instruction::~IN_instruction() {

}

Elf32_Word IN_instruction::read_instruction() {
	vector<string> words;
	Format::get_words(instuction, words);
	int shift_reg_op_code = 20;

	try {
		int arg_pos = -1;

		for (unsigned int i = 0; i < words.size(); i++)
			if (Parser::is_memonic(words[i])) {
				arg_pos = i;
				break;
			}
		if (arg_pos == -1)
			throw INSTRUCTION_NOT_FOUND;

		int arg_dst = arg_pos + 1;
		int arg_src = arg_pos + 2;

		if (Instruction_Parser::is_register(words[arg_dst])) {
			this->dst = Instruction_Parser::read_register(words[arg_dst]);
			if (this->dst > 15)
				throw NOT_ALLOWED_REG;
			this->op_code |= this->dst << shift_reg_op_code;
		} else
			throw NOT_REG;

		if (Instruction_Parser::is_register(words[arg_src])) {
			this->src = Instruction_Parser::read_register(words[arg_src]);
			if (this->src > 15)
				throw NOT_ALLOWED_REG;
			shift_reg_op_code -= 4;
			this->op_code |= this->src << shift_reg_op_code;
		} else
			throw NOT_REG;

		this->op_code |= 1 << 15;
		return this->op_code;

	} catch (int id) {
		cout << "Exception IN msg: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "IN " << exception_msgs[UNKNOWN_EXCEPTION]
				<< " Check IN instruction!" << endl;
	}
	return 0;

}

