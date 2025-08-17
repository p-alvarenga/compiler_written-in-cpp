#ifndef TOKEN__H__
#define TOKEN__H__

#include <vector>
#include <unordered_map>

enum class TokenType {
	ID, NUMERICAL, STRING, BOOL_LITERAL, // Literals & Identifier

	KW_DEF, KW_TYPE, KW, // Keywords

	OP_MINUS, OP_MINUS_EQUAL, OP_PLUS, OP_PLUS_EQUAL, 
	OP_STAR, OP_STAR_EQUAL, OP_SLASH, OP_SLASH_EQUAL, 
	OP_POWER, OP_COLON_EQUAL, OP_SEMICOLON, OP_EQUAL, 
	OP_EQUAL_EQUAL, OP_EXCLAMATION_EQUAL, OP_GREATER_THAN, OP_GREATER_OR_EQUAL,
	OP_LESS_THAN, OP_LESS_OR_EQUAL,

	TYPE_BIT, TYPE_BYTE, TYPE_INT16,

	ERR_UNKNOWN = 9999
};

enum class TokenHint {
	WORD,
	NUMERICAL, 
	OPERATOR,
};

struct Token {
	TokenType type; 
	std::string_view textptr; 
	int line = 1;
	int col  = 1; 
};

#endif
