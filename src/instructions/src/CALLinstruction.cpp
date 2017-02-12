/*
 * CALLinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "CALLinstruction.h"

CALL_instruction::CALL_instruction(int dst, int imm) {

	this->dst = dst;
	this->imm = imm;

}

CALL_instruction::CALL_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int dst, int imm) :
		Instruction(instruction, name, condition, psw_change, op_code) {

	this->dst = dst;
	this->imm = imm;
}

CALL_instruction::~CALL_instruction() {

}

Elf32_Word CALL_instruction::read_instruction() {
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
		unsigned int arg_imm = arg_pos + 2;

		if (words.size() - arg_pos > arg_imm + 1 - arg_pos)
			throw EXCESS_ARGUMENTS;

		if (Instruction_Parser::st->search_table(words[arg_dst])) {
			if (words.size() - arg_pos > arg_dst + 1 - arg_pos)
				throw EXCESS_ARGUMENTS;
			this->dst = PC; // call with label use PC register
			this->op_code |= this->dst << shift_reg_op_code;
			Elf_Symbol * symbol = Instruction_Parser::st->get_symbol(
					words[arg_dst]);
			//if (symbol->section!= Instruction_Parser::curr_symbol_section->section)throw NOT_SAME_SECTION;
			unsigned int offset = Instruction_Parser::lc + 1;
			unsigned short type = R_386_PC32;
			unsigned int id_sym =
					symbol->is_global ?
							symbol->id :
							Instruction_Parser::st->get_symbol(symbol->sec_name)->id;

			Relocation_Entry *r = new Relocation_Entry(offset, type, id_sym, 5);
			Instruction_Parser::rt->insert_reloction(r);

			if (symbol->is_global == true) {
//				 labela->value - adresa sledece instrkcije
//				 labela->value - (lc + 4) (adresa ciji sadrzaj menjamo + pomeraj)
//				 lc + 4 = adresa ciji sadrzaj menjamo + pomeraj
//				 lc + 4 = OFFSET + pomeraj
//				 lc + 4 = lc + 1 + pomeraj
//				 pomeraj = -3;

				// + 5b >>
				this->imm = -3;
			} else {

//                label->value - pomeraj
				// + 5b >>
				this->imm = symbol->value - 3;
			}

			if (this->imm > 262143 || this->imm < -262144)
				throw OUT_RANGE_IMMED;
			else {
				this->imm &= MASK_19B; // bound symbol!
				this->op_code |= this->imm;
				return this->op_code;
			}

		} else {
			if (Instruction_Parser::is_register(words[arg_dst])) {
				this->dst = Instruction_Parser::read_register(words[arg_dst]);
				this->op_code |= this->dst << shift_reg_op_code;
			} else
				throw NOT_REG;

			if (words.size() > arg_imm) {
				if (Instruction_Parser::is_immed(words[arg_imm])) {
					this->imm = Instruction_Parser::read_immed(words[arg_imm]);
					if (this->imm > 262143 || this->imm < -262144)
						throw OUT_RANGE_IMMED;
					else {
						this->imm &= MASK_19B;
						this->op_code |= this->imm;
					}
				} else
					throw NOT_IMMED;
			}
		}
		return this->op_code;
	} catch (int id) {
		cout << "Exception CALL msg: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "CALL " << exception_msgs[UNKNOWN_EXCEPTION]
				<< " Check CALL instruction!" << endl;
	}
	return 0;

}

