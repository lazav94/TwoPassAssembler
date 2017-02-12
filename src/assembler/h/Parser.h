/*
 * Parser.h
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <string>
#include <sstream>
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include "HashMaps.h"
#include "definitions.h"
#include "Format.h"


using namespace std;

class Parser {
private:
	Parser();
public:



	~Parser();

	//LABEL
	static bool is_label(string &s);


	//OP_CODE
		//PSW
	static bool have_psw_change(string &s);

		//CONDITION
	static bool have_condition(string &s);
	static string get_condition(string &s);
	static int get_elf_condition(string &s);

		//MEMONIC
	static bool is_memonic(string &s);
	static string get_memonic_from_instruction(string s);
	static int get_elf_memonic(string &s);
	static Elf32_Word parse_memonic(string &s);

	//SECTION
	static bool is_section(string s);
	static string get_section(string s);
	static string get_section_name(string s);

	static bool is_directive(string &s);
	static string get_directive_arguments(string &s);





};



#endif /* PARSER_H_ */
