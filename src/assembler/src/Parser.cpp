/*
 * Parser.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: laza
 */

#include "Parser.h"


Parser::Parser() {

}

Parser::~Parser() {

}

bool Parser::is_label(string &s) {
	if (s[s.size() - 1] == ':')
		return true;
	else
		return false;
}

bool Parser::is_memonic(string &s) {

	string ss = get_memonic_from_instruction(s);

	map<string, string>::iterator i = HashMaps::memonic_map.find(ss);
	if (i == HashMaps::memonic_map.end())
		return false;
	else
		return true; //i->first == s, i->second == HAS[S]

}

bool Parser::have_psw_change(string &s) {
	if (s[s.size() - 1] == 's')
		return true;
	return false;
}

bool Parser::have_condition(string &s) {
	string str;
	if (s.size() > 2) {
		if (have_psw_change(s) == true)
			str = s.substr(s.length() - 3, 2);
		else
			str = s.substr(s.length() - 2, 2);

		map<string, string>::iterator i = HashMaps::condition_map.find(str);
		if (i == HashMaps::condition_map.end()) {
			return false;
		} else {
			return true; //i->first == s, i->second == HAS[S]
		}
	}
	return false;

}


string Parser::get_condition(string &s) {
	string str;

	if (have_psw_change(s) == true)
		str = s.substr(s.length() - 3, 2);
	else
		str = s.substr(s.length() - 2, 2);

	map<string, string>::iterator i = HashMaps::condition_map.find(str);
	if (i == HashMaps::condition_map.end())
		return "";
	else
		return str; //i->first == s, i->second == HAS[S]

}

int Parser::get_elf_condition(string &s) {
	map<string, int>::iterator i = HashMaps::condition_elf_map.find(s);
	if (i != HashMaps::condition_elf_map.end())
		return i->second;
	else
		return 0;
}
string Parser::get_memonic_from_instruction(string s) {

	int s_size = s.length();
	string ss;
	if (have_psw_change(s))
		s_size--;
	if (have_condition(s))
		s_size -= 2;

	ss = s.substr(0, s_size);
	return ss;

}
int Parser::get_elf_memonic(string &s) {
	map<string, int>::iterator i = HashMaps::memonic_elf_map.find(s);
	if (i != HashMaps::memonic_elf_map.end())
		return i->second;
	return 0;
}
Elf32_Word Parser::parse_memonic(string &s) {
	Elf32_Word parsed = 0;
	unsigned int cond = 0;
	string condition = "";

	if (have_psw_change(s))
		parsed |= PSW_MASK;

	condition = get_condition(s);
	if (condition != "") {
		cond = HashMaps::condition_elf_map[condition];
		parsed |= cond << 25; //PROVERI BROJ :D

	} else
		parsed |= ELF_AL << 25;

	s = get_memonic_from_instruction(s);
	map<string, int>::iterator i = HashMaps::memonic_elf_map.find(s);
	if (i != HashMaps::memonic_elf_map.end()) {
		parsed |= i->second << 28;

	}

	return parsed;
}

bool Parser::is_directive(string &s) {
	if (s[0] == '.') {
		if (s == CHAR || s == EXTERN || s == LONG || s == ALIGN || s == SKIP
				|| s == WORD || s == PUBLIC || s == BYTE)
			return true;
	}
	return false;
}
string Parser::get_directive_arguments(string &s) {
	if (is_directive(s)) {
		size_t arg_pos = s.find(" ");
		return s.substr(arg_pos, s.size());
	}
	return "";
}

bool Parser::is_section(string s) {
	if (s[0] == '.') {
		size_t pos_dot = s.find_last_of('.');
		if (pos_dot != 0)
			s = s.substr(0, pos_dot);

		if (s == BSS || s == TEXT || s == DATA || s == END)
			return true;
	}
	return false;
}
string Parser::get_section(string s) {
	if (is_section(s)) {
		size_t pos_dot = s.find_last_of('.');
		if (pos_dot == 0)
					return s;
		return s.substr(0, pos_dot);
	}
	return "";
}
string Parser::get_section_name(string s) {
	if (is_section(s)) {
		size_t pos_dot = s.find_last_of('.');
		if (pos_dot == 0)
			return s;
		return s.substr(pos_dot, s.size());
	}
	return "";
}




