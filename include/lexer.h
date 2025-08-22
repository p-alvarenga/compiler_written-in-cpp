#ifndef LEXER__H__ 
#define LEXER__H__

#include "token.h"
//#include "compile-error.h"

class Lexer 
{
	private: 
		static const std::unordered_map<std::string_view, TokenType> m_keywords_map;
		static const std::unordered_map<std::string_view, TokenType> m_operators_map;

		
		const char* m_cur;
		const char* m_begin; 
		const char* m_eof;

		int m_line = 1;
		int m_col  = 1; 
	
		TokenType identifyToken(const std::string_view& text, TokenHint hint) const; 

		char advance(size_t step = 1);
		inline char peek(size_t offset) const;
		inline bool isIdentifierStart(unsigned char c) const;
		inline bool isIdentifierChar(unsigned char c) const;
		inline bool isOperatorChar(unsigned char c) const;
		inline bool isNumericalStart(unsigned char c) const;
		inline bool isNumericalChar(unsigned char c) const; 

	public: 
		std::string m_buffer; // PRIVATE!!! PUBLIC FOR TESTS ONLY!
		explicit Lexer(const std::string& src): m_buffer(src)
		{ 
			m_begin = src.data();
			m_cur = m_begin;
			m_eof = m_begin + src.size();
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

inline bool Lexer::isNumericalChar(unsigned char c) const
{
	return c == '.' || (unsigned int)(c - '0') <= 9;
}

inline bool Lexer::isNumericalStart(unsigned char c) const 
{
	return (unsigned int)(c - '0') <= 9; 
}

char Lexer::peek(size_t offset) const 
{
	const char* nptr = m_cur + offset;	
	if (nptr >= m_eof) return '\0'; 
	return *nptr; 
}

#endif 
