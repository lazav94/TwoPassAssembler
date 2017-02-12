/*
 * LDChlinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "LDChlinstruction.h"

LDChl_instruction::LDChl_instruction(int dst, int c, bool flag_h,
		bool flag_ldc) {
	this->dst = dst;
	this->c = c;
	this->flag_h = flag_h;
	this->flag_ldc = flag_ldc;

}

LDChl_instruction::LDChl_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int dst, int c,
		bool flag_h, bool flag_ldc) :
		Instruction(instruction, name, condition, psw_change, op_code) {

	this->dst = dst;
	this->c = c;
	this->flag_h = flag_h;
	this->flag_ldc = flag_ldc;

}

LDChl_instruction::~LDChl_instruction() {

}

Elf32_Word LDChl_instruction::read_instruction() {
	vector<string> words;
	Format::get_words(instuction, words);
	int shift_reg_op_code = 20;

//dst:4,h/l:1, nu:3,c:16
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
		unsigned int arg_c = arg_pos + 2;

		if (words.size() - arg_pos > arg_c + 1 - arg_pos)
			throw EXCESS_ARGUMENTS;

		if (Instruction_Parser::is_register(words[arg_dst])) {

			this->dst = Instruction_Parser::read_register(words[arg_dst]);
			this->op_code |= this->dst << shift_reg_op_code;
			shift_reg_op_code--;
		} else
			throw NOT_REG;

		if (Instruction_Parser::st->search_table(words[arg_c])) {
			Elf_Symbol * symbol = Instruction_Parser::st->get_symbol(
					words[arg_c]);
			//	if (symbol->section!= Instruction_Parser::curr_symbol_section->section)throw NOT_SAME_SECTION;
			unsigned int offset = Instruction_Parser::lc + 2;
			unsigned short type;

			if (name == "ldch")
				type = R_386_H16;
			else
				type = R_386_L16;


			unsigned int id_sym =
					symbol->is_global ?
							symbol->id :
							Instruction_Parser::st->get_symbol(symbol->sec_name)->id;
			Relocation_Entry *r = new Relocation_Entry(offset, type, id_sym, 0);
			Instruction_Parser::rt->insert_reloction(r);

			if (symbol->is_global == true)
				this->c = 0;
			else
				this->c = symbol->value;

			int mask = 0;

			if (this->flag_ldc == true) {
				if (name == "ldch") {
					mask = 0xFFFF0000;
					this->c = (this->c & mask) >> 16;
					this->c = this->c & MASK_16B;
					this->op_code |= 1 << 19;
					this->op_code |= this->c;
				} else if (name == "ldcl") {
					mask = MASK_16B;
					this->c = this->c & mask;
					this->op_code |= this->c;
				}
			} else {
				this->op_code |= this->c & MASK_16B;
			}

		} else if (Instruction_Parser::is_immed(words[arg_c])) {
			this->c = Instruction_Parser::read_immed(words[arg_c]);
			int mask = 0;

			if (this->flag_ldc == true) {
				if (name == "ldch") {
					mask = 0xFFFF0000;
					this->c = (this->c & mask) >> 16;
					this->c = this->c & MASK_16B;
					this->op_code |= 1 << 19;
					this->op_code |= this->c;
				} else if (name == "ldcl") {
					mask = MASK_16B;
					this->c = this->c & mask;
					this->op_code |= this->c;
				}
			} else {
				this->op_code |= this->c & MASK_16B;
			}

		} else
			throw ARGUMENT_INVALID;

		if (name == "ldch")
			this->op_code |= 1 << 19;

		return this->op_code;
	} catch (int id) {
		cout << "Exception LDCH/L msg: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "LDCH/L" << exception_msgs[UNKNOWN_EXCEPTION]
				<< " Check LDCH/L instruction!" << endl;
	}
	return 0;

}

