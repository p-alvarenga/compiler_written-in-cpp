#ifndef PARSER__H__
#define PARSER__H__

#include <memory>
#include <stdexcept>

#include "token.h"
#include "ast-nodes.h"

class Parser 
{
	private: 
		int m_it;
		std::vector<Token> m_tokens; 

	public: 
		explicit Parser(std::vector<Token>& tkns): m_it(0), m_tokens(tkns) {;} 
	
		inline Token peek();  
		inline Token advance(); 
		
		inline Token consume(TokenType type, const std::string& msg); 
		inline Token consumeRange(TokenType find, TokenType min, TokenType max, const std::string& msg);

		inline bool match(TokenType type); 

		std::unique_ptr<Declaration> parseDeclaration();
		std::unique_ptr<Assignment>  parseAssignment(); 
		// print statement

		std::unique_ptr<Expr>   parseExpr();
		std::unique_ptr<Term>   parseTerm(); 
		std::unique_ptr<Expo>   parseExpo();
		std::unique_ptr<Factor> parseFactor(); 
};

Token Parser::peek() { return m_tokens[m_it]; }
Token Parser::advance()
{
	if (++m_it >= m_tokens.size())
	{
		Token t(0, 0); 
		t.type = TokenType::END_OF_FILE; 
		return t; 
	}

	return m_tokens[m_it];
}

bool Parser::match(TokenType type)
{
	if (m_tokens[m_it].type == type)
	{
		advance();
		return true; 
	}

	return false;
}

Token Parser::consume(TokenType type, const std::string& msg)
{
	if (type == peek().type) return advance(); 
	
	throw std::runtime_error(msg);
}

Token Parser::consumeRange(TokenType find, TokenType min, TokenType max, const std::string& msg)
{
	for (int i = (int)min; i <= (int)max; i++) 
	{
		if (find == (TokenType)i)
		{
			return advance();  
		}
	}
	throw std::runtime_error(msg);
}

#endif
