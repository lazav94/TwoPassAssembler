/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Format.h
 * Author: laza
 *
 * Created on June 8, 2016, 8:13 PM
 */

#ifndef FORMAT_H
#define FORMAT_H

#include <vector>
#include <string>
#include <sstream>
#include <ctype.h>
#include <iostream>

#include <stdio.h>
#include <ostream>
#include "HashMaps.h"
#include "definitions.h"


using namespace std;

class Instruction;

class Format {
private:

	Format();
	Format(const Format&);
	Format& operator=(const Format&);

public:

//static Instruction* make_instruction(string &s);
	static string init_format(string &s);
	static string delete_comentar_from_line(string &s);

	static string delete_spaces(string &s);
	static string string_tolower(string &s);

	static bool is_end(string &s);





	static void get_words(string &s, vector<string>& words);
static void get_words_delimiter(string &s, vector<string>& words, char delimiter);


};

#endif /* FORMAT_H */

