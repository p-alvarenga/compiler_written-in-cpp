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

class Lexer {
	private: 	
		const std::unordered_map<std::string_view, TokenType> keywords {
			{ "def",  TokenType::KW_DEF     }, 
			{ "type", TokenType::KW_TYPE    },
			{ "bit" , TokenType::TYPE_BIT   },
			{ "byte", TokenType::TYPE_BYTE  },
			{ "int16", TokenType::TYPE_INT16 } 
		};

		std::string src;
		
		const char* cur; 
		const char* eof; 
		const char* begin; 

		unsigned int line = 1;
		unsigned int col = 1;		

		char peek(size_t offset) const; // check next byte on buffer  
		char advance(size_t step = 1); 
		//char skipWhiteSpace(); 
		
		TokenType identifyToken(const std::string_view& text, TokenHint hint);
		
		inline bool isIdentifierChar(unsigned char c) const; // set private
		inline bool isDigit(unsigned char c) const;  // set private	
		inline bool isIdentifierStart(unsigned char c) const;  // set private
		inline bool isOperatorChar(unsigned char c) const; 

	public: 

		explicit Lexer(const std::string& src):
			src(src),  
			begin(src.data()),
			cur(src.data()),
			eof(src.data() + src.size())
		{;}
		~Lexer() = default; // manage free memory here // 

		std::vector<Token> tokenize();
}; 

inline bool Lexer::isIdentifierStart(unsigned char c) const
{
	return c == '_' || (((unsigned int)(c | 0x20) - 'a') <= 25);
}	

inline bool Lexer::isIdentifierChar(unsigned char c) const
{
	if (c == '_') [[ unlikely ]] return true;  
	return ((unsigned int)(c | 0x20) - 'a') <= 25 || ((unsigned int)(c - '0') <= 9); 
}

inline bool Lexer::isDigit(unsigned char c) const 
{
	return (unsigned int)(c - '0') <= 9;
}

inline bool Lexer::isOperatorChar(unsigned char c) const 
{
	switch (c) 
	{
		case '=': case '+': case '-':
		case '*': case '/': case '^':
		case '!': case '>': case '<':
		case ':': case ';': return true;
	}

	return false; 
}

#endif
