/*
 * InstructionParser.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "InstructionParser.h"

SymbolTable *Instruction_Parser::st = new SymbolTable();
unsigned int Instruction_Parser::lc = 0; //location counter
unsigned int Instruction_Parser::id = 0; //id of symbol
Elf_Symbol *Instruction_Parser::curr_symbol_section;
Relocation_Table *Instruction_Parser::rt;
bool Instruction_Parser::not_first_section = false;
map<string, Relocation_Table*> Instruction_Parser::rel_map;
map<string, string> Instruction_Parser::binary_map;

unsigned int Instruction_Parser::byte_counter = 0;
unsigned int Instruction_Parser::ID_d = 0;

Instruction_Parser::Instruction_Parser() {

}
Instruction_Parser::~Instruction_Parser() {

}

Elf32_Word Instruction_Parser::change_to_lil_endianness(Elf32_Word value,
		unsigned int size) {
	Elf32_Word result = 0;

	switch (size) {
	case LILENDIAN_2_2:  // for .word
		result |= (value & 0x00FF) << 8;
		result |= (value & 0xFF00) >> 8;
		break;
	case LILENDIAN_3_4: // for instruction
		result |= (value & 0x000000FF) << 16;
		result |= (value & 0x0000FF00);
		result |= (value & 0x00FF0000) >> 16;
		result |= (value & 0xFF000000);

		break;
	case LILENDIAN_4_4:  // for .long
		result |= (value & 0x000000FF) << 24;
		result |= (value & 0x0000FF00) << 8;
		result |= (value & 0x00FF0000) >> 8;
		result |= (value & 0xFF000000) >> 24;
		break;
	default:
		break;
	}
	return result;
}
void Instruction_Parser::insert_binary(Elf32_Word word, unsigned int size) {

	int mask = 0xFF000000 >> (8 * (4 - size)); // 4 - 2 + 2
	unsigned int a = 0x00;
	stringstream stream;
	for (unsigned int i = 0; i < size; i++, mask >>= 8) {
		if (Instruction_Parser::byte_counter == 20) {
			stream << VERTICAL << endl << VERTICAL;
			Instruction_Parser::byte_counter = 0;
		}
		a = (word & mask) >> ((size - i - 1) * 8);
		a &= 0x000000FF;
		if (a == 0 || a < 16)
			stream << "0";

		stream << hex << a;
		stream << " ";
		Instruction_Parser::byte_counter++;

	}

	Instruction_Parser::binary_map[curr_symbol_section->name] += (stream.str());
}

bool Instruction_Parser::is_register(string &reg) {
	if (reg == "pc" || reg == "lr" || reg == "sp" || reg == "psw"
			|| reg[0] == 'r')
		return true;
	return false;
}
bool Instruction_Parser::is_immed(string &imm) {
	if (imm[0] == IMMED_SIGN)
		return true;
	return false;
}
int Instruction_Parser::read_immed(string &imm) {
	string str = imm.substr(1, imm.size());
	return stoi(str);
}

int Instruction_Parser::read_register(string &reg) {
	int reg_int;

	if (Instruction_Parser::is_register(reg)) {
		if (reg[0] == REGISTER_SIGN) {
			string str = reg.substr(1, reg.size());
			reg_int = stoi(str);
			if (reg_int > 15) {
				cout << "Error invalid nubmer for register!" << endl;
				return -1;
			} else
				return reg_int;
		} else {
			if (reg == "pc")
				return PC;
			else if (reg == "sp")
				return SP;
			else if (reg == "lr")
				return LR;
			else if (reg == "psw")
				return PSW;
			else {
				cout << "Error name of regiser!" << endl;
				return -1;
			}
		}
	} else {
		cout << "ERROR: this instuction must have registrer!" << endl;
		return -1;
	}
}

unsigned short Instruction_Parser::getPrePostIncDec(string &reg) {
	size_t pos_inc = reg.find(INCREMENT);
	size_t pos_dec = reg.find(DECREMENT);

	if (pos_inc != string::npos) {
		if (reg[0] == '+') {
			reg = reg.erase(pos_inc, pos_inc + 2);
			return INCREMENT_BEFORE;
		} else {
			reg = reg.erase(pos_inc, pos_inc + 2);
			return INCREMENT_AFTER;
		}
	} else if (pos_dec != string::npos) {
		if (reg[0] == '-') {
			reg = reg.erase(pos_dec, pos_dec + 2);
			return DECREMENT_BEFORE;
		} else {
			reg = reg.erase(pos_dec, pos_dec + 2);
			return DECREMENT_AFTER;
		}
	} else {
		return NO_INC_DEC;
	}

}

void Instruction_Parser::first_pass_label(string &label) {
	string label_name = label.substr(0, label.size() - 1);
	if (st->search_table(label_name) == false) {
		Elf_Symbol *e = new Elf_Symbol(label_name, lc, 0, LOCAL,
				curr_symbol_section->section, ++ID_d,
				curr_symbol_section->sec_name);
		st->insert_symbol(e);
	} else {
		st->change_value(label_name, lc);
		st->change_section(label_name, curr_symbol_section->section,
				curr_symbol_section->sec_name);
	}
}

void Instruction_Parser::first_pass_section(string &section) {
	try {
		string section_name = Parser::get_section_name(section);
		if (st->search_table(section_name) == false) {
			if (not_first_section == false)
				not_first_section = true;
			else
				st->chagne_size(curr_symbol_section->name, lc);

			if (Parser::get_section(section) == END)
				return;

			Elf_Symbol *e = new Elf_Symbol(section_name, 0, 0, LOCAL,
					Parser::get_section(section), ++id, section_name);
			st->insert_symbol(e);
			curr_symbol_section = e;
			lc = 0;
		} else
			throw MULTIPLE_SECTION;
	} catch (int id) {
		cout << "Exception first pass section: " << exception_msgs[id] << endl;
	} catch (...) {
		cout << "Exception first pass section!" << endl;
	}
}

bool Instruction_Parser::is_expression(string &s) {
	vector<string> words;
	Format::get_words(s, words);

	int arg_pos = -1;
	for (unsigned int i = 0; i < words.size(); i++)
		if (words[i] == LONG) {
			arg_pos = i;
			break;
		}

	if (arg_pos == -1)
		return false;

	if (s.find(PLUS) == string::npos && s.find(MINUS) == string::npos)
		return false;

	if (words.size() - arg_pos - 1 != 3)
		throw ARGUMENT_INVALID;

	bool condition = ((Instruction_Parser::st->search_table(words[arg_pos + 1])
			== false)
			|| ((words[arg_pos + 1].find_first_not_of("0123456789")
					== string::npos) == false))
			&& ((Instruction_Parser::st->search_table(words[arg_pos + 3])
					== false)
					|| ((words[arg_pos + 3].find_first_not_of("0123456789")
							== string::npos) == false));

	if (words[arg_pos + 2] != PLUS && words[arg_pos + 2] != MINUS)
		return false;
	return condition;
}

int Instruction_Parser::get_expression_value(vector<string> &op) {

	bool first_op = Instruction_Parser::st->search_table(op[0]), second_op =
			Instruction_Parser::st->search_table(op[2]);
	int val1 = 0, val2 = 0;
	//ako imamo 2 vrednosti moraju biti iz iste sekcije!

	if (first_op == true && second_op == true)
		if (Instruction_Parser::st->get_symbol(op[0])->sec_name
				!= Instruction_Parser::st->get_symbol(op[2])->sec_name)
			throw NOT_SAME_SECTION;

	if (first_op)
		val1 = Instruction_Parser::st->get_symbol(op[0])->value;
	else
		val1 = stoi(op[0]);
	if (second_op)
		val2 = Instruction_Parser::st->get_symbol(op[2])->value;
	else
		val2 = stoi(op[2]);
	if (op[1] == PLUS) {

		if (first_op == true) {
			int id_long;
			if (Instruction_Parser::st->get_symbol(op[0])->is_global == true)
				id_long = Instruction_Parser::st->get_symbol(op[0])->id;
			else {
				string sec = Instruction_Parser::st->get_symbol(op[0])->sec_name;
				id_long = Instruction_Parser::st->get_symbol(sec)->id;
			}

			Relocation_Entry *r1 = new Relocation_Entry(lc, R_386_LONG32,
					id_long);
			rt->insert_reloction(r1);
		}
		if (second_op == true) {
			int id_long;
			if (Instruction_Parser::st->get_symbol(op[2])->is_global == true)
				id_long = Instruction_Parser::st->get_symbol(op[0])->id;
			else {
				string sec = Instruction_Parser::st->get_symbol(op[2])->sec_name;
				id_long = Instruction_Parser::st->get_symbol(sec)->id;
			}
			Relocation_Entry *r2 = new Relocation_Entry(lc + 1, R_386_LONG32,
					id_long);
			rt->insert_reloction(r2);
		}

		return val1 + val2;

	} else if (op[1] == MINUS)
		return val1 - val2;
	else
		cout << "get expression value error!" << endl;
	return 0;
}

int Instruction_Parser::get_size_directive(string& directive,
		vector<string> &words_comma, string second_directive) {

	if (directive == CHAR) {
		int num_of_character = 0;
		for (unsigned int i = 0; i < words_comma.size(); i++)
			num_of_character += words_comma[i].size();
		return num_of_character * CHAR_SIZE;
	} else if (directive == WORD)
		return words_comma.size() * WORD_SIZE;
	else if (directive == BYTE)
		return words_comma.size() * BYTE_SIZE;
	else if (directive == LONG)
		return words_comma.size() * LONG_SIZE;
	else if (directive == SKIP) {
		int ret_val = 0;
		if (Parser::is_directive(second_directive)) {
			vector<string> words_temp(words_comma.begin() + 1,
					words_comma.end());
			ret_val = get_size_directive(second_directive, words_temp);
		} else
			ret_val = stoi(words_comma[0]);
		return ret_val;
	} else
		return 0;
}

void Instruction_Parser::first_pass_directive(string &line, string &directive) {
	vector<string> words_comma, words;
	Elf_Symbol* e;
	Format::get_words(line, words);
	string comma_line = "";
	string second_directive = "";
	bool first_directive = false;

	for (unsigned i = 0; i < words.size(); i++) {
		if (Parser::is_directive(words[i]) == false
				&& Parser::is_label(words[i]) == false)
			comma_line += words[i];
		else {
			if (first_directive == false)
				first_directive = true;
			else if (words[i] != SKIP)
				second_directive = words[i];
		}
	}

	Format::get_words_delimiter(comma_line, words_comma, COMMA);

	if (directive == PUBLIC) {
		for (unsigned j = 0; j < words_comma.size(); j++) {
			e = new Elf_Symbol(words_comma[j], 0, 0, GLOBAL, UND, ++ID_d, UND);
			st->insert_symbol(e);
		}
	} else if (directive == EXTERN) {
		for (unsigned j = 0; j < words_comma.size(); j++) {
			e = new Elf_Symbol(words_comma[j], 0, 0, GLOBAL, UND, ++ID_d, UND);
			st->insert_symbol(e);
		}

	} else if (directive == ALIGN) {

		unsigned int align_arg = 4;
		if (words[1].size() == 1)
			align_arg = stoi(words[1]);
		lc += lc % align_arg ? align_arg - (lc % align_arg) : 0;

	} else
		lc += get_size_directive(directive, words_comma, second_directive);

}

void Instruction_Parser::first_pass_memonic(string &memonic) {
	lc += INSTRUCTION_SIZE;
	string name = Parser::get_memonic_from_instruction(memonic);
	if (name == "ldc")
		lc += INSTRUCTION_SIZE;
}
void Instruction_Parser::first_pass(string &line) {
	vector<string> words;
	Format::get_words(line, words);
	Elf_Symbol *und = new Elf_Symbol(UND, 0, 0, LOCAL, UND, 0, UND);
	st->insert_symbol(und);
	for (unsigned int i = 0; i < words.size(); i++) {
		if (Parser::is_label(words[i])) {
			first_pass_label(words[i]);
		} else if (Parser::is_section(words[i])) {
			if (i == 0)
				first_pass_section(words[i]);
		} else if (Parser::is_directive(words[i])) {
			first_pass_directive(line, words[i]);
		} else if (Parser::is_memonic(words[i])) {
			first_pass_memonic(words[i]);
		}
	}

}

void Instruction_Parser::second_pass_label(string &label) {

}
void Instruction_Parser::second_pass_section(string &section) {

	try {
		if (Parser::get_section(section) == END)
			return;

		string section_name = Parser::get_section_name(section);
		if (st->search_table(section_name) == true) {

			rt = new Relocation_Table(section);
			rel_map[section_name] = rt;

			curr_symbol_section = st->get_symbol(section_name);
			Instruction_Parser::byte_counter = 0;
			lc = 0;
		} else
			throw SECOND_PASS_SECTION;
	} catch (...) {
		cout << "Exception second pass section!" << endl;
	}
}
void Instruction_Parser::second_pass_directive(string &line,
		string &directive) {
	vector<string> words_comma, words;
	Format::get_words(line, words);
	string comma_line = "";
	string second_directive = "";
	bool first_directive = false;

	for (unsigned i = 0; i < words.size(); i++) {
		if (Parser::is_directive(words[i]) == false
				&& Parser::is_label(words[i]) == false)
			comma_line += words[i];
		else {
			if (first_directive == false)
				first_directive = true;
			else
				second_directive = words[i];
		}
	}
	Format::get_words_delimiter(comma_line, words_comma, COMMA);
	try {
		int code = 0;
		if (directive == PUBLIC) {
			for (unsigned j = 0; j < words_comma.size(); j++) {
				if (st->get_symbol(words_comma[j])->section == UND) {
					cout << words[j + 1] << "  ";
					throw SYMBOL_NOT_DECLARED;
				}
			}
		} else if (directive == EXTERN) {
			for (unsigned j = 0; j < words_comma.size(); j++) {
				if (st->get_symbol(words_comma[j])->section != UND) {
					cout << words[j + 1] << "  ";
					throw SYMBOL_WAS_DECLARED;
				}
			}
		} else if (directive == ALIGN) {

			unsigned int align_arg = 4;
			if (words[1].size() == 1)
				align_arg = stoi(words[1]);
			int add = lc % align_arg ? align_arg - (lc % align_arg) : 0;
			lc += add;
			if (add != 0)
				insert_binary(0x00000000, add);

		} else if (directive == LONG) {
			int code = 0;
			if (is_expression(line) == true) {
				vector<string> op;
				for (unsigned i = 0; i < words.size(); i++) {
					if (Parser::is_directive(words[i]) == false
							&& Parser::is_memonic(words[i]) == false
							&& Parser::is_section(words[i]) == false)
						//char c = ;
						if (words[i][words[i].size() - 1] != ':')
							op.push_back(words[i]);
				}
				code = get_expression_value(op);
				code = change_to_lil_endianness(code, LILENDIAN_4_4);
				insert_binary(code, 4);
				lc += LONG_SIZE;

			} else {
				for (unsigned i = 0; i < words_comma.size(); i++) {
					if (st->search_table(words_comma[i]) == true) {
						Elf_Symbol * symbol = st->get_symbol(words_comma[i]);
						int id_sym;

						//if (symbol->section!= Instruction_Parser::curr_symbol_section->section)	throw NOT_SAME_SECTION;

						if (symbol->is_global == true) {
							id_sym = symbol->id;
							code = 0;
						} else {

							string s = "." + words_comma[i];
							if (Parser::is_section(s))
								id_sym = st->get_symbol(words_comma[i])->id;

							else { //TODO
								string sec_name =
										Instruction_Parser::st->get_symbol(
												symbol->sec_name)->name;
								id_sym = Instruction_Parser::st->get_symbol(
										sec_name)->id;
							}
							code = change_to_lil_endianness(symbol->value,
							LILENDIAN_4_4);

						}
						Relocation_Entry *r = new Relocation_Entry(lc, R_386_32,
								id_sym);
						rt->insert_reloction(r);

						insert_binary(code, 4);
						lc += LONG_SIZE;

					} else {
						string s = "." + words_comma[i];
						if (Parser::is_section(s)) {
							int id_sym = st->get_symbol(words_comma[i])->id;
							Relocation_Entry *r = new Relocation_Entry(lc,
									R_386_32, id_sym);
							rt->insert_reloction(r);
							code = 0;
						}
						else
							code = stoi(words_comma[i]) & MASK_32B;
						lc += LONG_SIZE;
						code = change_to_lil_endianness(code, LILENDIAN_4_4);
						insert_binary(code, 4);
					}

				}

			}

		} else if (directive == BYTE) {
			for (unsigned i = 0; i < words_comma.size(); i++) {
				code = 0;
				code |= stoi(words_comma[i]) & MASK_07B;
				if (code > 255) {
					cout << "Byte exception: ";
					throw OUT_OF_BOUNDS;
				}
				insert_binary(code, BYTE_SIZE);

			}

		} else if (directive == CHAR) {

			for (unsigned i = 0; i < words_comma.size(); i++) {
				for (unsigned int j = 0; j < words_comma[i].size(); j++) {
					code = 0;
					char character = words_comma[i][j];
					code |= ((int) character & MASK_08B);
					if (code > 255) {
						cout << "Char exception: ";
						throw OUT_OF_BOUNDS;
					}
					insert_binary(code, CHAR_SIZE);

				}
			}

		} else if (directive == WORD) {
			for (unsigned i = 0; i < words_comma.size(); i++) {
				code = 0;
				code |= stoi(words_comma[i]) & MASK_16B;
				if (code >= (1 << 16)) {
					cout << "Word exception: ";
					throw OUT_OF_BOUNDS;
				}
				code = change_to_lil_endianness(code, LILENDIAN_2_2);
				insert_binary(code, WORD_SIZE);
			}

		} else if (directive == SKIP) {
			int skip_byte = Instruction_Parser::get_size_directive(directive,
					words_comma);
			while (skip_byte != 0) {
				int skip = 0;
				if (skip_byte >= 4)
					skip = 4;
				else if (skip_byte == 3)
					skip = 3;
				if (skip_byte == 2)
					skip = 2;
				if (skip_byte == 1)
					skip = 1;

				insert_binary(0, skip);
				skip_byte -= skip;
			}
		}
		if (directive != LONG && directive != EXTERN && directive != PUBLIC)
			lc += Instruction_Parser::get_size_directive(directive,
					words_comma);

	} catch (int id) {
		cout << "Second pass directive exception: " << exception_msgs[id]
				<< endl;
	} catch (...) {
		cout << "Second pass directive exception: "
				<< exception_msgs[UNKNOWN_EXCEPTION] << endl;
	}
}
void Instruction_Parser::second_pass_memonic(string &line, string &memonic) {
	make_instruction(line, memonic);
	lc += INSTRUCTION_SIZE;
}

void Instruction_Parser::second_pass(string &line) {
	vector<string> words;
	Format::get_words(line, words);

	for (unsigned int i = 0; i < words.size(); i++) {
		if (Parser::is_label(words[i])) {
			second_pass_label(words[i]);
		} else if (Parser::is_section(words[i])) {
			if (i == 0)
				second_pass_section(words[i]);
		} else if (Parser::is_directive(words[i])) {
			second_pass_directive(line, words[i]);
		} else if (Parser::is_memonic(words[i])) {
			second_pass_memonic(line, words[i]);
		}
	}
}

Instruction* Instruction_Parser::make_instruction(string &s, string memonic) {
	Instruction* inst;
	try {
		bool read = true;
		string name = Parser::get_memonic_from_instruction(memonic);
		string cond = Parser::get_condition(memonic);
		bool psw_change = Parser::have_condition(memonic); // TODO correct this method!
		Elf32_Word op_code = Parser::parse_memonic(memonic);

		int instuction_elf = Parser::get_elf_memonic(name);

		switch (instuction_elf) {
		case ELF_INT:
			inst = new INT_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_ADD:
			inst = new ADD_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_SUB:
			inst = new SUB_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_MUL:
			inst = new MUL_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_DIV:
			inst = new DIV_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_CMP:
			inst = new CMP_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_AND:
			inst = new AND_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_OR:
			inst = new OR_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_NOT:
			inst = new NOT_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_TEST:
			inst = new TEST_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_LDR: //case ELF_STR:
			if (name == "ldr")
				inst = new LDR_instruction(s, name, cond, psw_change, op_code);
			else if (name == "str")
				inst = new STR_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_CALL:
			inst = new CALL_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_IN: //case ELF_OUT:
			if (name == "in")
				inst = new IN_instruction(s, name, cond, psw_change, op_code);
			else if (name == "out")
				inst = new OUT_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_MOV: //  case ELF_SHR: case ELF_SHL:
			if (name == "mov")
				inst = new MOV_instruction(s, name, cond, psw_change, op_code);
			else if (name == "shl")
				inst = new SHL_instruction(s, name, cond, psw_change, op_code);
			else if (name == "shr")
				inst = new SHR_instruction(s, name, cond, psw_change, op_code);
			break;
		case ELF_LDCH: // case ELF_LDCL:
			if (name == "ldch" || name == "ldcl")
				inst = new LDChl_instruction(s, name, cond, psw_change,
						op_code);
			else if (name == "ldc") {
				unsigned int temp_op_code = op_code;
				inst = new LDChl_instruction(s, "ldch", cond, psw_change,
						op_code,0,0,
						true,true);
				op_code = inst->read_instruction();
				op_code = change_to_lil_endianness(op_code, LILENDIAN_3_4);
				insert_binary(op_code, 4);
					if (op_code == 0)
						throw READ_INST_ERROR;


				lc += INSTRUCTION_SIZE;
				inst = new LDChl_instruction(s, "ldcl", cond, psw_change,
						temp_op_code,0,0,
						false,true);
				op_code = inst->read_instruction();

				read = false;
			}

			break;
		default:
			throw INSTRUCTION_NOT_FOUND;
			break;
		}
		if (read)
			op_code = inst->read_instruction();

		op_code = change_to_lil_endianness(op_code, LILENDIAN_3_4);
		insert_binary(op_code, 4);
		if (op_code == 0)
			throw READ_INST_ERROR;

	} catch (int id) {
		cout << "Instruction::read instruction exception" << exception_msgs[id]
				<< endl;
	} catch (...) {
		cout << "Instruction ivnalid" << endl;
	}
	return inst;

}

void Instruction_Parser::print() {
	st->print_symbol_table();

	for (map<string, string>::iterator it =
			Instruction_Parser::binary_map.begin();
			it != Instruction_Parser::binary_map.end(); it++) {
		if (Parser::get_section(it->first) != BSS) {
			cout << left << it->first << endl << left
					<< "╔════════════════════════════════════════════════════════════╗"
					<< endl << left << VERTICAL << it->second << endl << left
					<< "╚════════════════════════════════════════════════════════════╝"
					<< endl << endl;
		}
	}

	for (map<string, Relocation_Table*>::iterator it = rel_map.begin();
			it != rel_map.end(); it++)
		it->second->print_relocation_table();

}

void Instruction_Parser::write_byte_codes(ostream &os) {

	for (map<string, string>::iterator it =
			Instruction_Parser::binary_map.begin();
			it != Instruction_Parser::binary_map.end(); it++) {
		if (Parser::get_section(it->first) != BSS) {
			os << left << it->first << " [Hex]" << endl << left
					<< "╔════════════════════════════════════════════════════════════╗"
					<< endl << VERTICAL << it->second << endl
					<< "╚════════════════════════════════════════════════════════════╝"
					<< endl << endl;
		}
	}

}
void Instruction_Parser::write_rel(ostream &os) {
	for (map<string, Relocation_Table*>::iterator it =
			Instruction_Parser::rel_map.begin();
			it != Instruction_Parser::rel_map.end(); it++)
		if (Parser::get_section(it->first) != BSS)
			it->second->write_file(os);
}

void Instruction_Parser::write_file(ostream &os) {
	os << "╔════════════════════════════════════════════════════════╗" << endl
			<< VERTICAL << "Lazar Vasic 2013/298" << right << setw(39)
			<< setfill(SEPARATOR) << VERTICAL << endl << VERTICAL
			<< "Sistemski softver: \"Konstrukcija dvoprolaznog asemblera\""
			<< VERTICAL << endl
			<< "╚════════════════════════════════════════════════════════╝"
			<< endl;
	Instruction_Parser::st->write_file(os);
	Instruction_Parser::write_rel(os);
	Instruction_Parser::write_byte_codes(os);
}
