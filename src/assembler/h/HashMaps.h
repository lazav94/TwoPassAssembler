/*
 * HahsMap.h
 *
 *  Created on: Jun 9, 2016
 *      Author: laza
 */

#ifndef HASHMAPS_H_
#define HASHMAPS_H_

#include <string>
#include <map>
#include "definitions.h"

#define MEMONIC_MAP       1
#define CONDITION_MAP     2
#define INSTRUCTION_MAP   3
#define MEMONIC_ELF_MAP   4
#define CONDITION_ELF_MAP 5

using namespace std;

class HashMaps {
	HashMaps();
	~HashMaps();
public:

	static map<string, string> memonic_map;

	static map<string, string> condition_map;

	static map<string, int> memonic_elf_map;

	static map<string, int> condition_elf_map;


	static map<string, string> create__map_string(unsigned int MAP_ID);
	static map<string, int> create__map_int(unsigned int MAP_ID);

};

#endif /* HAHSMAP_H_ */
