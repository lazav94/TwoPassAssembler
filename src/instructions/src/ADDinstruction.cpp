/*
 * ADDinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "ADDinstruction.h"

ADD_instruction::ADD_instruction(int src, int dst, int imm, bool flag) {
	this->src = src;
	this->dst = dst;
	this->imm = imm;
	this->flag = flag;

}

ADD_instruction::ADD_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int src, int dst,
		int imm, bool flag) :
		Instruction(instruction, name, condition, psw_change, op_code) {

	this->src = src;
	this->dst = dst;
	this->imm = imm;
	this->flag = flag;

}

ADD_instruction::~ADD_instruction() {

}

Elf32_Word ADD_instruction::read_instruction() {
	vector<string> words;
	Format::get_words(instuction, words);
	int shift_reg_op_code = 19;

	try {
		int arg_pos = -1;
		for (unsigned int i = 0; i < words.size(); i++)
			if (Parser::is_memonic(words[i])) {
				arg_pos = i;
				break;
			}

		if (arg_pos == -1)
			throw INSTRUCTION_NOT_FOUND;

		unsigned int arg_dst = arg_pos + 1;
		unsigned int arg_src_imm = arg_pos + 2;

		if (words.size() - arg_pos != arg_src_imm + 1 - arg_pos )
			throw EXCESS_ARGUMENTS;

		if (Instruction_Parser::is_register(words[arg_dst])) {
			this->dst = Instruction_Parser::read_register(words[arg_dst]);
			if (this->dst == PSW)
				throw PSW_NOT_ALLOWED;
			this->op_code |= this->dst << shift_reg_op_code;
			shift_reg_op_code--;
		} else
			throw NOT_REG;

		if (Instruction_Parser::is_immed(words[arg_src_imm])) {
			this->flag = true;
			this->op_code |= 1 << shift_reg_op_code;
			this->imm = Instruction_Parser::read_immed(words[arg_src_imm]);
			if (this->imm > 131071 || this->imm < -131072)
				throw OUT_RANGE_IMMED;
			else {
				this->imm &= MASK_18B;
				this->op_code |= this->imm;

			}
		}

		else if (Instruction_Parser::is_register(words[arg_src_imm])) {
			this->src = Instruction_Parser::read_register(words[arg_src_imm]);
			if (this->src == PSW)
				throw PSW_NOT_ALLOWED;
			shift_reg_op_code -= 5;
			this->op_code |= this->src << shift_reg_op_code;

		} else
			throw ARGUMENT_NOT_FOUND;

		return op_code;
	} catch (int id) {
		cout << "Exception ADD msg: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "ADD " << exception_msgs[UNKNOWN_EXCEPTION]
				<< " Check ADD instruction!" << endl;
	}

	return 0;
}
