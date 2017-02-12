/*
 * SHRinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "SHRinstruction.h"

SHR_instruction::SHR_instruction(int src, int dst, int imm, bool flag_l) {
	this->src = src;
	this->dst = dst;
	this->imm = imm;
	this->flag_l = flag_l;

}

SHR_instruction::SHR_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int src, int dst,
		int imm, bool flag_l) :
		Instruction(instruction, name, condition, psw_change, op_code) {

	this->src = src;
	this->dst = dst;
	this->imm = imm;
	this->flag_l = flag_l;

}

SHR_instruction::~SHR_instruction() {

}

Elf32_Word SHR_instruction::read_instruction() {
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
		unsigned int arg_src = arg_pos + 2;
		unsigned int shift = arg_pos + 3;
		unsigned int arg_imm = arg_pos + 4;

		if (words.size() - arg_pos != arg_imm + 1 - arg_pos)
			throw EXCESS_ARGUMENTS;

		if (Instruction_Parser::is_register(words[arg_dst])) {
			this->dst = Instruction_Parser::read_register(words[arg_dst]);
			this->op_code |= this->dst << shift_reg_op_code;
		} else
			throw NOT_REG;
		if (Instruction_Parser::is_register(words[arg_src])) {
			this->src = Instruction_Parser::read_register(words[arg_src]);
			shift_reg_op_code -= 5;
			this->op_code |= this->src << shift_reg_op_code;
		} else
			throw NOT_REG;

		if (Instruction_Parser::is_immed(words[arg_imm])) {
			this->flag_l = true;
			this->imm = Instruction_Parser::read_immed(words[arg_imm]);
			if (this->imm > 131071 || this->imm < -131072)
				throw OUT_RANGE_IMMED;
			else {
				this->imm &= MASK_05B;
				shift_reg_op_code -= 5;
				this->op_code |= this->imm << shift_reg_op_code;

			}
		} else
			throw NOT_IMMED;

		if (words[shift] != ">>")
			throw SHIFT_NOT_FOUND;

		return this->op_code;;
	} catch (int id) {
		cout << "Exception SHR msg: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "SHR " << exception_msgs[UNKNOWN_EXCEPTION]
				<< " Check SHR instruction!" << endl;
	}
	return 0;
}
