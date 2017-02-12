/*
 * SymbolTable.h
 *
 *  Created on: Aug 15, 2016
 *      Author: laza
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <map>
#include <string>
#include <iostream>
#include <ostream>
#include "definitions.h"


using namespace std;

class SymbolTable {
private:

	map<string, Elf_Symbol*> simbol_table;

public:
	SymbolTable();
	~SymbolTable();

	bool search_table(string &name);
	Elf_Symbol* get_symbol(string &name);
	bool insert_symbol(Elf_Symbol *symbol);
	bool chagne_size(string &name,  unsigned int size);
	bool change_value(string &name, int value);
	bool change_section(string &name, string section, string sec_name="");

	void print_symbol_table();
	void write_file(ostream& os);

};



#endif /* SYMBOLTABLE_H_ */
