/*
 * LDRinstruction.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "LDRinstruction.h"

LDR_instruction::LDR_instruction(int a, int r, int f, int imm, bool flag_ldr) {
	this->a = a;
	this->r = r;
	this->f = f;
	this->imm = imm;
	this->flag_ldr = flag_ldr;

}

LDR_instruction::LDR_instruction(string instruction, string name,
		string condition, bool psw_change, Elf32_Word op_code, int a, int r,
		int f, int imm, bool flag_ldr) :
		Instruction(instruction, name, condition, psw_change, op_code) {

	this->a = a;
	this->r = r;
	this->f = f;
	this->imm = imm;
	this->flag_ldr = flag_ldr;

}

LDR_instruction::~LDR_instruction() {

}

Elf32_Word LDR_instruction::read_instruction() {
	vector<string> words;
	Format::get_words(instuction, words);
	unsigned int shift_reg_op_code = 19;

	try {
		int arg_pos = -1;

		for (unsigned int i = 0; i < words.size(); i++)
			if (Parser::is_memonic(words[i])) {
				arg_pos = i;
				break;
			}
		if (arg_pos == -1)
			throw INSTRUCTION_NOT_FOUND;

		unsigned int arg_a = arg_pos + 1;
		unsigned int arg_r = arg_pos + 2;
		unsigned int arg_imm = arg_pos + 3;

		if (words.size() - arg_pos > arg_imm + 1 - arg_pos)
			throw EXCESS_ARGUMENTS;

		this->f = Instruction_Parser::getPrePostIncDec(words[arg_a]);
		if (Instruction_Parser::is_register(words[arg_a])) {
			this->a = Instruction_Parser::read_register(words[arg_a]);
			if (this->a == PSW)
				throw PSW_NOT_ALLOWED;
			else
				this->op_code |= this->a << shift_reg_op_code;
			if (this->a == PC) //read comment.txt 5.
				this->f = ADDRESS_PC;

		} else
			throw NOT_REG;

		if (Instruction_Parser::st->search_table(words[arg_r])) {
			shift_reg_op_code -= 5;
			this->r = PC; // LDR with label use PC register
			this->op_code |= this->r << shift_reg_op_code;
			this->f = ADDRESS_PC;		// used pc register no prefix postfix!

			Elf_Symbol * symbol = Instruction_Parser::st->get_symbol(
					words[arg_r]);
			//if (symbol->section!= Instruction_Parser::curr_symbol_section->section)throw NOT_SAME_SECTION;
			unsigned int offset = Instruction_Parser::lc + 2; //vrednost tekuce instrukcije - vrednost labele - 2
			unsigned short type = R_386_32;

			unsigned int id_sym =
					symbol->is_global ?
							symbol->id :
							Instruction_Parser::st->get_symbol(symbol->sec_name)->id;

			Relocation_Entry *r = new Relocation_Entry(offset, type, id_sym , 6);
			Instruction_Parser::rt->insert_reloction(r);

			if (symbol->is_global == true)
				this->imm = 0;
			else
				this->imm = symbol->value;

			if (this->imm > 511 || this->imm < -512)
				throw OUT_RANGE_IMMED;
			else {
				shift_reg_op_code -= 4;
				this->op_code |= 1 << shift_reg_op_code; //LDR
				this->imm &= MASK_10B; // bound symbol!
				this->op_code |= this->imm;

				return this->op_code;

			}

		} else if (Instruction_Parser::is_register(words[arg_r])) {
			this->r = Instruction_Parser::read_register(words[arg_r]);
			shift_reg_op_code -= 5;
			this->op_code |= this->r << shift_reg_op_code;
			shift_reg_op_code -= 3;
			this->op_code |= this->f << shift_reg_op_code;
		} else
			throw NOT_REG;
		shift_reg_op_code--;
		this->op_code |= 1 << shift_reg_op_code; //LDR

		if (words.size() - 1 == arg_imm) {
			if (Instruction_Parser::is_immed(words[arg_imm])) {

				this->imm = Instruction_Parser::read_immed(words[arg_imm]);
				if (this->imm > 511 || this->imm < -512)
					throw OUT_RANGE_IMMED;
				else {
					this->imm &= MASK_10B;
					this->op_code |= this->imm;

				}
			} else
				throw NOT_IMMED;
		}

		return this->op_code;
	} catch (int id) {
		cout << "Exception LDR msg: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "LDR " << exception_msgs[UNKNOWN_EXCEPTION]
				<< " Check LDR instruction!" << endl;
	}
	return 0;

}
