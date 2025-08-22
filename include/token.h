#ifndef TOKEN__H__
#define TOKEN__H__

#include <vector>
#include <unordered_map>

enum class TokenType 
{
	ID, NUMERICAL_INT, NUMERICAL_FLOAT, STRING, BOOL_LITERAL, // Literals & Identifier
	LPAREN, RPAREN,

	KW_DEF, KW_TYPE, KW, // Keywords

	OP_MINUS, OP_MINUS_EQUAL, OP_PLUS, OP_PLUS_EQUAL, 
	OP_STAR, OP_STAR_EQUAL, OP_SLASH, OP_SLASH_EQUAL, 
	OP_POWER, OP_COLON_EQUAL, OP_SEMICOLON, OP_EQUAL, 
	OP_EQUAL_EQUAL, OP_EXCLAMATION_EQUAL, OP_GREATER_THAN, OP_GREATER_OR_EQUAL,
	OP_LESS_THAN, OP_LESS_OR_EQUAL, OP_LOGICAL_OR, OP_LOGICAL_AND

	TYPE_BIT, TYPE_BYTE, TYPE_INT16, TYPE_INT32, 
	TYPE_INT64, TYPE_UINT16, TYPE_UINT32, TYPE_UINT64,

	EOF, 

	UNKNOWN = 9999
};

enum class TokenHint { WORD, OPERATOR };

class Token 
{
	public: 
		TokenType type; 
		std::string_view textptr; 
	
		int line = 1;
		int col  = 1; 

		explicit Token(int col, int line): col(col), line(line) {;}
};

#endif
