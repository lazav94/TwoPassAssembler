/*
 * HahsMap.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: laza
 */

#include "HashMaps.h"

map<string, string> HashMaps::memonic_map = create__map_string(MEMONIC_MAP);
map<string, string> HashMaps::condition_map = create__map_string(
CONDITION_MAP);

map<string, int> HashMaps::memonic_elf_map = create__map_int(MEMONIC_ELF_MAP);
map<string, int> HashMaps::condition_elf_map = create__map_int(
		CONDITION_ELF_MAP);

//map<string, Instruction> HashMaps::instuction_map = create__map(INSTRUCTION_MAP);

map<string, int> HashMaps::create__map_int(unsigned int MAP_ID) {
	map<string, int> m;
	if (MAP_ID == MEMONIC_ELF_MAP) {
		m[INT] = ELF_INT;
		m[ADD] = ELF_ADD;
		m[SUB] = ELF_SUB;
		m[MUL] = ELF_MUL;
		m[DIV] = ELF_DIV;
		m[CMP] = ELF_CMP;
		m[AND] = ELF_AND;
		m[OR] = ELF_OR;
		m[NOT] = ELF_NOT;
		m[TEST] = ELF_TEST;
		m[LDR] = ELF_LDR;
		m[STR] = ELF_STR;
		m[CALL] = ELF_CALL;
		m[IN] = ELF_IN;
		m[OUT] = ELF_OUT;
		m[MOV] = ELF_MOV;
		m[SHR] = ELF_SHR;
		m[SHL] = ELF_SHL;
		m[LDCH] = ELF_LDCH;
		m[LDCL] = ELF_LDCL;
		m[LDC] = ELF_LDC;
	} else if (MAP_ID == CONDITION_ELF_MAP) {
		m[EQ] = ELF_EQ;
		m[NE] = ELF_NE;
		m[GT] = ELF_GT;
		m[GE] = ELF_GE;
		m[LT] = ELF_LT;
		m[LE] = ELF_LE;
		m[AL] = ELF_AL;
	}

	return m;
}
map<string, string> HashMaps::create__map_string(unsigned int MAP_ID) {
	map<string, string> m;
	if (MAP_ID == MEMONIC_MAP) {

		m[INT] = INT;
		m[ADD] = ADD;
		m[SUB] = SUB;
		m[MUL] = MUL;
		m[DIV] = DIV;
		m[CMP] = CMP;
		m[AND] = AND;
		m[OR] = OR;
		m[NOT] = NOT;
		m[TEST] = TEST;
		m[LDR] = LDR;
		m[STR] = STR;
		m[CALL] = CALL;
		m[IN] = IN;
		m[OUT] = OUT;
		m[MOV] = MOV;
		m[SHR] = SHR;
		m[SHL] = SHL;
		m[LDCH] = LDCH;
		m[LDCL] = LDCL;
		m[LDC] = LDC;
	} else if (MAP_ID == CONDITION_MAP) {
		m[EQ] = EQ;
		m[NE] = NE;
		m[GT] = GT;
		m[GE] = GE;
		m[LT] = LT;
		m[LE] = LE;
		m[AL] = AL;

	} else if (MAP_ID == INSTRUCTION_MAP) {

		/*	m[INT] = new Instruction(INT, "", 0);
		 m[ADD] = new Instruction(INT, "", 0);
		 m[SUB] = new Instruction(INT, "", 0);
		 m[MUL] = new Instruction(INT, "", 0);
		 m[DIV] = new Instruction(INT, "", 0);
		 m[CMP] = new Instruction(INT, "", 0);
		 m[AND] = new Instruction(INT, "", 0);
		 m[OR] = new Instruction(INT, "", 0);
		 m[NOT] = new Instruction(INT, "", 0);
		 m[TEST] = new Instruction(INT, "", 0);
		 m[LDR] = new Instruction(INT, "", 0);
		 m[STR] = new Instruction(INT, "", 0);
		 m[CALL] = new Instruction(INT, "", 0);
		 m[IN] = new Instruction(INT, "", 0);
		 m[OUT] = new Instruction(INT, "", 0);
		 m[MOV] = new Instruction(INT, "", 0);
		 m[SHR] = new Instruction(INT, "", 0);
		 m[SHL] = new Instruction(INT, "", 0);
		 m[LDCH] = new Instruction(INT, "", 0);
		 m[LDCL] = new Instruction(INT, "", 0);*/
	}

	return m;
}

