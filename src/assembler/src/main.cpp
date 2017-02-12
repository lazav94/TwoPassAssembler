/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: laza
 *
 * Created on June 8, 2016, 8:11 PM
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <locale>

#include <cctype>
#include "Format.h"
#include "Parser.h"
#include "InstructionParser.h"
#include "definitions.h"

using namespace std;

static ifstream input_stream;
static ofstream output_stream;
static string  INPUT_FILE = "/home/laza/Desktop/ss_project/tests/input4.txt";
static string  OUTPUT_FILE = "/home/laza/Desktop/ss_project/tests/output4.txt";

int main() {

	input_stream.open(INPUT_FILE);
	output_stream.open(OUTPUT_FILE);
	string line;
	vector<string> lines;

	if (input_stream.is_open()) {
		while (!input_stream.eof()) {
			getline(input_stream, line);
			if (Format::is_end(line)){		//.end
				lines.push_back(line);
				break;
			}
			Format::init_format(line);
			if (!line.empty())
				lines.push_back(line);
			vector<string> words;
			Format::get_words(line, words);

			for(unsigned int i = 0 ; i < words.size(); i++)
				if(i == 0 && Parser::is_section(words[i]))
					Instruction_Parser::ID_d++;

		}



		for (unsigned int i = 0; i < lines.size(); i++){
			try{
			Instruction_Parser::first_pass(lines[i]);
			}catch(...){
				cout << "Exception first pass: line: " << i <<endl;
			}
		}


		for (unsigned int i = 0; i < lines.size(); i++){
			try{
				Instruction_Parser::second_pass(lines[i]);
			}catch(...){
				cout << "Exception second pass: line: " << i <<endl;
			}

		}

		//cout << "7. finish first pass" << endl << "8. start write in file: " + OUTPUT_FILE << endl;


		//Instruction_Parser::print(); //<--- print output.txt on console!
		Instruction_Parser::write_file(output_stream);
		//cout << "9. finish  write in output file" << endl;

	} else
		cout << "Input file can't be open" << endl;

	input_stream.close();
	output_stream.close();

	//cout << "10. end" << endl;

	return 0;
}

