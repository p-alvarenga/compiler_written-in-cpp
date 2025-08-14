#ifndef TOKEN__H__
#define TOKEN__H__

#include <vector>
#include <unordered_map>

enum class TokenType {
	ID, NUMERICAL, STRING, BOOL_LITERAL, // Literals & Identifier

	KW_DEF, KW_TYPE, KW, // Keywords

	OP_MINUS, OP_PLUS, OP_STAR, OP_SLASH,
	OP_POWER, OP_INITIALIZER, OP_ENDCMD, OP_EQUAL,
	OP_EQUAL_EQUAL, OP_DIFF_OF, OP_GREATER_THAN,
	OP_LESS_THAN, 

	TYPE_BIT, TYPE_BYTE, TYPE_INT16
};

enum class TokenHint {
	WORD,
	NUMERICAL, 
	OPERATOR
};

struct Token {
	TokenType type; 
	std::string_view textptr; 
	int line = 1;
	int col  = 1; 
};

#endif
