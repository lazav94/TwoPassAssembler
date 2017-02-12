/*
 * RelocationTable.cpp
 *
 *  Created on: Aug 18, 2016
 *      Author: laza
 */

#include "RelocationTable.h"

Relocation_Table::Relocation_Table(string &name) {
	this->name = name;

}

Relocation_Table::~Relocation_Table() {

}

bool Relocation_Table::search_table(unsigned int &search_offset) {
	map<unsigned int, Relocation_Entry*>::iterator i =
			Relocation_Table::relocation_table.find(search_offset);
	if (i == Relocation_Table::relocation_table.end())
		return false;
	return true;
}

Relocation_Entry* Relocation_Table::get_relocation(
		unsigned int &search_offset) {
	map<unsigned int, Relocation_Entry*>::iterator i =
			Relocation_Table::relocation_table.find(search_offset);
	if (i == Relocation_Table::relocation_table.end())
		return new Relocation_Entry(0, false, 0);
	return i->second;

}

bool Relocation_Table::insert_reloction(Relocation_Entry *relocation) {
	if (Relocation_Table::search_table(relocation->offset) == false) {
		Relocation_Table::relocation_table[relocation->offset] = relocation;
		return true;
	}
	return false;
}

void Relocation_Table::print_relocation_table() {
	cout << left << "Relcoation table: " << this->name << endl << left
			<< "╔══════════╦══════════════╦══════════╗"
			<< endl << left << VERTICAL << setw(NAMEWIDTH) << setfill(SEPARATOR)
			<< "Offset" << VERTICAL << left << setw(14) << setfill(SEPARATOR)
			<< "Type" << VERTICAL << left << setw(NAMEWIDTH) << setfill(SEPARATOR)
			<< "Id" << VERTICAL << endl << left
			<< "╠══════════╬══════════════╬══════════╣"
			<< endl;

	for (map<Elf32_Word, Relocation_Entry*>::iterator it =
			relocation_table.begin(); it != relocation_table.end(); it++)
		it->second->print_relocation_entry();

	cout << "╚══════════╩══════════════╩══════════╝" << endl << endl;

}

void Relocation_Table::write_file(ostream & os) {
	os << left << "Relcoation table: " << this->name << " [Dec]" << endl << left
			<< "╔══════════╦════════╦═════════════╦══════════╗"
			<< endl << left  << VERTICAL<< setw(NAMEWIDTH) << setfill(SEPARATOR)
			<< "Offset"   << VERTICAL << left << setw(NUMWIDTH) << setfill(SEPARATOR)
			<< "   >>" << VERTICAL << left << setw(NAMEWIDTH + 3) << setfill(SEPARATOR)
			<< "Type" << VERTICAL << left << setw(NAMEWIDTH) << setfill(SEPARATOR)
			<< "Id" << VERTICAL << endl << left
			<< "╠══════════╬════════╬═════════════╬══════════╣"
			<< endl;
	for (map<Elf32_Word, Relocation_Entry*>::iterator it = Relocation_Table::relocation_table.begin();
			it != Relocation_Table::relocation_table.end(); it++)
		it->second->write_relocation(os);
	os 	 << "╚══════════╩════════╩═════════════╩══════════╝" << endl << endl;
}
