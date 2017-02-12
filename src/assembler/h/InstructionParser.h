/*
 * InstructionParser.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef INSTRUCTIONPARSER_H_
#define INSTRUCTIONPARSER_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include "Parser.h"
#include "SymbolTable.h"
#include "RelocationTable.h"

#include "INTinstruction.h"
#include "ADDinstruction.h"
#include "SUBinstruction.h"
#include "MULinstruction.h"
#include "DIVinstruction.h"
#include "CMPinstruction.h"
#include "ANDinstruction.h"
#include "ORinstruction.h"
#include "NOTinstruction.h"
#include "TESTinstruction.h"
#include "LDRinstruction.h"
#include "STRinstruction.h"
#include "CALLinstruction.h"
#include "INinstruction.h"
#include "OUTinstruction.h"
#include "MOVinstruction.h"
#include "SHLinstruction.h"
#include "SHRinstruction.h"
#include "LDChlinstruction.h"

#include "definitions.h"

using namespace std;

class Instruction_Parser {
private:
	Instruction_Parser();
	~Instruction_Parser();

public:

	static bool is_expression(string &s);
	static int get_expression_value(vector<string> &op);

	static SymbolTable *st;
	static unsigned int lc; //location counter
	static unsigned int id; //id of symbol
	static Elf_Symbol *curr_symbol_section;
	static Relocation_Table *rt;
	static map<string, Relocation_Table*> rel_map;
	static bool not_first_section;
	static unsigned ID_d ;

	static map<string, string> binary_map;
	static unsigned int byte_counter;

	static Instruction* make_instruction(string &line, string memonic);
	static bool is_register(string &reg);
	static unsigned short getPrePostIncDec(string &s);

	static int read_register(string &reg);

	static bool is_immed(string &imm);
	static int read_immed(string &imm);

	static void first_pass(string &line);
	static void print();

	static void first_pass_label(string &label);
	static void first_pass_section(string &section);
	static void first_pass_directive(string &line, string &directive);
	static void first_pass_memonic( string &memonic);

	static int get_size_directive(string& directive,
			vector<string> &words_comma, string second_directive = "");

	static void second_pass(string &line);
	static void second_pass_label(string &label);
	static void second_pass_section(string &section);
	static void second_pass_directive(string &line, string &directive);
	static void second_pass_memonic(string &line,string &memonic);

	static Elf32_Word change_to_lil_endianness(Elf32_Word value, unsigned int size);
	static void insert_binary(Elf32_Word word, unsigned int size);
	static void write_byte_codes(ostream &os);
	static void write_rel(ostream &os);
	static void write_file(ostream &os);

};

#endif /* INSTRUCTIONPARSER_H_ */
