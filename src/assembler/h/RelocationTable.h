/*
 * RelocationTable.h
 *
 *  Created on: Aug 18, 2016
 *      Author: laza
 */

#ifndef RELOCATIONTABLE_H_
#define RELOCATIONTABLE_H_

#include <map>
#include <string>
#include <iostream>
#include "definitions.h"

using namespace std;

class Relocation_Table {
private:
	map<unsigned int, Relocation_Entry*> relocation_table;
	string name;
public:
	Relocation_Table(string &name);
	~Relocation_Table();

	bool search_table(unsigned int &search_offset);
	Relocation_Entry* get_relocation(unsigned int &search_offset);
	bool insert_reloction(Relocation_Entry *relocation);

	void print_relocation_table();
	void write_file(ostream &os);
};


#endif /* RELOCATIONTABLE_H_ */
