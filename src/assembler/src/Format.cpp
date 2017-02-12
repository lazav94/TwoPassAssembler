/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Format.cpp
 * Author: laza
 * 
 * Created on June 8, 2016, 8:13 PM
 */

#include "Format.h"

string Format::delete_comentar_from_line(string &s) {
	size_t pos = s.find(COMMENTAR);
	if (pos != string::npos) {
		s.erase(pos);
		return s;
	}
	return "";
}

bool Format::is_end(string &s) {

	if (s == END)
		return true;
	return false;
}

//TO DO check this method
/*string Format::delete_spaces(string &s) {
 int size = s.length();
 for (int j = 0; j <= size; j++) {
 for (int i = 0; i <= j; i++) {
 if (s[i] == ' ' && s[i + 1] == ' ') {
 s.erase(s.begin() + i);
 } else if (s[0] == ' ') {
 s.erase(s.begin());
 } else if (s[i] == '\0' && s[i - 1] == ' ') {
 s.erase(s.end() - 1);
 }
 }
 }
 return s;
 }*/
string Format::delete_spaces(string &s) {
	int size = s.length();
	string new_string;
	bool blank = false, start = false;
	for (int i = 0, j = 0; i <= size; i++) {
		if (!isblank(s[i]))
			start = true;
		if (start == true) {
			if (isblank(s[i]) && blank == false) {
				blank = true;
				new_string[j++] = ' ';
			} else if (!isblank(s[i])) {
				new_string[j++] = s[i];
				blank = false;      //sledeci
			}

		}
	}

	return new_string;
}

string Format::string_tolower(string &s) {
	for (unsigned int i = 0; i < s.size(); i++) {
		if (isalnum(s[i]))
			s[i] = tolower(s[i]);
	}
	return s;
}

string Format::init_format(string &s) {
	//string_tolower(s);
	delete_comentar_from_line(s);
	delete_spaces(s);

	return s;
}

void Format::get_words(string &s, vector<string>& words) {

	stringstream ss(s);
	string temp;

	while (ss >> temp)
		words.push_back(temp);

}

void Format::get_words_delimiter(string &s, vector<string>& words,
		char delimiter) {

	stringstream ss(s);
	string temp;

	while (getline(ss, temp, delimiter))
		words.push_back(temp);

}

