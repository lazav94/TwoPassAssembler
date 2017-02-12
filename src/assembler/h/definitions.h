/* 
 * File:   definitions.h
 * Author: laza
 *
 * Created on June 8, 2016, 8:13 PM
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


typedef unsigned int       Elf32_Word;


#define COMMENTAR       	     "@"
#define IMMED_SIGN               '#'
#define REGISTER_SIGN            'r'
#define INCREMENT                "++"
#define DECREMENT                "--"
#define COMMA                    ','
#define MINUS                    "-"
#define PLUS                     "+"

#define NAMEWIDTH                10
#define NUMWIDTH                  8
#define SEPARATOR                ' '
#define VERTICAL                 "║"
#define HORIZONTAL               "═"
#define THREESPACES              "   "

#define UNKNOWN_EXCEPTION     	   0
#define INSTRUCTION_NOT_FOUND 	   1
#define MULTIPLE_SECTION      	   2
#define NOT_REG               	   3
#define NOT_ALLOWED_REG       	   4
#define PSW_NOT_ALLOWED      	   5
#define PC_NOT_ALLOWED       	   6
#define LR_NOT_ALOWED        	   7
#define SP_NOT_ALLOWED      	   8
#define NOT_IMMED             	   9
#define OUT_RANGE_IMMED      	  10
#define SHIFT_NOT_FOUND      	  11
#define DIRECTIVE_NOT_FOUND  	  12
#define SYMBOL_NOT_DECLARED  	  13
#define SYMBOL_WAS_DECLARED   	  14
#define SECOND_PASS_SECTION   	  15
#define NOT_SAME_SECTION     	  16
#define ARGUMENT_NOT_FOUND        17
#define OUT_OF_BOUNDS             18
#define EXCESS_ARGUMENTS          19
#define ARGUMENT_INVALID          20
#define READ_INST_ERROR           21

#define MSG_UNKNOWN_EXCEPTION     "Exception unknown!"
#define MSG_INSTRUCTION_NOT_FOUND "Instruction not found!"
#define MSG_MULTIPLE_SECTION      "Multiple section definition, you have 2 or more section with same name!"
#define MSG_NOT_REG               "Register required!"
#define MSG_NOT_ALLOWED_REG       "Some register are not allowed in these instruction!"
#define MSG_PSW_NOT_ALLOWED       "PSW register is not allowed in these instruction!"
#define MSG_PC_NOT_ALLOWED        "PC register is not allowed in these instruction!"
#define MSG_LR_NOT_ALLOWED        "LR register is not allowed in these instruction!"
#define MSG_SP_NOT_ALLOWED        "SP register is not allowed in these instruction!"
#define MSG_NOT_IMMED             "Immed/Label required!"
#define MSG_OUT_OF_RANGE_IMMED    "Immed value is out of range for these instruction"
#define MSG_SHIFT_NOT_FOUND       "Shift sign required!"
#define MSG_DIRECTIVE_NOT_FOUND   "Directive not found!"
#define MSG_SYMBOL_NOT_DECLARED   "Symbol has not been declared! (global public)!"
#define MSG_SYMBOL_WAS_DECLARED   "Symbol has been declared (global extern)"
#define MSG_SECOND_PASS_SECTION	  "Section doesn't found in second pass!"
#define MSG_NOT_SAME_SECTION      "Can't be used label from other section!"
#define MSG_ARGUMENT_NOT_FOUND    "Agrument not fount!"
#define MSG_OUT_OF_BOUNDS         "Out of bounds!"
#define MSG_EXCESS_ARGUMENTS      "Excess arguments in these intruction!"
#define MSG_ARGUMENT_INVALID      "Agrument is invalid!"
#define MSG_READ_INST_ERROR       "Error , cannot read instruction!"

static const vector<string> exception_msgs( {
								  MSG_UNKNOWN_EXCEPTION,
								  MSG_INSTRUCTION_NOT_FOUND,
								  MSG_MULTIPLE_SECTION,
								  MSG_NOT_REG,
								  MSG_NOT_ALLOWED_REG,
								  MSG_PSW_NOT_ALLOWED,
								  MSG_PC_NOT_ALLOWED,
								  MSG_LR_NOT_ALLOWED,
								  MSG_SP_NOT_ALLOWED,
								  MSG_NOT_IMMED,
								  MSG_OUT_OF_RANGE_IMMED,
								  MSG_SHIFT_NOT_FOUND,
								  MSG_DIRECTIVE_NOT_FOUND,
								  MSG_SYMBOL_NOT_DECLARED,
								  MSG_SYMBOL_WAS_DECLARED,
								  MSG_SECOND_PASS_SECTION,
								  MSG_NOT_SAME_SECTION,
								  MSG_ARGUMENT_NOT_FOUND,
								  MSG_OUT_OF_BOUNDS,
								  MSG_EXCESS_ARGUMENTS,
								  MSG_ARGUMENT_INVALID ,
								  MSG_READ_INST_ERROR});

#define LILENDIAN_1_1    0x1
#define LILENDIAN_2_2    0x2
#define LILENDIAN_3_4    0x3
#define LILENDIAN_4_4    0x4


//condition strings
#define EQ               "eq" // ==
#define NE               "ne" // !=
#define GT               "gt" // >  (signed)
#define GE               "ge" // <  (signed)
#define LT               "lt"	// >= (signed)
#define LE               "le" // <= (signed)
#define AL               "al" // no condition

//condition elf codes
#define ELF_EQ           0x0
#define ELF_NE           0x1
#define ELF_GT           0x2
#define ELF_GE           0x3
#define ELF_LT           0x4
#define ELF_LE           0x5
#define ELF_AL           0x7

//memonic strings
#define INT              "int"
#define ADD              "add"
#define SUB              "sub"
#define MUL              "mul"
#define DIV              "div"
#define CMP              "cmp"
#define AND              "and"
#define OR               "or"
#define NOT              "not"
#define TEST             "test"
#define LDR              "ldr"
#define STR              "str"
#define CALL             "call"
#define IN               "in"
#define OUT              "out"
#define MOV              "mov"
#define SHR              "shr"
#define SHL              "shl"
#define LDCH             "ldch"
#define LDCL             "ldcl"
#define LDC              "ldc"

//memonic elf codes
#define ELF_INT           0x0
#define ELF_ADD           0x1
#define ELF_SUB           0x2
#define ELF_MUL           0x3
#define ELF_DIV           0x4
#define ELF_CMP           0x5
#define ELF_AND           0x6
#define ELF_OR            0x7
#define ELF_NOT           0x8
#define ELF_TEST          0x9
#define ELF_LDR           0xA
#define ELF_STR           0xA
//B does't exist
#define ELF_CALL          0xC
#define ELF_IN            0xD
#define ELF_OUT           0xD
#define ELF_MOV           0xE
#define ELF_SHR           0xE
#define ELF_SHL           0xE
#define ELF_LDCH          0xF
#define ELF_LDCL          0xF
#define ELF_LDC           0xF


#define INSTRUCTION_SIZE  0x4
#define BYTE_SIZE         0x1
#define CHAR_SIZE         0x1
#define WORD_SIZE         0x2
#define LONG_SIZE         0x4

#define LDC_TRUE true

#define START_INSTRUCTION 0x00000000
#define UNDEF_INSTRUCTION 0xB6000000

#define MASK_05B          0x0000001F
#define MASK_07B          0x0000007F
#define MASK_08B          0x000000FF
#define MASK_10B          0x000003FF
#define MASK_16B          0x0000FFFF
#define MASK_18B          0x0003FFFF
#define MASK_19B          0x0007FFFF
#define MASK_20B          0x000FFFFF
#define MASK_24B          0x00FFFFFF
#define MASK_32B          0xFFFFFFFF

#define R0                 0
#define R1                 1
#define R2                 2
#define R3                 3
#define R4                 4
#define R5                 5
#define R6                 6
#define R7                 7
#define R8                 8
#define R9                 9
#define R10               10
#define R11               11
#define R12               12
#define R13               13
#define R14               14
#define R15               15
#define PC                16
#define SP                17
#define LR                18
#define PSW               19

#define ADDRESS_PC        0x0
#define NO_INC_DEC        0x1
#define INCREMENT_BEFORE  0x2
#define DECREMENT_BEFORE  0x3
#define INCREMENT_AFTER   0x4
#define DECREMENT_AFTER   0x5

#define OP_MASK           0xF0000000  //Operation code mask: 32 31 30 29 bit
#define COND_MASK         0x0E000000  //Condition mask:      28 27 26    bit
#define PSW_MASK          0x01000000  //PSW change flag:     25          bit


//visibility
#define LOCAL  false
#define GLOBAL true

//section
#define UND  "UND"
#define TEXT ".text" // sekcije koje sadrže mašinski kod,
#define DATA ".data" // sekcije koje sadrže inicijalizovane podatke
#define BSS ".bss"   // sekcije koje sadrže neinicijalizovane podatke
#define END ".end"   // fajl sa izvornim kodom se završava direktivom .end. Ostatak fajla se odbacuje (ne prevodi se)

//directive
#define PUBLIC ".public"
#define EXTERN ".extern"

#define CHAR  ".char"
#define BYTE  ".byte"
#define WORD  ".word"
#define LONG  ".long"
#define SKIP  ".skip"
#define ALIGN ".align"

struct Elf_Symbol {
	string       name;        // String
	int          value;       // Section ofset, or VM address
	int          size;        // Object size in bytes
	bool         is_global;   // Local or global (4 bits)
	string       section;     // Section header index, ABS, UNDEF of COMMON
	string       sec_name;
	unsigned int id;
	Elf_Symbol(string name = UND, int value = 0, int size = 0, bool is_global = LOCAL,
			std::string section = UND, unsigned int id = 0, string sec_name = "") {
		this->name      = name;
		this->value     = value;
		this->size      = size;
		this->is_global = is_global;
		this->sec_name  = sec_name;
		this->section   = section;
		this->id        = id;
	}
	void print_elfsymbol() {

		string gl = is_global ? "global" : "local";
		cout << left  << VERTICAL << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->name << VERTICAL
				   << left << setw(NUMWIDTH) << setfill(SEPARATOR) << this->value << VERTICAL
				   << left << setw(NUMWIDTH) << setfill(SEPARATOR) << this->size << VERTICAL
				   << left << setw(14) << setfill(SEPARATOR) << gl << VERTICAL
				   << left << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->section << VERTICAL
				   << left << setw(NUMWIDTH) << setfill(SEPARATOR) << this->id << VERTICAL
				   << endl;

	}
	void write_elfsymbol(ostream &os) {
		string gl = is_global ? "global" : "local";


		os << left  << VERTICAL << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->name << VERTICAL
		   << left << setw(NUMWIDTH) << setfill(SEPARATOR) << this->value << VERTICAL
		   << left << setw(NUMWIDTH) << setfill(SEPARATOR) << this->size << VERTICAL
		   << left << setw(14) << setfill(SEPARATOR) << gl << VERTICAL
		   << left << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->section << VERTICAL
		   << left << setw(NUMWIDTH) << setfill(SEPARATOR) << this->id << VERTICAL
		   << endl;


	}
};

#define TYPE_R_386_32      "R_386_32"
#define TYPE_R_386_PC32    "R_386_PC32"
#define TYPE_R_386_LONG32  "R_386_LONG32" // upisi zbir ali zapamti da moras da saberes sa PC
#define TYPE_R_386_H16	   "R_386_H16"
#define TYPE_R_386_L16	   "R_386_L16"

#define R_386_32           0
#define R_386_PC32         1
#define R_386_LONG32       2
#define R_386_H16		   3
#define R_386_L16		   4

struct Relocation_Entry {
	unsigned int   offset;
	unsigned int   bit_offset;
	unsigned short type;
	unsigned int   id_symbol;

	Relocation_Entry(unsigned int offset, unsigned short type, unsigned int id_symbol,unsigned int bit_offset = 0) {
		this->offset    = offset;
		this->bit_offset= bit_offset;
		this->type      = type;
		this->id_symbol = id_symbol;
	}
	void print_relocation_entry() {

		string type_str = "";
		switch (this->type) {
			case R_386_32:      type_str = TYPE_R_386_32;     break;
			case R_386_PC32:    type_str = TYPE_R_386_PC32;   break;
			case R_386_LONG32:  type_str = TYPE_R_386_LONG32; break;
			case R_386_H16:     type_str = TYPE_R_386_H16;    break;
			case R_386_L16:     type_str = TYPE_R_386_L16;    break;
			default:break;
		}
		cout  << left << VERTICAL << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->offset << VERTICAL
			  << left << VERTICAL << setw(NUMWIDTH) << setfill(SEPARATOR) << this->bit_offset << VERTICAL
			  << left << setw(14) << setfill(SEPARATOR) << type_str << VERTICAL
		      << left << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->id_symbol << VERTICAL << endl;
	}
	void write_relocation(ostream &os){
		string type_str = "";
			switch (this->type) {
			case R_386_32:      type_str = TYPE_R_386_32;     break;
			case R_386_PC32:    type_str = TYPE_R_386_PC32;   break;
			case R_386_LONG32:  type_str = TYPE_R_386_LONG32; break;
			case R_386_H16:     type_str = TYPE_R_386_H16;    break;
			case R_386_L16:     type_str = TYPE_R_386_L16;    break;
			default:break;
			}
			os << left << VERTICAL << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->offset << VERTICAL
		   << left  <<" +"<<this->bit_offset << setw(NUMWIDTH-3) << setfill(SEPARATOR) << "b" << VERTICAL
		   << left << setw(NAMEWIDTH + 3) << setfill(SEPARATOR) << type_str << VERTICAL
		   << left << setw(NAMEWIDTH) << setfill(SEPARATOR) << this->id_symbol << VERTICAL
		   << endl;
	}
};
// not used #defines
/*
//type
#define NOTYPE    0x0
#define SECTION   0x1
#define OBJECT    0x2
#define FUNCTION  0x3

//section
#define INDEX  'i'
#define DATAS  'd'
#define ABS    'a'  // za apsolutne vrednosti kojima ne treba relokacija
#define UNDEF  'u'  // za nedefinisane (korisceni u ovom modulu, definsani u nekom drugom)
#define COMMON 'c'  // za neincijlizovane podatke koj jos nisu alocirani

//masks
#define IMM_MASK          0x0000001F //the lowest 5 bits

#define PSWI_MASK         0x80000000 //I - Interrupt
#define PSWZ_MASK         0x00000001 //Z - Zero
#define PSWO_MASK         0x00000002 //O - Overflow
#define PSWC_MASK         0x00000004 //C - Carry
#define PSWN_MASK         0x00000008 //N - Negative

//interrupt
#define NUMBER_OF_IVT_ENTRYS 16
#define ONE_MINUTE 60000;

//IVT - interrupt vector table
#define IVT_ENTRY0  0x0  // interrupt on start/reset CPU
#define IVT_ENTRY1  0x1  // periodic timer (T = 1s) (only if PSWI == 1 else does't work)
#define TIMER_ENTRY 0x1
#define IVT_ENTRY2  0x2  // invalid instruction interrupt
#define IVT_ENTRY3  0x3  // key press interrupt
#define IVT_ENTRY4  0x4  // free entry
#define IVT_ENTRY5  0x5  // free entry
#define IVT_ENTRY6  0x6  // free entry
#define IVT_ENTRY7  0x7  // free entry
#define IVT_ENTRY8  0x8  // free entry
#define IVT_ENTRY9  0x9  // free entry
#define IVT_ENTRY10 0xA  // free entry
#define IVT_ENTRY11 0xB  // free entry
#define IVT_ENTRY12 0xC  // free entry
#define IVT_ENTRY13 0xD  // free entry
#define IVT_ENTRY14 0xE  // free entry
#define IVT_ENTRY15 0xF  // free entry

// key press event
#define PRESSED_KEY         0x1000
#define STATUS_REGISTER     0x1010
#define CHARACTER_ON_SCREEN 0x2000
*/


#endif /* DEFINITIONS_H */

