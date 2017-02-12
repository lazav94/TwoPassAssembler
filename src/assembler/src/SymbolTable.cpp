/*
 * SymbolTable.cpp
 *
 *  Created on: Aug 15, 2016
 *      Author: laza
 */

#include "SymbolTable.h"

SymbolTable::SymbolTable() {

}

SymbolTable::~SymbolTable() {

}

bool SymbolTable::search_table(string &name) {

	map<string, Elf_Symbol*>::iterator i = SymbolTable::simbol_table.find(name);
	if (i == SymbolTable::simbol_table.end())
		return false;
	return true;

}

Elf_Symbol* SymbolTable::get_symbol(string &name) {

	map<string, Elf_Symbol*>::iterator i = SymbolTable::simbol_table.find(name);
	if (i == SymbolTable::simbol_table.end()) {
		Elf_Symbol* pe = new Elf_Symbol();
		return pe;
	}
	return i->second;
}

bool SymbolTable::insert_symbol(Elf_Symbol *symbol) {
	if (SymbolTable::search_table(symbol->name) == false) {
		SymbolTable::simbol_table[symbol->name] = symbol;
		return true;
	}
	return false;
}

bool SymbolTable::chagne_size(string &name, unsigned int size) {
	if (SymbolTable::search_table(name)) {
		Elf_Symbol *e = get_symbol(name);
		e->size = size;
		return true;
	}
	return false;
}

bool SymbolTable::change_value(string &name, int value) {
	if (SymbolTable::search_table(name)) {
		Elf_Symbol *e = get_symbol(name);
		e->value = value;
		return true;
	}
	return false;
}
bool SymbolTable::change_section(string &name, string section, string sec_name) {
	if (SymbolTable::search_table(name)) {
		Elf_Symbol *e = get_symbol(name);
		e->section = section;
		e->sec_name = sec_name;
		return true;
	}
	return false;
}

void SymbolTable::print_symbol_table() {

	cout  <<  endl << left << "Symbol table" << endl
			   << left <<"╔══════════╦════════╦════════╦══════════════╦══════════╦════════╗" << endl
			   << left <<  VERTICAL << setw(NAMEWIDTH) << setfill(SEPARATOR)  <<"Name"       << VERTICAL
			   << left  << setw(NUMWIDTH) << setfill(SEPARATOR) << "Value"       << VERTICAL
			   << left  << setw(NUMWIDTH) << setfill(SEPARATOR)  << "Size"        << VERTICAL
			   << left  << setw(14) << setfill(SEPARATOR)  << "Visability" << VERTICAL
			   << left  << setw(NAMEWIDTH) << setfill(SEPARATOR)  << "Section"    << VERTICAL
			   << left  << setw(NUMWIDTH) << setfill(SEPARATOR)  <<"ID"          << VERTICAL << endl
			   << left << "╠══════════╬════════╬════════╬══════════════╬══════════╬════════╣" << endl;
	//for (unsigned int i = 0; i < this->simbol_table.size(); i++)
	for (map<string, Elf_Symbol*>::iterator it = simbol_table.begin();
			it != simbol_table.end(); it++)
		it->second->print_elfsymbol();
	cout  << left << "╚══════════╩════════╩════════╩══════════════╩══════════╩════════╝" << endl << endl;

}

void SymbolTable::write_file(ostream &os) {
	os  <<  endl << left << "Symbol table" << " [Dec]" << endl
			   << left <<"╔══════════╦════════╦════════╦══════════════╦══════════╦════════╗" << endl
			   << left <<  VERTICAL << setw(NAMEWIDTH) << setfill(SEPARATOR)  <<"Name"       << VERTICAL
			   << left  << setw(NUMWIDTH) << setfill(SEPARATOR) << "Value"       << VERTICAL
			   << left  << setw(NUMWIDTH) << setfill(SEPARATOR)  << "Size"        << VERTICAL
			   << left  << setw(14) << setfill(SEPARATOR)  << "Visability" << VERTICAL
			   << left  << setw(NAMEWIDTH) << setfill(SEPARATOR)  << "Section"    << VERTICAL
			   << left  << setw(NUMWIDTH) << setfill(SEPARATOR)  <<"ID"          << VERTICAL << endl
			   << left << "╠══════════╬════════╬════════╬══════════════╬══════════╬════════╣" << endl;
	for(unsigned int i = 0; i < SymbolTable::simbol_table.size()+2; i++){
		for (map<string, Elf_Symbol*>::iterator it = simbol_table.begin();it != simbol_table.end(); it++) {
			if(i == it->second->id)
				it->second->write_elfsymbol(os);
		}
	}
	os  << left << "╚══════════╩════════╩════════╩══════════════╩══════════╩════════╝" << endl << endl;

}

