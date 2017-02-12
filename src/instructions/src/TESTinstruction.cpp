/*
 * TESTinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "TESTinstruction.h"

TEST_instruction::TEST_instruction(int src, int dst) {
	this->src = src;
	this->dst = dst;

}

TEST_instruction::TEST_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int src, int dst) :
		Instruction(instruction, name, condition, psw_change, op_code) {
	this->src = src;
	this->dst = dst;

}

TEST_instruction::~TEST_instruction() {

}

Elf32_Word TEST_instruction::read_instruction() {
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

			if (words.size() - arg_pos != arg_src + 1 - arg_pos)
								throw EXCESS_ARGUMENTS;

			if (Instruction_Parser::is_register(words[arg_dst])) {
				this->dst = Instruction_Parser::read_register(words[arg_dst]);
				if(this->dst == PC || this->dst == LR || this->dst == PSW)
					throw NOT_ALLOWED_REG;
				this->op_code |= this->dst << shift_reg_op_code;
			} else
				throw NOT_REG;


			if (Instruction_Parser::is_register(words[arg_src])) {
				this->src = Instruction_Parser::read_register(words[arg_src]);
				if(this->src == PC || this->src == LR || this->src == PSW)
								throw NOT_ALLOWED_REG;
				shift_reg_op_code -= 5;
				this->op_code |= this->src << shift_reg_op_code;
			} else
				throw NOT_REG;


			return op_code;
		} catch (int id) {
			cout << "Exception TEST msg: " << exception_msgs[id] << endl;
		} catch (...) {
			cout << "TEST " << exception_msgs[UNKNOWN_EXCEPTION]
					<< " Check TEST instruction!" << endl;
		}
		return 0;

}
