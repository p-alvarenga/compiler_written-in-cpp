#ifndef LEXER__H__ 
#define LEXER__H__

#include "token.h"
//#include "compile-error.h"

class Lexer 
{
	private: 
		static const std::unordered_map<std::string_view, TokenType> keywords_map;
		std::string buffer; // <- keep it alive!
		
		const char* cur;
		const char* begin; 
		const char* eof;

		int line = 1;
		int col  = 1; 
	
		char peek(size_t offset) const;
		char advance(size_t step = 1);

		TokenType identifyToken(const std::string_view& text, TokenHint hint) const;
		
		inline bool isIdentifierStart(unsigned char c) const;
		inline bool isIdentifierChar(unsigned char c) const;
		inline bool isOperatorChar(unsigned char c) const;
		inline bool isDigitChar(unsigned char c) const; 

	public: 
		explicit Lexer(const std::string& src): buffer(src)
		{ 
			begin = src.data();
			cur = begin;
			eof = begin + src.size();
		}
		~Lexer() = default; // important: struct Token depends on Lexer::buffer; 

		std::vector<Token> tokenize();
};

inline bool Lexer::isIdentifierStart(unsigned char c) const
{
	return c == '_' || (((unsigned int)(c|0x20) - 'a') <= 25);
}

inline bool Lexer::isIdentifierChar(unsigned char c) const
{
	return c == '_' || (((unsigned int)(c|0x20) - 'a') <= 25 || ((unsigned int)(c - '0') <= 9));
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

inline bool Lexer::isDigitChar(unsigned char c) const
{
	return (unsigned int)(c - '0') <= 9;
}

#endif 
